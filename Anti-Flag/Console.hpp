/*
	Successor of Anti-Flag and Anti-Flag-V2.

	Developers:
	- DWORD64
	- Sixmax
*/

#pragma once

class Console;

#include <Windows.h>
#include <cstdio>
#include <string>

#include "WinColor.hpp"
#include "Help.hpp"

namespace
{
	using namespace std;
	using namespace colorwin;

	enum class LogType
	{
		Success,
		Warning,
		Error,
		Info
	};

	class Console
	{
	public:
		static void Log(const char* message, LogType type = LogType::Success)
		{
			unsigned char symbol;
			CW_COLORS col;

			switch (type)
			{
			case LogType::Success:
			default:
				symbol = (unsigned char)'+';
				col = green;
				break;

			case LogType::Warning:
				symbol = (unsigned char)'!';
				col = yellow;
				break;

			case LogType::Error:
				symbol = (unsigned char)'-';
				col = red;
				break;

			case LogType::Info:
				symbol = (unsigned char)'#';
				col = blue;
				break;
			}

			HWND handle = getHandle();

			{ // print time n shit 
				withcolor timeColor(dark_gray);

				SYSTEMTIME st;
				GetSystemTime(&st);
				printf("[%02d:%02d:%02d] ", st.wHour, st.wMinute, st.wSecond);
			}

			withcolor defaultWhite(white);

			cout << "[" << color(col) << symbol << color(white) << "] " << color(grey) << message << endl;
		}

		static HWND getHandle()
		{
			return GetConsoleWindow();
		}

		static RECT getRect()
		{
			RECT r;
			GetWindowRect(getHandle(), &r);
			return r;
		}

		static void CentralizeConsole()
		{
			HWND handle = getHandle();

			DWORD style = GetWindowLong(handle, GWL_STYLE);
			style &= ~WS_MAXIMIZEBOX & ~WS_SIZEBOX;
			SetWindowLong(handle, GWL_STYLE, style);
			
			RECT rc = getRect();
			int xPos = (GetSystemMetrics(SM_CXSCREEN) - rc.right) / 2;
			int yPos = (GetSystemMetrics(SM_CYSCREEN) - rc.bottom) / 2;
			
			SetWindowPos(handle, 0, xPos, yPos, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		}

		static void setTitle(const char* name)
		{
			SetConsoleTitleA(name);
		}

		static void randomizeTitle(int length = 20)
		{
			string name;

			for (int i = 0; i < length; i++)
				name += (char)Help::randomAsciiChar();
			
			setTitle(name.c_str());
		}

		static void Clear()
		{
			COORD topLeft = { 0, 0 };
			HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
			CONSOLE_SCREEN_BUFFER_INFO screen;
			DWORD written;

			GetConsoleScreenBufferInfo(console, &screen);
			FillConsoleOutputCharacterA(console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
			FillConsoleOutputAttribute(console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE, screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
			SetConsoleCursorPosition(console, topLeft);
		}
	};
}

/*
	Successor of Anti-Flag and Anti-Flag-V2.

	Developers:
	- DWORD64
	- Sixmax
*/
