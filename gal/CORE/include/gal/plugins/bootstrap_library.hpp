#pragma once

#ifndef GAL_LANG_PLUGIN_BOOTSTRAP_LIBRARY_HPP
#define GAL_LANG_PLUGIN_BOOTSTRAP_LIBRARY_HPP

#include <iostream>
#include <utils/type_traits.hpp>
#include <gal/types/view_type.hpp>
#include <gal/types/range_type.hpp>
#include <gal/types/list_type.hpp>
#include <gal/types/dict_type.hpp>
#include <gal/types/string_type.hpp>
#include <gal/types/string_view_type.hpp>
#include <gal/foundation/operator_register.hpp>

namespace gal::lang::plugin
{
	namespace bootstrap_library_detail
	{
		namespace detail
		{
			template<typename ContainerType>
			using detect_view_type = typename ContainerType::view_type;
			template<typename ContainerType>
			using detect_const_view_type = typename ContainerType::const_view_type;
		}

		template<typename ContainerType>
		using container_view_type = utils::detected_t<detail::detect_view_type, ContainerType>;
		template<typename ContainerType>
		using container_const_view_type = utils::detected_t<detail::detect_const_view_type, ContainerType>;
	}

	class bootstrap_library
	{
	private:
		template<typename ContainerType>
		static void register_default_constructible_container(const foundation::string_view_type name, foundation::engine_module& m) { m.add_function(name, default_ctor<ContainerType>()); }

		template<typename ContainerType>
		static void register_assignable_container(const foundation::string_view_type name, foundation::engine_module& m)
		{
			m.add_function(name, copy_ctor<ContainerType>());
			foundation::operator_register::register_assign<ContainerType>(m);
		}

		template<typename ContainerType>
		static void register_movable_container(const foundation::string_view_type name, foundation::engine_module& m)
		{
			m.add_function(name, move_ctor<ContainerType>());
			foundation::operator_register::register_move_assign<ContainerType>(m);
		}

		template<typename ContainerType>
		static void register_view_type(foundation::engine_module& m)
		{
			using container_type = ContainerType;
			using view_type = bootstrap_library_detail::container_view_type<container_type>;
			constexpr bool has_view_type = not std::is_same_v<view_type, utils::detect_nonesuch_t>;
			using const_view_type = bootstrap_library_detail::container_const_view_type<container_type>;
			constexpr bool has_const_view_type = not std::is_same_v<const_view_type, utils::detect_nonesuch_t>;

			if constexpr (has_view_type)
			{
				// container.view()
				m.add_function(
						foundation::container_view_interface_name::value,
						lang::fun(static_cast<view_type (container_type::*)() noexcept>(&container_type::view)));

				// view.empty()
				m.add_function(
						foundation::container_view_empty_interface_name::value,
						lang::fun(&view_type::empty));

				// view.get()
				m.add_function(
						foundation::container_view_star_interface_name::value,
						lang::fun(static_cast<foundation::boxed_value (view_type::*)() noexcept>(&view_type::get)));
				m.add_function(
						foundation::container_view_star_interface_name::value,
						lang::fun(static_cast<foundation::boxed_value (view_type::*)() const noexcept>(&view_type::get)));

				// view.next()
				m.add_function(
						foundation::container_view_advance_interface_name::value,
						lang::fun(&view_type::advance));
			}
			else {}

			if constexpr (has_const_view_type)
			{
				// container.view()
				m.add_function(
						foundation::container_view_interface_name::value,
						lang::fun(static_cast<const_view_type (container_type::*)() const noexcept>(&container_type::view)));

				// view.empty()
				m.add_function(
						foundation::container_view_empty_interface_name::value,
						lang::fun(&const_view_type::empty));

				static_assert(const_view_type::is_const_container);
				// view.get()
				// m.add_function(
				// 		foundation::container_view_star_interface_name::value,
				// 		lang::fun(&const_view_type::get));
				m.add_function(
						foundation::container_view_star_interface_name::value,
						lang::fun(static_cast<foundation::boxed_value (const_view_type::*)() const noexcept>(&const_view_type::get)));

				// view.next()
				m.add_function(
						foundation::container_view_advance_interface_name::value,
						lang::fun(&const_view_type::advance));
			}
			else {}
		}

