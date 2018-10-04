//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name    	:    SceneManager.cpp
// Description    	:    Game Management system
// Author       	:    Alex Coultas
// Mail         	:    alex.cou7417@mediadesign.school.nz
//

// This Includes //
#include "GameManager.h"


// Static Variables //
std::shared_ptr<GameManager> GameManager::m_pGameManager;

/************************************************************
#--Description--#:  Constructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	Takes contructor values
#--Return--#: 		NA
************************************************************/
GameManager::GameManager()
{
	// Initial Default
	PlayerInfo Player1;
	Player1.PlayerID = 0;
	vPlayerInfo.insert(std::pair<int, PlayerInfo>(0, Player1));
	PlayerInfo Player2;
	Player2.PlayerID = 1;
	vPlayerInfo.insert(std::pair<int, PlayerInfo>(1, Player2));
	PlayerInfo Player3;
	Player3.PlayerID = 2;
	vPlayerInfo.insert(std::pair<int, PlayerInfo>(2, Player3));
	PlayerInfo Player4;
	Player4.PlayerID = 3;
	vPlayerInfo.insert(std::pair<int, PlayerInfo>(3, Player4));
}


/************************************************************
#--Description--#:  Destructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	NA
#--Return--#: 		NA
************************************************************/
GameManager::~GameManager()
{
}

void GameManager::RemovePlayers()
{
	vPlayerInfo.clear();
}

/************************************************************
#--Description--#:  Retrieves static instance pointer to this class
#--Author--#: 		Alex Coultas
#--Parameters--#:	NA
#--Return--#: 		Returns static pointer to self
************************************************************/
std::shared_ptr<GameManager> GameManager::GetInstance()
{
	if (!m_pGameManager) // null or doesn't exist
	{
		m_pGameManager = std::shared_ptr<GameManager>(new GameManager());
	}
	return m_pGameManager;
}

/************************************************************
#--Description--#:  Destroys static instance pointer to this class
#--Author--#: 		Alex Coultas
#--Parameters--#:	NA
#--Return--#: 		NA
************************************************************/
void GameManager::DestoryInstance()
{
	m_pGameManager = nullptr;
}