//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name    	:    CSprite.cpp
// Description    	:    main implementation for CSprite
// Author       	:    Alex Coultas
// Mail         	:    alex.cou7417@mediadesign.school.nz
//

// Library Includes //

// OpenGL Library Includes //
#include <glew.h>
#include <freeglut.h>

// Engine Includes //
#include "Entity.h"
#include "Camera.h"
#include "Plane.h"

// Local Includes //

// This Includes //
#include "Utils.h"

// Static Variables //
int Utils::iEntityNumber = 0;
std::shared_ptr<Entity> Utils::WorldCubeMap;

/************************************************************
#--Description--#:  Gets position from anchor and current position
#--Author--#: 		Alex Coultas
#--Parameters--#:	Element position, dimensions and current anchor
#--Return--#: 		Returns vector 3 of new position
************************************************************/
glm::vec3 Utils::GetAncoredPosition2D(glm::vec2 position, glm::vec2 Dimensions, EANCHOR _AnchorType)
{
	glm::vec3 NewPos;
	switch (_AnchorType)
	{
	case Utils::TOP_LEFT:
		NewPos = glm::vec3(position.x + Dimensions.x / 2, position.y - Dimensions.y / 2, 0);
		break;
	case Utils::TOP_RIGHT:
		NewPos = glm::vec3(position.x - Dimensions.x / 2, position.y - Dimensions.y / 2, 0);
		break;
	case Utils::TOP_CENTER:
		NewPos = glm::vec3(position.x, position.y - Dimensions.y / 2, 0);
		break;
	case Utils::CENTER_LEFT:
		NewPos = glm::vec3(position.x + Dimensions.x / 2, position.y, 0);
		break;
	case Utils::CENTER:
		NewPos = glm::vec3(position.x, position.y, 0);
		break;
	case Utils::CENTER_RIGHT:
		NewPos = glm::vec3(position.x - Dimensions.x / 2, position.y, 0);
		break;
	case Utils::BOTTOM_LEFT:
		NewPos = glm::vec3(position.x + Dimensions.x / 2, position.y + Dimensions.y / 2, 0);
		break;
	case Utils::BOTTOM_CENTER:
		NewPos = glm::vec3(position.x, position.y + Dimensions.y / 2, 0);
		break;
	case Utils::BOTTOM_RIGHT:
		NewPos = glm::vec3(position.x - Dimensions.x / 2, position.y + Dimensions.y / 2, 0);
		break;
	default:
		break;
	}
	return NewPos;
}

/************************************************************
#--Description--#:  Gets position from anchor and current position
#--Author--#: 		Alex Coultas
#--Parameters--#:	Element position, dimensions and current anchor
#--Return--#: 		Returns vector 3 of new position
************************************************************/
glm::vec3 Utils::GetAncoredPosition(glm::vec3 position, glm::vec3 Dimensions, EANCHOR _AnchorType)
{
	glm::vec3 NewPos;
	switch (_AnchorType)
	{
	case Utils::TOP_LEFT:
		NewPos = glm::vec3(position.x + Dimensions.x / 2, position.y - Dimensions.y / 2, position.z);
		break;
	case Utils::TOP_RIGHT:
		NewPos = glm::vec3(position.x - Dimensions.x / 2, position.y - Dimensions.y / 2, position.z);
		break;
	case Utils::TOP_CENTER:
		NewPos = glm::vec3(position.x, position.y - Dimensions.y / 2, position.z);
		break;
	case Utils::CENTER_LEFT:
		NewPos = glm::vec3(position.x + Dimensions.x / 2, position.y, position.z);
		break;
	case Utils::CENTER:
		NewPos = glm::vec3(position.x, position.y, position.z);
		break;
	case Utils::CENTER_RIGHT:
		NewPos = glm::vec3(position.x - Dimensions.x / 2, position.y, position.z);
		break;
	case Utils::BOTTOM_LEFT:
		NewPos = glm::vec3(position.x + Dimensions.x / 2, position.y + Dimensions.y / 2, position.z);
		break;
	case Utils::BOTTOM_CENTER:
		NewPos = glm::vec3(position.x, position.y + Dimensions.y / 2, position.z);
		break;
	case Utils::BOTTOM_RIGHT:
		NewPos = glm::vec3(position.x - Dimensions.x / 2, position.y + Dimensions.y / 2, position.z);
		break;
	default:
		break;
	}
	return NewPos;
}

