#include <stdafx.h>
#pragma once

#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__

class InputManager
{
public:
	//Singleton Accessor
	static InputManager* GetInstance() { return m_instance; }
	//Singleton Creation
	static InputManager* CreateInstance();
	//Destory Instance
	static void DestoryInstance();
	//Window CallBack Handle
	static LRESULT CALLBACK HandleWindowCallbacks(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	//Set Key Value
	void SetKey(u8 a_key, bool a_value);
	//Get Key Down
	bool GetKeyDown(u8 a_key);
private:
	//Instance
	static InputManager* m_instance;
	
	//Constructor / Destructor
	InputManager();
	~InputManager() { };

	//Key Press Array
	bool m_keyCurrentState[256];
};
#endif // !__INPUT_MANAGER_H__
