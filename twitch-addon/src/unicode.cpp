#include "unicode.hpp"

#if defined(_WIN32)
#ifndef WIN32_LEAN_AND_MEAN
#   define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

std::string FromUtf16(const wchar_t* utf16_string, size_t utf16_string_length)
{
	int utf8_string_length = ::WideCharToMultiByte(CP_UTF8, 0, utf16_string, static_cast<int>(utf16_string_length), NULL, 0, NULL, NULL);
	std::string utf8_string(utf8_string_length, '\0');
	utf8_string_length = ::WideCharToMultiByte(CP_UTF8, 0, utf16_string, static_cast<int>(utf16_string_length), const_cast<char *>(utf8_string.c_str()), utf8_string_length, NULL, NULL);
	return utf8_string;
}

std::string FromUtf16(const wchar_t* utf16_string)
{
	return FromUtf16(utf16_string, wcslen(utf16_string));
}

#endif
