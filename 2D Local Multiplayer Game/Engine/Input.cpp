//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name    	:    CSprite.cpp
// Description    	:    main implementation for CSprite
// Author       	:    Alex Coultas
// Mail         	:    alex.cou7417@mediadesign.school.nz
//

// Library Includes //
#include <iostream>

// OpenGL Library Includes //
#include <glew.h>
#include <freeglut.h>

// Engine Includes //
#include "Input.h"
#include "UIButton.h"

// Static Variables //
Input* Input::m_pInput = nullptr;

// Prototypes //
void LprocessNormalKeysDown(unsigned char key, int x, int y);
void LprocessNormalKeysUp(unsigned char key, int x, int y);
void LprocessSpecialKeys(int key, int x, int y);
void LMouseInput(int x, int y);
void LMouseButton(int button, int state, int x, int y);
void LJoystick(unsigned int buttonMask, int x, int y, int z);

/************************************************************
#--Description--#:  Constructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	Takes contructor values
#--Return--#: 		NA
************************************************************/
Input::Input()
{

}

/************************************************************
#--Description--#:  Destructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	NA
#--Return--#: 		NA
************************************************************/
Input::~Input()
{
}

/************************************************************
#--Description--#:  Retrieves static instance pointer to this class
#--Author--#: 		Alex Coultas
#--Parameters--#:	NA
#--Return--#: 		Returns static pointer to self
************************************************************/
Input * Input::GetInstance()
{
	if (!m_pInput) // null or doesn't exist
	{
		m_pInput = new Input;
		std::fill(m_pInput->KeyState, m_pInput->KeyState + 255, INPUT_RELEASED);
		std::fill(m_pInput->MouseState, m_pInput->MouseState + 3, INPUT_RELEASED);
	}
	return m_pInput;
}

/************************************************************
#--Description--#:  Destroys static instance pointer to this class
#--Author--#: 		Alex Coultas
#--Parameters--#:	NA
#--Return--#: 		NA
************************************************************/
void Input::DestoryInstance()
{
	if (m_pInput)
		delete m_pInput;
	m_pInput = nullptr;
}

/************************************************************
#--Description--#: 	Initialises the OpenGL inputs to the local functions
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void Input::Init()
{
	glutKeyboardFunc(LprocessNormalKeysDown);
	glutKeyboardUpFunc(LprocessNormalKeysUp);
	glutSpecialFunc(LprocessSpecialKeys);
	glutPassiveMotionFunc(LMouseInput);
	glutMouseFunc(LMouseButton);
	glutMotionFunc(LMouseInput);
	glutJoystickFunc(LJoystick, 1.0f);
}

/************************************************************
#--Description--#: 	Proccess keys down and sets KeyState values
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Takes in the the key and the mouse pos
#--Return--#: 		NA
************************************************************/
void Input::processNormalKeysDown(unsigned char key, int x, int y)
{
	bKBHit = true;
	cLastKey = key;
	if (KeyState[key] == (INPUT_RELEASED | INPUT_FIRST_RELEASE))
	{
		KeyState[key] = INPUT_FIRST_PRESS;
	}
}

/************************************************************
#--Description--#: 	Proccess keys up and sets KeyState values
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Takes in the the key and the mouse pos
#--Return--#: 		NA
************************************************************/
void Input::processNormalKeysUp(unsigned char key, int x, int y)
{
	if (KeyState[key] == (INPUT_HOLD | INPUT_FIRST_PRESS))
	{
		KeyState[key] = INPUT_FIRST_RELEASE;
	}
}

/************************************************************
#--Description--#: 	Proccess Special keys
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Takes in the the key and the mouse pos
#--Return--#: 		NA
************************************************************/
void Input::processSpecialKeys(int key, int x, int y)
{

}

/************************************************************
#--Description--#: 	Proccess Mouse movement and sets the mouse position vector
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Takes in the the mouse pos
#--Return--#: 		NA
************************************************************/
void Input::MouseInput(int x, int y)
{
	MousePos = glm::vec2(x, y);
}

