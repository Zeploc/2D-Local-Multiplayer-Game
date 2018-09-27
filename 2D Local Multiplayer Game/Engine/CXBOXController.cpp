// This Includes //
#include "CXBOXController.h"

// Engine Includes //
#include "Input.h"

#include <iostream>

XBOXController::XBOXController(int playerNumber)
{
	// Set the Controller Number
	_controllerNum = playerNumber - 1;
	std::fill(ControllerButtons, ControllerButtons + 14, Input::INPUT_RELEASED);
}

XINPUT_STATE XBOXController::GetState()
{
	// Zeroise the state
	ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

	// Get the state
	XInputGetState(_controllerNum, &_controllerState);

	return _controllerState;
}

bool XBOXController::IsConnected()
{
	// Zeroise the state
	ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));

	// Get the state
	DWORD Result = XInputGetState(_controllerNum, &_controllerState);

	if(Result == ERROR_SUCCESS)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void XBOXController::Vibrate(int leftVal, int rightVal)
{
	// Create a Vibraton State
	XINPUT_VIBRATION Vibration;

	// Zeroise the Vibration
	ZeroMemory(&Vibration, sizeof(XINPUT_VIBRATION));

	// Set the Vibration Values
	Vibration.wLeftMotorSpeed = leftVal;
	Vibration.wRightMotorSpeed = rightVal;

	// Vibrate the controller
	XInputSetState(_controllerNum, &Vibration);
}

void XBOXController::Update()
{
	int iCurrentButton = 0;
	for (int i = XINPUT_GAMEPAD_DPAD_UP; i <= XINPUT_GAMEPAD_RIGHT_SHOULDER; i *= 2)
	{
		if (GetState().Gamepad.wButtons & i)
		{
			if (ControllerButtons[iCurrentButton] == Input::INPUT_FIRST_PRESS)
			{
				ControllerButtons[iCurrentButton] = Input::INPUT_HOLD;
			}
			else if (ControllerButtons[iCurrentButton] != Input::INPUT_HOLD)
			{
				ControllerButtons[iCurrentButton] = Input::INPUT_FIRST_PRESS;
				std::cout << iCurrentButton << " Pressed\n";
			}
		}
		else
		{
			if (ControllerButtons[iCurrentButton] == Input::INPUT_HOLD)
			{
				ControllerButtons[iCurrentButton] = Input::INPUT_FIRST_RELEASE;
			}
			else
			{
				ControllerButtons[iCurrentButton] = Input::INPUT_RELEASED;
			}
		}
		iCurrentButton++;
	}
	for (int i = XINPUT_GAMEPAD_A; i <= XINPUT_GAMEPAD_Y; i *= 2)
	{
		if (GetState().Gamepad.wButtons & i)
		{
			if (ControllerButtons[iCurrentButton] == Input::INPUT_FIRST_PRESS)
			{
				ControllerButtons[iCurrentButton] = Input::INPUT_HOLD;
			}
			else if (ControllerButtons[iCurrentButton] != Input::INPUT_HOLD)
			{
				ControllerButtons[iCurrentButton] = Input::INPUT_FIRST_PRESS;
				std::cout << iCurrentButton << " Pressed\n";
			}
		}
		else
		{
			if (ControllerButtons[iCurrentButton] == Input::INPUT_HOLD)
			{
				ControllerButtons[iCurrentButton] = Input::INPUT_FIRST_RELEASE;
			}
			else
			{
				ControllerButtons[iCurrentButton] = Input::INPUT_RELEASED;
			}
		}
		iCurrentButton++;
	}
}
