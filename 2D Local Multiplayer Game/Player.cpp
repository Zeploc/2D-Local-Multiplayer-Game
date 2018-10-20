//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name    	:    Player.cpp
// Description    	:    main implementation for Player
// Author       	:    Alex Coultas
// Mail         	:    alex.cou7417@mediadesign.school.nz
//

// This Includes //
#include "Player.h"

// Engine Includes //
#include "Engine\Plane.h"
#include "Engine\Input.h"
#include "Engine\Time.h"
#include "Engine\SceneManager.h"
#include "Engine\CXBOXController.h"
#include "Engine/SoundManager.h"

// Local Includes //
#include "Level.h"
#include "Weapon.h"
#include "GameManager.h"

#include <iostream>
#include <glm\gtx\string_cast.hpp>


Player::Player(glm::vec3 StartPosition, int PlayerID) // Will also take the type of player (asthetic)
	: Entity({ StartPosition , {0, 0, 0}, {1, 1, 1} }, Utils::CENTER)
{
	glm::vec4 Colour = { 1.0f, 1.0f, 1.0f, 1.0f };
	m_iPlayerID = PlayerID;

	switch (GameManager::GetInstance()->vPlayerInfo[m_iPlayerID].Skin)
	{
	case OfficeSquare:
	{
		NormalImage = "Resources/Images/office-square.png";
		BallImage = "Resources/Images/OfficeBall.png";
		break;
	}
	case SmexyHexy:
	{
		NormalImage = "Resources/Images/SmexyHexy.png";
		BallImage = "Resources/Images/SmexyBall.png";
		break;
	}
	case GuyAngle:
	{
		NormalImage = "Resources/Images/Guyangle.png";
		BallImage = "Resources/Images/GuyBall.png";
		break;
	}
	case Rhombage:
	{
		NormalImage = "Resources/Images/Rhombage.png";
		BallImage = "Resources/Images/Rhomball.png";
		break;
	}
	default:
		break;
	}

	std::shared_ptr<Plane> NewImage = std::make_shared<Plane>(Plane(0.5f, 0.5f, Colour, NormalImage));

	AddMesh(NewImage);
	NewImage->bCullFace = false;

	// Define another Circle shape for our dynamic body.
	circleShape.m_radius = EntityMesh->m_fHeight / 2.0f;

	boxShape.SetAsBox(EntityMesh->m_fWidth / 2.0f, EntityMesh->m_fHeight / 2.0f);
}


Player::~Player()
{

}

void Player::Init(b2World& world)
{
	// Not collide with bodys with a group index 0f -1
	//b2Filter NoPlayerCollisionFilter;
	//NoPlayerCollisionFilter.categoryBits = 0x004;// .groupIndex = -1;
	//NoPlayerCollisionFilter.maskBits = 0xFFFF & ~0x004; // Collide with everything but other players

	SetupB2BoxBody(world, b2_dynamicBody, false, true, 5.0f, 0.0f);
	//body->GetFixtureList()->SetFilterData(NoPlayerCollisionFilter);

	SoundManager::GetInstance()->AddAudio("Resources/Sounds/Hit.wav", false, "KnockbackSound " + std::to_string(m_iPlayerID));
}

