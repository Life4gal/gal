#pragma once

#ifndef GAL_UTILS_CONFUSABLE_HPP
	#define GAL_UTILS_CONFUSABLE_HPP

#include <cstdint>

namespace gal::utils
{
	constexpr const char* find_confusable(std::uint32_t codepoint);
}

#endif // GAL_UTILS_CONFUSABLE_HPP
