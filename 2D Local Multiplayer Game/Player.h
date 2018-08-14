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

class Player :	public Entity
{
public:

	Player(glm::vec3 StartPosition, int PlayerID);
	~Player();
	
	virtual void Update() override;
	virtual void Reset();

	void ApplyKnockback(glm::vec2 Direction);

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

