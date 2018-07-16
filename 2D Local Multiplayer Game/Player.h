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

	Player(glm::vec3 StartPosition);
	~Player();
	
	virtual void Update() override;

private:
	// Movement
	void MoveHorizontally(bool bLeft);
	void MoveVertical(bool bUp);
	glm::vec2 v2Speed = { 0, 0};
	float m_fCurrentPlayerSpeed = 3.0f;
};

