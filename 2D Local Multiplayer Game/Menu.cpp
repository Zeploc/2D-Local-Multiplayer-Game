//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name    	:    Menu.cpp
// Description    	:    main implementation for Menu
// Author       	:    Alex Coultas
// Mail         	:    alex.cou7417@mediadesign.school.nz
//


// This Includes //
#include "Menu.h"

// Engine Includes //
#include "Engine\UIButton.h"
#include "Engine/SceneManager.h"
#include "Engine/CXBOXController.h"
#include "Engine/Time.h"

// Local Includes //
#include "LevelManager.h"
#include "MenuPlayerController.h"

// TEMP
#include <iostream>

// Prototpyes //
void StartGameBtn();
void ExitGameBtn();
void OptionsScreenBtn();

void PlayBtn();

Menu::Menu() : Scene("Menu")
{
	// Add Title Elements
	std::shared_ptr<UIText> Title(new UIText(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, 100.0f), 0, glm::vec4(0.9, 0.9, 0.9, 1.0), "Local Multiplayer Game", "Resources/Fonts/Roboto-Black.ttf", 100, Utils::CENTER));
	std::shared_ptr<UIButton> StartBtn(new UIButton(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, Camera::GetInstance()->SCR_HEIGHT / 2), Utils::CENTER, 0.0f, glm::vec4(0.3f, 0.3f, 0.3f, 1.0f), glm::vec4(0.7f, 0.7f, 0.7f, 1.0f), 480, 70, StartGameBtn));
	StartBtn->AddText("START GAME", "Resources/Fonts/Roboto-Thin.ttf", 34, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), Utils::CENTER, { 0, 0 });
	std::shared_ptr<UIButton> OptionsBtn(new UIButton(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, Camera::GetInstance()->SCR_HEIGHT / 2 + 80), Utils::CENTER, 0.0f, glm::vec4(0.3f, 0.3f, 0.3f, 1.0f), glm::vec4(0.7f, 0.7f, 0.7f, 1.0f), 480, 70, OptionsScreenBtn));
	OptionsBtn->AddText("OPTIONS", "Resources/Fonts/Roboto-Thin.ttf", 34, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), Utils::CENTER, { 0, 0 });
	std::shared_ptr<UIButton> QuitBtn(new UIButton(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, Camera::GetInstance()->SCR_HEIGHT / 2 + 160), Utils::CENTER, 0.0f, glm::vec4(0.3f, 0.3f, 0.3f, 1.0f), glm::vec4(0.7f, 0.7f, 0.7f, 1.0f), 480, 70, ExitGameBtn));
	QuitBtn->AddText("QUIT GAME", "Resources/Fonts/Roboto-Thin.ttf", 34, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), Utils::CENTER, { 0, 0 });
	std::shared_ptr<UIImage> BackImage(new UIImage(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, Camera::GetInstance()->SCR_HEIGHT / 2), Utils::CENTER, 0.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), Camera::GetInstance()->SCR_WIDTH, Camera::GetInstance()->SCR_HEIGHT, "Resources/Images/Block.png", 2));
	std::shared_ptr<UIImage> UIIMG(new UIImage(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, 100.0f), Utils::CENTER, 0.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 600, 100, "Resources/Box.png", 2));
	// Add elements to scene UI elements
	AddUIElement(BackImage);
	AddUITextElement(Title);
	AddUIElement(StartBtn);
	AddUIElement(OptionsBtn);
	AddUIElement(QuitBtn);

	MenuElements.push_back(Title);
	MenuElements.push_back(StartBtn);
	MenuElements.push_back(OptionsBtn);
	MenuElements.push_back(QuitBtn);

	CurrentSelectedButton = StartBtn;
	CurrentSelectedButton->HoverOverride = true;


	std::shared_ptr<UIText> PlayerTitle(new UIText(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, 100.0f), 0, glm::vec4(0.9, 0.9, 0.9, 1.0), "Player Select", "Resources/Fonts/Roboto-Black.ttf", 80, Utils::CENTER));
	StartTimerText = std::make_shared<UIText>(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, Camera::GetInstance()->SCR_HEIGHT - 100.0f), 0, glm::vec4(0.9, 0.9, 0.9, 1.0), "Starting in 3...", "Resources/Fonts/Roboto-Regular.ttf", 40, Utils::CENTER);
	StartTimerText->SetActive(false);

	for (int i = 0; i < 4; i++)
	{
		PlayerStatus NewPlayerStatus;
		float XPos = Camera::GetInstance()->SCR_WIDTH / 2 - 450 + 300 * i;
		std::shared_ptr<UIText> PlayerLabel(new UIText(glm::vec2(XPos, Camera::GetInstance()->SCR_HEIGHT / 2 - 100), 0, glm::vec4(0.9, 0.9, 0.9, 1.0), "Player " + std::to_string(i + 1), "Resources/Fonts/Roboto-Thin.ttf", 25, Utils::CENTER));
		AddUIElement(PlayerLabel);
		PlayerSelectElements.push_back(PlayerLabel);
		std::shared_ptr<UIText> PlayerJoin(new UIText(glm::vec2(XPos, Camera::GetInstance()->SCR_HEIGHT / 2), 0, glm::vec4(0.9, 0.9, 0.9, 1.0), "Press Start to join", "Resources/Fonts/Roboto-Thin.ttf", 25, Utils::CENTER));
		AddUIElement(PlayerJoin);
		PlayerSelectElements.push_back(PlayerJoin);
		std::shared_ptr<UIText> PlayerReady(new UIText(glm::vec2(XPos, Camera::GetInstance()->SCR_HEIGHT / 2 + 100), 0, glm::vec4(0.9, 0.9, 0.9, 1.0), "Ready", "Resources/Fonts/Roboto-Thin.ttf", 25, Utils::CENTER));
		AddUIElement(PlayerReady);
		PlayerSelectElements.push_back(PlayerReady);
		PlayerReady->SetActive(false);

		NewPlayerStatus.PlayerJoinedText = PlayerJoin;
		NewPlayerStatus.PlayerReadyText = PlayerReady;
		vPlayerStatus.push_back(NewPlayerStatus);
	}

	AddUIElement(PlayerTitle);
	AddUIElement(StartTimerText);
	PlayerSelectElements.push_back(StartTimerText);
	PlayerSelectElements.push_back(PlayerTitle);

	SwitchScreens(Menu::MENU);


	for (int i = 0; i < 4; i++)
	{
		std::shared_ptr<MenuPlayerController> NewMenuPlayer = std::make_shared<MenuPlayerController>(i);
		AddEntity(NewMenuPlayer, true);
	}
}


