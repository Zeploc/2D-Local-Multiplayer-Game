//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name		:    Player.h
// Description		:    Header file outlining the Class
// Author			:    Alex Coultas
// Mail				:    alex.cou7417@mediadesign.school.nz
//

#pragma once
// Engine Includes //
#include "Engine\Entity.h"
#include "Engine/SceneManager.h"

// Library Includes //
#include <vector>

// Local Includes //
#include "Level.h"

class Player :	public Entity
{
public:

	Player(glm::vec3 StartPosition, int PlayerID);
	~Player();
	void Init(b2World& world);
	
	virtual void Update() override;
	virtual void Reset();

	void ChangePhysicsMode(bool IsBall);

	void ApplyKnockback(glm::vec2 Direction, bool Normalize = true);
	void AttemptMelee();
	bool GetIsRolling();
	void EquipWeapon(std::shared_ptr<class Weapon> NewWeapon);
	void DropCurrentWeapon();
	void Fire();
	std::shared_ptr<class Weapon> CurrentWeapon;
	int GetID() {
		return m_iPlayerID;
	};

private:
	// Movement
	float fJumpForce = 10.0f;
	float fSmackRange = 1.0f;
	float BaseKnockbackSize = 200.0f;
	float BaseRollKnockbackSize = 50.0f;
	float KnockbackPercentage = 1.0f;
	float MovementForce = 200.0f;
	float MaxSpeed = 3.0f;
	float NormalFriction = 1.0f;
	bool OutsideForcesApplying = false;
	float KnockedBackAirControl = 0.3f;
	float KnockBackControlTime = 0.2f;
	float PlayerDensity = 6.1f;

	bool CanJump = true;
	float KnockedBackTimer = 0.0f;

	float RollingJumpForce = 8.3f;
	float RollingFriction = 0.7f;
	float RollingAngularDamping = 2.5f;
	float RollingAccelerateSpeed = 12.0f;
	bool bIsRollingMode = false;
	b2CircleShape circleShape;
	b2PolygonShape boxShape;

	const char* NormalImage = "Resources/Images/office-square.png";
	const char* BallImage = "Resources/Images/OfficeBall.png";
	float CurrentHitVisualCooldown = 0;
	float HitVisualCooldown = 0.25f;
	void SetHitVisual(bool ShowVisual);


	int m_iPlayerID = -1;

	
};

class CheckGroundRay : public b2RayCastCallback
{
public:
	CheckGroundRay()
	{
		m_fixture = NULL;
	}

	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
	{
		m_fixture = fixture;
		m_point = point;
		m_normal = normal;
		m_fraction = fraction;
		Hit = true;
		return fraction;
	}

	b2Fixture* m_fixture;
	b2Vec2 m_point;
	b2Vec2 m_normal;
	float32 m_fraction;
	bool Hit = false;
};

class PlayerRay : public b2RayCastCallback
{
public:
	PlayerRay(std::shared_ptr<Entity> _OwningPlayer)
	{
		OwningPlayer = std::dynamic_pointer_cast<Player>(_OwningPlayer);
		//m_fixture = NULL;
	}

	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
	{
		//m_fixture = fixture;
		m_point = point;
		m_normal = normal;
		m_fraction = fraction;
		Hit = true;

		Entity* IsEntity = reinterpret_cast<Entity*>(fixture->GetBody()->GetUserData());
		std::shared_ptr<Player> IsPlayer = std::dynamic_pointer_cast<Player>(IsEntity->shared_from_this());
		if (IsPlayer)
		{
			std::shared_ptr<Level> LevelRef = std::dynamic_pointer_cast<Level>(SceneManager::GetInstance()->GetCurrentScene());
			for (auto& player : LevelRef->Players)
			{

				//if (fixture->GetBody() == player.second->body && player.second != OwningPlayer)
				if (IsPlayer->GetID() == player.second->GetID() && player.second != OwningPlayer)
				{
					// Push to vector result
					m_PlayerFixtureHits.push_back(player.second);
				}
			}
		}

		return fraction;
	}
	std::shared_ptr<Player> OwningPlayer;
	std::vector<std::shared_ptr<Player>> m_PlayerFixtureHits;
	b2Vec2 m_point;
	b2Vec2 m_normal;
	float32 m_fraction;
	bool Hit = false;
};
