//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name		:    Weapon.h
// Description		:    Header file outlining the Class
// Author			:    Alex Coultas
// Mail				:    alex.cou7417@mediadesign.school.nz
//

#pragma once
// Base Includes //
#include "Weapon.h"

class MachineGun :	public Weapon
{
public:
	MachineGun(glm::vec2 Position, Utils::EANCHOR _Anchor);
	~MachineGun();

	virtual void Fire() override;
};

