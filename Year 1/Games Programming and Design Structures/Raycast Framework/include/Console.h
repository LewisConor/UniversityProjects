#pragma once
#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <stdafx.h>

class Console
{
public:
	//Constructor and Destructor
	Console();
	~Console();

	//Initalise Function
	bool Initaialise(const char* a_windowTitle, const unsigned short a_xPos = 0, const unsigned short a_yPos = 0, const unsigned short a_width = 0, const unsigned short a_height = 0);

	//Write to Console
	unsigned int WriteToLocation(wchar_t* a_data, short a_dataLength, short a_xPos, short a_yPos);

	//Return Console Window
	HWND GetConsoleWindowHandle() { return m_consoleWindow; }
private:
	unsigned short m_xPos;
	unsigned short m_yPos;
	unsigned short m_consoleWidth;
	unsigned short m_consoleHeight;

	HANDLE m_consoleHandle;
	HWND m_consoleWindow;
};

#endif //__CONSOLE_H__