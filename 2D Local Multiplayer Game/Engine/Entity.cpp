//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name    	:    Entity.cpp
// Description    	:    main implementation for Entity
// Author       	:    Alex Coultas
// Mail         	:    alex.cou7417@mediadesign.school.nz
//

// This Includes //
#include "Entity.h"

// Library Includes //
#include <iostream>

// OpenGL Library Includes //
#include <glm\gtx\string_cast.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>

// Engine Includes //
#include "Shader.h"
#include "Camera.h"
#include "Time.h"
#include "Plane.h"
#include "Pyramid.h"
#include "Sphere.h"
#include "CollisionBounds.h"
#include "LogManager.h"

//************************************************************
//#--Description--#:	Constructor function with base position
//#--Author--#: 		Alex Coultas
//#--Parameters--#:		Takes contructor values
//#--Return--#: 		NA
//************************************************************/
Entity::Entity(Utils::Transform _Transform, Utils::EANCHOR _Anchor)
	: transform(_Transform), EntityAnchor(_Anchor)
{
	iEntityID = Utils::AddEntityID();
	LogManager::GetInstance()->DisplayLogMessage("New Entity created with ID #" + std::to_string(iEntityID));
	// Set initial States
	EntityInitialState.bActive = bActive;
	EntityInitialState.bVisible = bVisible;
	EntityInitialState.EntityAnchor = EntityAnchor;
	EntityInitialState.iEntityID = iEntityID;
	EntityInitialState.transform = transform;
}

/************************************************************
#--Description--#:  Destructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	NA
#--Return--#: 		NA
************************************************************/
Entity::~Entity()
{
	EntityMesh = nullptr;
}


void Entity::AddMesh(std::shared_ptr<Mesh> _NewMesh)
{
	EntityMesh = _NewMesh;
}

//void Entity::AddMesh(Utils::ESHAPE _NewShape)
//{
//	switch (_NewShape)
//	{
//	case Utils::PLANE:
//		EntityMesh = std::make_shared<Plane>(Plane(1, 1, { 1.0f, 1.0f, 1.0f,  1.0f }));
//		break;
//	case Utils::PYRAMID:
//		EntityMesh = std::make_shared<Pyramid>(Pyramid(1, 1, 1, { 1.0f, 1.0f, 1.0f,  1.0f }));
//		break;
//	case Utils::CUBE:
//		break;
//	case Utils::SPHERE:
//		EntityMesh = std::make_shared<Sphere>(Sphere(1, 1, 1, { 1.0f, 1.0f, 1.0f,  1.0f }));
//		break;
//	default:
//		break;
//	}
//	EntityMesh->EntityRef = this->shared_from_this();
//}

/************************************************************
#--Description--#: 	Draws the entity on the screen at the using the transform
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void Entity::DrawEntity()
{
	if (!EntityMesh || !bVisible) return;
	Utils::Transform AnchoredTransform = transform;
	if (EntityMesh->GetCollisionBounds())
		AnchoredTransform.Position = Utils::GetAncoredPosition(transform.Position, EntityMesh->GetCollisionBounds()->GetDimensions(), EntityAnchor);
	else
		AnchoredTransform.Position = Utils::GetAncoredPosition(transform.Position, glm::vec3(EntityMesh->m_fWidth, EntityMesh->m_fHeight, EntityMesh->m_fDepth), EntityAnchor);
	EntityMesh->Render(AnchoredTransform);
}

/************************************************************
#--Description--#: 	Base Update called every frame to check before called derived Update
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void Entity::BaseUpdate()
{
	if (!bActive)
		return;
	Update();
	if (!EntityMesh) EntityMesh->Update();
}

/************************************************************
#--Description--#: 	Updated every frame
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void Entity::Update()
{

}

/************************************************************
#--Description--#: 	Virtual function ran when the entity is destroyed
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void Entity::OnDestroy()
{
	LogManager::GetInstance()->DisplayLogMessage("Entity with ID #" + std::to_string(iEntityID) + " destroyed!");
}

void Entity::Reset()
{
	// Reset all entity variables
	bActive = EntityInitialState.bActive;
	bVisible = EntityInitialState.bVisible;
	EntityAnchor = EntityInitialState.EntityAnchor;
	iEntityID = EntityInitialState.iEntityID;
	transform = EntityInitialState.transform;
	// Reset Entity Mesh
	EntityMesh->Reset();
}

void Entity::SetActive(bool _bIsActive, bool _bIsInitialState)
{
	bActive = _bIsActive;
	if (_bIsInitialState)
		EntityInitialState.bActive = bActive;
}

void Entity::SetVisible(bool _bIsVisible, bool _bIsInitialState)
{
	bVisible = _bIsVisible;
	if (_bIsInitialState)
		EntityInitialState.bVisible = bVisible;
}

/************************************************************
#--Description--#: 	Moves the position by adding on the movement
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Takes in the movement to move the entity by
#--Return--#: 		NA
************************************************************/
void Entity::Translate(glm::vec3 _Movement)
{
	transform.Position += _Movement;
}

/************************************************************
#--Description--#: 	Rotates the entity by a certain amount
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Takes in the rotation to add
#--Return--#: 		NA
************************************************************/
void Entity::Rotate(glm::vec3 Rotate)
{
	transform.Rotation += Rotate;
}

/************************************************************
#--Description--#: 	Sets the entity scale
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Takes in the new scale
#--Return--#: 		NA
************************************************************/
void Entity::SetScale(glm::vec3 _NewScale)
{
	transform.Scale = _NewScale;
}
