#include "Bullet.h"

// Engine Includes //
#include "Engine/Plane.h"
#include "Engine/SceneManager.h"
#include "Engine/Scene.h"
#include "Player.h"
#include "Weapon.h"
#include <iostream>
#include "Engine\Input.h"

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
	SetupB2BoxBody(_world, b2_dynamicBody, false, true, 3.0f, 0.3f, true);
	if (CurrentPlayer->transform.Scale.x < 0)
	{
		FiredLeft = true;
	}

	if (CurrentPlayer->transform.Scale.x > 0)
	{
		FiredRight = true;
	}

	if (CurrentPlayer->CurrentWeapon->GetCurrentWeapon() == SHOTGUN)
	{
		UsingShotgun = true;
	}
}

void Bullet::Update()
{
	if (UsingShotgun)
	{
		if (FiredLeft)
		{
			this->body->SetLinearVelocity(b2Vec2{ -10,10 });
		}
		if (FiredRight)
		{
			this->body->SetLinearVelocity(b2Vec2{ 10,-10 });
		}
	}
	else
	{
		if (FiredLeft)
		{
			this->body->SetLinearVelocity(b2Vec2{ -10,0 });
		}
		if (FiredRight)
		{
			this->body->SetLinearVelocity(b2Vec2{ 10,0 });
		}
	}
	

	
	
	Entity::Update();
	
	
}
