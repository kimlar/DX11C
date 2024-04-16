#pragma once
#include <stdbool.h>

// Input
enum GameAction
{
	GameActionMoveCamFwd = 0,
	GameActionMoveCamBack,
	GameActionMoveCamLeft,
	GameActionMoveCamRight,
	GameActionTurnCamLeft,
	GameActionTurnCamRight,
	GameActionLookUp,
	GameActionLookDown,
	GameActionRaiseCam,
	GameActionLowerCam,
	GameActionPlayerMoveForward,
	GameActionPlayerMoveBackward,
	GameActionPlayerStrafeLeft,
	GameActionPlayerStrafeRight,
	GameActionCount
};
static bool global_keyIsDown[GameActionCount] = { 0 };
static bool prev_tab_key_is_down = false;

static void handle_keyboard_input(unsigned int key, bool isDown)
{
	switch (key)
	{
/*
		case 'W':
			global_keyIsDown[GameActionMoveCamFwd] = isDown;
			break;
		case 'A':
			global_keyIsDown[GameActionMoveCamLeft] = isDown;
			break;
		case 'S':
			global_keyIsDown[GameActionMoveCamBack] = isDown;
			break;
		case 'D':
			global_keyIsDown[GameActionMoveCamRight] = isDown;
			break;
*/
		case 'E':
			global_keyIsDown[GameActionRaiseCam] = isDown;
			break;
		case 'Q':
			global_keyIsDown[GameActionLowerCam] = isDown;
			break;
		case 'W':
			global_keyIsDown[GameActionPlayerMoveForward] = isDown;
			break;
		case 'S':
			global_keyIsDown[GameActionPlayerMoveBackward] = isDown;
			break;
		case 'A':
			global_keyIsDown[GameActionPlayerStrafeLeft] = isDown;
			break;
		case 'D':
			global_keyIsDown[GameActionPlayerStrafeRight] = isDown;
			break;
	}
}
