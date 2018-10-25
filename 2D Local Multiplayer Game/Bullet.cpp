#include "Bullet.h"

// Engine Includes //
#include "Engine/Plane.h"
#include "Engine/SceneManager.h"
#include "Engine/Scene.h"
#include "Player.h"
#include "Weapon.h"
#include <iostream>
#include "Engine\Input.h"
#include <glm\gtx\rotate_vector.hpp>

Bullet::Bullet(Utils::Transform _Transform, Utils::EANCHOR _Anchor, std::shared_ptr<Player> _CurrentPlayer)
	: Entity(_Transform, _Anchor)
{
	CurrentPlayer = _CurrentPlayer;
	const char* Texture = "Resources/Images/SniperBullet.png";
	switch (CurrentPlayer->CurrentWeapon->GetCurrentWeapon())
	{
	case ROCKET_LAUNCHER:
	case MACHINE_GUN:
		BulletSpeed = 10;
		KnockbackSize = -80;
		Texture = "Resources/Images/SniperBullet.png";
		break;
	case GRENADE_LAUNCHER:
	case SHOTGUN:
		BulletSpeed = 10;
		KnockbackSize = 10;
		Texture = "Resources/Images/ShotgunBullet.png";
		break;
	case SNIPER:
		BulletSpeed = 30.0f;
		KnockbackSize = 100;
		Texture = "Resources/Images/SniperBullet.png";
		break;
	default:
		
		break;
	}
	float Width = 0.2f;
	float Height = 0.1f;
	glm::vec4 UVCoords = glm::vec4{ 0, 1, 0, 1 };
	
	std::shared_ptr<Plane> BulletPlane = std::make_shared<Plane>(Plane(Width, Height, { 1.0f, 1.0f, 1.0f, 1.0f }, Texture, UVCoords));
	AddMesh(BulletPlane);
	BulletPlane->bCullFace = false;
	transform.Position.x = CurrentPlayer->transform.Position.x + (CurrentPlayer->transform.Scale.x * CurrentPlayer->EntityMesh->m_fWidth / 2 + 0.1f);
	//transform.Position.y = CurrentPlayer->transform.Position.y + CurrentPlayer->EntityMesh->m_fHeight / 2;
}

Bullet::~Bullet()
{
}

void Bullet::Init(b2World & _world)
{
	
	if (CurrentPlayer->transform.Scale.x < 0)
	{
		FiredLeft = true;
	}

	if (CurrentPlayer->transform.Scale.x > 0)
	{
		FiredRight = true;
	}

	switch (CurrentPlayer->CurrentWeapon->GetCurrentWeapon())
	{
	case ROCKET_LAUNCHER:
		break;
	case MACHINE_GUN:
		BulletSpeed = 10;
		KnockbackSize = -80;
		break;
	case GRENADE_LAUNCHER:
		break;
	case SNIPER:
		BulletSpeed = 30.0f;
		KnockbackSize = 100;
		break;
	case SHOTGUN:
		BulletSpeed = 10;
		KnockbackSize = 10;
	default:
		break;
	}

	SetupB2BoxBody(_world, b2_dynamicBody, false, true, 3, 0.0f, true);

	BulletVelocity = { BulletSpeed, 0 };
	BulletVelocity = glm::rotateZ(glm::vec3(BulletVelocity, 0), (body->GetAngle() * b2_pi) / 180);
}

void Bullet::Update()
{

	if (FiredLeft)
	{
		this->body->SetLinearVelocity(b2Vec2{ -BulletVelocity.x, BulletVelocity.y });
	}
	if (FiredRight)
	{
		this->body->SetLinearVelocity(b2Vec2{ BulletVelocity.x, BulletVelocity.y });
	}	
	
	Entity::Update();
		
}