/************************************************************
#--Description--#:  Gets text position from anchor and current position
#--Author--#: 		Alex Coultas
#--Parameters--#:	Element position, dimensions and current anchor
#--Return--#: 		Returns vector 3 of new position
************************************************************/
glm::vec3 Utils::GetTextAncoredPosition(glm::vec2 position, glm::vec2 Dimensions, EANCHOR _AnchorType)
{
	glm::vec3 NewPos;
	switch (_AnchorType)
	{
	case Utils::TOP_LEFT:
		NewPos = glm::vec3(position.x, position.y + Dimensions.y / 2, 0);
		break;
	case Utils::TOP_RIGHT:
		NewPos = glm::vec3(position.x - Dimensions.x, position.y + Dimensions.y / 2, 0);
		break;
	case Utils::TOP_CENTER:
		NewPos = glm::vec3(position.x - Dimensions.x / 2, position.y + Dimensions.y / 2, 0);
		break;
	case Utils::CENTER_LEFT:
		NewPos = glm::vec3(position.x, position.y, 0);
		break;
	case Utils::CENTER:
		NewPos = glm::vec3(position.x - Dimensions.x / 2, position.y, 0);
		break;
	case Utils::CENTER_RIGHT:
		NewPos = glm::vec3(position.x - Dimensions.x, position.y, 0);
		break;
	case Utils::BOTTOM_LEFT:
		NewPos = glm::vec3(position.x, position.y - Dimensions.y / 2, 0);
		break;
	case Utils::BOTTOM_CENTER:
		NewPos = glm::vec3(position.x - Dimensions.x / 2, position.y - Dimensions.y / 2, 0);
		break;
	case Utils::BOTTOM_RIGHT:
		NewPos = glm::vec3(position.x - Dimensions.x, position.y - Dimensions.y / 2, 0);
		break;
	default:
		break;
	}
	return NewPos;
}

/************************************************************
#--Description--#:  Returns whether the object is colliding
#--Author--#: 		Alex Coultas
#--Parameters--#:	two pointers to the entities
#--Return--#: 		Returns boolean whether the entities are colliding
************************************************************/
bool Utils::isColliding2D(std::shared_ptr<Entity> Entity1, std::shared_ptr<Entity> Entity2)
{
	std::shared_ptr<Plane> Entity1Mesh = std::dynamic_pointer_cast<Plane>(Entity1->EntityMesh);
	std::shared_ptr<Plane> Entity2Mesh = std::dynamic_pointer_cast<Plane>(Entity2->EntityMesh);
	float HalfWidth1 = (Entity1Mesh->CollisionBox.fWidth / 2) * abs(Entity1->transform.Scale.x);
	float HalfHeight1 = (Entity1Mesh->CollisionBox.fHeight / 2) * abs(Entity1->transform.Scale.y);
	float HalfWidth2 = (Entity2Mesh->CollisionBox.fWidth / 2) * abs(Entity2->transform.Scale.x);
	float HalfHeight2 = (Entity2Mesh->CollisionBox.fHeight / 2) * abs(Entity2->transform.Scale.y);
	
	glm::vec3 Entity1Pos = GetAncoredPosition2D(Entity1->transform.Position, glm::vec2(Entity1Mesh->m_fWidth, Entity1Mesh->m_fHeight) * (glm::vec2)Entity1->transform.Scale, Entity1->EntityAnchor);
	glm::vec3 Entity2Pos = GetAncoredPosition2D(Entity2->transform.Position, glm::vec2(Entity2Mesh->m_fWidth, Entity2Mesh->m_fHeight) * (glm::vec2)Entity2->transform.Scale, Entity2->EntityAnchor);

	if (Entity1Pos.x + Entity1Mesh->CollisionBox.v2Offset.x + HalfWidth1 > Entity2Pos.x + Entity2Mesh->CollisionBox.v2Offset.x - HalfWidth2
		&& Entity1Pos.x + Entity1Mesh->CollisionBox.v2Offset.x - HalfWidth1 < Entity2Pos.x + Entity2Mesh->CollisionBox.v2Offset.x + HalfWidth2
		&& Entity1Pos.y + Entity1Mesh->CollisionBox.v2Offset.y + HalfHeight1 > Entity2Pos.y + Entity2Mesh->CollisionBox.v2Offset.y - HalfHeight2
		&& Entity1Pos.y + Entity1Mesh->CollisionBox.v2Offset.y - HalfHeight1 < Entity2Pos.y + Entity2Mesh->CollisionBox.v2Offset.y + HalfHeight2)
		return true;
	return false;
}

