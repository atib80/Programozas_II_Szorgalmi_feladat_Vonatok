#include "string_helper_functions.h"
#include <cctype>

using namespace std;

string trim(const string &str) {
    if (str.empty()) return {};

    size_t begin{};
    size_t end{str.size() - 1};

    for (; begin <= end; ++begin) {
        if (!isspace(str[begin])) break;
    }

    if (begin > end) return string{};

    for (; end > begin; --end) {
        if (!isspace(str[end])) break;
    }

    return str.substr(begin, end - begin + 1);
}

wstring trim(const wstring &str) {
    if (str.empty()) return {};

    size_t begin{};
    size_t end{str.size() - 1};

    for (; begin <= end; ++begin) {
        if (!iswspace(str[begin])) break;
    }

    if (begin > end) return wstring{};

    for (; end > begin; --end) {
        if (!iswspace(str[end])) break;
    }

    return str.substr(begin, end - begin + 1);
}

vector<string> split(const std::string &source, const char *needle, const size_t max_count) {
    vector<string> parts;

    size_t prev{};

    string needle_st{needle};

    const size_t needle_len = needle_st.size();

    if (0u == source.length() || 0u == needle_st.length() || needle_st.length() >= source.length()) return parts;

    size_t number_of_parts = 0;

    while (true) {
        const size_t current = source.find(needle_st, prev);

        if (string::npos == current) break;

        number_of_parts++;

        if (string::npos != max_count && parts.size() == max_count) break;

        if (current - prev > 0) parts.emplace_back(source.substr(prev, current - prev));

        prev = current + needle_len;

        if (prev >= source.size()) break;
    }

    if (number_of_parts > 0 && prev < source.size()) {
        if (string::npos == max_count) {
            parts.emplace_back(source.substr(prev));
        } else if (parts.size() < max_count) {
            parts.emplace_back(source.substr(prev));
        }
    }

    return parts;
}

vector<wstring> split(const wstring &source, const wchar_t *needle, const size_t max_count) {
    vector<wstring> parts;

    size_t prev{};

    wstring needle_st{needle};

    const size_t needle_len = needle_st.size();

    if (source.empty() || needle_st.empty() || needle_st.length() >= source.length()) return parts;

    size_t number_of_parts = 0;

    while (true) {
        const size_t current = source.find(needle_st, prev);

        if (wstring::npos == current) break;

        number_of_parts++;

        if (wstring::npos != max_count && parts.size() == max_count) break;

        if (current - prev > 0) parts.emplace_back(source.substr(prev, current - prev));

        prev = current + needle_len;

        if (prev >= source.size()) break;
    }

    if (number_of_parts > 0 && prev < source.size()) {
        if (wstring::npos == max_count) {
            parts.emplace_back(source.substr(prev));
        } else if (parts.size() < max_count) {
            parts.emplace_back(source.substr(prev));
        }
    }

    return parts;
}
