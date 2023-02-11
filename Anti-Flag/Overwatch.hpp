/*
	Successor of Anti-Flag and Anti-Flag-V2.

	Developers:
	- DWORD64
	- Sixmax
*/
#pragma once 

#include "Patch.hpp"
#include "Help.hpp"
#include "RegKey.hpp"

#include <iostream>
#include <filesystem>

namespace OverwatchFlags
{
	using namespace std;

	namespace fs = filesystem;

	class Overwatch : public IPatch
	{
	public:
		string GetID()
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

			string installLocation = ReadRegistryValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Overwatch", "InstallLocation");

			cout << installLocation << endl;

			DELDIR(installLocation + S("\\_retail_\\cache\\"));
			DELDIR(installLocation + S("\\_retail_\\GPUCache\\"));

			// delete old bnet agents. the one with the greatest number is the latest one all other can be deleted
			
				string agentsPath = S(drive + S(":\\ProgramData\\Battle.net\\Agent\\"));

				if (!fs::exists(agentsPath)) { return false; }
				string latestAgent = "";
				int greatest = 0;

				for (const auto& entry : fs::directory_iterator(agentsPath))
				{
					if (!entry.is_directory() || !entry.path().u8string()._Starts_with("Agent")) { continue; }

					auto path = entry.path().u8string();
					auto agentID = stoi(Help::split(entry.path().filename().u8string(), '.')[1]);

					if (agentID > greatest) { greatest = agentID; latestAgent = path; }
				}

				for (const auto& entry : fs::directory_iterator(agentsPath))
				{
					if (!entry.is_directory() || !entry.path().u8string()._Starts_with("Agent") || entry.path().u8string() == latestAgent) { continue; }

					DELDIR(entry.path().u8string());
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
			/* Start of Ow-Cheat Orion*/ //Outdated
			DELDIR(drive + S(":\\ProgramData\\Orion\\"));
			/* END of Ow-Cheat Orion*/
			
			/* START of Ow-Cheat Critical Hit */ //Outdated
			REGDEL("HKLM\\SOFTWARE\\00330-80000-00000-AA302");
			/* END of Ow-Cheat Critical Hit */

			/* START of Ow-Cheat hyperFlick */ //Probs outdated
			DELDIR(drive + S(":\\Users\\") + USER + S("\\AppData\\Local\\Temp\\")); //due some User reports, we found out that they save/leave traces on your Pc inside the Temp folder! Credits you know
			/* END of Ow-Cheat hyperFlick */

			/* START of Ow-Cheat Oreo */
			DELFILE(drive + S(":\\Users\\") + USER + S("\\AppData\\Roaming\\")); //due some User reports, we found out that they save/leave traces on your Pc inside the Temp folder! Credits you know
			/* END of Ow-Cheat Oreo */
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