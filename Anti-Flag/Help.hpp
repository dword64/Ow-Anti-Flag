/*
	Successor of Anti-Flag and Anti-Flag-V2.

	Developers:
	- DWORD64
	- Sixmax
*/

#pragma once

#pragma comment(lib, "Shlwapi.lib")
#include <Shlwapi.h>

#include <fstream>
#include <iostream>
#include <sstream> 
#include <functional>
#include <Windows.h>
#include <locale>
#include <codecvt>
#include <filesystem>

#include "WinColor.hpp"
#include "System.hpp"

#pragma warning(disable : 4996)

namespace
{
	using namespace colorwin;

	static const char alphanum[] = "0123456789" "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "abcdefghijklmnopqrstuvwxyz";

	class Help
	{
		
	public:
		static int random255()
		{
			return alphanum[rand() % (sizeof(alphanum) - 1)];
		}

		static std::string CurUser()
		{
			wchar_t un[256 + 1];
			DWORD unLen = 256 + 1;
			GetUserNameW(un, &unLen);
			return ws2s(un);
		}

		static LPCWSTR StringToWStr(std::string s)
		{
			std::wstring stemp = std::wstring(s.begin(), s.end());
			LPCWSTR sw = stemp.c_str();
			return sw;
		}

		static std::wstring s2ws(const std::string& str)
		{
			using convert_typeX = std::codecvt_utf8<wchar_t>;
			std::wstring_convert<convert_typeX, wchar_t> converterX;

			return converterX.from_bytes(str);
		}

		static std::string ws2s(const std::wstring& wstr)
		{
			using convert_typeX = std::codecvt_utf8<wchar_t>;
			std::wstring_convert<convert_typeX, wchar_t> converterX;

			return converterX.to_bytes(wstr);
		}

		static std::string* readFile(const char* path)
		{
			std::ifstream ifs(path);

			if (!ifs)
				return nullptr;

			return new std::string((std::istreambuf_iterator<char>(ifs)),(std::istreambuf_iterator<char>()));
		}

		static std::vector<std::string> split(const std::string& s, char seperator)
		{
			std::vector<std::string> output;

			std::string::size_type prev_pos = 0, pos = 0;

			while ((pos = s.find(seperator, pos)) != std::string::npos)
			{
				std::string substring(s.substr(prev_pos, pos - prev_pos));

				output.push_back(substring);

				prev_pos = ++pos;
			}

			output.push_back(s.substr(prev_pos, pos - prev_pos)); // Last word

			return output;
		}

		static void EnumDrives(std::function<void(char)> callback)
		{
			const char drives[] = "CDEFGHIJKLMNOPQRSTUVWXYZ";

			for (char drive : drives)
			{
				std::string cs = std::string(drive + std::string(":\\"));
				
				if (FolderExists(cs.c_str()) == false)
					break;
				
				callback(drive);

			}
		}

		static void RegDel(const char* key)
		{
#if _DEBUG 
			Cmd::Run(std::string(std::string("reg delete \"") + key + std::string("\" /f")).c_str());
#else 
			Cmd::RunSilent(std::string(std::string("reg delete \"") + key + std::string("\" /f")).c_str());
#endif 
		}

		static bool FolderExists(const char* dir)
		{
			return PathIsDirectoryA(dir);
		}

		static bool FileExists(const char* dir)
		{
			std::filesystem::path p = std::string(dir);

			return std::filesystem::exists(p);
		}

		static bool DelFile(std::string dir)
		{
			if (dir.empty())
				return false;

			if (FileExists(dir.c_str()) == false)
				return false;

			return DeleteFileW(s2ws(dir).c_str());
		}

		static void RemDir(std::string dir)
		{
			if (dir.empty())
				return;

			if (FolderExists(dir.c_str()) == false)
				return;

			if (ends_with(dir, "\\"))
				dir = dir.substr(0, dir.length() - 1);

#if _DEBUG 
			std::cout << dir << std::endl;

			Cmd::Run(std::string(std::string("rd /s /q \"") + dir + std::string("\"")).c_str());
#else 
			Cmd::RunSilent(std::string(std::string("rd /s /q \"") + dir + std::string("\"")).c_str());
#endif 
			/*
			auto hash = std::hash<std::string>{}(dir);
			std::cout << color(dark_gray) << "Patched: " << color(green) << hash << std::endl;
			withcolor reset(white);
			*/
		}
	};
}

#define USER Help::CurUser()
#define FILEEXIST(path) Help::FileExists(path)
#define DIREXIST(path) Help::FolderExists(path)
#define DELFILE(path) Help::DelFile(path)
#define DELDIR(path) Help::RemDir(path)
#define REGDEL(path) Help::RegDel(path)
#define S(str) std::string(str)


/*
	Successor of Anti-Flag and Anti-Flag-V2.

	Developers:
	- DWORD64
	- Sixmax
*/