#pragma once

#if defined(_WIN32)
#include <string>

std::string FromUtf16(const wchar_t *utf16_string, size_t utf16_string_length);
std::string FromUtf16(const wchar_t *utf16_string);

#endif
