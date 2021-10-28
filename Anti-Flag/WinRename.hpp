#ifndef WINRENAME_HPP
#define WINRENAME_HPP

#include <string>
#include "Console.hpp"
#include "Help.hpp"
#include "Patch.hpp"

namespace winre
{
    class WinRename
    {
    private:
        static std::string setupPsFile(std::string& name)
        {
            std::string tempDir = std::filesystem::temp_directory_path().string();

            if (ends_with(tempDir, "\\") == false)
                tempDir += "\\";

            std::string psFilePath = tempDir + Help::GuidToString(Help::getGuid()) + std::string(".ps1");

            std::ofstream psFile(psFilePath);
            psFile << "Rename-Computer -NewName \"" << name << "\"";
            psFile.close();

            return psFilePath;
        }

    public:
        static void DoRename(std::string name = "")
        {
            if (name.empty() == true)
                name = Help::randomAsciiString(10);

            std::string path = setupPsFile(name);
            system(std::string("powershell.exe -executionpolicy bypass -file \"" + path + std::string("\" >nul 2>nul")).c_str());
            std::remove(path.c_str());
        }
    };
}

#endif 