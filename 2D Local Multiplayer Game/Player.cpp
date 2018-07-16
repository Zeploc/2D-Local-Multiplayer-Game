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


Player::Player(glm::vec3 StartPosition)
	: Entity({ StartPosition , {0, 0, 0}, {1, 1, 1} }, Utils::CENTER)
{
	std::shared_ptr<Plane> NewImage = std::make_shared<Plane>(Plane(0.5f, 0.5f, { 1.0f, 1.0f, 1.0f, 1.0f }, "Resources/Images/Box.png"));
	AddMesh(NewImage);
}


Player::~Player()
{

}

void Player::Update()
{
	Entity::Update();

	if (Input::GetInstance()->KeyState[(unsigned char)'d'] == Input::INPUT_HOLD || Input::GetInstance()->KeyState[(unsigned char)'d'] == Input::INPUT_FIRST_PRESS || Input::GetInstance()->Axis.x > 100)
	{
		MoveHorizontally(false);
	}
	else if (Input::GetInstance()->KeyState[(unsigned char)'a'] == Input::INPUT_HOLD || Input::GetInstance()->KeyState[(unsigned char)'a'] == Input::INPUT_FIRST_PRESS || Input::GetInstance()->Axis.x < -100)
	{
		MoveHorizontally(true);
	}
	else
	{
		v2Speed.x = 0;
	}

	if (Input::GetInstance()->KeyState[(unsigned char)'w'] == Input::INPUT_HOLD || Input::GetInstance()->KeyState[(unsigned char)'w'] == Input::INPUT_FIRST_PRESS || Input::GetInstance()->Axis.y < -100)
	{
		MoveVertical(true);
	}
	else if (Input::GetInstance()->KeyState[(unsigned char)'s'] == Input::INPUT_HOLD || Input::GetInstance()->KeyState[(unsigned char)'s'] == Input::INPUT_FIRST_PRESS || Input::GetInstance()->Axis.y > 100)
	{
		MoveVertical(false);
	}
	else
	{
		v2Speed.y = 0;
	}

	Translate(glm::vec3(v2Speed.x, v2Speed.y, 0));
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
