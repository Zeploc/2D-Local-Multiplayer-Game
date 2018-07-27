
// Credit File to
// https://www.codeproject.com/Articles/26949/Xbox-Controller-Input-in-C-with-XInput

#ifndef _XBOX_CONTROLLER_H_
#define _XBOX_CONTROLLER_H_

// No MFC
#define WIN32_LEAN_AND_MEAN

// We need the Windows Header and the XInput Header
#include <windows.h>
#include <XInput.h>

// Now, the XInput Library
// NOTE: COMMENT THIS OUT IF YOU ARE NOT USING A COMPILER THAT SUPPORTS THIS METHOD OF LINKING LIBRARIES
#pragma comment(lib, "XInput.lib")

enum InputController
{
	DPAD_UP = 0,
	DPAD_DOWN = 1,
	DPAD_LEFT = 2,
	DPAD_RIGHT = 3,
	SPECIAL_BUTTON_RIGHT = 4,
	SPECIAL_BUTTON_LEFT = 5,
	LEFT_STICK_DOWN = 6,
	RIGHT_STICK_DOWN = 7,
	LEFT_BUTTON = 8,
	RIGHT_BUTTON = 9,
	BOTTOM_FACE_BUTTON = 10,
	RIGHT_FACE_BUTTON = 11,
	LEFT_FACE_BUTTON = 12,
	TOP_FACE_BUTTON = 13,
};

// XBOX Controller Class Definition
class XBOXController
{
private:
	XINPUT_STATE _controllerState;
	int _controllerNum;

public:
	XBOXController(int playerNumber);
	XINPUT_STATE GetState();
	bool IsConnected();
	void Vibrate(int leftVal = 0, int rightVal = 0);
	void Update();


	unsigned int ControllerButtons[14];
};

#endif