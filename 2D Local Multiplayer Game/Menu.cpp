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

// Local Includes //
#include "LevelManager.h"

// Prototpyes //
void StartGameBtn();
void ExitGameBtn();
void OptionsScreenBtn();

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

void StartGameBtn()
{
	LevelManager::GetInstance()->SwitchToLevel("Level");
}

void ExitGameBtn()
{
	glutLeaveMainLoop();
}

void OptionsScreenBtn()
{
}
