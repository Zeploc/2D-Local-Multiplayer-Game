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
	if (EntityMesh) EntityMesh->Update();
}

/************************************************************
#--Description--#: 	Updated every frame
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void Entity::Update()
{
	if (body)
	{
		b2Vec2 BodyPosition = body->GetPosition();
		transform.Position = glm::vec3(BodyPosition.x, BodyPosition.y, 0.0f);
		transform.Rotation.z = (body->GetAngle() / b2_pi) * 180;
	}
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
	if (body) body->SetActive(false);
}

void Entity::Reset()
{
	// Reset all entity variables
	bActive = EntityInitialState.bActive;
	bVisible = EntityInitialState.bVisible;
	EntityAnchor = EntityInitialState.EntityAnchor;
	iEntityID = EntityInitialState.iEntityID;
	transform = EntityInitialState.transform;
	if (body)
	{
		body->SetTransform(b2Vec2(transform.Position.x, transform.Position.y), (transform.Rotation.z / 180) * b2_pi);
		body->SetAwake(true);
		body->SetActive(bActive);
		body->SetLinearVelocity(b2Vec2_zero);
		body->SetAngularVelocity(0.0f);
	}
	// Reset Entity Mesh
	if (EntityMesh) EntityMesh->Reset();
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

void Entity::SetupB2BoxBody(b2World & Box2DWorld, b2BodyType BodyType, bool bCanRotate, bool bHasFixture, float Density, float Friction, bool IsBullet)
{
	if (EntityMesh)
	{
		// Define the dynamic body. We set its position and call the body factory.
		b2BodyDef bodyDef;
		bodyDef.type = BodyType;
		bodyDef.position.Set(transform.Position.x, transform.Position.y);
		bodyDef.userData = &*this;
		body = Box2DWorld.CreateBody(&bodyDef);
		body->SetTransform(bodyDef.position, (transform.Rotation.z / 180) * b2_pi);
		body->SetFixedRotation(!bCanRotate);
		bodyDef.bullet = true;
		
		// Define another box shape for our dynamic body.
		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(EntityMesh->m_fWidth / 2.0f, EntityMesh->m_fHeight / 2.0f);
		if (bHasFixture)
		{
			// Define the dynamic body fixture.
			b2FixtureDef fixtureDef;
			fixtureDef.shape = &dynamicBox;
			// Set the box density to be non-zero, so it will be dynamic.
			fixtureDef.density = Density;
			// Override the default friction.
			fixtureDef.friction = Friction;

			// Add the shape to the body.
			body->CreateFixture(&fixtureDef);
		}
		else
		{
			body->CreateFixture(&dynamicBox, 0.0f);
		}
	}
	else
	{
		LogManager::GetInstance()->DisplayLogMessage("Failed to add Box2D body to Entity #" + std::to_string(iEntityID) + ", Entity has no Mesh");
	}
}


void Entity::SetupB2CircleBody(b2World & Box2DWorld, b2BodyType BodyType, bool bCanRotate, bool bHasFixture, float Density, float Friction)
{
	if (EntityMesh)
	{
		// Define the dynamic body. We set its position and call the body factory.
		b2BodyDef bodyDef;
		bodyDef.type = BodyType;
		bodyDef.position.Set(transform.Position.x, transform.Position.y);
		bodyDef.userData = &*this;
		body = Box2DWorld.CreateBody(&bodyDef);
		body->SetTransform(bodyDef.position, (transform.Rotation.z / 180) * b2_pi);
		body->SetFixedRotation(!bCanRotate);

		// Define another Circle shape for our dynamic body.
		b2CircleShape circleShape;
		circleShape.m_radius = EntityMesh->m_fHeight / 2.0f;
		circleShape.m_p = b2Vec2(0.0f, 0.0f);

		if (bHasFixture)
		{
			// Define the dynamic body fixture.
			b2FixtureDef fixtureDef;
			fixtureDef.shape = &circleShape;
			// Set the box density to be non-zero, so it will be dynamic.
			fixtureDef.density = Density;
			// Override the default friction.
			fixtureDef.friction = Friction;

			// Add the shape to the body.
			body->CreateFixture(&fixtureDef);
		}
		else
		{
			body->CreateFixture(&circleShape, 0.0f);
		}
	}
	else
	{
		LogManager::GetInstance()->DisplayLogMessage("Failed to add Box2D body to Entity #" + std::to_string(iEntityID) + ", Entity has no Mesh");
	}
}


void Entity::SetBox2DTransform(glm::vec3 _Position, float _Rotation)
{	
	if (body) body->SetTransform(b2Vec2(_Position.x, _Position.y), (_Rotation / 180) * b2_pi);
}