		static void register_boolean_type(foundation::engine_module& m)
		{
			m.add_type_info(foundation::boolean_type_name::value, foundation::make_type_info<bool>());

			m.add_function(foundation::boolean_type_name::value, default_ctor<bool>());
			m.add_function(foundation::boolean_type_name::value, copy_ctor<bool>());

			foundation::operator_register::register_assign<bool>(m);
			foundation::operator_register::register_equal<bool>(m);
			foundation::operator_register::register_not_equal<bool>(m);
			foundation::operator_register::register_unary_not<bool>(m);
			m.add_function(
					foundation::operator_to_string_name::value,
					fun([](const bool b) -> decltype(auto)
					{
						static types::string_type true_name{foundation::string_view_type{foundation::keyword_true_name::value}};
						static types::string_type false_name{foundation::string_view_type{foundation::keyword_false_name::value}};
						return b ? true_name : false_name;
					}));
		}

		static void register_range_type(foundation::engine_module& m)
		{
			m.add_type_info(foundation::range_type_name::value, types::range_type::class_type());

			// range(begin, end, step)
			m.add_function(
					foundation::range_type_name::value,
					ctor<types::range_type(types::range_type::size_type, types::range_type::size_type, types::range_type::size_type)>());

			// range(0, end, 1)
			m.add_function(
					foundation::range_type_name::value,
					ctor<types::range_type(types::range_type::size_type)>());

			// range(begin, end, 1)
			m.add_function(
					foundation::range_type_name::value,
					ctor<types::range_type(types::range_type::size_type, types::range_type::size_type)>());

			// operator==/operator!=
			foundation::operator_register::register_equal<bool>(m);
			foundation::operator_register::register_not_equal<bool>(m);
		}

		static void register_list_type(foundation::engine_module& m)
		{
			m.add_type_info(foundation::list_type_name::value, types::list_type::class_type());

			register_default_constructible_container<types::list_type>(foundation::list_type_name::value, m);
			register_assignable_container<types::list_type>(foundation::list_type_name::value, m);
			register_movable_container<types::list_type>(foundation::list_type_name::value, m);

			m.add_function(
					foundation::list_type_name::value,
					ctor<types::list_type(foundation::parameters_type&&)>());
			m.add_function(
					foundation::list_type_name::value,
					ctor<types::list_type(foundation::parameters_view_type)>());

			// operator+/operator+=
			// foundation::operator_register::register_plus<types::list_type>(m);
			// foundation::operator_register::register_plus_assign<types::list_type>(m);
			// operator*/operator*=
			// foundation::operator_register::register_multiply<types::list_type>(m, &types::list_type::operator*);
			// foundation::operator_register::register_multiply_assign<types::list_type>(m, &types::list_type::operator*=);

			// list.view()
			register_view_type<types::list_type>(m);

			// list[index]
			m.add_function(
					foundation::container_subscript_interface_name::value,
					fun(static_cast<types::list_type::reference (types::list_type::*)(types::list_type::difference_type) noexcept>(&types::list_type::get)));
			m.add_function(
					foundation::container_subscript_interface_name::value,
					fun(static_cast<types::list_type::const_reference (types::list_type::*)(types::list_type::difference_type) const noexcept>(&types::list_type::get)));

			// list.size()
			m.add_function(
					foundation::container_size_interface_name::value,
					fun(&types::list_type::size));

			// list.empty()
			m.add_function(
					foundation::container_empty_interface_name::value,
					fun(&types::list_type::empty));

			// list.clear()
			m.add_function(
					foundation::container_clear_interface_name::value,
					fun(&types::list_type::clear));

			// list.front()
			m.add_function(
					foundation::container_front_interface_name::value,
					fun(static_cast<types::list_type::reference (types::list_type::*)() noexcept>(&types::list_type::front)));
			m.add_function(
					foundation::container_front_interface_name::value,
					fun(static_cast<types::list_type::const_reference (types::list_type::*)() const noexcept>(&types::list_type::front)));

			// list.back()
			m.add_function(
					foundation::container_back_interface_name::value,
					fun(static_cast<types::list_type::reference (types::list_type::*)() noexcept>(&types::list_type::back)));
			m.add_function(
					foundation::container_back_interface_name::value,
					fun(static_cast<types::list_type::const_reference (types::list_type::*)() const noexcept>(&types::list_type::back)));

			// list.insert_at(index, value)/list.erase_at(index)
			m.add_function(
					foundation::container_insert_interface_name::value,
					fun(&types::list_type::insert_at));
			m.add_function(
					foundation::container_erase_interface_name::value,
					fun(&types::list_type::erase_at));

			// list.push_back(value)/list.pop_back()
			m.add_function(
					foundation::container_push_back_interface_name::value,
					fun(&types::list_type::push_back));
			m.add_function(
					foundation::container_pop_back_interface_name::value,
					fun(&types::list_type::pop_back));

			// list.push_front()/list.pop_front()
			m.add_function(
					foundation::container_push_front_interface_name::value,
					fun(&types::list_type::push_front));
			m.add_function(
					foundation::container_pop_front_interface_name::value,
					fun(&types::list_type::pop_front));

			// todo: extra interface
		}

