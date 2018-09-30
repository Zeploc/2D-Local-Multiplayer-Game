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
#include "GameManager.h"
#include "LevelManager.h"

// Library Includes //
#include <iostream>

// Prototypes
void BackToMenu();

Level::Level(std::string sSceneName, Gamemode LevelGM) : Scene(sSceneName), world(b2Vec2(0.0f, -10.0f))
{
	CurrentGamemode = LevelGM;

	std::shared_ptr<Entity> BottomPlatform = std::make_shared<Entity>(Entity({ { 0, -3.0f, 0 } ,{ 0, 0, 0 },{ 1, 1, 1 } }, Utils::CENTER));
	std::shared_ptr<Plane> NewImage = std::make_shared<Plane>(Plane(10.0f, 1.0f, { 0.3f, 0.4f, 0.9f, 1.0f }, "Resources/Images/Box.png", 1, false));
	BottomPlatform->AddMesh(NewImage);
	AddEntity(BottomPlatform, true);
	BottomPlatform->SetupB2BoxBody(world, b2_staticBody, false, false);
	Box2DCollisionObjects.push_back(BottomPlatform->body);

	std::shared_ptr<Entity> MiddlePlatform = std::make_shared<Entity>(Entity({ { 0, 1.0f, 0 } ,{ 0, 0, 0 },{ 1, 1, 1 } }, Utils::CENTER));
	std::shared_ptr<Plane> MiddlePlatformImage = std::make_shared<Plane>(Plane(6.0f, 0.5f, { 0.3f, 0.4f, 0.9f, 1.0f }, "Resources/Images/Box.png", 1, false));
	MiddlePlatform->AddMesh(MiddlePlatformImage);
	AddEntity(MiddlePlatform, true);
	MiddlePlatform->SetupB2BoxBody(world, b2_staticBody, false, false);
	Box2DCollisionObjects.push_back(MiddlePlatform->body);

	std::shared_ptr<Entity> LeftPlatform = std::make_shared<Entity>(Entity({ { -5.0f, -1.0f, 0 } ,{ 0, 0, 0 },{ 1, 1, 1 } }, Utils::CENTER));
	std::shared_ptr<Plane> LeftPlatformImage = std::make_shared<Plane>(Plane(3.0f, 0.5f, { 0.3f, 0.4f, 0.9f, 1.0f }, "Resources/Images/Box.png", 1, false));
	LeftPlatform->AddMesh(LeftPlatformImage);
	AddEntity(LeftPlatform, true);
	LeftPlatform->SetupB2BoxBody(world, b2_staticBody, false, false);
	Box2DCollisionObjects.push_back(LeftPlatform->body);

	std::shared_ptr<Entity> RightPlatform = std::make_shared<Entity>(Entity({ { 5.0f, -1.0f, 0 } ,{ 0, 0, 45 },{ 1, 1, 1 } }, Utils::CENTER));
	std::shared_ptr<Plane> RightPlatformImage = std::make_shared<Plane>(Plane(3.0f, 0.5f, { 0.3f, 0.4f, 0.9f, 1.0f }, "Resources/Images/Box.png", 1, false));
	RightPlatform->AddMesh(RightPlatformImage);
	AddEntity(RightPlatform, true);
	RightPlatform->SetupB2BoxBody(world, b2_staticBody, false, false);
	Box2DCollisionObjects.push_back(RightPlatform->body);

	CircleEntity = std::make_shared<Entity>(Entity({ { 5.0f, 2.0f, 0 } ,{ 0, 0, 45 },{ 1, 1, 1 } }, Utils::CENTER));
	std::shared_ptr<Plane> CircleImage = std::make_shared<Plane>(Plane(0.5f, 0.5f, { 0.3f, 0.4f, 0.9f, 1.0f }, "Resources/Images/Box.png"));
	CircleEntity->AddMesh(CircleImage);
	//AddEntity(CircleEntity, true);
	//CircleEntity->SetupB2CircleBody(world, b2_dynamicBody, true, true, 10.0f);
	Box2DCollisionObjects.push_back(CircleEntity->body);

	std::shared_ptr<Entity> DynamicBoxEntity = std::make_shared<Entity>(Entity({ { 0, 4, 0 } ,{ 0, 0, 20 },{ 1, 1, 1 } }, Utils::CENTER));
	std::shared_ptr<Plane> TestImage = std::make_shared<Plane>(Plane(0.5f, 0.5f, { 0.9f, 0.3f, 0.1f, 1.0f }, "Resources/Images/Box.png"));
	DynamicBoxEntity->AddMesh(TestImage);
	//AddEntity(DynamicBoxEntity, true);
	//DynamicBoxEntity->SetupB2BoxBody(world, b2_dynamicBody, true, true, 10.0f);
	Box2DCollisionObjects.push_back(DynamicBoxEntity->body);

	std::shared_ptr<Entity> DynamicBoxEntity2 = std::make_shared<Entity>(Entity({ { 4, 3, 0 } ,{ 0, 0, -10 },{ 1, 1, 1 } }, Utils::CENTER));
	DynamicBoxEntity2->AddMesh(TestImage);
	//AddEntity(DynamicBoxEntity2, true);
	//->SetupB2BoxBody(world, b2_dynamicBody, true, true, 10.0f);
	Box2DCollisionObjects.push_back(DynamicBoxEntity2->body);

	std::shared_ptr<Entity> DynamicBoxEntity3 = std::make_shared<Entity>(Entity({ { -1, -1, 0 } ,{ 0, 0, -10 },{ 1, 1, 1 } }, Utils::CENTER));
	DynamicBoxEntity3->AddMesh(TestImage);
	//AddEntity(DynamicBoxEntity3, true);
	//DynamicBoxEntity3->SetupB2BoxBody(world, b2_dynamicBody, true, true, 10.0f);
	Box2DCollisionObjects.push_back(DynamicBoxEntity3->body);
	

	std::shared_ptr<UIButton> QuitBtn(new UIButton(glm::vec2(10, Camera::GetInstance()->SCR_HEIGHT - 10), Utils::BOTTOM_LEFT, 0.0f, glm::vec4(0.3f, 0.3f, 0.3f, 1.0f), glm::vec4(0.7f, 0.7f, 0.7f, 1.0f), 480, 70, BackToMenu));
	QuitBtn->AddText("Back to Menu", "Resources/Fonts/Roboto-Thin.ttf", 34, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), Utils::CENTER, { 0, 0 });
	AddUIElement(QuitBtn);

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
		CircleEntity->body->SetAngularVelocity(20);
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
		std::shared_ptr<PlayerController> newPlayerController = std::make_shared<PlayerController>(PlayerController(player.second.PlayerID));
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

	}
		break;
	default:
		break;
	}
}

void Level::PControllerInput(InputController _ControllerInput)
{
	if (GamePaused)
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
				// unpause
			}
		}
	}
}

void PlayerContactListener::BeginContact(b2Contact * contact)
{
	void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData1 && bodyUserData2)
	{
		Entity* IsEntity1 = reinterpret_cast<Entity*>(bodyUserData1);
		Entity* IsEntity2 = reinterpret_cast<Entity*>(bodyUserData2);
		if (IsEntity1 && IsEntity2 && IsEntity1->GetEntityValue() > -1 && IsEntity2->GetEntityValue() > -1)
		{
			Level::ApplyCollision(IsEntity1->shared_from_this(), IsEntity2->shared_from_this());
			Level::ApplyCollision(IsEntity2->shared_from_this(), IsEntity1->shared_from_this());
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
