#include <ast/lexer.hpp>
#include <charconv>

namespace gal::ast
{
	lexer::multi_line_string_level_type lexer::read_multi_line_string_level()
	{
		multi_line_string_level_number_type number;
		const auto [ptr, ec] = std::from_chars(current_data(), data_end(), number);

		// how many characters been eat
		const auto offset = ptr - current_data();

		gal_assert(ec == std::errc{}, "Cannot read correct level number from string!");

		// just '<<' or '>>'
		if (offset == 0) { number = 0; }

		gal_assert(number >= 0, "Level number must be positive!");

		if (peek_char() != peek_char(offset)) { return offset == 0 ? std::make_pair(number, multi_line_string_its_not) : std::make_pair(number, multi_line_string_error_format); }
		// really eat them
		offset_ += offset;
		return std::make_pair(number, offset);
	}

	lexeme_point lexer::read_multi_line_string(const utils::position begin, const multi_line_string_level_type level, lexeme_point::token_type ok, lexeme_point::token_type broken)
	{
		gal_assert(is_multi_line_string_begin(), "Wrong multi line string format!");

		// eat the second '<'
		consume();

		const auto start_offset = offset_;

		while (peek_char())
		{
			if (is_multi_line_string_end())
			{
				if (const auto [end_level, end_length] = read_multi_line_string_level(); end_level == level.first)
				{
					gal_assert(is_multi_line_string_end(), "Wrong multi line string format!");
					// eat the second '>'
					consume();

					const auto end_offset = offset_ - level.second - 2;
					gal_assert(end_offset >= start_offset);

					return {ok, {begin, {0, 0}}, {buffer_.data() + start_offset, end_offset - start_offset}};
				}
			}
			else { consume(); }
		}

		return {broken, {begin, {0, 0}}};
	}

	lexeme_point lexer::read_quoted_string(const char quotation, const std::size_t length)
	{
		const auto begin = current_position();

		const auto start_offset = offset_;

		for (const auto c = peek_char(); c != quotation;)
		{
			switch (c)
			{
				case 0:
				case '\r':
				case '\n': { return {lexeme_point::token_type::broken_string, {begin, {0, 0}}}; }
				case '\\':
				{
					consume();
					switch (peek_char())
					{
						case '\r':
						{
							consume_until(utils::is_new_line);
							break;
						}
						case 0: { break; }
						case 'z':
						{
							consume();
							consume_until(utils::is_whitespace);
							break;
						}
						default: { consume(); }
					}
					break;
				}
				default: { consume(); }
			}
		}

		consume_n(length);

		return {lexeme_point::token_type::quoted_string, {begin, {0, 0}}, {buffer_.data() + start_offset, offset_ - start_offset - length}};
	}

	lexeme_point lexer::read_comment()
	{
		const auto begin = current_position();

		const auto start_offset = offset_;

		if (is_multi_line_string_begin())
		{
			if (const auto level = read_multi_line_string_level();
				level.second != multi_line_string_error_format) { return read_multi_line_string(begin, level, lexeme_point::token_type::block_comment, lexeme_point::token_type::broken_comment); }
		}

		// fall back to single-line comment
		for (const auto c = peek_char(); c && not utils::is_new_line(c); consume()) {}

		return {lexeme_point::token_type::comment, {begin, {0, 0}}, {buffer_.data() + start_offset, offset_ - start_offset}};
	}

	std::pair<ast_name_table::name_type, lexeme_point::token_type> lexer::read_name()
	{
		gal_assert(utils::is_alpha(peek_char()) || peek_char() == '_', "Wrong identifier!");

		const auto start_offset = offset_;

		consume();
		consume_until([](const char c) { return utils::is_alpha(c) || utils::is_digit(c) || c == '_'; });

		return read_name_ ? name_table_.insert_if_not_exist({buffer_.data() + start_offset, offset_ - start_offset}) : name_table_.get({buffer_.data() + start_offset, offset_ - start_offset});
	}

	lexeme_point lexer::read_number(const utils::position begin, const offset_type start_offset)
	{
		gal_assert(utils::is_digit(peek_char()), "Wrong number format!");

		consume();
		consume_until([](const char c) { return utils::is_digit(c) || c == '.' || c == '_'; });

		if (const auto e = peek_char(); e == 'e' || e == 'E')
		{
			consume();

			if (const auto sign = peek_char(); sign == '+' || sign == '-') { consume(); }
		}

		consume_until([](const char c) { return utils::is_alpha(c) || utils::is_digit(c) || c == '_'; });

		return {lexeme_point::token_type::number, {begin, {0, 0}}, {buffer_.data() + start_offset, offset_ - start_offset}};
	}

	lexeme_point lexer::read_utf8_error()
	{
		const auto begin = current_position();

		lexeme_point::codepoint_type codepoint;
		int size;

		if (const auto c = peek_char(); (c & 0b10000000) == 0b00000000)
		{
			size = 1;
			codepoint = c & 0x7F;
		}
		else if ((c & 0b11100000) == 0b11000000)
		{
			size = 2;
			codepoint = c & 0b11111;
		}
		else if ((c & 0b11110000) == 0b11100000)
		{
			size = 3;
			codepoint = c & 0b1111;
		}
		else if ((c & 0b11111000) == 0b11110000)
		{
			size = 4;
			codepoint = c & 0b111;
		}
		else
		{
			consume();
			return {{begin, {0, 0}}, lexeme_point::bad_codepoint};
		}

		consume();

		for (decltype(size) i = 1; i < size; ++i)
		{
			if (const auto c = peek_char(); (c & 0b11000000) != 0b10000000) { return {{begin, {0, 0}}, lexeme_point::bad_codepoint}; }
			else
			{
				codepoint = codepoint << 6;
				codepoint |= c & 0b00111111;
				consume();
			}
		}

		return {{begin, {0, 0}}, codepoint};
	}

