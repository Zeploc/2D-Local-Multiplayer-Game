//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name    	:    CollisionBoudns.cpp
// Description    	:    Collision Bound system
// Author       	:    Alex Coultas
// Mail         	:    alex.cou7417@mediadesign.school.nz
//

// This Includes //
#include "CollisionBounds.h"

// Engine Includes //
#include "Mesh.h"

/************************************************************
#--Description--#:  Constructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	Takes contructor values
#--Return--#: 		NA
************************************************************/
CollisionBounds::CollisionBounds(float _fWidth, float _fHeight, float _fDepth, std::shared_ptr<Entity> _EntityRef)
	: fHeight(_fHeight), fWidth(_fWidth), fDepth(_fDepth), EntityRef(_EntityRef)
{
	CollisionBoundsInitialState.fHeight = fHeight;
	CollisionBoundsInitialState.fWidth = fWidth;
	CollisionBoundsInitialState.fDepth = fDepth;
}

/************************************************************
#--Description--#:  Destructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	NA
#--Return--#: 		NA
************************************************************/
CollisionBounds::~CollisionBounds()
{

}

void CollisionBounds::Reset()
{
	fHeight = CollisionBoundsInitialState.fHeight;
	fWidth = CollisionBoundsInitialState.fWidth;
	fDepth = CollisionBoundsInitialState.fDepth;
	v3Offset = CollisionBoundsInitialState.v3Offset;
}

bool CollisionBounds::isColliding(std::shared_ptr<Entity> Entity2)
{
	if (!Entity2) return false;
	std::shared_ptr<Mesh> Entity1Mesh = std::dynamic_pointer_cast<Mesh>(EntityRef->EntityMesh);
	std::shared_ptr<Mesh> Entity2Mesh = std::dynamic_pointer_cast<Mesh>(Entity2->EntityMesh);
	float HalfWidth1 = (fWidth) / 2;// * * abs(EntityRef->transform.Scale.x);
	float HalfHeight1 = (fHeight) / 2;// * * abs(EntityRef->transform.Scale.y);
	float HalfDepth1 = (fDepth) / 2;// * * abs(EntityRef->transform.Scale.z);
	float HalfWidth2 = (Entity2Mesh->GetCollisionBounds()->fWidth) / 2;// * * abs(Entity2->transform.Scale.x);
	float HalfHeight2 = (Entity2Mesh->GetCollisionBounds()->fHeight) / 2;// * * abs(Entity2->transform.Scale.y);
	float HalfDepth2 = (Entity2Mesh->GetCollisionBounds()->fDepth) / 2;// * * abs(Entity2->transform.Scale.z);

	glm::vec3 Entity1Pos = Utils::GetAncoredPosition(EntityRef->transform.Position, Entity1Mesh->GetCollisionBounds()->GetDimensions(), EntityRef->EntityAnchor);
	glm::vec3 Entity2Pos = Utils::GetAncoredPosition(Entity2->transform.Position, Entity2Mesh->GetCollisionBounds()->GetDimensions(), Entity2->EntityAnchor);

	if (Entity1Pos.x + Entity1Mesh->GetCollisionBounds()->v3Offset.x + HalfWidth1 > Entity2Pos.x + Entity2Mesh->GetCollisionBounds()->v3Offset.x - HalfWidth2
		&& Entity1Pos.x + Entity1Mesh->GetCollisionBounds()->v3Offset.x - HalfWidth1 < Entity2Pos.x + Entity2Mesh->GetCollisionBounds()->v3Offset.x + HalfWidth2
		&& Entity1Pos.y + Entity1Mesh->GetCollisionBounds()->v3Offset.y + HalfHeight1 > Entity2Pos.y + Entity2Mesh->GetCollisionBounds()->v3Offset.y - HalfHeight2
		&& Entity1Pos.y + Entity1Mesh->GetCollisionBounds()->v3Offset.y - HalfHeight1 < Entity2Pos.y + Entity2Mesh->GetCollisionBounds()->v3Offset.y + HalfHeight2
		&& Entity1Pos.z + Entity1Mesh->GetCollisionBounds()->v3Offset.z + HalfDepth1 > Entity2Pos.z + Entity2Mesh->GetCollisionBounds()->v3Offset.z - HalfDepth2
		&& Entity1Pos.z + Entity1Mesh->GetCollisionBounds()->v3Offset.z - HalfDepth1 < Entity2Pos.z + Entity2Mesh->GetCollisionBounds()->v3Offset.z + HalfDepth2)
		return true;
	return false;
}

