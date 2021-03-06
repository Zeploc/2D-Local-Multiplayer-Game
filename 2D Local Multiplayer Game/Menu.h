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
#include <map>

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
	std::shared_ptr<class UIImage> PlayerImage;
	std::shared_ptr<class UIImage> ButtonHintImage;
	std::shared_ptr<class UIImage> LeftHintImage;
	std::shared_ptr<class UIImage> RightHintImage;
	enum PlayerSkin CurrentSkin;
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
	void UpdateImageStatus(int ID);
	
	void StartGame();

	void SwitchScreens(MenuScreens NewScreen);

	static const char* GetSkinPath(enum PlayerSkin Skin);
	static const char* GetInputImagePath(enum InputController InputType);

private:
	std::vector<std::shared_ptr<UIElement>> MenuElements;
	std::vector<std::shared_ptr<UIElement>> PlayerSelectElements;
	std::vector<std::shared_ptr<UIElement>> ControlsElements;
	std::vector<std::shared_ptr<UIElement>> CreditsElements;
	std::shared_ptr<class UIButton> CurrentSelectedButton;

	std::vector<PlayerStatus> vPlayerStatus;

	std::map<enum PlayerSkin, bool> UsedSkins;


	float StartTime = 3.0f;
	std::shared_ptr<UIText> StartTimerText;

	// DEBUG/TESTING
	bool SkipPlayerSelect = false;
};

