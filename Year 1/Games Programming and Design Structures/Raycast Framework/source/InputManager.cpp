//Precompiled Header File
#include <stdafx.h>

//Header File
#include "InputManager.h"

//Instance
InputManager* InputManager::m_instance = nullptr;

//Create Singleton Instance
InputManager* InputManager::CreateInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new InputManager();
	}

	return m_instance;
}

//Destory Singleton Instance
void InputManager::DestoryInstance()
{
	if (m_instance != nullptr)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}

//Constructor
InputManager::InputManager()
{
	memset(m_keyCurrentState, 0, 256);
}

//Handles CallBacks from Window
LRESULT CALLBACK InputManager::HandleWindowCallbacks(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	PAINTSTRUCT paintStruct;
	HDC hDC;
	Renderer* renderer = Renderer::GetInstance();

	if (hwnd == renderer->GetWindowHandle())
	{
		switch (message)
		{
			case WM_PAINT: 
			{
				hDC = BeginPaint(hwnd, &paintStruct);

				RECT clRect;
				GetClientRect(hwnd, &clRect);
				BitBlt(hDC, clRect.left, clRect.top, (clRect.right - clRect.left) + 1, (clRect.bottom - clRect.top) + 1, renderer->GetBufferContext(), 0, 0, SRCCOPY);

				EndPaint(hwnd, &paintStruct);
				break;
			}
			case WM_DESTROY:
			{
				PostQuitMessage(0);
				break;
			}
			case WM_KEYDOWN:
			{
				InputManager* im = InputManager::GetInstance();
				im->SetKey((u8)wParam, true);
				break;
			}
			case WM_KEYUP:
			{
				InputManager* im = InputManager::GetInstance();
				im->SetKey((u8)wParam, false);
				break;
			}
			default:
			{
				return DefWindowProc(hwnd, message, wParam, lParam);
			};
		}
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

//Sets a Key True or False
void InputManager::SetKey(u8 a_key, bool a_value)
{
	m_keyCurrentState[a_key] = a_value;
}

//Checks if the Key Pressed is True or False
bool InputManager::GetKeyDown(u8 a_key)
{
	return m_keyCurrentState[a_key];
}