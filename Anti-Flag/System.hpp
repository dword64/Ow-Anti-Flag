/*
	Simple Class to wrap System calls and automatically xor them :)
*/

/*
	Successor of Anti-Flag and Anti-Flag-V2.

	Developers:
	- DWORD64
	- Sixmax
*/
#pragma once

#include <Windows.h>
#include <string>

#include "xor.h"
#include "Extensions.hpp"

using namespace std;
using namespace Utils;

namespace 
{
	class Cmd
	{
	private:
		static void WrapXoR(string &cmd)
		{
			try
			{
				char c_cmd[2048];
				strcpy_s(c_cmd, sizeof(c_cmd), cmd.c_str());
				system(_xor_(c_cmd).c_str());
			}
#pragma warning(disable:4101)
			catch (exception& e)
			{
#if _DEBUG
				cout << e.what() << endl;
#endif 
				system(cmd.c_str());
			}
		}

	public:
		static void Run(const char* command)
		{
			string cmd;
			cmd.append(command);
			WrapXoR(cmd);
		}

		static void RunSilent(const char* command)
		{
			string cmd;
			cmd.append(command);
			
			if (ends_with(cmd, ">nul 2>nul") == false)
				cmd += ">nul 2>nul";
			
			WrapXoR(cmd);
		}
	};
}

/*
	Successor of Anti-Flag and Anti-Flag-V2.

	Developers:
	- DWORD64
	- Sixmax
*/