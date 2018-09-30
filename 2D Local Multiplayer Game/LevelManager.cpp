//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name    	:    LevelManager.cpp
// Description    	:    main implementation for LevelManager
// Author       	:    Alex Coultas
// Mail         	:    alex.cou7417@mediadesign.school.nz
//

// Library Includes //

// This Includes //
#include "LevelManager.h"

// Local Includes //
#include "Menu.h"
#include "Level.h"

// Engine Includes //
#include "Engine\SceneManager.h"

// Static Variables //
std::shared_ptr<LevelManager> LevelManager::m_pLevelManager;

/************************************************************
#--Description--#:  Constructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	Takes contructor values
#--Return--#: 		NA
************************************************************/
LevelManager::LevelManager()
{

}

/************************************************************
#--Description--#:  Destructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	NA
#--Return--#: 		NA
************************************************************/
LevelManager::~LevelManager()
{
}

/************************************************************
#--Description--#:  Initialises the level manager
#--Author--#: 		Alex Coultas
#--Parameters--#:	NA
#--Return--#: 		NA
************************************************************/
void LevelManager::Init()
{
	std::shared_ptr<Menu> MenuScene = std::shared_ptr<Menu>(new Menu());
	SceneManager::GetInstance()->AddScene(MenuScene);
}

void LevelManager::SwitchToLevel(std::string sLevel)
{
	SceneManager::GetInstance()->SwitchScene(sLevel);
}

/************************************************************
#--Description--#:  Retreive current level
#--Author--#: 		Alex Coultas
#--Parameters--#:	NA
#--Return--#: 		Returns current level pointer
************************************************************/
std::shared_ptr<Level> LevelManager::GetCurrentActiveLevel()
{
	std::shared_ptr<Scene> CurrentScene = SceneManager::GetInstance()->GetCurrentScene();
	if (CurrentScene)
		return std::dynamic_pointer_cast<Level>(CurrentScene);
	return nullptr;
}

void LevelManager::RemoveExcessLevel()
{
	std::shared_ptr<Scene> CurrentScene = SceneManager::GetInstance()->GetCurrentScene();
	for (auto& Scene : SceneManager::GetInstance()->Scenes)
	{
		std::shared_ptr<Level> IsLevel = std::dynamic_pointer_cast<Level>(Scene);
		if (IsLevel && Scene != CurrentScene) // Is level and not current scene
		{
			SceneManager::GetInstance()->RemoveScene(Scene); // remove old level scene
			return;
		}
	}
}

void LevelManager::NewRound(Gamemode NewGamemode)
{
	// Make new level from gamemode
	std::string NewSceneName = "Level " + SceneManager::GetInstance()->Scenes.size();
	std::shared_ptr<Level> LevelScene = std::shared_ptr<Level>(new Level(NewSceneName, NewGamemode));
	// Add and switch to level
	SceneManager::GetInstance()->AddScene(LevelScene);
	SceneManager::GetInstance()->SwitchScene(NewSceneName);
}

/************************************************************
#--Description--#:  Retrieves static instance pointer to this class
#--Author--#: 		Alex Coultas
#--Parameters--#:	NA
#--Return--#: 		Returns static pointer to self
************************************************************/
std::shared_ptr<LevelManager> LevelManager::GetInstance()
{
	if (!m_pLevelManager) // null or doesn't exist
	{
		m_pLevelManager = std::shared_ptr<LevelManager>(new LevelManager());
	}
	return m_pLevelManager;
}

/************************************************************
#--Description--#:  Destroys static instance pointer to this class
#--Author--#: 		Alex Coultas
#--Parameters--#:	NA
#--Return--#: 		NA
************************************************************/
void LevelManager::DestoryInstance()
{
	m_pLevelManager = nullptr;
}