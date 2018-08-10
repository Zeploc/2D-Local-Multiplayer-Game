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

class Level : public Scene
{
public:
	Level(std::string sSceneName);
	~Level();

	virtual void Update() override;
	virtual void OnLoadScene() override;
	
	std::vector<std::shared_ptr<class Player>> Players;

	std::vector<b2Body*> Box2DCollisionObjects;

	b2World world;
	float gravity = 15.0f;

	float32 timeStep;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

};

