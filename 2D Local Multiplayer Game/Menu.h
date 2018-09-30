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

struct PlayerStatus
{
	bool IsPlaying = false;
	bool IsReady = false;
	std::shared_ptr<UIText> PlayerJoinedText;
	std::shared_ptr<UIText> PlayerReadyText;
	// Player asthetic chosen
};

class Menu : public Scene
{
public:
	enum MenuScreens
	{
		MENU,
		PLAYERSELECT,
		CONTROLS,
		CREDITS
	};

	Menu();
	~Menu();

	virtual void Update() override;
	virtual void OnLoadScene() override;

	void PlayerControllerInput(int ID, enum InputController Input);
	void ControllerInputAxis(InputDirection NewInput);
	void CheckPlayersToStartTimer();
	void ResetPlayerSelectScreen();

	void SwitchScreens(MenuScreens NewScreen);

private:
	std::vector<std::shared_ptr<UIElement>> MenuElements;
	std::vector<std::shared_ptr<UIElement>> PlayerSelectElements;
	std::vector<std::shared_ptr<UIElement>> ControlsElements;
	std::vector<std::shared_ptr<UIElement>> CreditsElements;
	std::vector<PlayerStatus> vPlayerStatus;

	std::shared_ptr<class UIButton> CurrentSelectedButton;

	float StartTime = 3.0f;
	std::shared_ptr<UIText> StartTimerText;

	// DEBUG/TESTING
	bool SkipPlayerSelect = true;
};

