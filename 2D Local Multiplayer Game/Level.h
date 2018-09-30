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
#include "Engine\Scene.h"
#include "Engine\LogManager.h"
#include <Box2D.h>

class PlayerContactListener : public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact);

	void EndContact(b2Contact* contact)
	{ /* handle end event */
	}

	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);

	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
};

class Level : public Scene
{
public:
	Level(std::string sSceneName);
	~Level();

	virtual void Update() override;
	virtual void OnLoadScene() override;

	static void ApplyCollision(std::shared_ptr<Entity> Object, std::shared_ptr<Entity> Collided);
	
	std::vector<std::shared_ptr<class Player>> Players;

	std::vector<b2Body*> Box2DCollisionObjects;

	std::shared_ptr<Entity> CircleEntity;

	b2World world;
	float gravity = 15.0f;

	float32 timeStep;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	float CameraCloseRange = 5;
	float CameraClosestZoom = 180.0f;
	float CameraFurthestZoom = 120.0f; // Smaller is further
	float CameraZoomOutMultiplyer = 15.0f;

	float PlayerFalloutYPosition = -7.0f;

private:
	PlayerContactListener CustomContactListener;

	float FrameTime = 0;
	int CurrentFrames = 0;
};

