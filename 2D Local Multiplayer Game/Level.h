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
#include "Engine\CXBOXController.h"

#include <map>

enum InputDirection;

enum Gamemode
{
	DROPOUT,
	BOMB_SURVIVAL	
};

struct ContactInfo
{
	std::shared_ptr<Entity> Object1 = nullptr;
	std::shared_ptr<Entity> Object2 = nullptr;
	b2Vec2 Object1Velocity = b2Vec2_zero;
	b2Vec2 Object2Velocity = b2Vec2_zero;
};

std::string GetGamemodeString(Gamemode _gamemode);
Gamemode GetRandomGamemode();


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
	Level(std::string sSceneName, Gamemode LevelGM);
	~Level();

	virtual void Update() override;
	virtual void OnLoadScene() override;

	void ApplyCollision(std::shared_ptr<Entity> Object, std::shared_ptr<Entity> Collided);
	void PlayerKnockedOut(int PlayerID);
	void OnGameComplete();
	void ShowEndScreen();
	void GamemodeProcess();
	void RandomWeaponsSpawnCycle();
	void SpawnRandomWeapon();
	void RunCollisionResponses();
	void SpawnBomb();
	void RandomSpawnBomb();

	void TogglePause();

	void AddDropoutBlock(glm::vec2 Pos, int TileCount = 1, const char* ImagePath = "Resources/Images/Box.png");
	void AddBlock(glm::vec2 Pos, float Width = 0.5f, float Height = 0.5f, const char* ImagePath = "Resources/Images/Box.png");
	void AddSpike(glm::vec2 Pos);

	void PControllerInput(InputController _ControllerInput);
	void ControllerInputAxis(InputDirection NewInput);

	std::map<int, std::shared_ptr<class Player>> Players;
	std::map<int, std::shared_ptr<class PlayerController>> PlayerControllers;
	std::map<int, std::shared_ptr<UIText>> KnockbackTexts;

	std::vector<ContactInfo> AllContacts;

	std::shared_ptr<Entity> CircleEntity;
	std::shared_ptr<class MachineGun> NewWeapon;

	b2World world;
	float gravity = 15.0f;

	float32 timeStep;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	float CameraCloseRange = 5;
	float CameraClosestZoom = 170.0f;
	float CameraFurthestZoom = 120.0f; // Smaller is further
	float CameraZoomOutMultiplyer = 15.0f;

	float PlayerFalloutYPosition = -7.0f;

	bool GamePaused = false;
	bool GameIsComplete = false;

	Gamemode CurrentGamemode;

private:
	PlayerContactListener CustomContactListener;
	
	// Weapon system
	float WeaponSpawnTime = 0.0f;

	float MinWeaponSpawnTime = 4.0f;
	float MaxWeaponSpawnTime = 20.0f;

	float BombSpawnTime = 5.0f;
	float MinBombSpawnTime = 2.0f;
	float MaxBombSpawnTime = 5.0f;

	glm::vec2 MinPosition = { -6, -2 };
	glm::vec2 MaxPosition = { 5.5, 3 };

	std::vector<std::shared_ptr<UIElement>> PauseElements;
	std::shared_ptr<class UIButton> CurrentSelectedButton;
};