Menu::~Menu()
{

}

void Menu::Update()
{
	Scene::Update();

	if (StartTimerText->IsActive())
	{
		StartTime -= Time::dTimeDelta;
		StartTimerText->sText = "Starting in " + std::to_string((int)ceil(StartTime)) + "...";
		if (StartTime <= 0)
		{
			LevelManager::GetInstance()->SwitchToLevel("Level");
		}
	}
}

void Menu::OnLoadScene()
{
	Scene::OnLoadScene();

}

void Menu::PlayerControllerInput(int ID, InputController Input)
{
	if (PlayerSelectElements[0]->IsActive())
	{
		if (Input == SPECIAL_BUTTON_RIGHT || (Input == BOTTOM_FACE_BUTTON && !vPlayerStatus[ID].IsPlaying))
		{
			vPlayerStatus[ID].IsPlaying = !vPlayerStatus[ID].IsPlaying;
			if (vPlayerStatus[ID].IsPlaying)
				vPlayerStatus[ID].PlayerJoinedText->sText = "Joined";
			else
			{
				vPlayerStatus[ID].PlayerJoinedText->sText = "Press Start to join";
				vPlayerStatus[ID].PlayerReadyText->SetActive(false);
				vPlayerStatus[ID].IsReady = false;
			}
		}
		else if (Input == BOTTOM_FACE_BUTTON)
		{
			vPlayerStatus[ID].IsReady = !vPlayerStatus[ID].IsReady;
			CheckPlayersToStartTimer();
			if (vPlayerStatus[ID].IsReady)
			{
				vPlayerStatus[ID].PlayerReadyText->SetActive(true);

			}
			else
				vPlayerStatus[ID].PlayerReadyText->SetActive(false);
		}
	}
	else if (Input == BOTTOM_FACE_BUTTON)
	{
		CurrentSelectedButton->Pressed();
	}


}

void Menu::ControllerInputAxis(InputDirection NewInput)
{
	CurrentSelectedButton->HoverOverride = false;
	
	for (int i = 0; i < MenuElements.size(); i++)
	{
		if (MenuElements[i] == CurrentSelectedButton)
		{
			CurrentSelectedButton = nullptr;
			while (CurrentSelectedButton == nullptr)
			{
				if (NewInput == DOWN || NewInput == RIGHT)
				{
					i++;
					if (i >= MenuElements.size()) i = 0;
				}
				else
				{
					i--;
					if (i < 0) i = MenuElements.size() - 1;
				}
				std::shared_ptr<UIButton> IsButton = std::dynamic_pointer_cast<UIButton>(MenuElements[i]);
				if (IsButton)
				{
					CurrentSelectedButton = IsButton;
					CurrentSelectedButton->HoverOverride = true;
				}
			}
			break;
		}
	}
}

void Menu::CheckPlayersToStartTimer()
{
	bool AllReady = true;
	int NumPlayers = 0;
	for (auto& PStat : vPlayerStatus)
	{
		if (PStat.IsPlaying)
		{
			NumPlayers++;
			if (!PStat.IsReady)
			{
				AllReady = false;
			}
		}
	}

	if (AllReady && NumPlayers >= 2)
	{
		StartTime = 3;
		StartTimerText->sText = "Starting in " + std::to_string((int)StartTime) + "...";
		StartTimerText->SetActive(true);
	}
	else
	{
		StartTime = 3;
		StartTimerText->SetActive(false);
	}
}

void Menu::SwitchScreens(MenuScreens NewScreen)
{
	for (auto& UIElem : MenuElements)
	{
		UIElem->SetActive(false);
	}
	for (auto& UIElem : PlayerSelectElements)
	{
		UIElem->SetActive(false);
	}

	switch (NewScreen)
	{
	case Menu::MENU:
	{
		for (auto& UIElem : MenuElements)
		{
			UIElem->SetActive(true);
		}
	}
		break;
	case Menu::PLAYERSELECT:
	{
		for (auto& UIElem : PlayerSelectElements)
		{
			UIElem->SetActive(true);
		}
		for (auto& PStat : vPlayerStatus)
		{
			PStat.PlayerReadyText->SetActive(false);
		}
		StartTimerText->SetActive(false);
	}
		break;
	default:
		break;
	}
}

void StartGameBtn()
{
	std::shared_ptr<Menu> MenuScene = std::dynamic_pointer_cast<Menu>(SceneManager::GetInstance()->GetCurrentScene());
	if (MenuScene)
	{
		MenuScene->SwitchScreens(Menu::PLAYERSELECT);
	}
}

void ExitGameBtn()
{
	glutLeaveMainLoop();
}

void OptionsScreenBtn()
{
}

void PlayBtn()
{
	LevelManager::GetInstance()->SwitchToLevel("Level");
}
