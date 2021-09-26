/*
	Successor of Anti-Flag and Anti-Flag-V2.

	Developers:
	- DWORD64
	- Sixmax
*/

#pragma once

#include "Patch.hpp"
#include "Console.hpp"

namespace
{
	using namespace std;

	class Networking : public IPatch
	{
	public:
		std::string GetID()
		{
			return "Networking";
		}

		list<string>* GetProcesses()
		{
			return new list<string>{
			};
		}

		bool DoPatch(char drive)
		{
			Cmd::RunSilent("netsh winsock reset");
			Cmd::RunSilent("netsh winsock reset catalog");
			Cmd::RunSilent("netsh int ip reset");
			Cmd::RunSilent("netsh advfirewall reset");
			Cmd::RunSilent("netsh int reset all");
			Cmd::RunSilent("netsh int ipv4 reset");
			Cmd::RunSilent("netsh int ipv6 reset");
			Cmd::RunSilent("ipconfig / release");
			Cmd::RunSilent("ipconfig / renew");
			Cmd::RunSilent("ipconfig / flushdns");

			//BraveCookies
			DELFILE(drive + S(":\\Users\\") + USER + S("\\AppData\\Local\\BraveSoftware\\Brave - Browser\\User Data\Default\\Cookies"));

			//chromeCookies
			DELFILE(drive + S(":\\Users\\") + USER + S("\\AppData\\Local\\Google\\Chrome\\User Data\\Default\\Cookies"));

			//operaCookies
			DELFILE(drive + S(":\\Users\\") + USER + S("\\AppData\\Local\\Opera Software\\Opera Stable\\Cookies"));

			//firefoxCookies
			//do we need a loop?
			
			// "\\AppData\\Local\\Mozilla\Firefox\Profiles\<irgendein ordner>\cookies.sqlite"


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