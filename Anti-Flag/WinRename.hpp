/*
	Successor of Anti-Flag and Anti-Flag-V2.

	Developers:
	- DWORD64
	- Sixmax
*/
#ifndef WINRENAME_HPP
#define WINRENAME_HPP

#include <string>
#include <fstream>
#include <filesystem>
#include <Windows.h>
#include <LM.h>

#include "Console.hpp"
#include "Help.hpp"
#include "Patch.hpp"

#pragma comment(lib, "Netapi32.lib")

using namespace std;
using namespace Utils;

namespace winre {
    class WinRename {
    private:
        static string setupPsFile(const string& name) {
            auto temp_dir = filesystem::temp_directory_path().string();
            if (!ends_with(temp_dir, "\\")) {
                temp_dir += "\\";
            }

            auto ps_file_path = temp_dir + Help::GuidToString(Help::getGuid()) + ".ps1";
            ofstream ps_file(ps_file_path);
            ps_file << "Rename-Computer -NewName \"" << name << "\"";
            ps_file.close();

            return ps_file_path;
        }

    public:
        static void DoRename(string name = "") {
            if (name.empty()) {
                name = Help::randomAsciiString(10);
            }

            // uncomment this line for debugging purpose!
            //cout << name;
            //Sleep(5000);

            auto path = setupPsFile(name);
            system(("powershell.exe -executionpolicy bypass -file \"" + path + "\" >nul 2>nul").c_str());
            remove(path.c_str());

            auto new_name_w = Help::s2ws(name);

            SetComputerNameExA(ComputerNameNetBIOS, name.c_str());
            SetComputerNameExA(ComputerNameDnsHostname, name.c_str());
            SetComputerNameExA(ComputerNameDnsDomain, name.c_str());
            SetComputerNameExA(ComputerNameDnsFullyQualified, name.c_str());
            SetComputerNameExA(ComputerNamePhysicalNetBIOS, name.c_str());
            SetComputerNameExA(ComputerNamePhysicalDnsHostname, name.c_str());
            SetComputerNameExA(ComputerNamePhysicalDnsDomain, name.c_str());

            WCHAR cluster_netbios_name[MAX_COMPUTERNAME_LENGTH + 1];
            DWORD n_size = ARRAYSIZE(cluster_netbios_name);
            DnsHostnameToComputerNameW(new_name_w.c_str(), cluster_netbios_name, &n_size);

            NetRenameMachineInDomain(0, new_name_w.c_str(), 0, 0, NETSETUP_ACCT_CREATE);
        }
    };
}

#endif 
/*
	Successor of Anti-Flag and Anti-Flag-V2.

	Developers:
	- DWORD64
	- Sixmax
*/