bool CollisionBounds::CheckCollision(std::shared_ptr<Entity> Entity2, glm::vec3 Movement)
{
	std::shared_ptr<Mesh> Entity1Mesh = std::dynamic_pointer_cast<Mesh>(EntityRef->EntityMesh);
	std::shared_ptr<Mesh> Entity2Mesh = std::dynamic_pointer_cast<Mesh>(Entity2->EntityMesh);
	float HalfWidth1 = (fWidth) / 2;// *abs(EntityRef->transform.Scale.x);
	float HalfHeight1 = (fHeight) / 2;// *abs(EntityRef->transform.Scale.y);
	float HalfDepth1 = (fDepth) / 2;// *abs(EntityRef->transform.Scale.z);
	float HalfWidth2 = (Entity2Mesh->GetCollisionBounds()->fWidth) / 2;// *abs(Entity2->transform.Scale.x);
	float HalfHeight2 = (Entity2Mesh->GetCollisionBounds()->fHeight) / 2;// *abs(Entity2->transform.Scale.y);
	float HalfDepth2 = (Entity2Mesh->GetCollisionBounds()->fDepth) / 2;// *abs(Entity2->transform.Scale.z);

	glm::vec3 Entity1Pos = Utils::GetAncoredPosition(EntityRef->transform.Position, Entity1Mesh->GetCollisionBounds()->GetDimensions(), EntityRef->EntityAnchor);
	glm::vec3 Entity2Pos = Utils::GetAncoredPosition(Entity2->transform.Position, Entity2Mesh->GetCollisionBounds()->GetDimensions(), Entity2->EntityAnchor);

	if (Entity1Pos.x + Entity1Mesh->GetCollisionBounds()->v3Offset.x + HalfWidth1 + Movement.x > Entity2Pos.x + Entity2Mesh->GetCollisionBounds()->v3Offset.x - HalfWidth2
		&& Entity1Pos.x + Entity1Mesh->GetCollisionBounds()->v3Offset.x - HalfWidth1 + Movement.x < Entity2Pos.x + Entity2Mesh->GetCollisionBounds()->v3Offset.x + HalfWidth2
		&& Entity1Pos.y + Entity1Mesh->GetCollisionBounds()->v3Offset.y + HalfHeight1 + Movement.y > Entity2Pos.y + Entity2Mesh->GetCollisionBounds()->v3Offset.y - HalfHeight2
		&& Entity1Pos.y + Entity1Mesh->GetCollisionBounds()->v3Offset.y - HalfHeight1 + Movement.y < Entity2Pos.y + Entity2Mesh->GetCollisionBounds()->v3Offset.y + HalfHeight2
		&& Entity1Pos.z + Entity1Mesh->GetCollisionBounds()->v3Offset.z + HalfDepth1 + Movement.z > Entity2Pos.z + Entity2Mesh->GetCollisionBounds()->v3Offset.z - HalfDepth2
		&& Entity1Pos.z + Entity1Mesh->GetCollisionBounds()->v3Offset.z - HalfDepth1 + Movement.z < Entity2Pos.z + Entity2Mesh->GetCollisionBounds()->v3Offset.z + HalfDepth2)
		return true;
	return false;
}

