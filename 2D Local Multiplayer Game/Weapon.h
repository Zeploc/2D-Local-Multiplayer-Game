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
// Engine Includes //
#include "Engine\Entity.h"

enum WeaponType
{
	ROCKET_LAUNCHER,
	MACHINE_GUN,
	GRENADE_LAUNCHER,
	SNIPER,
	SHOTGUN
};

class Weapon :	public Entity
{
public:
	Weapon(glm::vec2 Position, Utils::EANCHOR _Anchor, WeaponType _Weapon);
	~Weapon();

	virtual void Fire();
	virtual void Update();
	void Init(b2World & _world);

	void AddToPlayer(std::shared_ptr<class Player> NewOwner);
	void RemovePlayer();
	std::shared_ptr<class Player> GetCurrentPlayer() { return CurrentPlayer;  };

	WeaponType GetCurrentWeapon() { return CurrentWeapon; };

	glm::vec2 HoldingOffset = { 0, -0.1 };

private:
	WeaponType CurrentWeapon;
	float Timer = 0.0;
	float CooldownTime = 1.0;
	

	std::shared_ptr<class Player> CurrentPlayer;
};