void Player::Update()
{
	Entity::Update();

	if (CurrentHitVisualCooldown > 0)
	{
		CurrentHitVisualCooldown -= Time::dTimeDelta;
		if (CurrentHitVisualCooldown <= 0)
		{
			SetHitVisual(false);
		}
	}

	float TimeStepRate = 60.0f;// (60 / Time::dTimeDelta) / 60.0f;
	if (body)
	{
		CheckGroundRay Result;
		b2Vec2 CurrentPosition = b2Vec2(transform.Position.x, transform.Position.y);
		b2Vec2 EndPosition = CurrentPosition + b2Vec2(0.0f, -EntityMesh->m_fHeight / 2.0f - 0.05f);
		body->GetWorld()->RayCast(&Result, CurrentPosition, EndPosition);
		if (Result.Hit && !CanJump)
		{
			CanJump = true;
		}

		if ((Input::GetInstance()->KeyState[(unsigned char)'g'] == Input::INPUT_FIRST_PRESS && m_iPlayerID == 1) || Input::GetInstance()->Players[m_iPlayerID]->ControllerButtons[TOP_FACE_BUTTON] == Input::INPUT_FIRST_PRESS)
		{
			/*b2Filter NoCollisionFilter;
			NoCollisionFilter.groupIndex = bIsRollingMode - 2;
			body->GetFixtureList()->SetFilterData(NoCollisionFilter);*/

			bIsRollingMode = !bIsRollingMode;

			b2Fixture *fixtureA = body->GetFixtureList();
			body->DestroyFixture(fixtureA);

			// Define the dynamic body fixture.
			b2FixtureDef fixtureDef;
			if (bIsRollingMode)
			{
				fixtureDef.shape = &circleShape;
				// Override the default friction.
				fixtureDef.friction = RollingFriction;
				body->SetAngularDamping(RollingAngularDamping);
				body->SetFixedRotation(false);
				std::dynamic_pointer_cast<Plane>(EntityMesh)->TextureSource = BallImage;
				EntityMesh->Rebind();
			}
			else
			{
				fixtureDef.shape = &boxShape;
				// Override the default friction.
				fixtureDef.friction = NormalFriction;
				body->SetTransform(body->GetPosition(), 0.0f);
				body->SetAngularDamping(0.0f);
				body->SetFixedRotation(true);
				std::dynamic_pointer_cast<Plane>(EntityMesh)->TextureSource = NormalImage;
				EntityMesh->Rebind();
			}

			//// Not collide with bodys with a group index 0f -1
			//b2Filter NoPlayerCollisionFilter;
			//NoPlayerCollisionFilter.groupIndex = -1;
			//fixtureDef.filter = NoPlayerCollisionFilter;
			// Set the box density to be non-zero, so it will be dynamic.
			fixtureDef.density = 5.0f;
			
			// Add the shape to the body.
			body->CreateFixture(&fixtureDef);
		}
	}

	glm::vec2 Direction = { 0.0f, 0.0f };
	glm::vec2 LeftThumbStick = { Input::GetInstance()->Players[m_iPlayerID]->GetState().Gamepad.sThumbLX , Input::GetInstance()->Players[m_iPlayerID]->GetState().Gamepad.sThumbLY };

	bool APressed = m_iPlayerID == 1 && (Input::GetInstance()->KeyState[(unsigned char)'a'] == Input::INPUT_HOLD || Input::GetInstance()->KeyState[(unsigned char)'a'] == Input::INPUT_FIRST_PRESS);
	bool DPressed = m_iPlayerID == 1 && (Input::GetInstance()->KeyState[(unsigned char)'d'] == Input::INPUT_HOLD || Input::GetInstance()->KeyState[(unsigned char)'d'] == Input::INPUT_FIRST_PRESS);

	if (LeftThumbStick.x > 10000 || LeftThumbStick.x < -10000)
	{
		Direction.x = LeftThumbStick.x;
	}
	else if (APressed || DPressed)
	{
		if (!(APressed && DPressed))
		{
			if (APressed) Direction.x = -1;
			else Direction.x = 1;
		}
	}

	if (LeftThumbStick.y > 10000 || LeftThumbStick.y < -10000)
	{
		Direction.y = LeftThumbStick.y;
	}
	if (glm::length(Direction) > 0) Direction = glm::normalize(Direction);

	if (Direction.x < 0 && transform.Scale.x >= 0)
		transform.Scale.x = -1.0f;
	else if (Direction.x > 0 && transform.Scale.x <= 0)
		transform.Scale.x = 1.0f;
		
	if (CanJump && (Input::GetInstance()->Players[m_iPlayerID]->ControllerButtons[BOTTOM_FACE_BUTTON] == Input::INPUT_FIRST_PRESS || (Input::GetInstance()->KeyState[32] == Input::INPUT_FIRST_PRESS && m_iPlayerID == 1)))
	{
		float ForceToCounterCurrentVelocity = body->GetLinearVelocity().y * body->GetMass() * TimeStepRate;
		if (bIsRollingMode) body->ApplyForce(b2Vec2(0, RollingJumpForce - ForceToCounterCurrentVelocity), body->GetWorldCenter(), true);
		else body->ApplyForce(b2Vec2(0, fJumpForce - ForceToCounterCurrentVelocity), body->GetWorldCenter(), true);
		
		CanJump = false;
	}

	if (Input::GetInstance()->Players[m_iPlayerID]->ControllerButtons[LEFT_FACE_BUTTON] == Input::INPUT_FIRST_PRESS || (Input::GetInstance()->KeyState[(unsigned char)'f'] == Input::INPUT_FIRST_PRESS  && m_iPlayerID == 1))
	{
		AttemptMelee();
	}

	if ((Input::GetInstance()->KeyState[(unsigned char)'e'] == Input::INPUT_FIRST_PRESS && m_iPlayerID == 1) || Input::GetInstance()->Players[m_iPlayerID]->ControllerButtons[RIGHT_FACE_BUTTON] == Input::INPUT_FIRST_PRESS)
	{
		DropCurrentWeapon();
	}

	if ((Input::GetInstance()->MouseState[Input::MOUSE_LEFT] == Input::INPUT_FIRST_PRESS && m_iPlayerID == 1) && CurrentWeapon != NULL || Input::GetInstance()->Players[m_iPlayerID]->ControllerButtons[RIGHT_BUTTON] == Input::INPUT_FIRST_PRESS && CurrentWeapon != NULL)
	{
		Fire();
	}
	
	if (body)
	{
		float ForceToCounterCurrentVelocity = body->GetLinearVelocity().x * body->GetMass() * TimeStepRate;
		float ForceToApply = MaxSpeed * body->GetMass() * TimeStepRate;


		//if (bIsRollingMode)
		// No outside forces applying
		if (!OutsideForcesApplying || bIsRollingMode)
		{

			if (bIsRollingMode)
				body->ApplyForce(b2Vec2(Direction.x * RollingAccelerateSpeed, 0.0f), body->GetWorldCenter(), true);
			// Trys to move sideways
			else if ((Direction.x > 0 && body->GetLinearVelocity().x < MaxSpeed) || (Direction.x < 0 && body->GetLinearVelocity().x > -MaxSpeed))
			{
				body->ApplyForce(b2Vec2(Direction.x * ForceToApply - ForceToCounterCurrentVelocity, 0.0f), body->GetWorldCenter(), true);

				body->GetFixtureList()->SetFriction(0.0f);
			}
			//// Trys to move left, and is not currently moving left
			//else if ()
			//{
			//	if (!bIsRollingMode)
			//		body->ApplyForce(b2Vec2(Direction.x * ForceToApply - ForceToCounterCurrentVelocity, 0.0f), body->GetWorldCenter(), true);
			//	else
			//		body->ApplyForce(b2Vec2(Direction.x * RollingAccelerateSpeed, 0.0f), body->GetWorldCenter(), true);

			//	if (!bIsRollingMode) body->GetFixtureList()->SetFriction(0.0f);
			//}
			// Body is moving but input not moving
			else if (Direction.x == 0.0f)
			{
				if (!bIsRollingMode)
				{
					body->ApplyForce(b2Vec2(-ForceToCounterCurrentVelocity, 0.0f), body->GetWorldCenter(), true);
					body->GetFixtureList()->SetFriction(NormalFriction);
				}
			}
		}
		// Outside forces applying
		else if (OutsideForcesApplying && !bIsRollingMode)
		{			
			// Being knocked back
			if (KnockedBackTimer > 0)
			{
				KnockedBackTimer -= Time::dTimeDelta;
				if (KnockedBackTimer <= 0.0f)
					KnockedBackTimer = 0.0f;
			}
			// Nnockback timer finished and is trying to move
			else if (abs(Direction.x) > 0.2f)
			{
				if (abs(body->GetLinearVelocity().x) <= MaxSpeed)
				{
					OutsideForcesApplying = false;
				}
				else
				{
					float ForceToApply = KnockedBackAirControl * body->GetMass() *60.0f;
					body->ApplyForce(b2Vec2(Direction.x * ForceToApply, 0.0f), body->GetWorldCenter(), true);
				}
			}
			
			if (!bIsRollingMode) body->GetFixtureList()->SetFriction(NormalFriction);
			else  body->GetFixtureList()->SetFriction(RollingFriction);
		}		
		//if (m_iPlayerID == 1) std::cout << "Velocity " << body->GetLinearVelocity().x << ", " << body->GetLinearVelocity().y << " with friction " << body->GetFixtureList()->GetFriction() << std::endl;
	}
}

