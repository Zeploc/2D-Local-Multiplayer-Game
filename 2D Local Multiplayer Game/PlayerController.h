//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name		:    Player Controller.h
// Description		:    Header file outlining the Class
// Author			:    Alex Coultas
// Mail				:    alex.cou7417@mediadesign.school.nz
//

#pragma once
// Engine Includes //
#include "Engine\Entity.h"

class PlayerController : public Entity
{
public:
	PlayerController(int PlayerID, std::shared_ptr<class Level> LevelRef);
	~PlayerController();

	virtual void Update() override;

private:
	int ControllerID = -1;

	std::shared_ptr<class Level> CurrentLevel;
};

