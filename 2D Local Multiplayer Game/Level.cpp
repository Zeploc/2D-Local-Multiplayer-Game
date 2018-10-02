//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name    	:    Menu.cpp
// Description    	:    main implementation for Menu
// Author       	:    Alex Coultas
// Mail         	:    alex.cou7417@mediadesign.school.nz
//


// This Includes //
#include "Level.h"

// Engine Includes //
#include "Engine\Plane.h"
#include "Engine\UIButton.h"
#include "Engine\SceneManager.h"
#include "Engine\Cube.h"
#include "Engine\Sphere.h"
#include "Engine\Input.h"
#include "Engine\LogManager.h"
#include "Engine\Time.h"
//#include <Box2D/Dynamics/b2World.h>

// Local Includes //
#include "Player.h"
#include "PlayerController.h"
#include "SpikeHazard.h"
#include "GameManager.h"
#include "LevelManager.h"
#include "MachineGun.h"
#include "DropoutBlock.h"

// Library Includes //
#include <iostream>
#include <glm\gtx\string_cast.hpp>
// Prototypes
void BackToMenu();

Level::Level(std::string sSceneName, Gamemode LevelGM) : Scene(sSceneName), world(b2Vec2(0.0f, -10.0f))
{
	CurrentGamemode = LevelGM;

	// Pause Screen elements
	std::shared_ptr<UIImage> BackImage(new UIImage(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, Camera::GetInstance()->SCR_HEIGHT / 2), Utils::CENTER, 0.0f, glm::vec4(0.5f, 0.5f, 0.5f, 0.6f), Camera::GetInstance()->SCR_WIDTH * 0.8, Camera::GetInstance()->SCR_HEIGHT * 0.7));
	std::shared_ptr<UIText> Title(new UIText(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, Camera::GetInstance()->SCR_HEIGHT / 2 - 100.0f), 0, glm::vec4(0.9, 0.9, 0.9, 1.0), "Paused", "Resources/Fonts/Roboto-Black.ttf", 100, Utils::CENTER));
	AddUIElement(BackImage);
	AddUIElement(Title);
	PauseElements.push_back(BackImage);
	PauseElements.push_back(Title);
	BackImage->SetActive(false);
	Title->SetActive(false);

	CircleEntity = std::make_shared<Entity>(Entity({ { 5.0f, 2.0f, 0 } ,{ 0, 0, 45 },{ 1, 1, 1 } }, Utils::CENTER));
	std::shared_ptr<Plane> CircleImage = std::make_shared<Plane>(Plane(0.5f, 0.5f, { 0.3f, 0.4f, 0.9f, 1.0f }, "Resources/Images/Box.png"));
	CircleEntity->AddMesh(CircleImage);
	//AddEntity(CircleEntity, true);
	//CircleEntity->SetupB2CircleBody(world, b2_dynamicBody, true, true, 10.0f);

	std::shared_ptr<Entity> DynamicBoxEntity = std::make_shared<Entity>(Entity({ { 0, 4, 0 } ,{ 0, 0, 20 },{ 1, 1, 1 } }, Utils::CENTER));
	std::shared_ptr<Plane> TestImage = std::make_shared<Plane>(Plane(0.5f, 0.5f, { 0.9f, 0.3f, 0.1f, 1.0f }, "Resources/Images/Box.png"));
	DynamicBoxEntity->AddMesh(TestImage);
	//AddEntity(DynamicBoxEntity, true);
	//DynamicBoxEntity->SetupB2BoxBody(world, b2_dynamicBody, true, true, 10.0f);
		

	std::shared_ptr<SpikeHazard> SpikeHazzard1 = std::make_shared<SpikeHazard>(SpikeHazard({ { -2, 1, 0 } ,{ 0, 0, -10 },{ 1, 1, 1 } }, Utils::CENTER));
	SpikeHazzard1->Init(world);
	AddEntity(SpikeHazzard1, true);
	
	std::shared_ptr<UIButton> QuitBtn(new UIButton(glm::vec2(10, Camera::GetInstance()->SCR_HEIGHT - 10), Utils::BOTTOM_LEFT, 0.0f, glm::vec4(0.3f, 0.3f, 0.3f, 1.0f), glm::vec4(0.7f, 0.7f, 0.7f, 1.0f), 480, 70, BackToMenu));
	QuitBtn->AddText("Back to Menu", "Resources/Fonts/Roboto-Thin.ttf", 34, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), Utils::CENTER, { 0, 0 });
	//AddUIElement(QuitBtn);

	std::shared_ptr<UIText> KnockbackPercentage1(new UIText(glm::vec2(50, Camera::GetInstance()->SCR_HEIGHT -40), Utils::BOTTOM_CENTER, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), "100", "Resources/Fonts/Roboto-Medium.ttf", 50, Utils::CENTER));
	AddUIElement(KnockbackPercentage1);

	std::shared_ptr<UIText> KnockbackPercentage2(new UIText(glm::vec2(400, Camera::GetInstance()->SCR_HEIGHT - 40), Utils::BOTTOM_CENTER, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), "100", "Resources/Fonts/Roboto-Medium.ttf", 50, Utils::CENTER));
	AddUIElement(KnockbackPercentage2);

	std::shared_ptr<UIText> KnockbackPercentage3(new UIText(glm::vec2(800, Camera::GetInstance()->SCR_HEIGHT - 40), Utils::BOTTOM_CENTER, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), "100", "Resources/Fonts/Roboto-Medium.ttf", 50, Utils::CENTER));
	AddUIElement(KnockbackPercentage3);

	std::shared_ptr<UIText> KnockbackPercentage4(new UIText(glm::vec2(1200, Camera::GetInstance()->SCR_HEIGHT - 40), Utils::BOTTOM_CENTER, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), "100", "Resources/Fonts/Roboto-Medium.ttf", 50, Utils::CENTER));
	AddUIElement(KnockbackPercentage4);

	//bIsPersistant = true;	
	world.SetGravity(b2Vec2(0.0f, -gravity));

	Camera::GetInstance()->SetWindowScale(CameraClosestZoom);

	timeStep = 1.0f / 60.0f;

	world.SetContactListener(&CustomContactListener);
}