glm::vec3 CollisionBounds::GetDistance(std::shared_ptr<Entity> Entity2)
{
	std::shared_ptr<Mesh> Entity1Mesh = std::dynamic_pointer_cast<Mesh>(EntityRef->EntityMesh);
	std::shared_ptr<Mesh> Entity2Mesh = std::dynamic_pointer_cast<Mesh>(Entity2->EntityMesh);
	glm::vec3 fDistance = glm::vec3(0, 0, 0);
	float HalfWidth1 = (fWidth) / 2;// * * abs(EntityRef->transform.Scale.x);
	float HalfHeight1 = (fHeight) / 2;// * * abs(EntityRef->transform.Scale.y);
	float HalfDepth1 = (fDepth) / 2;// * * abs(EntityRef->transform.Scale.z);
	float HalfWidth2 = (Entity2Mesh->GetCollisionBounds()->fWidth) / 2;// * * abs(Entity2->transform.Scale.x);
	float HalfHeight2 = (Entity2Mesh->GetCollisionBounds()->fHeight) / 2;// * * abs(Entity2->transform.Scale.y);
	float HalfDepth2 = (Entity2Mesh->GetCollisionBounds()->fDepth) / 2;// * * abs(Entity2->transform.Scale.z);

	glm::vec3 Entity1Pos = Utils::GetAncoredPosition(EntityRef->transform.Position, Entity1Mesh->GetCollisionBounds()->GetDimensions(), EntityRef->EntityAnchor);
	glm::vec3 Entity2Pos = Utils::GetAncoredPosition(Entity2->transform.Position, Entity2Mesh->GetCollisionBounds()->GetDimensions(), Entity2->EntityAnchor);

	if (Entity1Pos.x + Entity1Mesh->GetCollisionBounds()->v3Offset.x + HalfWidth1 <= Entity2Pos.x + Entity2Mesh->GetCollisionBounds()->v3Offset.x - HalfWidth2)
	{
		fDistance.x = abs((Entity1Pos.x + Entity1Mesh->GetCollisionBounds()->v3Offset.x + HalfWidth1) - (Entity2Pos.x + Entity2Mesh->GetCollisionBounds()->v3Offset.x - HalfWidth2));
	}
	else if (Entity1Pos.x + Entity1Mesh->GetCollisionBounds()->v3Offset.x - HalfWidth1 >= Entity2Pos.x + Entity2Mesh->GetCollisionBounds()->v3Offset.x + HalfWidth2)
	{
		fDistance.x = abs((Entity1Pos.x + Entity1Mesh->GetCollisionBounds()->v3Offset.x - HalfWidth1) - (Entity2Pos.x + Entity2Mesh->GetCollisionBounds()->v3Offset.x + HalfWidth2));
	}

	if (Entity1Pos.y + Entity1Mesh->GetCollisionBounds()->v3Offset.y + HalfHeight1 <= Entity2Pos.y + Entity2Mesh->GetCollisionBounds()->v3Offset.y - HalfHeight2)
	{
		fDistance.y = abs((Entity1Pos.y + Entity1Mesh->GetCollisionBounds()->v3Offset.y + HalfHeight1) - (Entity2Pos.y + Entity2Mesh->GetCollisionBounds()->v3Offset.y - HalfHeight2));
	}
	else if (Entity1Pos.y + Entity1Mesh->GetCollisionBounds()->v3Offset.y - HalfHeight1 >= Entity2Pos.y + Entity2Mesh->GetCollisionBounds()->v3Offset.y + HalfHeight2)
	{
		fDistance.y = abs((Entity1Pos.y + Entity1Mesh->GetCollisionBounds()->v3Offset.y - HalfHeight1) - (Entity2Pos.y + Entity2Mesh->GetCollisionBounds()->v3Offset.y + HalfHeight2));
	}

	if (Entity1Pos.z + Entity1Mesh->GetCollisionBounds()->v3Offset.z + HalfDepth1 <= Entity2Pos.z + Entity2Mesh->GetCollisionBounds()->v3Offset.z - HalfDepth2)
	{
		fDistance.z = abs((Entity1Pos.z + Entity1Mesh->GetCollisionBounds()->v3Offset.z + HalfDepth1) - (Entity2Pos.z + Entity2Mesh->GetCollisionBounds()->v3Offset.z - HalfDepth2));
	}
	else if (Entity1Pos.z + Entity1Mesh->GetCollisionBounds()->v3Offset.z - HalfDepth1 >= Entity2Pos.z + Entity2Mesh->GetCollisionBounds()->v3Offset.z + HalfDepth2)
	{
		fDistance.z = abs((Entity1Pos.z + Entity1Mesh->GetCollisionBounds()->v3Offset.z - HalfDepth1) - (Entity2Pos.z + Entity2Mesh->GetCollisionBounds()->v3Offset.z + HalfDepth2));
	}
	return fDistance;
}
