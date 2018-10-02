//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name    	:    DropoutBlock.cpp
// Description    	:    Drop out hazzard block
// Author       	:    Alex Coultas
// Mail         	:    alex.cou7417@mediadesign.school.nz
//

// This Includes //
#include "DropoutBlock.h"

// Engine Includes //
#include "Engine\Plane.h"
#include "Engine\Time.h"


DropoutBlock::DropoutBlock(glm::vec2 Position, Utils::EANCHOR _Anchor, const char* ImagePath, float _Width, float _Height, float _FallDelay, float _RespawnTime)
	: Entity({ glm::vec3(Position, 1) ,{ 0, 0, 0 },{ 1, 1, 1 } }, _Anchor)
{
	FallDelay = _FallDelay;
	RespawnTime = _RespawnTime;
	std::shared_ptr<Plane> BlockImage = std::make_shared<Plane>(Plane(_Width, _Height, { 1.0f, 1.0f, 1.0f, 1.0f }, ImagePath));
	AddMesh(BlockImage);

}


DropoutBlock::~DropoutBlock()
{

}

void DropoutBlock::Update()
{
	if (IsHit)
	{
		if (CurrentTimer > 0)
		{
			CurrentTimer -= Time::dTimeDelta;
		}
		else
		{
			Drop();
		}
	}
	else if (IsFalling)
	{
		glm::vec3 NewPosition = transform.Position;
		CurrentFallSpeed += FallAcceleration * Time::dTimeDelta;
		NewPosition.y -= CurrentFallSpeed * Time::dTimeDelta;
		transform.Position = NewPosition;
		SetBox2DTransform(NewPosition, transform.Rotation.z);
		// move down
		if (CurrentTimer > 0)
		{
			CurrentTimer -= Time::dTimeDelta;
		}
		else
		{
			Respawn();
		}
	}
}

void DropoutBlock::Init(b2World& world)
{
	SetupB2BoxBody(world, b2_staticBody, false, false);
}

void DropoutBlock::BlockHit()
{
	if (IsHit || IsFalling) return;
	CurrentTimer = FallDelay;
	IsHit = true;
	EntityMesh->Colour.r *= 1.5;
	EntityMesh->Rebind();
}

void DropoutBlock::Drop()
{
	IsFalling = true;
	IsHit = false;
	CurrentTimer = RespawnTime;
	EntityMesh->Colour.a = 0.3f;
	EntityMesh->Colour.r /= 1.5;
	EntityMesh->Rebind();
	body->SetActive(false);
}

void DropoutBlock::Respawn()
{
	IsFalling = false;
	IsHit = false;

	Reset();
	//EntityMesh->Colour.a = 1.0f;
	//EntityMesh->Rebind();
}