Level::~Level()
{

}

void Level::Update()
{
	if (GamePaused)
	{
		for (auto& PController : PlayerControllers)
		{
			PController.second->Update();
		}
		return;
	}
	Scene::Update();

	//world.Step(Time::dTimeDelta, 6, 2);
	world.Step(timeStep, 6, 2);
	
	RunCollisionResponses();
	RandomWeaponsSpawnCycle();
	GamemodeProcess();

	FrameTime += Time::dTimeDelta;
	CurrentFrames++;
	if (FrameTime >= 1)
	{
		std::cout << "Frame count: " << CurrentFrames << std::endl;
		FrameTime = 0.0f;
		CurrentFrames = 0;
	}

	float RangeOutsideClosetView = 0.0f;
	
	auto Endit = Players.end();

	if (Input::GetInstance()->KeyState[(unsigned char)'l'] == Input::INPUT_FIRST_PRESS)
	{
		NewWeapon = std::make_shared<MachineGun>(MachineGun({ 0, 0 }, Utils::CENTER));
		AddEntity(NewWeapon);
		Players[0]->EquipWeapon(NewWeapon);
	}

	for (auto it = Players.begin(); it != Endit;)
	{
		if ((*it).second->transform.Position.x < -CameraCloseRange || (*it).second->transform.Position.x > CameraCloseRange)
		{
			float PDist = abs((*it).second->transform.Position.x) - CameraCloseRange;
			if (PDist > RangeOutsideClosetView) RangeOutsideClosetView = PDist;
		}
		// Check if they've fallen out
		if ((*it).second->transform.Position.y < PlayerFalloutYPosition)
		{
			int PlayerId = (*it).first;
			DestroyEntity((*it).second);
			it = Players.erase(it);
			Endit = Players.end();
			PlayerKnockedOut(PlayerId);
			continue;
			
		}
		++it;
	}
	float NewZoom = glm::clamp(CameraClosestZoom - RangeOutsideClosetView * CameraZoomOutMultiplyer, CameraFurthestZoom, CameraClosestZoom);
	Camera::GetInstance()->SetWindowScale(NewZoom);
}

