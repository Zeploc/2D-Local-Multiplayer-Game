//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name    	:    SceneManager.cpp
// Description    	:    main implementation for SceneManager
// Author       	:    Alex Coultas
// Mail         	:    alex.cou7417@mediadesign.school.nz
//

// Library Includes //
#include <iostream>

// OpenGL Library Includes //

// Engine Includes //
#include "Scene.h"
#include "LogManager.h"

// Local Includes //

// This Includes //
#include "SceneManager.h"

// Static Variables //
std::shared_ptr<SceneManager> SceneManager::m_pSceneManager;

/************************************************************
#--Description--#:  Constructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	Takes contructor values
#--Return--#: 		NA
************************************************************/
SceneManager::SceneManager()
{

}
/************************************************************
#--Description--#:  Destructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	NA
#--Return--#: 		NA
************************************************************/
SceneManager::~SceneManager()
{
	for (auto it : Scenes)
	{
		it->DeleteScene();
		it = nullptr;
	}
}

/************************************************************
#--Description--#: 	Adds scene to scene manager
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Scene to add
#--Return--#: 		NA
************************************************************/
void SceneManager::AddScene(std::shared_ptr<Scene> _Scene)
{
	if (Scenes.empty())
		_Scene->OnLoadScene();
	Scenes.push_back(_Scene);
}

/************************************************************
#--Description--#: 	Removes scene from scene manager
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Name of scene to remove
#--Return--#: 		NA
************************************************************/
void SceneManager::RemoveScene(std::string SceneName)
{
	for (auto it = Scenes.begin(); it != Scenes.end(); ++it)
	{
		if ((*it)->SceneName == SceneName)
		{
			(*it)->DeleteScene();
			Scenes.erase(it);
			return;
		}
	}
}

/************************************************************
#--Description--#: 	Removes scene from scene manager
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Scene to remove
#--Return--#: 		NA
************************************************************/
void SceneManager::RemoveScene(std::shared_ptr<Scene> _Scene)
{
	for (auto it = Scenes.begin(); it != Scenes.end(); ++it)
	{
		if ((*it) == _Scene)
		{
			(*it)->DeleteScene();
			Scenes.erase(it);
			return;
		}
	}
	
}

/************************************************************
#--Description--#: 	Switches to scene with matching name
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Takes in scene name to switch to
#--Return--#: 		Returns true if scene found, if not returns false
************************************************************/
void SceneManager::SwitchScene(std::string SceneName, bool _bInstant)
{
	for (unsigned int i = 0; i < Scenes.size(); i++)
	{
		if (Scenes[i]->SceneName == SceneName)
		{
			if (_bInstant)
			{
				CurrentScene = i;
				Scenes[SceneToSwitch]->OnLoadScene();
				LogManager::GetInstance()->DisplayLogMessage("Switching to Scene \"" + Scenes[SceneToSwitch]->SceneName + "\"");
			}
			else
				SceneToSwitch = i;
			return;
		}
	}
	LogManager::GetInstance()->DisplayLogMessage("Could not find scene " + SceneName);
}

/************************************************************
#--Description--#: 	Updates the current scene every frame
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void SceneManager::UpdateCurrentScene()
{
	Scenes[CurrentScene]->Update();
	// Switch to scene flag has been set
	if (SceneToSwitch != CurrentScene)
	{
		CurrentScene = SceneToSwitch;
		Scenes[SceneToSwitch]->OnLoadScene();
		LogManager::GetInstance()->DisplayLogMessage("Switching to Scene \"" + Scenes[SceneToSwitch]->SceneName + "\"");
	}
}

/************************************************************
#--Description--#:	Render Current scene to the screen
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void SceneManager::RenderCurrentScene()
{
	Scenes[CurrentScene]->RenderScene();
}

/************************************************************
#--Description--#:  Retrieves static instance pointer to this class
#--Author--#: 		Alex Coultas
#--Parameters--#:	NA
#--Return--#: 		Returns static pointer to self
************************************************************/
std::shared_ptr<SceneManager> SceneManager::GetInstance()
{
	if (!m_pSceneManager) // null or doesn't exist
	{
		m_pSceneManager = std::shared_ptr<SceneManager>(new SceneManager());
	}
	return m_pSceneManager;
}

/************************************************************
#--Description--#:  Destroys static instance pointer to this class
#--Author--#: 		Alex Coultas
#--Parameters--#:	NA
#--Return--#: 		NA
************************************************************/
void SceneManager::DestoryInstance()
{
	m_pSceneManager = nullptr;
}

