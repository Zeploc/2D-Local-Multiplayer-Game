//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name		:    SceneManager.h
// Description		:    Header file outlining the Class
// Author			:    Alex Coultas
// Mail				:    alex.cou7417@mediadesign.school.nz
//

// Library Includes //
#include <vector>
#include <memory>

class Scene;

#pragma once
class SceneManager
{
public:

	std::vector<std::shared_ptr<Scene>> Scenes;

	void AddScene(std::shared_ptr<Scene> _Scene);
	void RemoveScene(std::string SceneName);
	void RemoveScene(std::shared_ptr<Scene> _Scene);
	void SwitchScene(std::string SceneName);

	void UpdateCurrentScene();
	void RenderCurrentScene();
	std::shared_ptr<Scene> GetCurrentScene() { return Scenes[CurrentScene]; };

	int CurrentScene = 0;

	// Singleton
public:
	static std::shared_ptr<SceneManager> GetInstance();
	static void DestoryInstance();
	~SceneManager(); // Shared pointer has to be able to call destructor so can't be private

private:
	static std::shared_ptr<SceneManager> m_pSceneManager;
	SceneManager();
	SceneManager(SceneManager const&);              // Don't Implement
	void operator=(SceneManager const&); // Don't implement
};


