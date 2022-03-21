#pragma once

#ifndef GAL_LANG_FUNCTION_REGISTER_HPP
	#define GAL_LANG_FUNCTION_REGISTER_HPP

	#include <gal/foundation/function_register.hpp>

namespace gal::lang
{
	/**
	 * @brief Creates a new proxy_function object from a free function, member function or data member.
	 *
	 * @param function Function / member to expose.
	 *
	 * @code
	 * fun(&a_free_function)
	 * fun(&a_class::a_member_function)
	 * fun(&a_class::a_member_data)
	 * @endcode
	 */
	template<typename Function>
	[[nodiscard]] foundation::proxy_function fun(Function&& function)
	{
		return foundation::function_register::register_function(std::forward<Function>(function), utils::make_function_signature(function));
	}

	/**
	 * @brief Creates a new proxy_function object from a free function, member function or data member.
	 * @note It is allowed to bind the first n parameters of the function first, if it is not the first n parameters then a lambda should be used.
	 *
	 * @code
	 * a_class a;
	 * fun(&a_class::a_member_function, std::ref(a))
	 * @endcode
	 */
	template<typename Function, typename... PreBindParams>
	[[nodiscard]] foundation::proxy_function fun(Function&& function, PreBindParams... params)
	{
		return fun(std::bind_front(std::forward<Function>(function), std::forward<PreBindParams>(params)...));
	}

	template<typename ConstructorSignature>
	[[nodiscard]] foundation::proxy_function ctor()
	{
		return foundation::function_register::register_constructor<ConstructorSignature>();
	}

	template<typename Class>
	[[nodiscard]] foundation::proxy_function default_ctor()
	{
		return ctor<Class()>();
	}

	template<typename Class>
	[[nodiscard]] foundation::proxy_function copy_ctor()
	{
		return ctor<Class(const Class&)>();
	}

	template<typename Class>
	[[nodiscard]] foundation::proxy_function move_ctor()
	{
		return ctor<Class(Class &&)>();
	}

	/**
	 * @brief Single step command for registering a class.
	 *
	 * @param core Core to add class to.
	 * @param name Name of the class being registered.
	 * @param constructors Constructors to add.
	 * @param functions Methods to add.
	 *
	 * @code
	 *
	 * register_class(
	 *	core,
	 *	"my_class",
	 *	{
	 *		default_ctor<my_class()>(), // default ctor
	 *		copy_ctor<my_class(const my_class&)>() // copy ctor
	 *	},
	 *	{
	 *		{"function1", fun(&my_class::function1)},
	 *		{"function2", fun(&my_class::function2)},
	 *		{"overload_function1", fun(static_cast<std::string(my_class::*)(int)>(&my_class::overload_function1)},
	 *		{"overload_function2", fun(static_cast<std::string(my_class::*)(double)>(&my_class::overload_function2)}
	 *	}
	 * );
	 *
	 * @endcode
	 */
	template<typename T>
	void register_class(
			foundation::engine_core&																 core,
			const foundation::engine_core::name_view_type											 name,
			foundation::proxy_functions_type&&														 constructors,
			// todo: container?
			std::vector<std::pair<foundation::engine_core::name_type, foundation::proxy_function>>&& functions)
	{
		core.add_type_info(name, foundation::make_type_info<T>());

		std::ranges::for_each(
				constructors,
				[&core, name](auto&& ctor)
				{
					core.add_function(name, std::move(ctor));
				});

		std::ranges::for_each(
				functions,
				[&core, name](auto&& pair)
				{
					core.add_function(std::move(pair.first), std::move(pair.second));
				});
	}

//	template<typename Target>
//	requires std::is_arithmetic_v<Target>
//	void register_arithmetic(
//			foundation::engine_core&					  core,
//			const foundation::engine_core::name_view_type name)
//	{
//		core.add_function(name, fun([](const foundation::boxed_number& number)
//									{ return number.template as<Target>(); }));
//	}
}// namespace gal::lang

#endif//GAL_LANG_FUNCTION_REGISTER_HPP
