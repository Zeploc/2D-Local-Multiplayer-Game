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
	const char* Texture = "Resources/Images/Block.png";
	float Width = 0.2f;
	float Height = 0.1f;
	glm::vec4 UVCoords = glm::vec4{ 1, 1, 1, 1 };
	CurrentPlayer = _CurrentPlayer;
	std::shared_ptr<Plane> BulletPlane = std::make_shared<Plane>(Plane(Width, Height, { 0.1f, 1.0f, 1.0f, 1.0f }, Texture, UVCoords));
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
	float Density = 3.0f;
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
		Density = 0.5f;
		break;
	case GRENADE_LAUNCHER:
		break;
	case SNIPER:
		Density = 10.0f;
		BulletSpeed = 20.0f;
		break;
	case SHOTGUN:
	default:
		break;
	}

	SetupB2BoxBody(_world, b2_dynamicBody, false, true, Density, 0.0f, true);

	BulletVelocity = { BulletSpeed, 0 };
	BulletVelocity = glm::rotateZ(glm::vec3(BulletVelocity, 0), body->GetAngle());
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