void Player::Reset()
{
	CanJump = true;
	OutsideForcesApplying = false;
	KnockedBackTimer = 0.0f;
}

void Player::ApplyKnockback(glm::vec2 Direction, bool Normalize)
{
	SetHitVisual(true);
	SoundManager::GetInstance()->PlayAudio("KnockbackSound " + std::to_string(m_iPlayerID));
	if (Normalize)
	{
		Direction = glm::normalize(Direction);
		Direction *= BaseKnockbackSize * KnockbackPercentage;

		if (glm::normalize(Direction).y >= -0.1f && glm::normalize(Direction).y <= 0.1f)
			Direction.y = 0.5f;
	}
	else
	{
		if (glm::normalize(Direction).y >= -0.1f && glm::normalize(Direction).y <= 0.1f)
			Direction.y = abs(Direction.x) * 0.5;
		Direction *= BaseRollKnockbackSize * KnockbackPercentage;
	}
	KnockbackPercentage += 0.1f;

	std::cout << "Applying knockback to player " << m_iPlayerID << "by " << glm::to_string(Direction) << "\n";
	body->ApplyForceToCenter(b2Vec2(Direction.x, Direction.y), true);
	OutsideForcesApplying = true;
	KnockedBackTimer = KnockBackControlTime;
	GameManager::GetInstance()->vPlayerInfo[m_iPlayerID].KnockbackText->sText = std::to_string(int(KnockbackPercentage * 100)) + "%";
}

