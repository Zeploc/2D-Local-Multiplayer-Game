//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name		:    Camera.h
// Description		:    Header file outlining the Class
// Author			:    Alex Coultas
// Mail				:    alex.cou7417@mediadesign.school.nz
//

// Library Includes //
#include <vector>
#include <memory>

// OpenGL Library Includes //

// Engine Includes //

// Local Includes //
//#include "Level.h"

// This Includes //

// Static Variables //

#pragma once
class LevelManager
{
public:

	void Init();
	
	void SwitchToLevel(std::string sLevel);
	std::shared_ptr<class Level> GetCurrentActiveLevel();

	void NewRound(enum Gamemode NewGamemode);
	void RemoveExcessLevel();
	void AddRandomMapForGamemode(std::shared_ptr<class Level> LevelToAddTo);

private:
	int LastMapPlayed = -1;
	
	// Singleton
public:
	static std::shared_ptr<LevelManager> GetInstance();
	static void DestoryInstance();
	void Update();
	~LevelManager(); // Shared pointer has to be able to call destructor so can't be private

private:
	static std::shared_ptr<LevelManager> m_pLevelManager;
	LevelManager();
	LevelManager(LevelManager const&);              // Don't Implement
	float SpawnTimer = 0.5f;
	void operator=(LevelManager const&); // Don't implement
};

