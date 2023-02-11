/*
	Successor of Anti-Flag and Anti-Flag-V2.

	Developers:
	- DWORD64
	- Sixmax
*/
#pragma once

#include <string>
#include <algorithm>

using namespace std;

namespace Utils
{
	inline bool ends_with(const string &value, const string &ending)
	{
		if (ending.size() > value.size()) return false;
		return equal(ending.rbegin(), ending.rend(), value.rbegin());
	}

	inline string toLowerStr(string str)
	{
		if (str.empty())
			return str;

		transform(str.begin(), str.end(), str.begin(), ::tolower);

		return str;
	}
}
/*
	Successor of Anti-Flag and Anti-Flag-V2.

	Developers:
	- DWORD64
	- Sixmax
*/