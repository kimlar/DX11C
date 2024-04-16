#pragma once
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>

#include <assert.h>
#include <stdbool.h>

#include "../Input/Keyboard.h"
#include "../Input/Mouse.h"

static bool global_windowDidResize = true; // To force initial perspectiveMat calculation
static bool window_is_running = true;
HWND hwnd;
int windowWidth, windowHeight;
float windowAspectRatio;

// Prototypes
static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
static bool window_create(HINSTANCE hInstance);
static void window_destroy();
static void window_event_pump();
static void window_get_dimensions();
static void window_center_mouse_position();
static void window_clip_mouse(bool isClipped);

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	LRESULT result = 0;
	switch (msg)
	{
		case WM_KEYDOWN:
		case WM_KEYUP:
		{
			bool isDown = (msg == WM_KEYDOWN);
			if (wparam == VK_ESCAPE)
				DestroyWindow(hwnd);
			else if (wparam == VK_TAB)
			{
				if (!prev_tab_key_is_down)
				{
					//mouse_visible = !mouse_visible;
					window_center_mouse_position();
					window_clip_mouse(mouse_visible);
				}
				prev_tab_key_is_down = isDown;
			}

			// Handle keyboard input
			handle_keyboard_input((unsigned int)wparam, isDown);
			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
		case WM_SIZE:
		{
			global_windowDidResize = true;
			break;
		}
		default:
			result = DefWindowProcW(hwnd, msg, wparam, lparam);
	}
	return result;
}

// Create window
static bool window_create(HINSTANCE hInstance)
{
	WNDCLASSEXW winClass = { 0 };
	winClass.cbSize = sizeof(WNDCLASSEXW);
	winClass.style = CS_HREDRAW | CS_VREDRAW;
	winClass.lpfnWndProc = &WndProc;
	winClass.hInstance = hInstance;
	winClass.hIcon = LoadIconW(0, IDI_APPLICATION);
	winClass.hCursor = LoadCursorW(0, IDC_ARROW);
	winClass.lpszClassName = L"MyWindowClass";
	winClass.hIconSm = LoadIconW(0, IDI_APPLICATION);

	if (!RegisterClassExW(&winClass))
	{
		MessageBoxA(0, "RegisterClassEx failed", "Fatal Error", MB_OK);
		return false; // Failure
	}

	RECT initialRect = { 0, 0, 1024, 768 };
	AdjustWindowRectEx(&initialRect, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_OVERLAPPEDWINDOW);
	LONG initialWidth = initialRect.right - initialRect.left;
	LONG initialHeight = initialRect.bottom - initialRect.top;

	hwnd = CreateWindowExW(WS_EX_OVERLAPPEDWINDOW,
		winClass.lpszClassName,
		L"DirectX Game Template",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT,
		initialWidth,
		initialHeight,
		0, 0, hInstance, 0);

	if (!hwnd)
	{
		MessageBoxA(0, "CreateWindowEx failed", "Fatal Error", MB_OK);
		return false; // Failure
	}

	// Update window dimensions
	window_get_dimensions();

	// Center the mouse position
	window_center_mouse_position();

	// Clip the mouse cursor
	window_clip_mouse(true);

	return true; // Success
}

// Destroy window
static void window_destroy()
{
	window_clip_mouse(false);
}

// Retrieve events
static void window_event_pump()
{
	MSG msg = { 0 };
	while (PeekMessageW(&msg, 0, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
			window_is_running = false;
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
}

// Get window dimensions
static void window_get_dimensions()
{
	RECT clientRect;
	GetClientRect(hwnd, &clientRect);
	windowWidth = clientRect.right - clientRect.left;
	windowHeight = clientRect.bottom - clientRect.top;
	windowAspectRatio = (float)windowWidth / (float)windowHeight;
}

// Center the mouse position
static void window_center_mouse_position()
{
	RECT windowRect;
	GetWindowRect(hwnd, &windowRect);
	mouse_center_x = (unsigned short)(windowRect.left + windowRect.right) / 2;
	mouse_center_y = (unsigned short)(windowRect.top + windowRect.bottom) / 2;
	SetCursorPos(mouse_center_x, mouse_center_y);
}

// Clip the mouse cursor
static void window_clip_mouse(bool isClipped)
{
	if (isClipped)
	{
		int clipLenght = 350;
		RECT clipRect = { mouse_center_x - clipLenght, mouse_center_y - clipLenght, mouse_center_x + clipLenght, mouse_center_y + clipLenght };
		ClipCursor(&clipRect);
		ShowCursor(false);
		mouse_visible = false;
	}
	else
	{
		ClipCursor(NULL);
		ShowCursor(true);
		mouse_visible = true;
	}
}
