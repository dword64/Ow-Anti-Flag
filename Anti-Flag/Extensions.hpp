/*
	Successor of Anti-Flag and Anti-Flag-V2.

	Developers:
	- DWORD64
	- Sixmax
*/

#pragma once

#include <string>

#define LENGTH(a) (sizeof(a) / sizeof(a[0]))

namespace
{
	bool ends_with(std::string const& value, std::string const& ending)
	{
		if (ending.size() > value.size()) return false;
		return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
	}

	std::string toLowerStr(std::string str)
	{
		if (str.empty())
			return str;

		for (unsigned int i = 0; i < str.length(); i++)
			str[i] = tolower(str.c_str()[i]);

		return str;
	}
}

/*
	Successor of Anti-Flag and Anti-Flag-V2.

	Developers:
	- DWORD64
	- Sixmax
*/