/************************************************************
#--Description--#: 	Proccess Mouse buttons
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Takes in the the button and the state and mouse pos
#--Return--#: 		NA
************************************************************/
void Input::MouseButton(int button, int state, int x, int y)
{
	MousePos = glm::vec2(x, y);
	if (button < 3)
	{
		if (state == GLUT_DOWN)
		{
			MouseState[button] = INPUT_FIRST_PRESS;
		}
		else if (state == GLUT_UP)
		{
			MouseState[button] = INPUT_FIRST_RELEASE;
		}
		else
		{
			std::cout << "Unknown mouse state\n";
		}
		
	}

}

void Input::Joystick(unsigned int buttonMask, int x, int y, int z)
{
	int CurrentValue = buttonMask;
	while (CurrentValue > 0)
	{
		if (CurrentValue >= 512)
		{
			if (ControllerState[RIGHT_STICK_DOWN] != INPUT_HOLD)
				ControllerState[RIGHT_STICK_DOWN] = INPUT_FIRST_PRESS;
			CurrentValue -= 512;
		}
		else if (CurrentValue >= 256)
		{
			if (ControllerState[LEFT_STICK_DOWN] != INPUT_HOLD)
				ControllerState[LEFT_STICK_DOWN] = INPUT_FIRST_PRESS;
			CurrentValue -= 256;
		}
		else if (CurrentValue >= 128)
		{
			if (ControllerState[SPECIAL_BUTTON_RIGHT] != INPUT_HOLD)
				ControllerState[SPECIAL_BUTTON_RIGHT] = INPUT_FIRST_PRESS;
			CurrentValue -= 128;
		}
		else if (CurrentValue >= 64)
		{
			if (ControllerState[SPECIAL_BUTTON_LEFT] != INPUT_HOLD)
				ControllerState[SPECIAL_BUTTON_LEFT] = INPUT_FIRST_PRESS;
			CurrentValue -= 64;
		}
		else if (CurrentValue >= 32)
		{
			if (ControllerState[RIGHT_BUTTON] != INPUT_HOLD)
				ControllerState[RIGHT_BUTTON] = INPUT_FIRST_PRESS;
			CurrentValue -= 32;
		}
		else if (CurrentValue >= 16)
		{
			if (ControllerState[LEFT_BUTTON] != INPUT_HOLD)
				ControllerState[LEFT_BUTTON] = INPUT_FIRST_PRESS;
			CurrentValue -= 16;
		}
		else if (CurrentValue >= 8)
		{
			if (ControllerState[TOP_FACE_BUTTON] != INPUT_HOLD)
				ControllerState[TOP_FACE_BUTTON] = INPUT_FIRST_PRESS;
			CurrentValue -= 8;
		}
		else if (CurrentValue >= 4)
		{
			if (ControllerState[LEFT_FACE_BUTTON] != INPUT_HOLD)
				ControllerState[LEFT_FACE_BUTTON] = INPUT_FIRST_PRESS;
			CurrentValue -= 4;
		}
		else if (CurrentValue >= 2)
		{
			if (ControllerState[RIGHT_FACE_BUTTON] != INPUT_HOLD)
				ControllerState[RIGHT_FACE_BUTTON] = INPUT_FIRST_PRESS;
			CurrentValue -= 2;
		}
		else if (CurrentValue >= 1)
		{
			if (ControllerState[BOTTOM_FACE_BUTTON] != INPUT_HOLD)
				ControllerState[BOTTOM_FACE_BUTTON] = INPUT_FIRST_PRESS;
			CurrentValue -= 1;
		}
	}
/*
	switch (buttonMask)
	{
		case 0:
		{

			break;
		}
		case 1:
		{
			ControllerState[BOTTOM_FACE_BUTTON] = INPUT_FIRST_PRESS;
			break;
		}
		case 2:
		{
			ControllerState[RIGHT_FACE_BUTTON] = INPUT_FIRST_PRESS;
			break;
		}
		case 4:
		{
			ControllerState[LEFT_FACE_BUTTON] = INPUT_FIRST_PRESS;
			break;
		}
		case 8:
		{
			ControllerState[TOP_FACE_BUTTON] = INPUT_FIRST_PRESS;
			break;
		}
		case 16:
		{
			ControllerState[LEFT_BUTTON] = INPUT_FIRST_PRESS;
			break;
		}
		case 32:
		{
			ControllerState[RIGHT_BUTTON] = INPUT_FIRST_PRESS;
			break;
		}
		case 64:
		{
			ControllerState[SPECIAL_BUTTON_LEFT] = INPUT_FIRST_PRESS;
			break;
		}
		case 128:
		{
			ControllerState[SPECIAL_BUTTON_RIGHT] = INPUT_FIRST_PRESS;
			break;
		}
		case 256:
		{
			ControllerState[LEFT_STICK_DOWN] = INPUT_FIRST_PRESS;
			break;
		}
		case 512:
		{
			ControllerState[RIGHT_STICK_DOWN] = INPUT_FIRST_PRESS;
			break;
		}
	}*/
	Axis = { x, y, z };
	std::cout << "Button mask: [" << buttonMask << "] x: [" << x << "] y: [" << y << "] z: [" << z << "]" << std::endl;
}

