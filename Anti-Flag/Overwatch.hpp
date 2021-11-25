/*
	Successor of Anti-Flag and Anti-Flag-V2.

	Developers:
	- DWORD64
	- Sixmax
*/

#pragma once 

#include "Patch.hpp"
#include "Help.hpp"

#include <iostream>
#include <filesystem>

namespace
{
	using namespace std;

	namespace fs = std::filesystem;

	class Overwatch : public IPatch
	{
	public:
		std::string GetID()
		{
			return "Overwatch";
		}

		list<string>* GetProcesses()
		{
			return new list<string>{
				"battle.net",
				"agent",
				"overwatch",
			};
		}

		/*
			Please Note:

			Not everything we are deleting here is related to Blizzard Device Flags, we are also clearing Cache etc simply to 
			*clean* your installation.
		*/
		bool DoPatch(char drive)
		{
#pragma region Blizz Device Flags / Installation Cleanup
			DELDIR(drive + S(":\\Users\\") + USER + S("\\AppData\\Local\\Battle.net\\"));
			DELDIR(drive + S(":\\Users\\") + USER + S("\\AppData\\Local\\Blizzard\\"));
			DELDIR(drive + S(":\\Users\\") + USER + S("\\AppData\\Local\\Blizzard Entertainment\\"));
			DELDIR(drive + S(":\\Users\\") + USER + S("\\AppData\\Roaming\\Battle.net\\"));
			DELDIR(drive + S(":\\Users\\") + USER + S("\\Documents\\Overwatch\\Logs\\"));
		
			DELDIR(drive + S(":\\ProgramData\\Battle.net\\Setup\\"));
			DELDIR(drive + S(":\\ProgramData\\Battle.net\\Agent\\data\\"));
			DELDIR(drive + S(":\\ProgramData\\Battle.net\\Agent\\Logs\\"));
			DELDIR(drive + S(":\\ProgramData\\Blizzard Entertainment\\"));

			DELDIR(drive + S(":\\Program Files (x86)\\Overwatch\\_retail_\\cache\\"));
			DELDIR(drive + S(":\\Program Files (x86)\\Overwatch\\_retail_\\GPUCache\\"));

			// delete old bnet agents. the one with the greatest number is the latest one all other can be deleted
			{
				string agentsPath = S(drive + S(":\\ProgramData\\Battle.net\\Agent\\"));

				if (fs::exists(agentsPath))
				{
					string latestAgent = "";
					int greatest = 0;

					for (const auto& entry : fs::directory_iterator(agentsPath))
					{
						if (entry.is_directory() == false)
							continue;

						auto path = entry.path().u8string();
						auto args = Help::split(path, '\\');
						auto folder = args[args.size() - 1];

						if (folder._Starts_with("Agent") == false)
							continue;

						int agentID = stoi(Help::split(folder, '.')[1]);

						if (agentID > greatest)
						{
							greatest = agentID;
							latestAgent = path;
						}
					}

					for (const auto& entry : fs::directory_iterator(agentsPath))
					{
						if (entry.is_directory() == false)
							continue;

						auto path = entry.path().u8string();
						auto args = Help::split(path, '\\');
						auto folder = args[args.size() - 1];

						if (folder._Starts_with("Agent") == false)
							continue;

						if (path != latestAgent)
						{
							DELDIR(path);
						}
					}
				}
			}

			REGDEL("HKEY_LOCAL_MACHINE\\SOFTWARE\\WOW6432Node\\Blizzard Entertainment");
			REGDEL("HKEY_CURRENT_USER\\SOFTWARE\\Blizzard Entertainment");
			REGDEL("HKEY_CURRENT_USER\\SOFTWARE\\Activision");
			REGDEL("HKEY_CLASSES_ROOT\\Applications\\Overwatch.exe");
			REGDEL("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\microphone\\NonPackaged\\C:#Program Files (x86)#Overwatch#_retail_#Overwatch.exe");
			REGDEL("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\RADAR\\HeapLeakDetection\\DiagnosedApplications\\Overwatch.exe");
			REGDEL("HKEY_CURRENT_USER\\VirtualStore\\MACHINE\\SOFTWARE\\WOW6432Node\\Activision");
			REGDEL("HKEY_CURRENT_USER\\SOFTWARE\\Classes\\VirtualStore\\MACHINE\\SOFTWARE\\WOW6432Node\\Activision");
#pragma endregion 



#pragma region Cheats 
			/* Start of Ow-Cheat Orion*/
			DELDIR(drive + S(":\\ProgramData\\Orion\\"));
			/* END of Ow-Cheat Orion*/
			
			/* START of Ow-Cheat Critical Hit */
			REGDEL("HKLM\\SOFTWARE\\00330-80000-00000-AA302");
			/* END of Ow-Cheat Critical Hit */

			/* START of Ow-Cheat Noble/hyperFlick */
			DELDIR(drive + S(":\\Users\\") + USER + S("\\AppData\\Local\\Temp\\")); //due some User reports, we found out that they save/leave traces on your Pc inside the Temp folder! Credits you know
			/* END of Ow-Cheat Noble/hyperFlick */


#pragma endregion

			return true;
		}
	};
}

/*
	Successor of Anti-Flag and Anti-Flag-V2.

	Developers:
	- DWORD64
	- Sixmax
*/