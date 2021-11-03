#pragma once 

#include "Patch.hpp"

namespace
{
	using namespace std;
	namespace fs = std::filesystem;

	class Cookies : public IPatch
	{
	public:
		std::string GetID()
		{
			return "Browser Cookies";
		}

		list<string>* GetProcesses()
		{
			return new list<string>
			{
				"msedge",
				"firefox",
				"chrome",
				"brave",
				"opera"
			};
		}

		bool DoPatch(char drive)
		{
			// Brave Cookies
			DELFILE(drive + S(":\\Users\\") + USER + S("\\AppData\\Local\\BraveSoftware\\Brave-Browser\\User Data\\Default\\Cookies"));

			// chrome Cookies
			DELFILE(drive + S(":\\Users\\") + USER + S("\\AppData\\Local\\Google\\Chrome\\User Data\\Default\\Cookies"));

			// opera Cookies
			DELFILE(drive + S(":\\Users\\") + USER + S("\\AppData\\Local\\Opera Software\\Opera Stable\\Cookies"));

			// firefox cookies
			{
				std::string path = drive + S(":\\Users\\") + USER + S("\\AppData\\Local\\Mozilla\\Firefox\\Profiles\\");

				if (fs::exists(path) == true)
				{
					for (const auto& entry : fs::directory_iterator(path))
					{
						if (entry.is_directory() == false)
							continue;

						std::string path = entry.path().u8string();

						if (ends_with(path, "\\") == false)
							path += "\\";

						path += "cookies.sqlite";

						if (fs::exists(path) == true)
							DELFILE(path);
					}
				}
			}

			return true;
		}
	};
}