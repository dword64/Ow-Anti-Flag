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

	class Networking
	{
	public:
		static void Patch(char drive)
		{
			if (drive != 'C')
				return;

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
		}
	};
}

/*
	Successor of Anti-Flag and Anti-Flag-V2.

	Developers:
	- DWORD64
	- Sixmax
*/