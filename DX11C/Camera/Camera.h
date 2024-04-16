#pragma once
#include "../Math/gpu_math.h"
#include "../Input/Keyboard.h"
#include "../Input/Mouse.h"

// Camera
float3 cameraPos;
//float3 cameraFwd;
float cameraPitch;
float cameraYaw;

static float4x4 perspectiveMat = { 0 };
static float4x4 viewMat = { 0 };

// Prototypes
static void camera_reset();
static void camera_get_input();
static void camera_update(float3 object_position);

// Reset camera
static void camera_reset()
{
	cameraPos = (float3){ 0.0f, 1.5f, 2.5f };
	//cameraFwd = (float3){ 0.0f, 0.0f, -1.0f };
	cameraPitch = degreesToRadians(-20.0f);
	cameraYaw = 0.0f;

	viewMat = identityMat();
	
}

// Update camera
static void camera_get_input()
{
	// Mouse look camera
	if (!mouse_visible)
	{
		float camera_look_sensitivity = 0.002f;
		POINT mouse;
		GetCursorPos(&mouse);
		cameraYaw += (float)(mouse_center_x - mouse.x) * camera_look_sensitivity;
		cameraPitch += (float)(mouse_center_y - mouse.y) * camera_look_sensitivity;
		SetCursorPos(mouse_center_x, mouse_center_y);
	}

	// Wrap yaw to avoid floating-point errors if we turn too far
	while (cameraYaw >= (float)(2 * M_PI))
		cameraYaw -= (float)(2 * M_PI);
	while (cameraYaw <= (float)(-2 * M_PI))
		cameraYaw += (float)(2 * M_PI);

	// Clamp pitch to stop camera flipping upside down
	if (cameraPitch > degreesToRadians(30))
		cameraPitch = degreesToRadians(30);
	if (cameraPitch < -degreesToRadians(85))
		cameraPitch = -degreesToRadians(85);
}

// Update camera view matrix and camera position
static void camera_update(float3 object_position)
{
	const float3 camera_offset = { 0.0f, -1.5f, -2.5f };

	// Update the view matrix
	viewMat = identityMat();
	viewMat = mul44(viewMat, translationMat(negate(object_position)));
	viewMat = mul44(viewMat, translationMat((float3) { 0.0f, camera_offset.y, 0.0f }));
	viewMat = mul44(viewMat, rotateYMat(-cameraYaw));
	viewMat = mul44(viewMat, rotateXMat(-cameraPitch));
	viewMat = mul44(viewMat, translationMat((float3) { 0.0f, 0.0f, camera_offset.z }));

	// Tell the Camera its new position
	cameraPos = get_position_from_matrix(&viewMat);
}
