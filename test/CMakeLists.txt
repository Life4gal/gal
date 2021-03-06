project(
		gal-TEST
		LANGUAGES CXX
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 20)

set(
		${PROJECT_NAME}_SOURCE_UTILS
		
		test_utils/test_point.cpp
		test_utils/test_string_utils.cpp
		test_utils/test_string_pool.cpp
		test_utils/test_template_string.cpp
		test_utils/test_function_signature.cpp
		test_utils/test_proxy.cpp
)

set(
	${PROJECT_NAME}_SOURCE_CORE

	test_gal/test_cast.cpp
)

add_executable(
		${PROJECT_NAME}

		${${PROJECT_NAME}_SOURCE_UTILS}
		${${PROJECT_NAME}_SOURCE_CORE}
)

target_compile_features(
		${PROJECT_NAME}
		PRIVATE

		$<$<CXX_COMPILER_ID:MSVC>:cxx_std_23>
		$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:cxx_std_20>		
)

target_compile_options(
	${PROJECT_NAME}
	PRIVATE

	$<$<CXX_COMPILER_ID:MSVC>:/bigobj>
	$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wa,-mbig-obj>
)

include(${GAL_3RDPARTY_PATH}/google-test.cmake)

target_link_libraries(
		${PROJECT_NAME}
		PRIVATE
		gal::UTILS
		gal::CORE
		gtest_main
)

# for gtest_discover_tests
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

include(${GAL_MODULE_PATH}/config_build_type.cmake)
BuildAsPrivate()
