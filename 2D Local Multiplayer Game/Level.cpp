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

// Local Includes //
#include "Player.h"

Level::Level(std::string sSceneName) : Scene(sSceneName)
{
	std::shared_ptr<Player> PlayerEnt = std::make_shared<Player>(Player({0, 0, 0}));
	AddEntity(PlayerEnt);
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
