#pragma once
#include "../Math/gpu_math.h"
#include "../Input/Keyboard.h"
#include "../Input/Mouse.h"
//#include "../GameObject/Player.h"

extern float3 player_position;
extern float3 player_forward;

// Camera
float3 cameraPos;
float3 cameraFwd;
float cameraPitch;
float cameraYaw;

static float4x4 perspectiveMat = { 0 };
static float4x4 viewMat = { 0 };

// Prototypes
static void camera_reset();
//static void camera_update(float dt, bool* global_keyIsDown);
static void camera_update(float dt);
static void camera_update_view_matrix();
static void camera_update_forward_vector();

// Reset camera
static void camera_reset()
{
	cameraPos = (float3){ 0.0f, 1.5f, 2.0f };
	cameraFwd = (float3){ 0.0f, 0.0f, -1.0f };
	cameraPitch = degreesToRadians(-20.0f);
	cameraYaw = 0.0f;
}

// Update camera
//static void camera_update(float dt, bool* global_keyIsDown)
static void camera_update(float dt)
{
	player_forward = (float3){ -viewMat.m[2][0], -viewMat.m[2][1], -viewMat.m[2][2] };
	//float3 camFwdXZ;
	cameraFwd.x = player_forward.x;
	cameraFwd.y = player_forward.y;
	cameraFwd.z = player_forward.z;


	//float3 cameraRightXZ = cross(cameraFwd, (float3) { 0, 1, 0 });

	cameraPos.x = player_position.x;
	cameraPos.y = player_position.y;
	cameraPos.z = player_position.z;

	add_equal(&cameraPos, mul((float3) { 0.0f, 1.0f, 0.0f }, 1.5f));
	//add_equal(&cameraPos, mul((float3) {0.0f, 0.0f, 1.0f}, 2.0f));
	add_equal(&cameraPos, mul(cameraFwd, -2.0f));



	//float3 camFwdXZ = normalise((float3) { player_forward.x, 0, player_forward.z });
	//float3 cameraRightXZ = cross(camFwdXZ, (float3) { 0, 1, 0 });


	//float3 camFwdXZ = normalise((float3) { cameraFwd.x, 0, cameraFwd.z });
	//float3 cameraRightXZ = cross(camFwdXZ, (float3) { 0, 1, 0 });


/*
	//float3 camFwdXZ;
	cameraFwd.x = player_forward.x;
	cameraFwd.y = player_forward.y;
	cameraFwd.z = player_forward.z;

	float3 cameraRightXZ = cross(cameraFwd, (float3) { 0, 1, 0 });




	cameraPos.x = player_position.x;
	cameraPos.y = player_position.y;
	cameraPos.z = player_position.z;


	add_equal(&cameraPos, mul((float3) { 0.0f, 1.0f, 0.0f }, 1.5f));
	//add_equal(&cameraPos, mul((float3) {0.0f, 0.0f, 1.0f}, 2.0f));
	add_equal(&cameraPos, mul(cameraFwd, -2.0f));
*/


//	const float CAM_MOVE_SPEED = 5.f; // in metres per second
//	const float CAM_MOVE_AMOUNT = CAM_MOVE_SPEED * dt;
//	if (global_keyIsDown[GameActionMoveCamFwd])
//		add_equal(&cameraPos, mul(cameraFwd, CAM_MOVE_AMOUNT));
//	if (global_keyIsDown[GameActionMoveCamBack])
//		sub_equal(&cameraPos, mul(cameraFwd, CAM_MOVE_AMOUNT));
//	if (global_keyIsDown[GameActionMoveCamLeft])
//		sub_equal(&cameraPos, mul(cameraRightXZ, CAM_MOVE_AMOUNT));
//	if (global_keyIsDown[GameActionMoveCamRight])
//		add_equal(&cameraPos, mul(cameraRightXZ, CAM_MOVE_AMOUNT));
//	if (global_keyIsDown[GameActionRaiseCam])
//		cameraPos.y += CAM_MOVE_AMOUNT;
//	if (global_keyIsDown[GameActionLowerCam])
//		cameraPos.y -= CAM_MOVE_AMOUNT;

//	const float CAM_TURN_SPEED = (const float)M_PI; // in radians per second
//	const float CAM_TURN_AMOUNT = CAM_TURN_SPEED * dt;
//	if (global_keyIsDown[GameActionTurnCamLeft])
//		cameraYaw += CAM_TURN_AMOUNT;
//	if (global_keyIsDown[GameActionTurnCamRight])
//		cameraYaw -= CAM_TURN_AMOUNT;
//	if (global_keyIsDown[GameActionLookUp])
//		cameraPitch += CAM_TURN_AMOUNT;
//	if (global_keyIsDown[GameActionLookDown])
//		cameraPitch -= CAM_TURN_AMOUNT;

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
	if (cameraPitch > degreesToRadians(85))
		cameraPitch = degreesToRadians(85);
	if (cameraPitch < -degreesToRadians(85))
		cameraPitch = -degreesToRadians(85);

	//-----------------------------------------------------------------------------

	// Calculate view matrix from camera data
	camera_update_view_matrix();

	// Update the forward vector we use for camera movement:
	camera_update_forward_vector();
}

// Calculate view matrix from camera data
static void camera_update_view_matrix()
{
	// Calculate view matrix from camera data
	// 
	// float4x4 viewMat = inverse(rotateXMat(cameraPitch) * rotateYMat(cameraYaw) * translationMat(cameraPos));
	// NOTE: We can simplify this calculation to avoid inverse()!
	// Applying the rule inverse(A*B) = inverse(B) * inverse(A) gives:
	// float4x4 viewMat = inverse(translationMat(cameraPos)) * inverse(rotateYMat(cameraYaw)) * inverse(rotateXMat(cameraPitch));
	// The inverse of a rotation/translation is a negated rotation/translation:
	viewMat = mul44x3(translationMat(negate(cameraPos)), rotateYMat(-cameraYaw), rotateXMat(-cameraPitch));


}

// Update the forward vector we use for camera movement:
static void camera_update_forward_vector()
{
	// Update the forward vector we use for camera movement:
	cameraFwd = (float3){ -viewMat.m[2][0], -viewMat.m[2][1], -viewMat.m[2][2] };
}