/************************************************************
#--Description--#:  Returns whether the object would collide given movement
#--Author--#: 		Alex Coultas
#--Parameters--#:	two pointers to the entities and the movement to check for first entity
#--Return--#: 		Returns boolean whether the entities would collide
************************************************************/
bool Utils::CheckCollision2D(std::shared_ptr<Entity> Entity1, std::shared_ptr<Entity> Entity2, glm::vec2 Movement)
{
	std::shared_ptr<Plane> Entity1Mesh = std::dynamic_pointer_cast<Plane>(Entity1->EntityMesh);
	std::shared_ptr<Plane> Entity2Mesh = std::dynamic_pointer_cast<Plane>(Entity2->EntityMesh);
	float HalfWidth1 = (Entity1Mesh->CollisionBox.fWidth / 2) * abs(Entity1->transform.Scale.x);
	float HalfHeight1 = (Entity1Mesh->CollisionBox.fHeight / 2) * abs(Entity1->transform.Scale.y);
	float HalfWidth2 = (Entity2Mesh->CollisionBox.fWidth / 2) * abs(Entity2->transform.Scale.x);
	float HalfHeight2 = (Entity2Mesh->CollisionBox.fHeight / 2) * abs(Entity2->transform.Scale.y);

	glm::vec3 Entity1Pos = GetAncoredPosition2D(Entity1->transform.Position, glm::vec2(Entity1Mesh->m_fWidth, Entity1Mesh->m_fHeight) * (glm::vec2)Entity1->transform.Scale, Entity1->EntityAnchor);
	glm::vec3 Entity2Pos = GetAncoredPosition2D(Entity2->transform.Position + glm::vec3(Entity2Mesh->CollisionBox.v2Offset, 0), glm::vec2(Entity2Mesh->m_fWidth, Entity2Mesh->m_fHeight) * (glm::vec2)Entity2->transform.Scale, Entity2->EntityAnchor);

	if (Entity1Pos.x + Entity1Mesh->CollisionBox.v2Offset.x + HalfWidth1 + Movement.x > Entity2Pos.x + Entity2Mesh->CollisionBox.v2Offset.x - HalfWidth2
		&& Entity1Pos.x + Entity1Mesh->CollisionBox.v2Offset.x - HalfWidth1 + Movement.x < Entity2Pos.x + Entity2Mesh->CollisionBox.v2Offset.x + HalfWidth2
		&& Entity1Pos.y + Entity1Mesh->CollisionBox.v2Offset.y + HalfHeight1 + Movement.y > Entity2Pos.y + Entity2Mesh->CollisionBox.v2Offset.y - HalfHeight2
		&& Entity1Pos.y + Entity1Mesh->CollisionBox.v2Offset.y - HalfHeight1 + Movement.y < Entity2Pos.y + Entity2Mesh->CollisionBox.v2Offset.y + HalfHeight2)
		return true;
	return false;
}