void Player::AttemptMelee()
{
	PlayerRay Result(this->shared_from_this());
	b2Vec2 CurrentPosition = b2Vec2(transform.Position.x + (EntityMesh->m_fWidth / 2.0f) * -transform.Scale.x, transform.Position.y);
	b2Vec2 EndPosition = CurrentPosition + b2Vec2((EntityMesh->m_fWidth / 2.0f + fSmackRange) * transform.Scale.x, 0.0f);
	body->GetWorld()->RayCast(&Result, CurrentPosition, EndPosition);
	for (int i = 0; i < Result.m_PlayerFixtureHits.size(); i++)
	{
		Result.m_PlayerFixtureHits[i]->ApplyKnockback(Result.m_PlayerFixtureHits[i]->transform.Position - transform.Position);
		//std::cout << "Hit Player " << Result.m_PlayerFixtureHits[i]->m_iPlayerID << std::endl;
	}

}

bool Player::GetIsRolling()
{
	return bIsRollingMode;
}

void Player::EquipWeapon(std::shared_ptr<class Weapon> NewWeapon)
{
	if(CurrentWeapon)
	{
		return;
	}
	NewWeapon->AddToPlayer(std::dynamic_pointer_cast<Player>(this->shared_from_this()));
	CurrentWeapon = NewWeapon;
}

void Player::DropCurrentWeapon()
{
	if (CurrentWeapon) CurrentWeapon->RemovePlayer();
	CurrentWeapon = nullptr;
}

void Player::Fire()
{
	CurrentWeapon->Fire();
}

void Player::SetHitVisual(bool ShowVisual)
{
	if (ShowVisual)
	{
		EntityMesh->Colour = { 1.0f, 0.1f, 0.1f, 1.0f };
		EntityMesh->Rebind();
		CurrentHitVisualCooldown = HitVisualCooldown;
	}
	else
	{
		CurrentHitVisualCooldown = 0;
		EntityMesh->Colour = { 1.0f, 1.0f, 1.0f, 1.0f };
		EntityMesh->Rebind();
	}
}

