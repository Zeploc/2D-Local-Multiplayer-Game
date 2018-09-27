//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name		:    Camera.h
// Description		:    Header file outlining the Class
// Author			:    Alex Coultas
// Mail				:    alex.cou7417@mediadesign.school.nz
//


#pragma once

// Engine Includes //
#include "Engine\Scene.h"

// Library Includes //
#include <vector>

enum InputDirection
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Menu : public Scene
{
public:
	enum MenuScreens
	{
		MENU,
		PLAYERSELECT
	};

	Menu();
	~Menu();

	virtual void Update() override;
	virtual void OnLoadScene() override;

	void SelectCurrentButton();
	void ControllerInputAxis(InputDirection NewInput);

	void SwitchScreens(MenuScreens NewScreen);

private:
	std::vector<std::shared_ptr<UIElement>> MenuElements;
	std::vector<std::shared_ptr<UIElement>> PlayerSelectElements;

	std::shared_ptr<class UIButton> CurrentSelectedButton;
};