/************************************************************
#--Description--#: 	Updated every frame
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void Input::Update()
{
	for (int i = 0; i < 255; i++)
	{
		if (KeyState[i] == INPUT_FIRST_RELEASE)
		{
			KeyState[i] = INPUT_RELEASED;
		}
		if (KeyState[i] == INPUT_FIRST_PRESS)
		{
			KeyState[i] = INPUT_HOLD;
		}
	}
	for (int i = 0; i < 3; i++)
	{
		if (MouseState[i] == INPUT_FIRST_RELEASE)
		{
			MouseState[i] = INPUT_RELEASED;
		}
		if (MouseState[i] == INPUT_FIRST_PRESS)
		{
			MouseState[i] = INPUT_HOLD;
		}
	}
	bKBHit = false;
	UIButton::bButtonPressedThisFrame = false;
}

/************************************************************
#--Description--#: 	Converts enum value to string
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Takes in enum value
#--Return--#: 		Returns enum name as string
************************************************************/
std::string Input::InputStateString(unsigned int State)
{
	switch (State)
	{
		case Input::INPUT_FIRST_RELEASE:
			return "INPUT_FIRST_RELEASE";
		case Input::INPUT_RELEASED:
			return "INPUT_RELEASED";
		case Input::INPUT_FIRST_PRESS:
			return "INPUT_FIRST_PRESS";
		case Input::INPUT_HOLD:
			return "INPUT_HOLD";
		default:
			return "ERROR";
	}
}

/************************************************************
#--Description--#:	Local function to pass opengl input to singleton input function 
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Takes in key and mouse pos
#--Return--#: 		NA
************************************************************/
void LprocessNormalKeysDown(unsigned char key, int x, int y)
{
	Input::GetInstance()->processNormalKeysDown(key, x, y);
}

/************************************************************
#--Description--#:	Local function to pass opengl input to singleton input function
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Takes in key and mouse pos
#--Return--#: 		NA
************************************************************/
void LprocessNormalKeysUp(unsigned char key, int x, int y)
{
	Input::GetInstance()->processNormalKeysUp(key, x, y);
}

/************************************************************
#--Description--#:	Local function to pass opengl input to singleton input function
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Takes in key and mouse pos
#--Return--#: 		NA
************************************************************/
void LprocessSpecialKeys(int key, int x, int y)
{
	Input::GetInstance()->processSpecialKeys(key, x, y);
}

/************************************************************
#--Description--#:	Local function to pass opengl input to singleton input function
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Takes mouse pos
#--Return--#: 		NA
************************************************************/
void LMouseInput(int x, int y)
{
	Input::GetInstance()->MouseInput(x, y);
}

/************************************************************
#--Description--#:	Local function to pass opengl input to singleton input function
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Takes in mouse key and state and mouse pos
#--Return--#: 		NA
************************************************************/
void LMouseButton(int button, int state, int x, int y)
{
	Input::GetInstance()->MouseButton(button, state, x, y);
}

void LJoystick(unsigned int buttonMask, int x, int y, int z)
{
	Input::GetInstance()->Joystick(buttonMask, x, y, z);
}
