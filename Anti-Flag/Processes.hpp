/*
	killing and handling of processes 

*/


/*
    Successor of Anti-Flag and Anti-Flag-V2.

    Developers:
    - DWORD64
    - Sixmax
*/

#pragma once

#include <windows.h>
#include <process.h>
#include <Tlhelp32.h>
#include <winbase.h>
#include <list>
#include <string>
#include <comdef.h>

#include "System.hpp"
#include "Extensions.hpp"

namespace
{
    using namespace std;

    class ProcessHandler
    {
    public:
        static bool killByName(string processName)
        {
            if (processName.empty())
                return false;

            if (ends_with(processName, ".exe") == false)
                processName += ".exe";

            HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);

            if (!snap)
                return false;

            bool procKilled = false;

            PROCESSENTRY32 entry;
            entry.dwSize = sizeof(entry);

            BOOL hasProcess = Process32First(snap, &entry);

            while (hasProcess)
            {
                _bstr_t xf = entry.szExeFile;

                if (toLowerStr(string(xf)) != toLowerStr(processName))
                {
                    hasProcess = Process32Next(snap, &entry);
                    continue;
                }

                HANDLE procHandle = OpenProcess(PROCESS_TERMINATE, false, (DWORD)entry.th32ProcessID);

                if (procHandle == NULL)
                {
                    hasProcess = Process32Next(snap, &entry);
                    continue;
                }

                procKilled = TerminateProcess(procHandle, 1);

                // if it fails to close like that, take a hammer and bash its head in.
                if (procKilled == false)
                {
                    string cmd;

                    cmd += "taskkill /f /t /pid ";
                    cmd += to_string(long long(entry.th32ProcessID));

                    Cmd::RunSilent(cmd.c_str());
                }

                CloseHandle(procHandle);

                hasProcess = Process32Next(snap, &entry);
            }

            CloseHandle(snap);

            return procKilled;
        }
    };
}
/*
    Successor of Anti-Flag and Anti-Flag-V2.

    Developers:
    - DWORD64
    - Sixmax
*/