//Precompiled Header File
#include <stdafx.h>

//Header File
#include "Renderer.h"

//Renderer Instance
Renderer* Renderer::m_instance = nullptr;

//Constructor
Renderer::Renderer() : m_windowWidth(0), m_windowHeight(0), m_windowHandle(nullptr), m_windowDC(nullptr), m_bmpInfo(nullptr), m_bitBuffer(nullptr), m_bmpBuffer(nullptr), m_bufferDC(nullptr), m_bitmapHandle(nullptr)
{
	m_instance = this;
}

//Destructor
Renderer::~Renderer()
{
	m_instance = nullptr;
}

//Initaliser
int Renderer::Initialise(HWND a_consoleWindow, const char* a_windowTitle, unsigned int a_windowWidth, unsigned int a_windowHeight)
{
	m_windowWidth = a_windowWidth;
	m_windowHeight = a_windowHeight;

	//Creates the Window Class
	WNDCLASSEX wndClass = { 0 };
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = InputManager::GetInstance()->HandleWindowCallbacks;
	wndClass.hInstance = (HINSTANCE)GetModuleHandle(NULL);
	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
	wndClass.lpszMenuName = nullptr;
	wndClass.lpszClassName = "Raycaster Framework";

	if (!RegisterClassEx(&wndClass))
	{
		return 1;
	}

	//Setup Window
	LONG x = 0, y = 0;
	RECT consoleRect = { NULL };

	if (GetWindowRect(a_consoleWindow, &consoleRect))
	{
		x = consoleRect.right;
		y = consoleRect.top;
	}

	RECT windowRect = { x, y, x + (LONG)m_windowWidth, y + (LONG)m_windowHeight };
	AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

	//Creates the Window and Shows it
	m_windowHandle = CreateWindowA("Raycaster Framework", a_windowTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, nullptr, nullptr, (HINSTANCE)GetModuleHandle(NULL), nullptr);
	ShowWindow(m_windowHandle, SW_SHOW);
	MoveWindow(m_windowHandle, x, y, m_windowWidth, m_windowHeight, TRUE);

	//Create Back Buffer Rendering Target
	m_windowDC = GetDC(m_windowHandle);

	if (m_windowDC == nullptr)
	{
		return 1;
	}

	//Create a Bite Size Array for Bitmap Info Header
	char* data = (char*)malloc(sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD));
	if (data != nullptr)
	{
		m_bmpInfo = (BITMAPINFO*)data;
		m_bmpInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		m_bmpInfo->bmiHeader.biWidth = (LONG)m_windowWidth;
		m_bmpInfo->bmiHeader.biHeight = -(LONG)m_windowHeight;
		m_bmpInfo->bmiHeader.biBitCount = 32;
		m_bmpInfo->bmiHeader.biPlanes = 1;
		m_bmpInfo->bmiHeader.biCompression = BI_RGB;
		m_bmpInfo->bmiHeader.biSizeImage = 0;
		m_bmpInfo->bmiHeader.biXPelsPerMeter = 0;
		m_bmpInfo->bmiHeader.biYPelsPerMeter = 0;
		m_bmpInfo->bmiHeader.biClrUsed = 0;
		m_bmpInfo->bmiHeader.biClrImportant = 0;

		m_bmpBuffer = CreateDIBSection(m_windowDC, m_bmpInfo, DIB_RGB_COLORS, &m_bitBuffer, NULL, 0);
		
		if (m_bmpBuffer == nullptr)
		{
			free(data);
			return 1;
		}

		m_bufferDC = CreateCompatibleDC(m_windowDC);

		if (m_bufferDC == nullptr)
		{
			free(data);
			return 1;
		}

		m_bitmapHandle = (HBITMAP)SelectObject(m_bufferDC, m_bmpBuffer);

		if (m_bitmapHandle == nullptr)
		{
			free(data);
			return 1;
		}

		free(data);
		return 0;
	}
	
	return 1;
}

//Clear Window Background
void Renderer::ClearRenderBuffer()
{
	RECT clRect;
	GetClientRect(m_windowHandle, &clRect);

	FillRect(m_bufferDC, &clRect, (HBRUSH)(0x0000) + 2);
}

//Fill Render Buffer with Data
void Renderer::FillRenderBuffer(const unsigned int& a_x, const unsigned int& a_y, const unsigned int& a_width, const unsigned int& a_height, const void* a_data)
{
	unsigned int* backBuffer = (unsigned int*)m_bitBuffer;
	unsigned int* imageData = (unsigned int*)a_data;
	unsigned int index = a_x + (a_y * m_windowWidth);

	if (index < (m_windowWidth * m_windowHeight))
	{
		//Copy Row Data to Bitmap Buffer
		for (unsigned int y = 0; y < a_height; ++y)
		{
			if (a_y + y < m_windowHeight)
			{
				unsigned int bytesToCopy = BYTES_PER_PIXEL * a_width;
				if (a_x + a_width > m_windowWidth)
				{
					bytesToCopy = (a_width - ((a_x + a_width) - m_windowWidth)) * BYTES_PER_PIXEL;
				}
				index = a_x + ((a_y + y) * m_windowWidth);
				memcpy(&backBuffer[index], &imageData[y * a_width], bytesToCopy);
			}
		}
	}
}

//Fill Render Buffer with Colour
void Renderer::FillRenderBuffer(const unsigned int& a_x, const unsigned int& a_y, const unsigned int& a_width, const unsigned int& a_height, const u32 a_colour)
{
	unsigned int index = a_x + (a_y * m_windowWidth);

	if (index < (m_windowWidth * m_windowHeight))
	{
		unsigned int* backBuffer = (unsigned int*)m_bitBuffer;
		unsigned int pixelsToFill = a_width;

		if ((a_x + a_width) > m_windowWidth)
		{
			pixelsToFill = (a_width - ((a_x + a_width) - m_windowWidth));
		}

		u32* rowBuffer = new u32[pixelsToFill];

		for (u32 i = 0; i < pixelsToFill; i++)
		{
			rowBuffer[i] = a_colour;
		}

		for (unsigned int y = 0; y < a_height; ++y)
		{
			index = a_x + ((a_y + y) * m_windowWidth);

			if ((a_y + y) < m_windowHeight)
			{
				memcpy(&backBuffer[index], rowBuffer, pixelsToFill * BYTES_PER_PIXEL);
				continue;
			}
			break;
		}

		delete[] rowBuffer;
	}
}

//Redraws all elements on Renderer Window
void Renderer::Draw()
{
	RedrawWindow(m_windowHandle, nullptr, nullptr, RDW_INVALIDATE);
}

//Draws Background
void Renderer::DrawBackground()
{
	unsigned int ceilingColour = 0x00505050;
	unsigned int floorColour = 0x00B2B2B2;

	FillRenderBuffer(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT / 2, ceilingColour);
	FillRenderBuffer(0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT, floorColour);
}