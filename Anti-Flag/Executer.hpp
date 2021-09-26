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

#include "Net.hpp"

#define NEWLINE cout << endl;

namespace
{
    using namespace std;
    using namespace colorwin;

    void PrintWatermark(CW_COLORS color = red)
    {
        withcolor watermarkColor(color);

        /*
        string* watermark = Help::readFile("./watermark.txt");
        if (watermark == nullptr)
        {
            delete watermark;
            Console::Log("Failed to get Watermark!", LogType::Error);
            return;
        }
        cout << (*watermark) << endl << endl;

        delete watermark;
        */

        const wchar_t* Blank = L"\r\n";
        const wchar_t* Top1 = L"  ______            _______  _______  ______        _  \r\n";
        const wchar_t* Top2 = L" (  __  \\ |\\     /|(  ___  )(  ____ )(  __  \\      ( )  \r\n";
        const wchar_t* Tp3 = L" | (  \\  )| )   ( || (   ) || (    )|| (  \\  )     | | \r\n";
        const wchar_t* Tp4 = L" | |   ) || | _ | || |   | || (____)|| |   ) |   __| |\r\n";
        const wchar_t* Tp5 = L" | |   | || |( )| || |   | ||     __)| |   | |  (__   __)\r\n";
        const wchar_t* Tp6 = L" | |   ) || || || || |   | || (\\ (   | |   ) |     | |\r\n";
        const wchar_t* Tp7 = L" | (__/  )| () () || (___) || ) \\ \\__| (__/  )     | |\r\n";
        const wchar_t* Tp8 = L" (______/ (_______)(_______)|/   \\__/(______/      (_) \r\n";
        const wchar_t* Tp9 = L"\r\n";
        const wchar_t* Tp10 = L"  _______ _________          _______  _______          \r\n";
        const wchar_t* Tp11 = L" (  ____ \\\\__   __/|\\     /|(       )(  ___  )|\\     /|\r\n";
        const wchar_t* Tp12 = L" | (    \\/   ) (   ( \\   / )| () () || (   ) |( \\   / )\r\n";
        const wchar_t* Tp13 = L" | (_____    | |    \\ (_) / | || || || (___) | \\ (_) /\r\n";
        const wchar_t* Tp14 = L" (_____  )   | |     ) _ (  | |(_)| ||  ___  |  ) _ (\r\n";
        const wchar_t* Tp15 = L"       ) |   | |    / ( ) \\ | |   | || (   ) | / ( ) \\ \r\n";
        const wchar_t* Tp16 = L" /\\____) |___) (___( /   \\ )| )   ( || )   ( |( /   \\ ) \r\n";
        const wchar_t* Tp17 = L" \\_______)\\_______/|/     \\||/     \\||/     \\||/     \\|\r\n";


        WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), Blank, wcslen(Blank), 0, 0);
        WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), Top1, wcslen(Top1), 0, 0);
        WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), Top2, wcslen(Top2), 0, 0);
        WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), Tp3, wcslen(Tp3), 0, 0);
        WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), Tp4, wcslen(Tp4), 0, 0);
        WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), Tp5, wcslen(Tp5), 0, 0);
        WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), Tp6, wcslen(Tp6), 0, 0);
        WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), Tp7, wcslen(Tp7), 0, 0);
        WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), Tp8, wcslen(Tp8), 0, 0);
        WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), Tp9, wcslen(Tp9), 0, 0);
        WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), Tp10, wcslen(Tp10), 0, 0);
        WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), Tp11, wcslen(Tp11), 0, 0);
        WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), Tp12, wcslen(Tp12), 0, 0);
        WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), Tp13, wcslen(Tp13), 0, 0);
        WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), Tp14, wcslen(Tp14), 0, 0);
        WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), Tp15, wcslen(Tp15), 0, 0);
        WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), Tp16, wcslen(Tp16), 0, 0);
        WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), Tp17, wcslen(Tp17), 0, 0);

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
            Console::CentralizeConsole();
            Console::randomizeTitle();

            PrintWatermark();

                return 0;

                /*
#if !_DEBUG
                Console::Log("Are you sure you want to run this program? [Y/N]", LogType::Info);
                if (tolower(cin.get()) != 'y')
                {
                    Console::Log("Done.");
                    return 0;
                }
#endif
*/

                list<IPatch*>* patches = new list<IPatch*>
                {
                    new Overwatch,
                    new Networking
                };


                NEWLINE


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


                NEWLINE


#pragma region Patching
                    Console::Log("Patching...", LogType::Warning);

                for_each(patches->begin(), patches->end(), [](IPatch* patch)
                    {
                        Help::EnumDrives([=](char drive)
                            {

                                Console::Log(string("Patching: '" + patch->GetID()).c_str(), LogType::Info);

                                patch->DoPatch(drive);

                                Console::Log(string("Finished patching " + patch->GetID()).c_str(), LogType::Success);

                                NEWLINE

                            });
                    });

                Console::Log("Done patching.", LogType::Info);
#pragma endregion


                NEWLINE


#pragma region Cleanup
                    for (IPatch* patch : *patches)
                        delete patch;

                patches->clear();

                delete patches;
#pragma endregion

                /*
                char a = 2;
                auto test = [a](char poop) mutable {
                    a++;
                };
                */


                Console::Log("Finished.", LogType::Info);
            

            NEWLINE

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