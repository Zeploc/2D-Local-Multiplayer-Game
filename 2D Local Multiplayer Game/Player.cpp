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

// Local Includes //
#include "Level.h"

#include <iostream>
#include <glm\gtx\string_cast.hpp>


Player::Player(glm::vec3 StartPosition, int PlayerID)
	: Entity({ StartPosition , {0, 0, 0}, {1, 1, 1} }, Utils::CENTER)
{
	std::shared_ptr<Plane> NewImage;
	if (PlayerID == 1) NewImage = std::make_shared<Plane>(Plane(0.5f, 0.5f, { 0.4f, 1.0f, 0.6f, 1.0f }, "Resources/Images/Box.png"));
	else NewImage = std::make_shared<Plane>(Plane(0.5f, 0.5f, { 1.0f, 1.0f, 1.0f, 1.0f }, "Resources/Images/Box.png"));
	AddMesh(NewImage);
	m_iPlayerID = PlayerID;
}


Player::~Player()
{

}

void Player::Update()
{
	Entity::Update();

	glm::vec2 Direction = { 0, 0 };
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

	v2Speed = Direction * m_fCurrentPlayerSpeed * (float)Time::dTimeDelta;
			
	if (Input::GetInstance()->Players[m_iPlayerID]->ControllerButtons[BOTTOM_FACE_BUTTON] == Input::INPUT_FIRST_PRESS || (Input::GetInstance()->KeyState[32] == Input::INPUT_FIRST_PRESS && m_iPlayerID == 1))
	{
		//v2Speed *= 10.0f;
		body->ApplyForce(b2Vec2(0, fJumpForce), body->GetWorldCenter(), false);
	}

	if (Input::GetInstance()->Players[m_iPlayerID]->ControllerButtons[LEFT_FACE_BUTTON] == Input::INPUT_FIRST_PRESS || Input::GetInstance()->KeyState[(unsigned char)'f'] == Input::INPUT_FIRST_PRESS)
	{
		std::shared_ptr<Level> LevelRef = std::dynamic_pointer_cast<Level>(SceneManager::GetInstance()->GetCurrentScene());
		if (LevelRef)
		{
			for (auto& cPlayer : LevelRef->Players)
			{
				if (glm::distance(transform.Position, cPlayer->transform.Position) <= fSmackRange && cPlayer->m_iPlayerID != m_iPlayerID)
				{
					cPlayer->ApplyKnockback(glm::normalize(cPlayer->transform.Position - transform.Position));
				}
			}
			//LevelRef->DestroyEntity(LevelRef->DynamicBoxEntity);
		}

	}
	v2Speed *= 100.0f;
	if (body)
	{
		body->SetLinearVelocity(b2Vec2(v2Speed.x, body->GetLinearVelocity().y)); //>ApplyForce(b2Vec2(v2Speed.x, v2Speed.y), body->GetWorldCenter(), false);// 
	}
	//Translate(glm::vec3(v2Speed.x, v2Speed.y, 0));
}

void Player::ApplyKnockback(glm::vec2 Direction)
{
	Direction.x *= KnockbackSize;
	if (Direction.y <= 0.1f) Direction.y = 0.1f;
	std::cout << "Applying knockback to player " << m_iPlayerID << "by " << glm::to_string(Direction) << "\n";
	body->ApplyLinearImpulseToCenter(b2Vec2(Direction.x, Direction.y), true);// body->GetWorldCenter(), false);
}

void Player::MoveHorizontally(bool bLeft)
{
	int Direction;
	if (bLeft) Direction = -1;
	else Direction = 1;
	
	if (bLeft)
		v2Speed.x = -m_fCurrentPlayerSpeed * (float)Time::dTimeDelta;
	else
		v2Speed.x = m_fCurrentPlayerSpeed * (float)Time::dTimeDelta;
	return;
		
}

void Player::MoveVertical(bool bUp)
{
	int Direction;
	if (bUp) Direction = -1;
	else Direction = 1;

	if (bUp)
		v2Speed.y = m_fCurrentPlayerSpeed * (float)Time::dTimeDelta;
	else
		v2Speed.y = -m_fCurrentPlayerSpeed * (float)Time::dTimeDelta;
	return;

	
}
