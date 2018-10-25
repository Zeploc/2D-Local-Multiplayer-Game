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
#include "DropoutBlock.h"

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
		std::shared_ptr<Level> IsLevel = std::dynamic_pointer_cast<Level>(Scene.second);
		if (IsLevel && Scene.second != CurrentScene) // Is level and not current scene
		{
			SceneManager::GetInstance()->RemoveScene(Scene.second); // remove old level scene
			return;
		}
	}
}

void LevelManager::AddRandomMapForGamemode(std::shared_ptr<class Level> LevelToAddTo)
{
	int RandomMap = rand() % 4;
	while (RandomMap == LastMapPlayed && LastMapPlayed != -1)
	{
		RandomMap = rand() % 4;
	}
	LastMapPlayed = RandomMap;
	switch (LevelToAddTo->CurrentGamemode)
	{
	case DROPOUT:
	{
		switch (RandomMap)
		{
		default:
		case 0:
		{
			//Dropout Blocks
			LevelToAddTo->AddDropoutBlock({ -6.5, -3.5 }, 4);
			LevelToAddTo->AddDropoutBlock({ 5, -3.5 }, 4);
			LevelToAddTo->AddDropoutBlock({ -2.5, -2.5 }, 11);
			LevelToAddTo->AddDropoutBlock({ -5.5, -0.5 }, 5);
			LevelToAddTo->AddDropoutBlock({ 3.5, -0.5 }, 5);
			LevelToAddTo->AddDropoutBlock({ -1, 1 }, 5);
			LevelToAddTo->AddDropoutBlock({ -7, 1.5 }, 2);
			LevelToAddTo->AddDropoutBlock({ 6.5, 1.5 }, 2);
			LevelToAddTo->AddDropoutBlock({ -4, 2.5 }, 4);
			LevelToAddTo->AddDropoutBlock({ 2.5, 2.5 }, 4);

			// Spawn Points
			LevelToAddTo->AddSpawnPoint({ -6, -3 });
			LevelToAddTo->AddSpawnPoint({ 6, -3 });
			LevelToAddTo->AddSpawnPoint({ -2, -2 });
			LevelToAddTo->AddSpawnPoint({ 2, -2 });
			LevelToAddTo->AddSpawnPoint({ -4.5, 0 });
			LevelToAddTo->AddSpawnPoint({ 4.5, 0 });
			LevelToAddTo->AddSpawnPoint({ 0, 1.5 });
			LevelToAddTo->AddSpawnPoint({ -6.5, 2 });
			LevelToAddTo->AddSpawnPoint({ 6.5, 2 });
			LevelToAddTo->AddSpawnPoint({ -3, 3 });
			LevelToAddTo->AddSpawnPoint({ 3, 3 });
			break;
		}
		case 1:
		{
			//Dropout Blocks
			LevelToAddTo->AddDropoutBlock({ -2.5, -4 }, 11);
			LevelToAddTo->AddDropoutBlock({ -6.5, -3 }, 11);
			LevelToAddTo->AddDropoutBlock({ 1.5, -3 }, 11);
			LevelToAddTo->AddDropoutBlock({ -6.5, -2 }, 2, false);
			LevelToAddTo->AddDropoutBlock({ 6.5, -2 }, 2, false);
			LevelToAddTo->AddDropoutBlock({ -7, -1 }, 2, false);
			LevelToAddTo->AddDropoutBlock({ 7, -1 }, 2, false);
			LevelToAddTo->AddDropoutBlock({ -2, -1.5 }, 9);
			LevelToAddTo->AddDropoutBlock({ -5, -0.5 }, 5);
			LevelToAddTo->AddDropoutBlock({ 3, -0.5 }, 5);
			LevelToAddTo->AddDropoutBlock({ -1, 0 }, 5);
			LevelToAddTo->AddDropoutBlock({ -3, 1 }, 3);
			LevelToAddTo->AddDropoutBlock({ 2, 1 }, 3);
			LevelToAddTo->AddDropoutBlock({ 0, 2 }, 3, false);
			LevelToAddTo->AddDropoutBlock({ -1, 2.5 }, 5);

			LevelToAddTo->AddDropoutBlock({ -5, 1.5 }, 2);
			LevelToAddTo->AddDropoutBlock({ 4.5, 1.5 }, 2);
			LevelToAddTo->AddDropoutBlock({ -6, 2 }, 2);
			LevelToAddTo->AddDropoutBlock({ 5.5, 2 }, 2);
			LevelToAddTo->AddDropoutBlock({ -7, 2.5 }, 2);
			LevelToAddTo->AddDropoutBlock({ 6.5, 2.5 }, 2);
			LevelToAddTo->AddDropoutBlock({ -3.5, 3 }, 3);
			LevelToAddTo->AddDropoutBlock({ 2.5, 3 }, 3);


			// Spawn Points
			LevelToAddTo->AddSpawnPoint({ -4.5, -2.5 });
			LevelToAddTo->AddSpawnPoint({ 4.5, -2.5 });
			LevelToAddTo->AddSpawnPoint({ 0, -1 });
			LevelToAddTo->AddSpawnPoint({ -4, 0 });
			LevelToAddTo->AddSpawnPoint({ 4, 0 });
			LevelToAddTo->AddSpawnPoint({ 0, 3 });
			break;
		}
		case 2:
		{
			//Dropout Blocks
			LevelToAddTo->AddDropoutBlock({ -6.5, 3 }, 1);
			LevelToAddTo->AddDropoutBlock({ -6.5, -1.5 }, 1);
			LevelToAddTo->AddDropoutBlock({ 6.5, 3 }, 1);
			LevelToAddTo->AddDropoutBlock({ 6.5, -1.5 }, 1);
			LevelToAddTo->AddDropoutBlock({ -1, 3 }, 5);
			LevelToAddTo->AddDropoutBlock({ -6, 1 }, 4);
			LevelToAddTo->AddDropoutBlock({ -2.5, 1 }, 4);
			LevelToAddTo->AddDropoutBlock({ 1, 1 }, 4);
			LevelToAddTo->AddDropoutBlock({ 4.5, 1 }, 4);
			LevelToAddTo->AddDropoutBlock({ -4.5, -0.5 }, 4);
			LevelToAddTo->AddDropoutBlock({ 3, -0.5 }, 4);
			LevelToAddTo->AddDropoutBlock({ -2.5, -2 }, 4);
			LevelToAddTo->AddDropoutBlock({ 1, -2 }, 4);

			// Spawn Points
			LevelToAddTo->AddSpawnPoint({ -6.5, 3.5 });
			LevelToAddTo->AddSpawnPoint({ 6.5, 3.5 });
			LevelToAddTo->AddSpawnPoint({ -1, 3.5 });
			LevelToAddTo->AddSpawnPoint({ 1, 3.5 });
			LevelToAddTo->AddSpawnPoint({ -2.5, 1.5 });
			LevelToAddTo->AddSpawnPoint({ 2.5, 1.5 });
			LevelToAddTo->AddSpawnPoint({ -1, 1.5 });
			LevelToAddTo->AddSpawnPoint({ 1, 1.5 });
			break;
		}
		case 3:
		{
			//Dropout Blocks
			LevelToAddTo->AddDropoutBlock({ -6.5, 3 }, 12);
			LevelToAddTo->AddDropoutBlock({ 1, 3 }, 12);
			LevelToAddTo->AddDropoutBlock({ -6, 1 }, 10);
			LevelToAddTo->AddDropoutBlock({ 1.5, 1 }, 10);
			LevelToAddTo->AddDropoutBlock({ -5.5, -1 }, 8);
			LevelToAddTo->AddDropoutBlock({ 2, -1 }, 8);
			LevelToAddTo->AddDropoutBlock({ -5, -3 }, 6);
			LevelToAddTo->AddDropoutBlock({ 2.5, -3 }, 6);
			LevelToAddTo->AddDropoutBlock({ -0.5, -3.5 }, 3);

			// Spawn Points
			LevelToAddTo->AddSpawnPoint({ -6.5, 3.5 });
			LevelToAddTo->AddSpawnPoint({ 6.5, 3.5 });
			LevelToAddTo->AddSpawnPoint({ -1, 3.5 });
			LevelToAddTo->AddSpawnPoint({ 1, 3.5 });
			LevelToAddTo->AddSpawnPoint({ -5, 3.5 });
			LevelToAddTo->AddSpawnPoint({ 5, 3.5 });
			LevelToAddTo->AddSpawnPoint({ -2.5, 3.5 });
			LevelToAddTo->AddSpawnPoint({ 2.5, 3.5 });
			break;
		}
		}
	}
	break;
	case BOMB_SURVIVAL:
	default:
	{
		switch (RandomMap)
		{
		case 0:
		default:
		{
			// Blocks
			LevelToAddTo->AddBlock({ 0, -3 }, 10);
			LevelToAddTo->AddBlock({ 0, 1 }, 6);
			LevelToAddTo->AddBlock({ -5, -1 }, 3);
			LevelToAddTo->AddBlock({ 5, -1 }, 3);
			// Spikes
			LevelToAddTo->AddSpike({ -1, -2.5 });
			LevelToAddTo->AddSpike({ 1, -2.5 });
			LevelToAddTo->AddSpike({ -6, -0.5 });
			LevelToAddTo->AddSpike({ 6, -0.5 });

			// Spawn Points
			LevelToAddTo->AddSpawnPoint({ -4, -2.5 });
			LevelToAddTo->AddSpawnPoint({ 4, -2.5 });
			LevelToAddTo->AddSpawnPoint({ -4.5, -0.5 });
			LevelToAddTo->AddSpawnPoint({ 4.5, -0.5 });
			LevelToAddTo->AddSpawnPoint({ -2.5, 1.5 });
			LevelToAddTo->AddSpawnPoint({ 2.5, 1.5 });
			break;
		}
		case 1:
		{
			// Layer 1
			LevelToAddTo->AddBlock({ -7, 4 }, 6, 0.5, Utils::CENTER_LEFT, false);
			LevelToAddTo->AddBlock({ 7, 4 }, 6, 0.5, Utils::CENTER_RIGHT, false);
			LevelToAddTo->AddBlock({ -5.5, 3.5 }, 0.5, 0.5, Utils::CENTER_LEFT, false);
			LevelToAddTo->AddBlock({ 5.5, 3.5 }, 0.5, 0.5, Utils::CENTER_RIGHT, false);

			LevelToAddTo->AddBlock({ 0, 3.5 }, 0.5, 1.0, Utils::TOP_CENTER);

			// Layer 2
			LevelToAddTo->AddBlock({ -7, 2 }, 3.5, 0.5, Utils::CENTER_LEFT);
			LevelToAddTo->AddBlock({ 7, 2 }, 3.5, 0.5, Utils::CENTER_RIGHT);
			LevelToAddTo->AddBlock({ -7, 1.5 }, 0.5, 1.0, Utils::TOP_CENTER, false);
			LevelToAddTo->AddBlock({ 7, 1.5 }, 0.5, 1.0, Utils::TOP_CENTER, false);

			LevelToAddTo->AddBlock({ 0, 1 }, 3.5, 0.5, Utils::CENTER);

			// Layer 3
			LevelToAddTo->AddBlock({ -7, -0.5 }, 2, 0.5, Utils::CENTER_LEFT);
			LevelToAddTo->AddBlock({ 7, -0.5 }, 2, 0.5, Utils::CENTER_RIGHT);
			LevelToAddTo->AddBlock({ -7, -1 }, 0.5, 1.5, Utils::TOP_CENTER, false);
			LevelToAddTo->AddBlock({ 7, -1 }, 0.5, 1.5, Utils::TOP_CENTER, false);

			LevelToAddTo->AddBlock({ -3, -0.5 }, 1, 0.5, Utils::CENTER_LEFT);

			LevelToAddTo->AddBlock({ 3, -0.5 }, 1, 0.5, Utils::CENTER_RIGHT);
			LevelToAddTo->AddBlock({ -2.5, -1.0 }, 2, 0.5, Utils::CENTER_LEFT);
			LevelToAddTo->AddBlock({ 2.5, -1.0 }, 2, 0.5, Utils::CENTER_RIGHT);

			// Layer 4
			LevelToAddTo->AddBlock({ -7, -3.5 }, 2.5, 0.5, Utils::CENTER_LEFT);
			LevelToAddTo->AddBlock({ 7, -3.5 }, 2.5, 0.5, Utils::CENTER_RIGHT);

			LevelToAddTo->AddBlock({ -2.5, -3.0 }, 2, 0.5, Utils::CENTER_LEFT);
			LevelToAddTo->AddBlock({ 2.5, -3.0 }, 2, 0.5, Utils::CENTER_RIGHT);
			LevelToAddTo->AddBlock({ -3, -3.5 }, 1, 0.5, Utils::CENTER_LEFT);
			LevelToAddTo->AddBlock({ 3, -3.5 }, 1, 0.5, Utils::CENTER_RIGHT);

			LevelToAddTo->AddDropoutBlock({ -4.0, -2.0 });
			LevelToAddTo->AddDropoutBlock({ 4.0, -2.0 });

			LevelToAddTo->AddBlock({ 0, -4.0 }, 0.5, 0.5, Utils::CENTER);

			// Spawn Points
			LevelToAddTo->AddSpawnPoint({ -6, 2.5 });
			LevelToAddTo->AddSpawnPoint({ 6, 2.5 });
			LevelToAddTo->AddSpawnPoint({ 0, 1.5 });
			LevelToAddTo->AddSpawnPoint({ -6.5, 0 });
			LevelToAddTo->AddSpawnPoint({ 6.5, 0 });
			LevelToAddTo->AddSpawnPoint({ -1.5, -0.5 });
			LevelToAddTo->AddSpawnPoint({ 1.5, -0.5 });
			LevelToAddTo->AddSpawnPoint({ -2.5, -2.5 });
			LevelToAddTo->AddSpawnPoint({ 2.5, -2.5 });
			LevelToAddTo->AddSpawnPoint({ -6, -3 });
			LevelToAddTo->AddSpawnPoint({ 6, -3 });
			break;
		}
		case 2:
		{
			// Blocks
			LevelToAddTo->AddBlock({ -7, -0.5 }, 4);
			LevelToAddTo->AddBlock({ -3, -0.5 }, 4);
			LevelToAddTo->AddBlock({ 1.5, -0.5 }, 4);
			LevelToAddTo->AddBlock({ 5.5, -0.5 }, 4);

			LevelToAddTo->AddDropoutBlock({ -5, -0.5 }, 4);
			LevelToAddTo->AddDropoutBlock({ 3.5, -0.5 }, 4);

			// Spikes
			LevelToAddTo->AddSpike({ -7, 1 });
			LevelToAddTo->AddSpike({ 7, 1 });
			LevelToAddTo->AddSpike({ -1.5, 1 });
			LevelToAddTo->AddSpike({ 1.5, 1 });

			// Spawn Points
			LevelToAddTo->AddSpawnPoint({ -6, 1 });
			LevelToAddTo->AddSpawnPoint({ -5.5, 1 });
			LevelToAddTo->AddSpawnPoint({ -3, 1 });
			LevelToAddTo->AddSpawnPoint({ -2.5, 1 });
			LevelToAddTo->AddSpawnPoint({ 2.5, 1 });
			LevelToAddTo->AddSpawnPoint({ 3, 1 });
			LevelToAddTo->AddSpawnPoint({ 5.5, 1 });
			LevelToAddTo->AddSpawnPoint({ 6, 1 });
			break;
		}
		case 3:
		{
			// Blocks
			LevelToAddTo->AddBlock({ -6, 2.5 }, 5);
			LevelToAddTo->AddBlock({ -6, -0.5 }, 5);
			LevelToAddTo->AddBlock({ -6, -3.5 }, 5);
			LevelToAddTo->AddBlock({ -1, 2.5 }, 5);
			LevelToAddTo->AddBlock({ -1, -0.5 }, 5);
			LevelToAddTo->AddBlock({ -1, -3.5 }, 5);
			LevelToAddTo->AddBlock({ 4, 2.5 }, 5);
			LevelToAddTo->AddBlock({ 4, -0.5 }, 5);
			LevelToAddTo->AddBlock({ 4, -3.5 }, 5);


			LevelToAddTo->AddDropoutBlock({ -3.5, 1 }, 5);
			LevelToAddTo->AddDropoutBlock({ -3.5, -2 }, 5);
			LevelToAddTo->AddDropoutBlock({ 1.5, 1 }, 5);
			LevelToAddTo->AddDropoutBlock({ 1.5, -2 }, 5);

			// Spikes
			LevelToAddTo->AddSpike({ 0, 3 });
			LevelToAddTo->AddSpike({ 0, 0 });
			LevelToAddTo->AddSpike({ 0, -3 });

			// Spawn Points
			LevelToAddTo->AddSpawnPoint({ -5, 3 });
			LevelToAddTo->AddSpawnPoint({ -5, 0 });
			LevelToAddTo->AddSpawnPoint({ -5, -3 });
			LevelToAddTo->AddSpawnPoint({ 5, 3 });
			LevelToAddTo->AddSpawnPoint({ 5, 0 });
			LevelToAddTo->AddSpawnPoint({ 5, -3 });
			break;
		}
		}
	}
	break;
	}
}


void LevelManager::NewRound(Gamemode NewGamemode)
{
	// Make new level from gamemode
	int LevelID = 0;
	std::string NewSceneName = "Level " + std::to_string(LevelID);
	while (SceneManager::GetInstance()->Scenes.count(NewSceneName) > 0)
	{
		LevelID++;
		NewSceneName = "Level " + std::to_string(LevelID);
	}
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
