//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name		:    Input.h
// Description		:    Header file outlining the Class
// Author			:    Alex Coultas
// Mail				:    alex.cou7417@mediadesign.school.nz
//

// OpenGL Library Includes //
#include <glm/common.hpp>

// Library Includes //
#include <string>

enum InputController
{
	BOTTOM_FACE_BUTTON = 0,
	RIGHT_FACE_BUTTON = 1,
	LEFT_FACE_BUTTON = 2,
	TOP_FACE_BUTTON = 3,
	LEFT_BUTTON = 4,
	RIGHT_BUTTON = 5,
	SPECIAL_BUTTON_LEFT = 6,
	SPECIAL_BUTTON_RIGHT = 7,
	LEFT_STICK_DOWN = 8,
	RIGHT_STICK_DOWN = 9
};

#pragma once
class Input
{
public:
	enum InputState
	{
		INPUT_FIRST_RELEASE, // First frame of Up state
		INPUT_RELEASED, // Default State (Up)
		INPUT_FIRST_PRESS, // First frame of Down state
		INPUT_HOLD, // Key is held Down
	};
	enum InputMouse
	{
		MOUSE_LEFT,
		MOUSE_MIDDLE,
		MOUSE_RIGHT,
	};
	
	
	glm::vec2 MousePos;
	unsigned int KeyState[255];
	unsigned int MouseState[3];
	unsigned int ControllerState[10];
	glm::vec3 Axis = { 0, 0, 0 };

	void Init();
	void processNormalKeysDown(unsigned char key, int x, int y);
	void processNormalKeysUp(unsigned char key, int x, int y);
	void processSpecialKeys(int key, int x, int y);
	void MouseInput(int x, int y);
	void MouseButton(int button, int state, int x, int y);
	void Joystick(unsigned int buttonMask, int x, int y, int z);
	void Update();

	std::string InputStateString(unsigned int State);

	bool bKBHit = false;
	unsigned char cLastKey;

private:



public:
	// Singleton
	static Input* GetInstance();
	static void DestoryInstance();

	
private:
	static Input* m_pInput;
	Input();
	~Input();
	Input(Input const&);              // Don't Implement
	void operator=(Input const&); // Don't implement


};

