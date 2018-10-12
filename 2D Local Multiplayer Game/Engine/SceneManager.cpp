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
		it.second->DeleteScene();
		it.second = nullptr;
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
	{
		Scenes.insert(std::pair<std::string, std::shared_ptr<Scene>>(_Scene->SceneName, _Scene));
		CurrentScene = _Scene->SceneName;
		SceneToSwitch = CurrentScene;
		_Scene->OnLoadScene();
	}
	else
		Scenes.insert(std::pair<std::string, std::shared_ptr<Scene>>(_Scene->SceneName, _Scene));
}

/************************************************************
#--Description--#: 	Removes scene from scene manager
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Name of scene to remove
#--Return--#: 		NA
************************************************************/
void SceneManager::RemoveScene(std::string SceneName)
{
	if (Scenes.count(SceneName) == 0)
	{
		// Scene Doesn't exist
		LogManager::GetInstance()->DisplayLogMessage("Could not find scene " + SceneName);
		return;
	}
	Scenes[SceneName]->DeleteScene();
	Scenes.erase(SceneName);
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
		if ((*it).second == _Scene)
		{
			(*it).second->DeleteScene();
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
	if (Scenes.count(SceneName) == 0)
	{
		// Scene Doesn't exist
		LogManager::GetInstance()->DisplayLogMessage("Could not find scene " + SceneName);
		return;
	}

	if (_bInstant)
	{
		CurrentScene = SceneName;
		LogManager::GetInstance()->DisplayLogMessage("Switching to Scene \"" + Scenes[CurrentScene]->SceneName + "\"");
		Scenes[CurrentScene]->OnLoadScene();
	}
	else
		SceneToSwitch = SceneName;

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
		LogManager::GetInstance()->DisplayLogMessage("Switching to Scene \"" + Scenes[SceneToSwitch]->SceneName + "\"");
		Scenes[SceneToSwitch]->OnLoadScene();
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

std::shared_ptr<Scene> SceneManager::GetCurrentScene()
{
	if (Scenes.empty())
		return nullptr;
	else
		return Scenes[CurrentScene];
};

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

