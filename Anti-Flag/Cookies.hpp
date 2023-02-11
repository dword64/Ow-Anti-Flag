/*
	Successor of Anti-Flag and Anti-Flag-V2.

	Developers:
	- DWORD64
	- Sixmax
*/
#pragma once 

#include "Patch.hpp"


using namespace std;
namespace fs = filesystem;

class Cookies : public IPatch
{
public:
	string GetID()
	{
		return "Browser Cookies";
	}

	list<string>* GetProcesses()
	{
		return new list<string>
		{
			"msedge","firefox","chrome","brave","opera"
		};
	}

	bool DoPatch(char drive)
	{
		string USERPROFILE = getenv("USERPROFILE");
		string APPDATA = getenv("APPDATA");

		// Brave Cookies
		if (!DELFILE((drive + S(":") + USERPROFILE + S("\\AppData\\Local\\BraveSoftware\\Brave-Browser\\User Data\\Default\\Cookies")).c_str()))
			printf("Error deleting Brave cookies\n");

		// chrome Cookies
		if (!DELFILE((drive + S(":") + APPDATA + S("\\Google\\Chrome\\User Data\\Default\\Cookies")).c_str()))
			printf("Error deleting Chrome cookies\n");

		// opera Cookies
		if (!DELFILE((drive + S(":") + APPDATA + S("\\Opera Software\\Opera Stable\\Cookies")).c_str()))
			printf("Error deleting Opera cookies\n");

		// firefox cookies
		string path = drive + S(":") + APPDATA + S("\\Mozilla\\Firefox\\Profiles\\");

		if (fs::exists(path) == true)
		{
			for (const auto& entry : fs::directory_iterator(path))
			{
				if (entry.is_directory() == false)
					continue;

				string path = entry.path().u8string();
				if (ends_with(path, "\\") == false)
					path += "\\";
				path += "cookies.sqlite";

				if (fs::exists(path) == true)
					if (!DELFILE(path.c_str()))
						printf("Error deleting Firefox cookies\n");
			}
		}
		return true;
	}
};

/*
	Successor of Anti-Flag and Anti-Flag-V2.

	Developers:
	- DWORD64
	- Sixmax
*/