	lexeme_point lexer::read_next()
	{
		const auto begin = current_position();
		auto make_location = [begin](const utils::point::size_type length) { return make_horizontal_line(begin, length); };

		const auto [token, length] = lexeme_point::get_compound_symbol(
				[this](const std::size_t offset) constexpr noexcept { return peek_char(offset); });

		if (token == lexeme_point::token_type::comment)
		{
			consume_n(length);
			return read_comment();
		}
		if (token == lexeme_point::token_type::quoted_string)
		{
			const auto quotation = peek_char();
			consume_n(length);
			return read_quoted_string(quotation, length);
		}

		const auto scalar = lexeme_point::token_to_scalar(token);
		if (scalar == multi_line_string_begin())
		{
			consume_n(length);
			const auto level = read_multi_line_string_level();

			if (level.second == multi_line_string_error_format) { return {lexeme_point::token_type::broken_string, make_location(0)}; }
			if (level.second == multi_line_string_its_not) { return {token, make_location(0)}; }
			return read_multi_line_string(begin, level, lexeme_point::token_type::raw_string, lexeme_point::token_type::broken_string);
		}
		if (scalar == lexeme_point::get_dot_symbol()) { if (utils::is_digit(peek_char(1))) { return read_number(begin, offset_); } }
		if (utils::is_digit(static_cast<char>(scalar))) { return read_number(begin, offset_); }
		if (utils::is_alpha(static_cast<char>(scalar)) || scalar == lexeme_point::get_underscore_symbol())
		{
			const auto [name, type] = read_name();

			return {type, make_location(0), name};
		}
		if (scalar & 0x80) { return read_utf8_error(); }

		// length == 0 and we didn't handle it
		if (length == 0) { return lexeme_point::bad_lexeme_point(make_location(0)); }

		return {token, make_location(length)};
	}

	bool lexer::write_quoted_string(ast_name_owned data)
	{
		if (data.empty() || data.find('\\') == decltype(data)::npos) { return true; }

		const auto size = data.size();
		decltype(data)::size_type write = 0;

		for (decltype(write) i = 0; i < size;)
		{
			if (data[i] != '\\')
			{
				data[write++] = data[i];
				++i;
				continue;
			}

			if (i + 1 == size) { return false; }

			const auto escape = data[i + 1];
			i += 2;// skip \e

			switch (escape)
			{
				case '\n':
				{
					data[write++] = '\n';
					break;
				}
				case '\r':
				{
					data[write++] = '\n';
					if (i < size && data[i] == '\n') { ++i; }
					break;
				}
				case 0: { return false; }
				case 'x':
				{
					// hex escape codes are exactly 2 hex digits long
					if (i + 2 > size) { return false; }

					lexeme_point::codepoint_type code = 0;
					for (int j = 0; j < 2; ++j)
					{
						const auto c = data[i + j];
						if (not utils::is_hex_digit(c)) { return false; }

						code = 16 * code + (utils::is_digit(c) ? utils::to_digit(c) : utils::to_alpha(c));
					}

					data[write++] = static_cast<decltype(data)::value_type>(code);
					i += 2;
					break;
				}
				case 'z':
				{
					while (i < size && utils::is_whitespace(data[i])) { ++i; }
					break;
				}
				case 'u':
				{
					// unicode escape codes are at least 3 characters including braces
					if (i + 3 > size) { return false; }
					if (data[i] != '{') { return false; }

					++i;
					if (data[i] == '}') { return false; }

					lexeme_point::codepoint_type code = 0;
					for (int j = 0; j < 16; ++j, ++i)
					{
						if (i == size) { return false; }

						const auto c = data[i];

						if (c == '}') { break; }
						if (not utils::is_hex_digit(c)) { return false; }

						code = 16 * code + (utils::is_digit(c) ? utils::to_digit(c) : utils::to_alpha(c));
					}

					if (i == size || data[i] != '}') { return false; }
					++i;

					if (const auto utf8 = utils::to_utf8(data.data() + write, code); utf8 == 0) { return false; }
					else { write += utf8; }
					break;
				}
				default:
				{
					if (utils::is_digit(escape))
					{
						auto code = utils::to_digit(escape);

						for (int j = 0; j < 2; ++j, ++i)
						{
							if (i == size || not utils::is_digit(data[i])) { break; }

							code = 10 * code + utils::to_digit(data[i]);
						}

						if (code > std::numeric_limits<unsigned char>::max()) { return false; }

						data[write++] = static_cast<char>(code);
					}
				}
			}
		}

		gal_assert(write <= size);
		data.resize(write);

		return true;
	}

	void lexer::write_multi_line_string(ast_name_owned data)
	{
		if (data.empty()) { return; }

		// skip leading newline
		ast_name::size_type pos = data.find("\r\n") + 1;
		while ((pos = data.find("\r\n", pos)) != ast_name::npos) { data.replace(pos, 2, "\n"); }
	}
}
