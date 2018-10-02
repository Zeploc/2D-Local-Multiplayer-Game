// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name		:    DropoutBlock.h
// Description		:    Header file outlining the Class
// Author			:    Alex Coultas
// Mail				:    alex.cou7417@mediadesign.school.nz
//

#pragma once
// Engine Includes //
#include "Engine\Entity.h"

class DropoutBlock : public Entity
{
public:
	DropoutBlock(glm::vec2 Position, Utils::EANCHOR _Anchor, const char* ImagePath, float _Width = 0.5f, float _Height = 0.5f, float _FallDelay = 1.0f, float _RespawnTime = 4.0f);
	~DropoutBlock();

	virtual void Update() override;
	void Init(b2World& world);

	void BlockHit();
	void Drop();
	void Respawn();

private:
	float FallDelay = 1.0f;
	float RespawnTime = 2.0f;

	bool IsHit = false;
	bool IsFalling = false;
	float CurrentTimer = 0.0f;

	float FallAcceleration = 9.8f;
	float CurrentFallSpeed = 0.0f;
};

