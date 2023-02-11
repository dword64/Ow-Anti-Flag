/*
	Successor of Anti-Flag and Anti-Flag-V2.

	Developers:
	- DWORD64
	- Sixmax
*/
#pragma once 

#include <list>
#include <string>

#include "Console.hpp"
#include "Processes.hpp"

namespace
{
	using namespace std;
	
	class IPatch
	{
	public:
		virtual bool DoPatch(char drive) = 0;
		virtual list<string>* GetProcesses() = 0;
		virtual string GetID() = 0;

		bool PatchAll(char drive)
		{
			list<string>* procs = GetProcesses();

			for (string proc : *procs)
			{
				if (ProcessHandler::killByName(proc))
				{
					Console::Log(string("Killed " + proc + ".").c_str(), LogType::Success);
				}
			}

			delete procs;

			return DoPatch(drive);
		}
	};
}
/*
	Successor of Anti-Flag and Anti-Flag-V2.

	Developers:
	- DWORD64
	- Sixmax
*/