void Level::OnLoadScene()
{
	Scene::OnLoadScene();
	LevelManager::GetInstance()->RemoveExcessLevel();
	LevelManager::GetInstance()->AddRandomMapForGamemode(std::dynamic_pointer_cast<Level>(this->shared_from_this()));
	glm::vec3 SpawnPosition = { -2, -2, 0 };
	for (auto& player : GameManager::GetInstance()->vPlayerInfo)
	{
		// Add player
		std::shared_ptr<Player> PlayerEnt = std::make_shared<Player>(Player(SpawnPosition, player.second.PlayerID));
		AddEntity(PlayerEnt, true);
		PlayerEnt->Init(world);
		Players.insert(std::pair<int, std::shared_ptr<Player>>(player.second.PlayerID, PlayerEnt));
		SpawnPosition.x += 1;
		// Add Player Controller
		std::shared_ptr<PlayerController> newPlayerController = std::make_shared<PlayerController>(PlayerController(player.second.PlayerID, std::dynamic_pointer_cast<Level>(this->shared_from_this())));
		PlayerControllers.insert(std::pair<int, std::shared_ptr<PlayerController>>(player.second.PlayerID, newPlayerController));
		AddEntity(newPlayerController);
	}		
}

void BackToMenu()
{
	SceneManager::GetInstance()->SwitchScene("Menu");
}

void Level::ApplyCollision(std::shared_ptr<Entity> Object, std::shared_ptr<Entity> Collided)
{
	std::shared_ptr<Player> Player1 = std::dynamic_pointer_cast<Player>(Object);
	std::shared_ptr<Player> Player2 = std::dynamic_pointer_cast<Player>(Collided);
	std::shared_ptr<DropoutBlock> DropBlock = std::dynamic_pointer_cast<DropoutBlock>(Collided);
	std::shared_ptr<Weapon> SpeedyGun = std::dynamic_pointer_cast<Weapon>(Object);
	std::shared_ptr<SpikeHazard> Spike = std::dynamic_pointer_cast<SpikeHazard>(Collided);

	if (Player1 && Collided->body && Player2 && Collided->body)
	{	
		if (Player1->body->GetLinearVelocity().Length() > Player2->body->GetLinearVelocity().Length() && Player1->GetIsRolling() == true)
		{
			Player2->ApplyKnockback(glm::vec2(Player1->body->GetLinearVelocity().x, Player1->body->GetLinearVelocity().y), false);
		}
		else if(Player2->GetIsRolling() == true)
		{
			Player1->ApplyKnockback((glm::vec2(Player2->body->GetLinearVelocity().x, Player2->body->GetLinearVelocity().y)), false);
		}
	}
	else if (Player1 && Collided->body && DropBlock) // OR if a bullet is the first object
	{
		DropBlock->BlockHit();
	}
	else if (Player1 && Collided->body && Spike) // OR if a bullet is the first object
	{
		std::cout << "Collided with Spike" << std::endl;
		//SceneManager::GetInstance()->GetCurrentScene()->DestroyEntity((Player1->shared_from_this()));		

		int PlayerId = Player1->GetID();
		DestroyEntity(Player1);
		PlayerKnockedOut(PlayerId);
	}
	else if (Player1 && Collided->body && SpeedyGun) // OR if a bullet is the first object
	{
		std::cout << "Gun Collision" << std::endl;
		//std::shared_ptr<Player> Player1 = std::dynamic_pointer_cast<Player>(IsEntity2->shared_from_this());
		//Player1->EquipWeapon(SpeedyGun);
	}
}

