//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name    	:    Weapon.cpp
// Description    	:    main base class for a weapon
// Author       	:    Alex Coultas
// Mail         	:    alex.cou7417@mediadesign.school.nz
//

// This Includes //
#include "Weapon.h"

// Engine Includes //
#include "Engine\Plane.h"

// This Includes //
#include "Player.h"

Weapon::Weapon(glm::vec2 Position, Utils::EANCHOR _Anchor, WeaponType _Weapon)
	: Entity({ glm::vec3(Position, 2) ,{ 0, 0, 0 },{ 1, 1, 1 } }, _Anchor)
{
	const char* Texture = "Resources/Images/gun5.png";
	float Width = 1.0f;
	float Height = 1.0f;
	CurrentWeapon = _Weapon;
	switch (CurrentWeapon)
	{
	case ROCKET_LAUNCHER:
		break;
	case MACHINE_GUN:
		Texture = "Resources/Images/gun5.png";
		Width = 0.65f;
		Height = 0.15f;
		break;
	case GRENADE_LAUNCHER:
		break;
	case SNIPER:
		break;
	case SHOTGUN:
		break;
	default:
		break;
	}
	std::shared_ptr<Plane> GunImage = std::make_shared<Plane>(Plane(Width, Height, { 1.0f, 1.0f, 1.0f, 1.0f }, Texture));
	GunImage->bCullFace = false;
	AddMesh(GunImage);
}

Weapon::~Weapon()
{

}

void Weapon::Fire()
{

}

void Weapon::Update()
{
	Entity::Update();

	if (CurrentPlayer)
	{
		transform.Position = glm::vec3(glm::vec2(CurrentPlayer->transform.Position) + HoldingOffset, transform.Position.z);
		transform.Scale.x = CurrentPlayer->transform.Scale.x;
	}
}

void Weapon::AddToPlayer(std::shared_ptr<class Player> NewOwner)
{
	CurrentPlayer = NewOwner;
}

void Weapon::RemovePlayer()
{
	CurrentPlayer = nullptr;
}
