#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>
#include <assert.h>
#include <stdbool.h>

// Game Engine
#include "D3D11/Direct3D.h"
#include "Window/Window.h"
#include "Camera/Camera.h"
#include "Timer/Timer.h"
#include "Scene/SkyBox.h"
#include "Scene/Terrain.h"
#include "GameObject/SpinningQuad.h"
#include "GameObject/WoodenBox.h"
#include "GameObject/Player.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd)
{
    OutputDebugStringA("Hello, World!\n"); // <-- Use dgbview64.exe to see this

	// Create Window
	if (!window_create(hInstance))
	{
		MessageBox(0, L"Window creation failed", L"Error", MB_OK);
		exit(1);
	}

	// Create Direct3D
	if (!direct3d_create())
	{
		MessageBox(0, L"Failed to create Direct3D", L"Error", MB_OK);
		exit(1);
	}

	// Create Sky Box
	if (!sky_box_create())
	{
		exit(1);
	}

	// Create Spinning Quad GameObject
	if (!spinning_quad_create())
	{
		exit(1);
	}

	// Create Wooden Box GameObject
	if (!wooden_box_create())
	{
		exit(1);
	}

	// Create Player GameObject
	if (!player_create())
	{
		exit(1);
	}

	// Create Terrain
	if (!terrain_create())
	{
		exit(1);
	}

    // Reset Camera
	camera_reset();

	// Initialize Timer
	timer_init();
	
    // Main Loop
    while (window_is_running)
    {
		float dt = timer_update();

		// Retrieve events
		window_event_pump();

		// Get window dimensions
		window_get_dimensions();
			
		// Check if window resized
		direct3d_did_resize();

		// Update the player
		player_update(dt);

		// Update camera
		//camera_update(dt);


		// Update the sky box
		sky_box_update();

		// Update the terrain
		terrain_update();

		// Update the spinning quad
		spinning_quad_update();

		// Update the wooden box
		wooden_box_update();

		// ------------------------------------------------------------------------------------------------
		direct3d_pre_render(); // Pre render
		{
			// Sky Box Pipeline
			sky_box_pipeline();

			// Sky Box Render
			sky_box_render();


			// Terrain Pipeline
			terrain_pipeline();

			// Terrain Render
			terrain_render();



			// Spinning Quad Pipeline
			spinning_quad_pipeline();

			// Spinning Quad Render
			spinning_quad_render();



			// Wooden Box Pipeline
			wooden_box_pipeline();

			// Wooden Box Render
			wooden_box_render();


			// Player Pipeline
			player_pipeline();

			// Player Render
			player_render();
		}
		direct3d_post_render(); // Post render
		// ------------------------------------------------------------------------------------------------
	}

	// Clean up window stuff
	window_destroy();

    return 0;
}
