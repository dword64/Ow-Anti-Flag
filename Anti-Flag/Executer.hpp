/*
I put this in its own class/file because "using namespace ..." was being weird in the global scope.
So I decided to put it into a new file/class to put it in an anonymous namespace and evade these issues :)
*/

/*
    Successor of Anti-Flag and Anti-Flag-V2.

    Developers:
    - DWORD64
    - Sixmax
*/

#pragma once 

#include <Windows.h>
#include <iostream>
#include <algorithm>

#include "Console.hpp"
#include "WinColor.hpp"

#include "System.hpp"
#include "Processes.hpp"

#include "Extensions.hpp"

#include "Patch.hpp"

#include "Overwatch.hpp"
#include "WinRename.hpp"
#include "Net.hpp"
#include "Cookies.hpp"

#define NEWLINE cout << endl;

namespace
{
    using namespace std;
    using namespace colorwin;

    void PrintWatermark(CW_COLORS color = red)
    {
        withcolor watermarkColor(color);

        std::string antiflag = R"(_______       __________      _______________               
___    |________  /___(_)     ___  ____/__  /_____ _______ _
__  /| |_  __ \  __/_  /________  /_   __  /_  __ `/_  __ `/
_  ___ |  / / / /_ _  /_/_____/  __/   _  / / /_/ /_  /_/ / 
/_/  |_/_/ /_/\__/ /_/        /_/      /_/  \__,_/ _\__, /  
                                                   /____/   
)";
        std::cout << antiflag << std::endl;

        withcolor byColor(white);
        std::cout << "By" << std::endl;

        withcolor avalonColor(blue);
        std::string avalon = R"(
   ___            __            _____                 
  / _ |_  _____ _/ /__  ___    / ___/______  __ _____ 
 / __ | |/ / _ `/ / _ \/ _ \  / (_ / __/ _ \/ // / _ \
/_/ |_|___/\_,_/_/\___/_//_/  \___/_/  \___/\_,_/ .__/
                                               /_/    )";

        std::cout << avalon << std::endl;

        std::cout << std::endl << std::endl << std::endl;

        std::cout << colorwin::color(red) << "WARNING:" << std::endl;
        std::cout << colorwin::color(yellow) << "all instances of 'Overwatch' and 'Battle.Net' will be closed." << std::endl;
        std::cout << colorwin::color(yellow) << "Also your Browser Cookies will be cleared, so make sure you have all your Login's saved." << std::endl;

        std::cout << std::endl;

        withcolor reset(white);
    }

    class Exe
    {
    public:
        static int run()
        {
            std::srand((unsigned)time(NULL));

            Console::CentralizeConsole();
            Console::randomizeTitle();

            PrintWatermark();

#if !_DEBUG
            Console::Log("Are you sure you want to run this program? [Y/N]", LogType::Info);
            if (tolower(cin.get()) != 'y')
            {
                Console::Log("Done.");
                return 0;
            }
#endif

            list<IPatch*>* patches = new list<IPatch*>
            {
                new Overwatch,
                new Cookies
            };


            NEWLINE;


#pragma region Process Killer
            Console::Log("Killing Processes...", LogType::Warning);

            for_each(patches->begin(), patches->end(), [](IPatch* patch)
                {
                    list<string>* procs = patch->GetProcesses();

                    for (string proc : *procs)
                    {
                        if (ProcessHandler::killByName(proc))
                        {
                            Console::Log(string("Killed '" + proc + "'.").c_str(), LogType::Success);
                        }
                    }

                    delete procs;
                });

            Console::Log("Done killing.", LogType::Info);
#pragma endregion


            NEWLINE;


#pragma region Patching
            Console::Log("Patching...", LogType::Warning);

            for_each(patches->begin(), patches->end(), [](IPatch* patch)
                {
                    Help::EnumDrives([=](char drive)
                        {
                            Console::Log(string("Running Patch: '" + patch->GetID() + "' for Drive '" + drive + "'").c_str(), LogType::Info);

                            patch->DoPatch(drive);

                            Console::Log(string("Finished Patch: " + patch->GetID()).c_str(), LogType::Success);

                            NEWLINE;
                        });
                });

            Console::Log("Done patching.", LogType::Info);
#pragma endregion

            NEWLINE;

            Console::Log("Renaming Windows...", LogType::Info);

            winre::WinRename::DoRename(Help::randomAsciiString(10));

            Console::Log("Windows has been renamed.", LogType::Success);

            NEWLINE;

            Console::Log("Resetting Network Sockets", LogType::Info);

            Networking::Patch('c'); // networking doesnt need to get patched for every drive as its systemwide, so we do it once for C:\

            Console::Log("Network Sockets have been reset.", LogType::Success);

            NEWLINE;

#pragma region Cleanup
            for (IPatch* patch : *patches)
                delete patch;

            patches->clear();

            delete patches;
#pragma endregion

            Console::Log("Finished.", LogType::Info);

            NEWLINE;

            Console::Log("You can RESTART your Computer now to finish the cleaning.", LogType::Info);

#if _DEBUG
            Cmd::Run("pause");
#else 
            Cmd::RunSilent("pause");
#endif 

            return 0;
        }
    };
}

#undef NEWLINE

/*
    Successor of Anti-Flag and Anti-Flag-V2.

    Developers:
    - DWORD64
    - Sixmax
*/
