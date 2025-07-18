#ifndef STRING_HELPER_FUNCTIONS_H
#define STRING_HELPER_FUNCTIONS_H

#include <string>
#include <vector>

std::string trim(const std::string &);

std::wstring trim(const std::wstring &);

std::vector<std::string> split(const std::string &source, const char *needle,
                               const size_t max_count = std::string::npos);

std::vector<std::wstring> split(const std::wstring &source, const char *needle,
                                const size_t max_count = std::wstring::npos);

#endif /* STRING_HELPER_FUNCTIONS_H */