void Level::PlayerKnockedOut(int PlayerID)
{
	/// Assign score/place
	GameManager::GetInstance()->vPlayerInfo[PlayerID].CurrentGamePlace = Players.size(); 
	if (Players.size() <= 1)
	{
		OnGameComplete();
	}
}

void Level::OnGameComplete()
{
	GamePaused = true;
	GameIsComplete = true;
	ShowEndScreen();
}

void Level::ShowEndScreen()
{
	std::shared_ptr<UIImage> BackImage(new UIImage(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, Camera::GetInstance()->SCR_HEIGHT / 2), Utils::CENTER, 0.0f, glm::vec4(0.5f, 0.5f, 0.5f, 0.6f), Camera::GetInstance()->SCR_WIDTH * 0.8, Camera::GetInstance()->SCR_HEIGHT * 0.7));
	std::shared_ptr<UIText> Title(new UIText(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, Camera::GetInstance()->SCR_HEIGHT / 2 - 100.0f), 0, glm::vec4(0.9, 0.9, 0.9, 1.0), "Game Complete", "Resources/Fonts/Roboto-Black.ttf", 100, Utils::CENTER));
	AddUIElement(BackImage);
	AddUIElement(Title);

	/// Have players stats, get from game manager, display each position, and each score
	/// Generate random new gamemode
	/// Display next gamemode (GetGamemodeString())
		
}

void Level::GamemodeProcess()
{
	switch (CurrentGamemode)
	{
	case DROPOUT:
	{

	}
		break;
	case BOMB_SURVIVAL:
	{
		/// Add random spawning of bombs
	}
		break;
	default:
		break;
	}
}

void Level::SpawnRandomWeapon()
{
	WeaponType NewWeaponType = WeaponType(rand() % 5);

	glm::vec2 RandomPos = { 0, 0 };
	RandomPos.x = rand() % int((MaxPosition.x - MinPosition.x) * 1000);
	RandomPos.x /= 1000.0f;
	RandomPos.x += MinPosition.x;
	RandomPos.y = rand() % int((MaxPosition.y - MinPosition.y) * 1000);
	RandomPos.y /= 1000.0f;
	RandomPos.y += MinPosition.y;

	std::shared_ptr<class Weapon> NewWeapon;
	switch (NewWeaponType)
	{
	case ROCKET_LAUNCHER:
		NewWeapon = std::make_shared<MachineGun>(MachineGun(RandomPos, Utils::CENTER));
		break;
	case MACHINE_GUN:
		NewWeapon = std::make_shared<MachineGun>(MachineGun(RandomPos, Utils::CENTER));
		break;
	case GRENADE_LAUNCHER:
		NewWeapon = std::make_shared<MachineGun>(MachineGun(RandomPos, Utils::CENTER));
		break;
	case SNIPER:
		NewWeapon = std::make_shared<MachineGun>(MachineGun(RandomPos, Utils::CENTER));
		break;
	case SHOTGUN:
		NewWeapon = std::make_shared<MachineGun>(MachineGun(RandomPos, Utils::CENTER));
		break;
	default:
		break;
	}
	AddEntity(NewWeapon);
}

void Level::RunCollisionResponses()
{
	for (auto& ColInfo : AllContacts)
	{
		ApplyCollision(ColInfo.Object1, ColInfo.Object2);
		ApplyCollision(ColInfo.Object2, ColInfo.Object1);
	}
	AllContacts.clear();
}

void Level::TogglePause()
{
	GamePaused = !GamePaused;
	for (auto& PauseElement : PauseElements)
	{
		PauseElement->SetActive(GamePaused);
	}
}