/************************************************************
#--Description--#:  Gets the distance from the edges of the entities collision boxes
#--Author--#: 		Alex Coultas
#--Parameters--#:	two pointers to the entities
#--Return--#: 		Returns vector 2 of distance
************************************************************/
glm::vec2 Utils::GetDistance2D(std::shared_ptr<Entity> Entity1, std::shared_ptr<Entity> Entity2)
{
	std::shared_ptr<Plane> Entity1Mesh = std::dynamic_pointer_cast<Plane>(Entity1->EntityMesh);
	std::shared_ptr<Plane> Entity2Mesh = std::dynamic_pointer_cast<Plane>(Entity2->EntityMesh);
	glm::vec2 fDistance = glm::vec2(0, 0);
	float HalfWidth1 = (Entity1Mesh->CollisionBox.fWidth / 2) * abs(Entity1->transform.Scale.x);
	float HalfHeight1 = (Entity1Mesh->CollisionBox.fHeight / 2) * abs(Entity1->transform.Scale.y);
	float HalfWidth2 = (Entity2Mesh->CollisionBox.fWidth / 2) * abs(Entity2->transform.Scale.x);
	float HalfHeight2 = (Entity2Mesh->CollisionBox.fHeight / 2) * abs(Entity2->transform.Scale.y);
	
	glm::vec3 Entity1Pos = GetAncoredPosition2D(Entity1->transform.Position, glm::vec2(Entity1Mesh->m_fWidth, Entity1Mesh->m_fHeight) * (glm::vec2)Entity1->transform.Scale, Entity1->EntityAnchor);
	glm::vec3 Entity2Pos = GetAncoredPosition2D(Entity2->transform.Position, glm::vec2(Entity2Mesh->m_fWidth, Entity2Mesh->m_fHeight) * (glm::vec2)Entity2->transform.Scale, Entity2->EntityAnchor);

	if (Entity1Pos.x + Entity1Mesh->CollisionBox.v2Offset.x + HalfWidth1 <= Entity2Pos.x + Entity2Mesh->CollisionBox.v2Offset.x - HalfWidth2)
	{
		fDistance.x = abs((Entity1Pos.x + Entity1Mesh->CollisionBox.v2Offset.x + HalfWidth1) - (Entity2Pos.x + Entity2Mesh->CollisionBox.v2Offset.x - HalfWidth2));
	}
	else if (Entity1Pos.x + Entity1Mesh->CollisionBox.v2Offset.x - HalfWidth1 >= Entity2Pos.x + Entity2Mesh->CollisionBox.v2Offset.x + HalfWidth2)
	{
		fDistance.x = abs((Entity1Pos.x + Entity1Mesh->CollisionBox.v2Offset.x - HalfWidth1) - (Entity2Pos.x + Entity2Mesh->CollisionBox.v2Offset.x + HalfWidth2));
	}

	if (Entity1Pos.y + Entity1Mesh->CollisionBox.v2Offset.y + HalfHeight1 <= Entity2Pos.y + Entity2Mesh->CollisionBox.v2Offset.y - HalfHeight2)
	{
		fDistance.y = abs((Entity1Pos.y + Entity1Mesh->CollisionBox.v2Offset.y + HalfHeight1) - (Entity2Pos.y + Entity2Mesh->CollisionBox.v2Offset.y - HalfHeight2));
	}
	else if (Entity1Pos.y + Entity1Mesh->CollisionBox.v2Offset.y - HalfHeight1 >= Entity2Pos.y + Entity2Mesh->CollisionBox.v2Offset.y + HalfHeight2)
	{
		fDistance.y = abs((Entity1Pos.y + Entity1Mesh->CollisionBox.v2Offset.y - HalfHeight1) - (Entity2Pos.y + Entity2Mesh->CollisionBox.v2Offset.y + HalfHeight2));
	}
	return fDistance;
}

