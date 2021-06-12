#pragma once
#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <stdafx.h>

class Renderer
{
public:
	//Constructor and Destructor
	Renderer();
	~Renderer();

	//Get Renderer Instance
	static Renderer* GetInstance() { return m_instance; }

	//Initialise Function
	int Initialise(HWND a_consoleWindow, const char* a_windowTitle, unsigned int a_windowWidth, unsigned int a_windowHeight);

	//Buffer Functions
	void ClearRenderBuffer();
	void FillRenderBuffer(const unsigned int& a_x, const unsigned int& a_y, const unsigned int& a_width, const unsigned int& a_height, const void* a_data);
	void FillRenderBuffer(const unsigned int& a_x, const unsigned int& a_y, const unsigned int& a_width, const unsigned int& a_height, const u32 a_colour);
	void Draw();
	void DrawBackground();

	HWND GetWindowHandle() const { return m_windowHandle; }
	HDC GetBufferContext() const { return m_bufferDC; }

private:
	static Renderer* m_instance;

	unsigned int m_windowWidth;
	unsigned int m_windowHeight;

	HWND m_windowHandle;
	HDC m_windowDC;
	void* m_bitBuffer;
	BITMAPINFO* m_bmpInfo;
	HBITMAP m_bmpBuffer;
	HDC m_bufferDC;
	HBITMAP m_bitmapHandle;
};

#endif //__RENDERER_H__