void Level::AddDropoutBlock(glm::vec2 Pos, int TileCount, const char * ImagePath)
{
	for (int i = 0; i < TileCount; i++)
	{
		std::shared_ptr<DropoutBlock> FallBlock = std::make_shared<DropoutBlock>(DropoutBlock(Pos, Utils::CENTER, ImagePath));
		FallBlock->Init(world);
		AddEntity(FallBlock, true);
		Pos.x += 0.5;
	}
}

void Level::AddBlock(glm::vec2 Pos, float Width, float Height, const char * ImagePath)
{
	std::shared_ptr<Entity> NewPlatform = std::make_shared<Entity>(Entity({ { Pos, 0 } ,{ 0, 0, 0 },{ 1, 1, 1 } }, Utils::CENTER));
	std::shared_ptr<Plane> NewPlatformImage = std::make_shared<Plane>(Plane(Width, Height, { 0.5f, 0.7f, 0.9f, 1.0f }, "Resources/Images/Box.png", 1, false));
	NewPlatform->AddMesh(NewPlatformImage);
	AddEntity(NewPlatform, true);
	NewPlatform->SetupB2BoxBody(world, b2_staticBody, false, false);
}

void Level::RandomWeaponsSpawnCycle()
{
	WeaponSpawnTime -= Time::dTimeDelta;
	if (WeaponSpawnTime <= 0.0f)
	{
		int RangeSize = (MaxWeaponSpawnTime - MinWeaponSpawnTime) * 1000;
		WeaponSpawnTime = (rand() % RangeSize) / 1000 + MinWeaponSpawnTime;
		SpawnRandomWeapon();
		std::cout << "New random time " << WeaponSpawnTime << std::endl;
	}
}

void Level::PControllerInput(InputController _ControllerInput)
{
	// Check if players presses start button, tell level (check if paused) and act accordingly
	if (_ControllerInput == SPECIAL_BUTTON_RIGHT)
	{
		if (GameIsComplete)
		{
			// next random round
			LevelManager::GetInstance()->NewRound(GetRandomGamemode());
		}
		else
		{
			TogglePause();
			// unpause
		}
	}
}

void PlayerContactListener::BeginContact(b2Contact * contact)
{
	std::shared_ptr<Level> LevelRef = std::dynamic_pointer_cast<Level>(SceneManager::GetInstance()->GetCurrentScene());
	void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData1 && bodyUserData2)
	{
		Entity* IsEntity1 = reinterpret_cast<Entity*>(bodyUserData1);
		Entity* IsEntity2 = reinterpret_cast<Entity*>(bodyUserData2);

		if (IsEntity1 && IsEntity2 && IsEntity1->GetEntityValue() > -1 && IsEntity2->GetEntityValue() > -1)
		{
			ContactInfo NewContactInfo;
			NewContactInfo.Object1 = IsEntity1->shared_from_this();
			NewContactInfo.Object2 = IsEntity2->shared_from_this();
			NewContactInfo.Object1Velocity = IsEntity1->body->GetLinearVelocity();
			NewContactInfo.Object2Velocity = IsEntity2->body->GetLinearVelocity();
			LevelRef->AllContacts.push_back(NewContactInfo);
		}
	}
}

void PlayerContactListener::PreSolve(b2Contact * contact, const b2Manifold * oldManifold)
{

}

void PlayerContactListener::PostSolve(b2Contact * contact, const b2ContactImpulse * impulse)
{
}

std::string GetGamemodeString(Gamemode _gamemode)
{
	switch (_gamemode)
	{
		case DROPOUT:
			return "Dropout";
		case BOMB_SURVIVAL:
			return "Bomb Survival";
	}
	return "NONE";
}

Gamemode GetRandomGamemode()
{
	int RandGamemode = rand() % 2;
	std::cout << GetGamemodeString(Gamemode(RandGamemode)) << std::endl;
	return Gamemode(RandGamemode);
}
