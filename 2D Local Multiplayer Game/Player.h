//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name		:    Camera.h
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
	
	virtual void Update() override;
	virtual void Reset();

	void ApplyKnockback(glm::vec2 Direction);
	void AttemptMelee();

private:
	// Movement
	float fJumpForce = 600.0f;
	float fSmackRange = 1.0f;
	float BaseKnockbackSize = 200.0f;
	float KnockbackModifierSize = 500.0f;
	float KnockbackPercentage = 0.1f;
	float MovementForce = 200.0f;
	float MaxSpeed = 3.0f;
	float NormalFriction = 1.0f;
	bool OutsideForcesApplying = false;
	float KnockedBackAirControl = 0.3f;
	float KnockBackControlTime = 0.2f;

	bool CanJump = true;
	float KnockedBackTimer = 0.0f;

	float RollingFriction = 0.7f;
	float RollingAngularDamping = 2.5f;
	float RollingAccelerateSpeed = 80.0f;
	bool bIsRollingMode = false;
	b2CircleShape circleShape;
	b2PolygonShape boxShape;

	const char* NormalImage = "Resources/Images/office-square.png";
	const char* BallImage = "Resources/Images/OfficeBall.png";

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

		std::shared_ptr<Level> LevelRef = std::dynamic_pointer_cast<Level>(SceneManager::GetInstance()->GetCurrentScene());
		for (auto& player : LevelRef->Players)
		{
			if (fixture->GetBody() == player->body && player != OwningPlayer)
			{
				// Push to vector result
				m_PlayerFixtureHits.push_back(player);
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
