//Includes - In-App > External > Windows
#include "Framework.h"
#include "ShaderUtilities.h"
#include "Utilities.h"

#include <glad/glad.h>
#include <GLFW\glfw3.h>

#include <iostream>
#include <string>
#include <Windows.h>

//Creation of Application
bool Framework::Create(unsigned int a_windowWidth, unsigned int a_windowHeight, std::string a_windowName, bool a_fullscreen)
{
	m_consoleWindow = GetConsoleWindow();

	if (!glfwInit()) { return false; }

	m_windowWidth = a_windowWidth;
	m_windowHeight = a_windowHeight;

	m_window = glfwCreateWindow(m_windowWidth, m_windowHeight, a_windowName.c_str() , (a_fullscreen ? glfwGetPrimaryMonitor() : nullptr), nullptr);

	if (!m_window)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(m_window);

	if (!gladLoadGL())
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
		return false;
	}

	int major = glfwGetWindowAttrib(m_window, GLFW_CONTEXT_VERSION_MAJOR);
	int minor = glfwGetWindowAttrib(m_window, GLFW_CONTEXT_VERSION_MINOR);
	int revision = glfwGetWindowAttrib(m_window, GLFW_CONTEXT_REVISION);

	a_windowName += " - OpenGL Version: ";
	a_windowName += std::to_string(major);
	a_windowName += ".";
	a_windowName += std::to_string(minor);
	a_windowName += ".";
	a_windowName += std::to_string(revision);

	glfwSetWindowTitle(m_window, a_windowName.c_str());

	bool result = OnCreate();
	if (result == false)
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}

	return result;
}

//Running the Application
void Framework::Run(unsigned int a_windowWidth, unsigned int a_windowHeight, const char* a_applicationName, bool a_fullscreen)
{
	if (Create(a_windowWidth, a_windowHeight, a_applicationName, a_fullscreen))
	{
		Utilities::ResetTimer();
		m_running = true;

		do
		{
			float deltaTime = Utilities::TickTimer();

			Update(deltaTime);

			Draw();

			glfwSwapBuffers(m_window);
			glfwPollEvents();
		} while (m_running == true && glfwWindowShouldClose(m_window) == 0);



		Destroy();
	}

	ShaderUtilities::DestroyInstance();

	glfwDestroyWindow(m_window);
	glfwTerminate();
}