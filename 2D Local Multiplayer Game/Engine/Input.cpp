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

#define Controller_Bottom_Face_Button 1
#define Controller_Right_Face_Button 2
#define Controller_Left_Face_Button 4
#define Controller_Top_Face_Button 8
#define Controller_Left_Button 16
#define Controller_Right_Button 32
#define Special_Left_Button 64
#define Special_Right_Button 128
#define Left_Stick_Down 256
#define Right_Stick_Down 512


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
		std::fill(m_pInput->ControllerState, m_pInput->ControllerState + 10, INPUT_RELEASED);
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
	glutJoystickFunc(LJoystick, (float)GLUT_JOYSTICK_POLL_RATE / 100.0f);
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
	bool ReleasedCheck[10];
	for (int i = 0; i < 10; i++)
	{
		ReleasedCheck[i] = false;
	}
	if (buttonMask & 1024)
	{
		std::cout << "Different button pressed?\n";
	}
	if (buttonMask & Right_Stick_Down)
	{
		if (ControllerState[RIGHT_STICK_DOWN] != INPUT_HOLD)
		{
			ControllerState[RIGHT_STICK_DOWN] = INPUT_FIRST_PRESS;
			std::cout << "RIGHT_STICK_DOWN Pressed\n";
		}
		ReleasedCheck[RIGHT_STICK_DOWN] = true;
	}
	if (buttonMask & Left_Stick_Down)
	{
		if (ControllerState[LEFT_STICK_DOWN] != INPUT_HOLD)
		{
			ControllerState[LEFT_STICK_DOWN] = INPUT_FIRST_PRESS;
			std::cout << "LEFT_STICK_DOWN Pressed\n";
		}
		ReleasedCheck[LEFT_STICK_DOWN] = true;
	}
	if (buttonMask & Special_Right_Button)
	{
		if (ControllerState[SPECIAL_BUTTON_RIGHT] != INPUT_HOLD)
		{
			ControllerState[SPECIAL_BUTTON_RIGHT] = INPUT_FIRST_PRESS;
			std::cout << "SPECIAL_BUTTON_RIGHT Pressed\n";
		}
		ReleasedCheck[SPECIAL_BUTTON_RIGHT] = true;
	}
	if (buttonMask & Special_Left_Button)
	{
		if (ControllerState[SPECIAL_BUTTON_LEFT] != INPUT_HOLD)
		{
			ControllerState[SPECIAL_BUTTON_LEFT] = INPUT_FIRST_PRESS;
			std::cout << "SPECIAL_BUTTON_LEFT Pressed\n";
		}
		ReleasedCheck[SPECIAL_BUTTON_LEFT] = true;
	}
	if (buttonMask & Controller_Right_Button)
	{
		if (ControllerState[RIGHT_BUTTON] != INPUT_HOLD)
		{
			ControllerState[RIGHT_BUTTON] = INPUT_FIRST_PRESS;
			std::cout << "RIGHT_BUTTON Pressed\n";
		}
		ReleasedCheck[RIGHT_BUTTON] = true;
	}
	if (buttonMask & Controller_Left_Button)
	{
		if (ControllerState[LEFT_BUTTON] != INPUT_HOLD)
		{
			ControllerState[LEFT_BUTTON] = INPUT_FIRST_PRESS;
			std::cout << "LEFT_BUTTON Pressed\n";
		}
		ReleasedCheck[LEFT_BUTTON] = true;
	}
	if (buttonMask & Controller_Top_Face_Button)
	{
		if (ControllerState[TOP_FACE_BUTTON] != INPUT_HOLD)
		{
			ControllerState[TOP_FACE_BUTTON] = INPUT_FIRST_PRESS;
			std::cout << "TOP_FACE_BUTTON Pressed\n";
		}
		ReleasedCheck[TOP_FACE_BUTTON] = true;
	}
	if (buttonMask & Controller_Left_Face_Button)
	{
		if (ControllerState[LEFT_FACE_BUTTON] != INPUT_HOLD)
		{
			ControllerState[LEFT_FACE_BUTTON] = INPUT_FIRST_PRESS;
			std::cout << "LEFT_FACE_BUTTON Pressed\n";
		}
		ReleasedCheck[LEFT_FACE_BUTTON] = true;
	}
	if (buttonMask & Controller_Right_Face_Button)
	{
		if (ControllerState[RIGHT_FACE_BUTTON] != INPUT_HOLD)
		{
			ControllerState[RIGHT_FACE_BUTTON] = INPUT_FIRST_PRESS;
			std::cout << "RIGHT_FACE_BUTTON Pressed\n";
		}
		ReleasedCheck[RIGHT_FACE_BUTTON] = true;
	}
	if (buttonMask & Controller_Bottom_Face_Button)
	{
		if (ControllerState[BOTTOM_FACE_BUTTON] != INPUT_HOLD)
		{
			ControllerState[BOTTOM_FACE_BUTTON] = INPUT_FIRST_PRESS;
			std::cout << "BOTTOM_FACE_BUTTON Pressed\n";
		}
		ReleasedCheck[BOTTOM_FACE_BUTTON] = true;
	}

	for (int i = 0; i < 10; i++)
	{
		if (!ReleasedCheck[i] && ControllerState[i] == INPUT_HOLD)
		{
			ControllerState[i] = INPUT_FIRST_RELEASE;
			std::cout << i << " button released\n";
		}
	}
	Axis = { x, y, z };
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

	for (int i = 0; i < 10; i++)
	{
		if (ControllerState[i] == INPUT_FIRST_RELEASE)
		{
			ControllerState[i] = INPUT_RELEASED;
		}
		if (ControllerState[i] == INPUT_FIRST_PRESS)
		{
			ControllerState[i] = INPUT_HOLD;
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