		static void register_dict_type(foundation::engine_module& m)
		{
			m.add_type_info(foundation::dict_type_name::value, types::dict_type::class_type());

			register_default_constructible_container<types::dict_type>(foundation::dict_type_name::value, m);
			register_assignable_container<types::dict_type>(foundation::dict_type_name::value, m);
			register_movable_container<types::dict_type>(foundation::dict_type_name::value, m);

			// pair
			using pair_type = types::dict_type::value_type;
			const auto pair_name = foundation::string_type{foundation::dict_type_name::value}.append(foundation::pair_suffix_name::value);
			m.add_type_info(pair_name, types::dict_type::pair_class_type());
			register_default_constructible_container<pair_type>(pair_name, m);
			// register_assignable_container<pair_type>(pair_name, m);
			m.add_function(pair_name, copy_ctor<pair_type>());
			// register_movable_container<pair_type>(pair_name, m);
			m.add_function(pair_name, move_ctor<pair_type>());
			m.add_function(pair_name, ctor<pair_type(const pair_type::first_type&, const pair_type::second_type&)>());
			m.add_function(foundation::pair_first_interface_name::value, fun(&pair_type::first));
			m.add_function(foundation::pair_second_interface_name::value, fun(&pair_type::second));

			// operator+/operator+=
			// foundation::operator_register::register_plus<types::dict_type>(m);
			// foundation::operator_register::register_plus_assign<types::dict_type>(m);

			// dict.view()
			register_view_type<types::dict_type>(m);

			// dict[key]
			m.add_function(
					foundation::container_subscript_interface_name::value,
					fun(static_cast<types::dict_type::mapped_reference (types::dict_type::*)(types::dict_type::key_const_reference)>(&types::dict_type::get)));
			m.add_function(
					foundation::container_subscript_interface_name::value,
					fun(static_cast<types::dict_type::mapped_const_reference (types::dict_type::*)(types::dict_type::key_const_reference) const>(&types::dict_type::get)));

			// dict.size()
			m.add_function(
					foundation::container_size_interface_name::value,
					fun(&types::dict_type::size));

			// dict.empty()
			m.add_function(
					foundation::container_empty_interface_name::value,
					fun(&types::dict_type::empty));

			// dict.clear()
			m.add_function(
					foundation::container_clear_interface_name::value,
					fun(&types::dict_type::clear));

			// dict.erase_at(key)
			m.add_function(
					foundation::container_erase_interface_name::value,
					fun(&types::dict_type::erase_at));

			// todo: extra interface
		}

