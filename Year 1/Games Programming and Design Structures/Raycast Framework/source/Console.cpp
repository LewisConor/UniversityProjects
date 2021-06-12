//Precompiled Header File
#include <stdafx.h>

//Header File
#include "Console.h"

//Constructor
Console::Console() : m_xPos(0), m_yPos(0), m_consoleWidth(0), m_consoleHeight(0), m_consoleHandle(nullptr), m_consoleWindow(nullptr) { }

//Destructor
Console::~Console() { }

//Initalise Console Window
bool Console::Initaialise(const char* a_windowTitle, const unsigned short a_xPos, const unsigned short a_yPos, const unsigned short a_width, const unsigned short a_height)
{
	m_xPos = a_xPos ? a_xPos : CONSOLE_X_POS;
	m_yPos = a_yPos ? a_yPos : CONSOLE_Y_POS;
	m_consoleWidth = a_width ? a_width : CONSOLE_WIDTH;
	m_consoleHeight = a_height ? a_height : CONSOLE_HEIGHT;

	//Windows code to create Screen Buffer
	m_consoleHandle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(m_consoleHandle);
	
	COORD consoleSize = { (short)m_consoleWidth, (short)m_consoleHeight };
	SetConsoleScreenBufferSize(m_consoleHandle, consoleSize);

	SetConsoleTitle(a_windowTitle);

	m_consoleWindow = GetConsoleWindow();
	SetWindowPos(m_consoleWindow, 0, 20, 180, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	return true;
}

//Writes to the Console
unsigned int Console::WriteToLocation(wchar_t* a_data, short a_numCharacters, short a_xPos, short a_yPos)
{
	DWORD dwBytesWritten = 0;

	WriteConsoleOutputCharacter(m_consoleHandle, (LPCSTR)a_data, a_numCharacters * sizeof(wchar_t), { a_xPos, a_yPos }, &dwBytesWritten);

	return dwBytesWritten;
}