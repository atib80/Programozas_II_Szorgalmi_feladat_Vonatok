#include "string_helper_functions.h"
#include <cctype>

using namespace std;

string trim(const string& str)
{

	size_t begin = 0u;
	size_t end = str.size() - 1;

	if (0u == str.length()) return string{};

	for (; begin <= end; ++begin) {

		if (!isspace(str[begin])) break;
		
	}

	if (begin > end) return string{};

	for (; end > begin; --end)
	{
		if (!isspace(str[end])) break;
	}

	return str.substr(begin, end - begin + 1);
}

wstring trim(const wstring& str)
{

	size_t begin = 0u;
	size_t end = str.size() - 1;

	if (0u == str.length()) return wstring{};

	for (; begin <= end; ++begin) {

		if (!iswspace(str[begin])) break;		
	}

	if (begin > end) return wstring{};

	for (; end > begin; --end)
	{
		if (!iswspace(str[end])) break;		
	}

	return str.substr(begin, end - begin + 1);
}

vector<string> split(const std::string& source, const char* needle, const size_t max_count)
{
	vector<string> parts{};

	size_t prev = 0, current;

	string needle_st{ needle };

	const size_t needle_len = needle_st.size();

	if ((0u == source.length()) || (0u == needle_st.length()) || (needle_st.length() >= source.length())) return parts;

	size_t number_of_parts = 0;

	do
	{
		current = source.find(needle_st, prev);

		if (string::npos == current) break;

		number_of_parts++;

		if ((string::npos != max_count) && (parts.size() == max_count)) break;

		if ((current - prev) > 0) parts.emplace_back(source.substr(prev, current - prev));

		prev = current + needle_len;

		if (prev >= source.size()) break;
	} while (string::npos != current);

	if (number_of_parts > 0 && prev < source.size())
	{
		if (string::npos == max_count) parts.emplace_back(source.substr(prev));

		else if ((string::npos != max_count) && (parts.size() < max_count)) parts.emplace_back(source.substr(prev));
	}

	return parts;
}

vector<wstring> split(const wstring& source, const wchar_t* needle, const size_t max_count)
{
	vector<wstring> parts{};

	size_t prev = 0, current;

	wstring needle_st{ needle };

	const size_t needle_len = needle_st.size();

	if ((0u == source.length()) || (0u == needle_st.length()) || (needle_st.length() >= source.length())) return parts;

	size_t number_of_parts = 0;

	do
	{
		current = source.find(needle_st, prev);

		if (wstring::npos == current) break;

		number_of_parts++;

		if ((wstring::npos != max_count) && (parts.size() == max_count)) break;

		if ((current - prev) > 0) parts.emplace_back(source.substr(prev, current - prev));

		prev = current + needle_len;

		if (prev >= source.size()) break;

	} while (wstring::npos != current);

	if (number_of_parts > 0 && prev < source.size())
	{
		if (wstring::npos == max_count) parts.emplace_back(source.substr(prev));

		else if ((wstring::npos != max_count) && (parts.size() < max_count)) parts.emplace_back(source.substr(prev));
	}

	return parts;

}
