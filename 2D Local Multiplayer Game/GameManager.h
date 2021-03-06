//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name		:    GameManager.h
// Description		:    Header file outlining the Class
// Author			:    Alex Coultas
// Mail				:    alex.cou7417@mediadesign.school.nz
//

// Library Includes //
#include <memory>
#include <map>

enum PlayerSkin
{
	OfficeSquare,
	SmexyHexy,
	GuyAngle,
	Rhombage
};

struct PlayerInfo
{
	int PlayerID = -1;
	int CurrentScore = 0;
	int CurrentGamePlace = 0;
	int FullGamePlace = 0;
	std::shared_ptr<class UIText> KnockbackText;
	PlayerSkin Skin;
	// current player image/type/asthetic
};

#pragma once
class GameManager
{
public:

	std::map<int, PlayerInfo> vPlayerInfo;

	void RemovePlayers();

	int NumRounds = 10;
	int CurrentRound = 1;

	// Singleton
public:
	static std::shared_ptr<GameManager> GetInstance();
	static void DestoryInstance();
	~GameManager(); // Shared pointer has to be able to call destructor so can't be private

private:
	static std::shared_ptr<GameManager> m_pGameManager;
	GameManager();
	GameManager(GameManager const&);              // Don't Implement
	void operator=(GameManager const&); // Don't implement
};

