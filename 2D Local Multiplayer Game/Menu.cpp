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
	std::shared_ptr<UIButton> PlayBtn(new UIButton(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, Camera::GetInstance()->SCR_HEIGHT - 100), Utils::BOTTOM_CENTER, 0.0f, glm::vec4(0.3f, 0.3f, 0.3f, 1.0f), glm::vec4(0.7f, 0.7f, 0.7f, 1.0f), 480, 70, PlayBtn));
	PlayBtn->AddText("Play", "Resources/Fonts/Roboto-Thin.ttf", 34, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), Utils::CENTER, { 0, 0 });

	AddUIElement(PlayerTitle);
	AddUIElement(PlayBtn);

	PlayerSelectElements.push_back(PlayerTitle);
	PlayerSelectElements.push_back(PlayBtn);

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

}

void Menu::OnLoadScene()
{
	Scene::OnLoadScene();

}

void Menu::SelectCurrentButton()
{
	std::cout << "Selecting current button\n";
	CurrentSelectedButton->Pressed();
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