		static void register_string_type(foundation::engine_module& m)
		{
			m.add_type_info(foundation::string_type_name::value, types::string_type::class_type());

			// foundation::string_type => string_type
			// m.add_function(
			// 		foundation::string_type_name::value,
			// 		ctor<types::string_type(const foundation::string_type&)>());
			m.add_convertor(make_explicit_convertor<foundation::string_type, types::string_type>(
					[](const foundation::string_type& string) { return types::string_type{string}; }));

			// foundation::string_view_type => string_type
			// m.add_function(
			// 		foundation::string_type_name::value,
			// 		ctor<types::string_type(foundation::string_view_type)>());
			m.add_convertor(make_explicit_convertor<foundation::string_view_type, types::string_type>(
					[](const foundation::string_view_type string) { return types::string_type{string}; }));

			// string_type => foundation::string_type
			m.add_convertor(make_explicit_convertor<types::string_type, foundation::string_type>(
					[](const types::string_type& string) { return foundation::string_type{string.data()}; }));

			// string_type => foundation::string_view_type
			m.add_convertor(make_explicit_convertor<types::string_type, foundation::string_view_type>(
					[](const types::string_type& string) { return foundation::string_view_type{string.data()}; }));

			// string_type => string_view_type
			m.add_convertor(make_explicit_convertor<types::string_type, types::string_view_type>(
					[](const types::string_type& string) { return types::string_view_type{string.data()}; }));

			register_default_constructible_container<types::string_type>(foundation::string_type_name::value, m);
			register_assignable_container<types::string_type>(foundation::string_type_name::value, m);
			register_movable_container<types::string_type>(foundation::string_type_name::value, m);

			// operator+/operator+=
			foundation::operator_register::register_plus<types::string_type>(m);
			foundation::operator_register::register_plus<types::string_type>(
					m,
					[](const types::string_type& string, const types::char_type other) -> decltype(auto) { return string + other; });
			foundation::operator_register::register_plus_assign<types::string_type>(m);
			foundation::operator_register::register_plus_assign<types::string_type>(
					m,
					[](types::string_type& string, const types::char_type other) -> decltype(auto) { return string += other; });
			// operator*/operator*=
			foundation::operator_register::register_multiply<types::string_type>(m, &types::string_type::operator*);
			foundation::operator_register::register_multiply_assign<types::string_type>(m, &types::string_type::operator*=);

			// ==/!=</<=/>/>=
			register_comparison<types::string_type>(m);

			// string.view()
			register_view_type<types::string_type>(m);

			// string[index]
			m.add_function(
					foundation::container_subscript_interface_name::value,
					fun(static_cast<types::string_type::reference (types::string_type::*)(types::string_type::difference_type) noexcept>(&types::string_type::get)));
			m.add_function(
					foundation::container_subscript_interface_name::value,
					fun(static_cast<types::string_type::const_reference (types::string_type::*)(types::string_type::difference_type) const noexcept>(&types::string_type::get)));

			// string.size()
			m.add_function(
					foundation::container_size_interface_name::value,
					fun(&types::string_type::size));

			// string.empty()
			m.add_function(
					foundation::container_empty_interface_name::value,
					fun(&types::string_type::empty));

			// string.clear()
			m.add_function(
					foundation::container_clear_interface_name::value,
					fun(&types::string_type::clear));

			// string.front()
			m.add_function(
					foundation::container_front_interface_name::value,
					fun(static_cast<types::string_type::reference (types::string_type::*)() noexcept>(&types::string_type::front)));
			m.add_function(
					foundation::container_front_interface_name::value,
					fun(static_cast<types::string_type::const_reference (types::string_type::*)() const noexcept>(&types::string_type::front)));

			// string.back()
			m.add_function(
					foundation::container_back_interface_name::value,
					fun(static_cast<types::string_type::reference (types::string_type::*)() noexcept>(&types::string_type::back)));
			m.add_function(
					foundation::container_back_interface_name::value,
					fun(static_cast<types::string_type::const_reference (types::string_type::*)() const noexcept>(&types::string_type::back)));

			// string.insert_at(index, value)/string.erase_at(index)
			m.add_function(
					foundation::container_insert_interface_name::value,
					fun(&types::string_type::insert_at));
			m.add_function(
					foundation::container_erase_interface_name::value,
					fun(&types::string_type::erase_at));

			// string.push_back(value)/string.pop_back()
			m.add_function(
					foundation::container_push_back_interface_name::value,
					fun(&types::string_type::push_back));
			m.add_function(
					foundation::container_pop_back_interface_name::value,
					fun(&types::string_type::pop_back));

			// todo: extra interface
		}

		static void register_string_view_type(foundation::engine_module& m)
		{
			m.add_type_info(foundation::string_view_type_name::value, types::string_view_type::class_type());

			// foundation::string_type => string_view_type
			// m.add_function(
			// 		foundation::string_view_type_name::value,
			// 		ctor<types::string_view_type(const foundation::string_type&)>());
			m.add_convertor(make_explicit_convertor<foundation::string_type, types::string_view_type>(
					[](const foundation::string_type& string) { return types::string_view_type{string}; }));

			// foundation::string_view_type => string_view_type
			// m.add_function(
			// 		foundation::string_view_type_name::value,
			// 		ctor<types::string_view_type(foundation::string_view_type)>());
			m.add_convertor(make_explicit_convertor<foundation::string_view_type, types::string_view_type>(
					[](const foundation::string_view_type string) { return types::string_view_type{string}; }));

			// string_view_type => foundation::string_type
			m.add_convertor(make_explicit_convertor<types::string_view_type, foundation::string_type>(
					[](const types::string_view_type view) { return foundation::string_type{view.data()}; }));

			// string_view_type => foundation::string_view_type
			m.add_convertor(make_explicit_convertor<types::string_view_type, foundation::string_view_type>(
					[](const types::string_view_type view) { return foundation::string_view_type{view.data()}; }));

			// string_view_type => string_type
			m.add_convertor(make_explicit_convertor<types::string_view_type, types::string_type>(
					[](const types::string_view_type view) { return types::string_type{view.data()}; }));

			register_default_constructible_container<types::string_view_type>(foundation::string_view_type_name::value, m);
			register_assignable_container<types::string_view_type>(foundation::string_view_type_name::value, m);
			register_movable_container<types::string_view_type>(foundation::string_view_type_name::value, m);

			// ==/!=</<=/>/>=
			register_comparison<types::string_view_type>(m);

			// string.view()
			register_view_type<types::string_view_type>(m);

			// string[index]
			m.add_function(
					foundation::container_subscript_interface_name::value,
					fun(&types::string_view_type::get));

			// string.size()
			m.add_function(
					foundation::container_size_interface_name::value,
					fun(&types::string_view_type::size));

			// string.empty()
			m.add_function(
					foundation::container_empty_interface_name::value,
					fun(&types::string_view_type::empty));

			// string.front()
			m.add_function(
					foundation::container_front_interface_name::value,
					fun(&types::string_view_type::front));

			// string.back()
			m.add_function(
					foundation::container_back_interface_name::value,
					fun(&types::string_view_type::back));

			// todo: extra interface

			// todo: allow string_view_type to do +/+=/*/*= operations with string_type?
		}

