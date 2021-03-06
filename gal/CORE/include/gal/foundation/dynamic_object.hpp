#pragma once

#ifndef GAL_LANG_FOUNDATION_DYNAMIC_OBJECT_HPP
#define GAL_LANG_FOUNDATION_DYNAMIC_OBJECT_HPP

#include<gal/foundation/boxed_value.hpp>
#include <unordered_map>

namespace gal::lang::foundation
{
	class dynamic_object
	{
	public:
		constexpr static string_view_type missing_method_name = GAL_LANG_FUNCTION_METHOD_MISSING_NAME;

		using members_type = std::unordered_map<string_view_type, boxed_value, std::hash<string_view_type>, std::equal_to<>>;

		static const gal_type_info& class_type() noexcept
		{
			GAL_LANG_TYPE_INFO_DEBUG_DO_OR(constexpr,) static gal_type_info type = make_type_info<dynamic_object>();
			return type;
		}

	private:
		string_view_type type_name_;

		members_type members_;

	public:
		explicit dynamic_object(const string_view_type name)
			: type_name_{name} {}

		//************************************************************************
		//****************************** INTERFACES ****************************
		//************************************************************************

		[[nodiscard]] constexpr string_view_type nameof() const noexcept { return type_name_; }

		[[nodiscard]] bool has_attr(const string_view_type name) const { return members_.contains(name); }

		[[nodiscard]] boxed_value& get_attr(const string_view_type name) { return members_[name]; }

		[[nodiscard]] const boxed_value& get_attr(const string_view_type name) const
		{
			if (const auto it = members_.find(name);
				it != members_.end()) { return it->second; }
			throw std::range_error{std_format::format("Member '{}' not found and cannot be added to a const object", name)};
		}

		bool set_attr(const string_view_type name, boxed_value&& new_value) { return members_.insert_or_assign(name, std::move(new_value)).second; }

		bool set_attr(const string_view_type name, const boxed_value& new_value) { return members_.insert_or_assign(name, new_value).second; }

		bool del_attr(const string_view_type name) { return members_.erase(name); }

		/**
		 * @brief A function of the signature method_missing(object, name, param1, param2, param3) will be called if an appropriate method cannot be found.
		 *
		 * @code
		 *
		 * def method_missing(int i, string name, vector v) :
		 *	print("integer ${i} has no method named ${name} with ${v.size()} params")
		 *
		 * 42.not_exist_function(1, 2, 3) // prints "integer 42 has no method named not_exist_function with 3 params"
		 *
		 * @endcode
		 *
		 * @note method_missing signature can be either 2 parameters or 3 parameters.
		 * If the signature contains two parameters it is treated as a property.
		 * If the property contains a function then additional parameters are passed to the contained function.
		 * If both a 2 parameter and a 3 parameter signature match, the 3 parameter function always wins.
		 */
		[[nodiscard]] decltype(auto) method_missing(const string_view_type name) const { return get_attr(name); }
	};
}

#endif // GAL_LANG_FOUNDATION_DYNAMIC_OBJECT_HPP
