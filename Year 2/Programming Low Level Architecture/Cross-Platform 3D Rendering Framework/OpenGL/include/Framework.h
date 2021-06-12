#pragma once

#include <string>
#include <Windows.h>

struct GLFWwindow;

class Framework
{
public:
	Framework() : m_window(nullptr), m_windowWidth(0), m_windowHeight(0), m_running(false){}
	virtual ~Framework(){}
	
	bool Create(unsigned int a_windowWidth, unsigned int a_windowHeight, std::string a_windowName, bool a_fullscreen);
	void Run(unsigned int a_windowWidth, unsigned int a_windowHeight, const char* a_windowName, bool a_fullscreen);
	void Quit() { m_running = false; }
protected:
	virtual bool OnCreate() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;
	virtual void Destroy() = 0;

	GLFWwindow* m_window;
	unsigned int m_windowWidth;
	unsigned int m_windowHeight;

	HWND m_consoleWindow;

	bool m_running;
};