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
#include "Level.h"

// Engine Includes //
#include "Engine\Plane.h"
#include "Engine\UIButton.h"
#include "Engine\SceneManager.h"

// Local Includes //
#include "Player.h"

// Prototypes
void BackToMenu();

Level::Level(std::string sSceneName) : Scene(sSceneName)
{
	std::shared_ptr<Player> PlayerEnt = std::make_shared<Player>(Player({0, 0, 0}, 0));
	AddEntity(PlayerEnt);

	std::shared_ptr<Player> Player2Ent = std::make_shared<Player>(Player({ 3, 2, 0 }, 1));
	AddEntity(Player2Ent);

	std::shared_ptr<Entity> NewEnt = std::make_shared<Entity>(Entity({ { -2, 2, 0 } ,{ 0, 0, 0 },{ 1, 1, 1 } }, Utils::CENTER));
	std::shared_ptr<Plane> NewImage = std::make_shared<Plane>(Plane(0.5f, 0.5f, { 0.3f, 0.4f, 0.9f, 1.0f }, "Resources/Images/Box.png"));
	NewEnt->AddMesh(NewImage);
	AddEntity(NewEnt);

	TestEntity = std::make_shared<Entity>(Entity({ { 2, -2, 0 } ,{ 0, 0, 0 },{ 1, 1, 1 } }, Utils::CENTER));
	std::shared_ptr<Plane> TestImage = std::make_shared<Plane>(Plane(0.5f, 0.5f, { 0.9f, 0.3f, 0.1f, 1.0f }, "Resources/Images/Box.png"));
	TestEntity->AddMesh(TestImage);
	AddEntity(TestEntity);

	std::shared_ptr<UIButton> QuitBtn(new UIButton(glm::vec2(10, Camera::GetInstance()->SCR_HEIGHT - 10), Utils::BOTTOM_LEFT, 0.0f, glm::vec4(0.3f, 0.3f, 0.3f, 1.0f), glm::vec4(0.7f, 0.7f, 0.7f, 1.0f), 480, 70, BackToMenu));
	QuitBtn->AddText("Back to Menu", "Resources/Fonts/Roboto-Thin.ttf", 34, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), Utils::CENTER, { 0, 0 });
	AddUIElement(QuitBtn);
	//bIsPersistant = true;
}


Level::~Level()
{

}

void Level::Update()
{
	Scene::Update();

}

void Level::OnLoadScene()
{
	Scene::OnLoadScene();

}

void BackToMenu()
{
	SceneManager::GetInstance()->SwitchScene("Menu");
}