/************************************************************
#--Description--#:  Gets the distance with direction from the edges of the entities collision boxes
#--Author--#: 		Alex Coultas
#--Parameters--#:	two pointers to the entities
#--Return--#: 		Returns vector 2 of distance with direction
************************************************************/
glm::vec2 Utils::GetDifference2D(std::shared_ptr<Entity> Entity1, std::shared_ptr<Entity> Entity2)
{
	std::shared_ptr<Plane> Entity1Mesh = std::dynamic_pointer_cast<Plane>(Entity1->EntityMesh);
	std::shared_ptr<Plane> Entity2Mesh = std::dynamic_pointer_cast<Plane>(Entity2->EntityMesh);
	glm::vec2 fDistance = glm::vec2(0, 0);
	float HalfWidth1 = (Entity1Mesh->CollisionBox.fWidth / 2) * abs(Entity1->transform.Scale.x);
	float HalfHeight1 = (Entity1Mesh->CollisionBox.fHeight / 2) * abs(Entity1->transform.Scale.y);
	float HalfWidth2 = (Entity2Mesh->CollisionBox.fWidth / 2) * abs(Entity2->transform.Scale.x);
	float HalfHeight2 = (Entity2Mesh->CollisionBox.fHeight / 2) * abs(Entity2->transform.Scale.y);

	glm::vec3 Entity1Pos = GetAncoredPosition2D(Entity1->transform.Position, glm::vec2(Entity1Mesh->m_fWidth, Entity1Mesh->m_fHeight) * (glm::vec2)Entity1->transform.Scale, Entity1->EntityAnchor);
	glm::vec3 Entity2Pos = GetAncoredPosition2D(Entity2->transform.Position, glm::vec2(Entity2Mesh->m_fWidth, Entity2Mesh->m_fHeight) * (glm::vec2)Entity2->transform.Scale, Entity2->EntityAnchor);

	if (Entity1Pos.x + Entity1Mesh->CollisionBox.v2Offset.x + HalfWidth1 < Entity2Pos.x + Entity2Mesh->CollisionBox.v2Offset.x - HalfWidth2)
	{
		fDistance.x = (Entity1Pos.x + Entity1Mesh->CollisionBox.v2Offset.x + HalfWidth1) - (Entity2Pos.x + Entity2Mesh->CollisionBox.v2Offset.x - HalfWidth2);
	}
	else if (Entity1Pos.x + Entity1Mesh->CollisionBox.v2Offset.x - HalfWidth1 > Entity2Pos.x + Entity2Mesh->CollisionBox.v2Offset.x + HalfWidth2)
	{
		fDistance.x = (Entity1Pos.x + Entity1Mesh->CollisionBox.v2Offset.x - HalfWidth1) - (Entity2Pos.x + Entity2Mesh->CollisionBox.v2Offset.x + HalfWidth2);
	}

	if (Entity1Pos.y + Entity1Mesh->CollisionBox.v2Offset.y + HalfHeight1 < Entity2Pos.y + Entity2Mesh->CollisionBox.v2Offset.y - HalfHeight2)
	{
		fDistance.y = (Entity1Pos.y + Entity1Mesh->CollisionBox.v2Offset.y + HalfHeight1) - (Entity2Pos.y + Entity2Mesh->CollisionBox.v2Offset.y - HalfHeight2);
	}
	else if (Entity1Pos.y + Entity1Mesh->CollisionBox.v2Offset.y - HalfHeight1 > Entity2Pos.y + Entity2Mesh->CollisionBox.v2Offset.y + HalfHeight2)
	{
		fDistance.y = (Entity1Pos.y + Entity1Mesh->CollisionBox.v2Offset.y - HalfHeight1) - (Entity2Pos.y + Entity2Mesh->CollisionBox.v2Offset.y + HalfHeight2);
	}
	return fDistance;
}

int Utils::AddEntityID()
{
	iEntityNumber++;
	return iEntityNumber;
}
