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
#include "Engine/Time.h"

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
		transform.Position = glm::vec3(glm::vec2(CurrentPlayer->transform.Position) + HoldingOffset, 2);
		transform.Scale.x = CurrentPlayer->transform.Scale.x;
		SetBox2DTransform(transform.Position, transform.Rotation.z);
	}
	if (Timer > 0)
	{
		Timer -= Time::dTimeDelta;

		if (Timer <= 0)
		{
			body->SetActive(true);
		}
	}
	
}

void Weapon::AddToPlayer(std::shared_ptr<class Player> NewOwner)
{
	CurrentPlayer = NewOwner;
	body->SetActive(false);
}

void Weapon::RemovePlayer()
{
	CurrentPlayer = nullptr;
	Timer = CooldownTime;
	
}

void Weapon::Init(b2World & _world)
{
	SetupB2BoxBody(_world, b2_staticBody, false);
	//body->SetActive(false);

	// Not collide with bodys with a group index 0f -1
	b2Filter NoPlayerCollisionFilter;
	NoPlayerCollisionFilter.categoryBits = 0x002;// .groupIndex = -1;
	NoPlayerCollisionFilter.maskBits = 0xFFFF & ~0x002; // Collide with everything but itselves

	body->GetFixtureList()->SetFilterData(NoPlayerCollisionFilter);
}