/*
    Successor of Anti-Flag and Anti-Flag-V2.

    Developers:
    - DWORD64
    - Sixmax
*/

#if !_WIN32
#include <iostream>
int main()
{
    printf("You can only compile this on and for Windows.\n");
    return 0;
}
#else 
#include "Executer.hpp"
int main()
{
    return Exe::run();
}
#endif

/*
			system(_xor_("taskkill /f /im EpicGamesLauncher.exe >nul 2>&1").c_str());
			system(_xor_("taskkill /f /im FortniteClient-Win64-Shipping.exe >nul 2>&1").c_str());
			system(_xor_("taskkill /f /im OneDrive.exe >nul 2>&1").c_str());
			system(_xor_("taskkill /f /im RustClient.exe >nul 2>&1").c_str());
			system(_xor_("taskkill /f /im Origin.exe >nul 2>&1").c_str());
			system(_xor_("taskkill /f /im r5apex.exe >nul 2>&1").c_str());
			system(_xor_("taskkill /f /im Battle.net.exe >nul 2>&1").c_str());
			system(_xor_("taskkill /f /im Agent.exe >nul 2>&1").c_str());

			KillProcess("Launcher");
			KillProcess("FortniteClient-Win64-Shipping");
			KillProcess("EasyAntiCheat");
			KillProcess("OneDrive");
			KillProcess("dnf");
			KillProcess("DNF");
			KillProcess("CrossProxy");
			KillProcess("tensafe_1");
			KillProcess("TenSafe_1");
			KillProcess("tensafe_2");
			KillProcess("tencentdl");
			KillProcess("TenioDL");
			KillProcess("uishell");
			KillProcess("BackgroundDownloader");
			KillProcess("conime");
			KillProcess("QQDL");
			KillProcess("qqlogin");
			KillProcess("dnfchina");
			KillProcess("dnfchinatest");
			KillProcess("dnf");
			KillProcess("txplatform");
			KillProcess("TXPlatform");
			KillProcess("OriginWebHelperService");
			KillProcess("Origin");
			KillProcess("OriginClientService");
			KillProcess("OriginER");
			KillProcess("OriginThinSetupInternal");
			KillProcess("OriginLegacyCLI");
			KillProcess("OriginLegacyCLI");
			KillProcess("Agent");
			KillProcess("Client");*/

/*
	Successor of Anti-Flag and Anti-Flag-V2.

	Developers:
	- DWORD64
	- Sixmax
*/