		static void register_type_to_string(foundation::engine_module& m)
		{
			// number
			m.add_function(foundation::operator_to_string_name::value,
			               fun([](const types::number_type& num) -> decltype(auto) { return types::string_type{num.to_string()}; }));

			// range
			m.add_function(foundation::operator_to_string_name::value,
			               fun([](const types::range_type& range) -> decltype(auto) { return types::string_type{std_format::format("range(begin={}, end={}, step={})", range.begin(), range.end(), range.step())}; }));

			// list
			// m.add_evaluation(
			// 		std_format::format(
			// 				R"(
			// 		{} {}({} l)
			// 		{{
			// 			var s = "["
			// 			for(var v in l)
			// 			{{
			// 				s += to_string(v)
			// 				s += ", "
			// 			}}
			// 			# erase ' '
			// 			s.pop_back()
			// 			# overwrite ','
			// 			s[s.size() - 1] = ']'
			// 			return s
			// 		}}
			// 	)",
			// 				foundation::keyword_define_name::value,
			// 				foundation::operator_to_string_name::value,
			// 				foundation::list_type_name::value));

			// dict
			// todo: to_string(dict)? need dispatcher_state!

			// string
			m.add_function(foundation::operator_to_string_name::value,
			               fun([](const types::string_type& string) -> decltype(auto) { return string; }));

			// string_view
			m.add_function(foundation::operator_to_string_name::value,
			               fun([](const types::string_view_type& string) -> decltype(auto) { return string; }));
		}

		static void register_print(foundation::engine_module& m)
		{
			// boolean
			m.add_function(
					"print",
					fun([](const bool b) { std::cout << (b ? foundation::keyword_true_name::value : foundation::keyword_false_name::value); }));

			// number
			m.add_function(
					"print",
					fun([](const types::number_type& num) { std::cout << num.to_string(); }));

			// list
			// m.add_evaluation(
			// 		std_format::format(
			// 				R"(
			// 		{} print({} l)
			// 		{{
			// 			print(to_string(l))
			// 		}}
			// 		)",
			// 				foundation::keyword_define_name::value,
			// 				foundation::list_type_name::value));

			// string
			// m.add_function(
			// 		"print",
			// 		fun([](const types::string_type& string) { std::cout << string.data(); }));

			// string_view
			m.add_function(
					"print",
					fun([](const types::string_view_type string) { std::cout << string.data(); }));

			// empty
			m.add_function(
					"println",
					fun([] { std::cout << '\n'; }));

			// boolean
			m.add_function(
					"println",
					fun([](const bool b) { std::cout << (b ? foundation::keyword_true_name::value : foundation::keyword_false_name::value) << '\n'; }));

			// number
			m.add_function(
					"println",
					fun([](const types::number_type& num) { std::cout << num.to_string() << '\n'; }));

			// list
			// m.add_evaluation(
			// 		std_format::format(
			// 				R"(
			// 		{} println({} l)
			// 		{{
			// 			println(to_string(l))
			// 		}}
			// 		)",
			// 				foundation::keyword_define_name::value,
			// 				foundation::list_type_name::value));

			// string
			// m.add_function(
			// 		"println",
			// 		fun([](const types::string_type& string) { std::cout << string.data() << '\n'; }));

			// string_view
			m.add_function(
					"println",
					fun([](const types::string_view_type string) { std::cout << string.data() << '\n'; }));
		}

	public:
		static void do_bootstrap(foundation::engine_module& m)
		{
			register_boolean_type(m);
			register_range_type(m);
			register_list_type(m);
			register_dict_type(m);
			register_string_type(m);
			register_string_view_type(m);

			register_type_to_string(m);

			register_print(m);
		}
	};
}

#endif // GAL_LANG_PLUGIN_BOOTSTRAP_LIBRARY_HPP
