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
#include "Engine\SoundManager.h"
//#include <Box2D/Dynamics/b2World.h>

// Local Includes //
#include "Player.h"
#include "PlayerController.h"
#include "SpikeHazard.h"
#include "GameManager.h"
#include "LevelManager.h"
#include "MachineGun.h"
#include "DropoutBlock.h"
#include "Menu.h"
#include "Bomb.h"
#include "Bullet.h"

// Library Includes //
#include <iostream>
#include <glm\gtx\string_cast.hpp>
// Prototypes
void BackToMenu();
void Resume();

Level::Level(std::string sSceneName, Gamemode LevelGM) : Scene(sSceneName), world(b2Vec2(0.0f, -10.0f))
{
	CurrentGamemode = LevelGM;

	SoundManager::GetInstance()->AddAudio("Resources/Sounds/DeathSound.wav", false, "PlayerDeath");
	// Pause Screen elements
	std::shared_ptr<UIImage> BackImage(new UIImage(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, Camera::GetInstance()->SCR_HEIGHT / 2), Utils::CENTER, 0.0f, glm::vec4(0.5f, 0.5f, 0.5f, 0.6f), Camera::GetInstance()->SCR_WIDTH * 0.8, Camera::GetInstance()->SCR_HEIGHT * 0.7));
	std::shared_ptr<UIText> Title(new UIText(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, Camera::GetInstance()->SCR_HEIGHT / 2 - 100.0f), 0, glm::vec4(0.9, 0.9, 0.9, 1.0), "Paused", "Resources/Fonts/Roboto-Black.ttf", 100, Utils::CENTER));
	std::shared_ptr<UIButton> ResumeBtn(new UIButton(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, Camera::GetInstance()->SCR_HEIGHT / 2 + 80), Utils::CENTER, 0.0f, glm::vec4(0.3f, 0.3f, 0.3f, 1.0f), glm::vec4(0.7f, 0.7f, 0.7f, 1.0f), 480, 70, Resume));
	ResumeBtn->AddText("RESUME", "Resources/Fonts/Roboto-Thin.ttf", 34, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), Utils::CENTER, { 0, 0 });
	std::shared_ptr<UIButton> QuitBtn(new UIButton(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, Camera::GetInstance()->SCR_HEIGHT / 2 + 160), Utils::CENTER, 0.0f, glm::vec4(0.3f, 0.3f, 0.3f, 1.0f), glm::vec4(0.7f, 0.7f, 0.7f, 1.0f), 480, 70, BackToMenu));
	QuitBtn->AddText("QUIT", "Resources/Fonts/Roboto-Thin.ttf", 34, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), Utils::CENTER, { 0, 0 });

	std::shared_ptr<UIImage> RoundBackImage(new UIImage(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, Camera::GetInstance()->SCR_HEIGHT), Utils::BOTTOM_CENTER, 0.0f, glm::vec4(0.2f, 0.2f, 0.2f, 0.8f), Camera::GetInstance()->SCR_WIDTH, 70));
	AddUIElement(RoundBackImage);
	IngameHUD.push_back(RoundBackImage);

	AddUIElement(BackImage);
	AddUIElement(Title);
	AddUIElement(ResumeBtn);
	AddUIElement(QuitBtn);
	PauseElements.push_back(BackImage);
	PauseElements.push_back(Title);
	PauseElements.push_back(ResumeBtn);
	PauseElements.push_back(QuitBtn);
	BackImage->SetActive(false);
	Title->SetActive(false);
	ResumeBtn->SetActive(false);
	QuitBtn->SetActive(false);
	CurrentSelectedButton = ResumeBtn;
	CurrentSelectedButton->HoverOverride = true;
		

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

	//std::cout << "Frame count: " << Time::dFPS << std::endl;

	float RangeOutsideClosetView = 0.0f;
	
	auto Endit = Players.end();

	if (Input::GetInstance()->KeyState[(unsigned char)'l'] == Input::INPUT_FIRST_PRESS)
	{
		NewWeapon = std::make_shared<MachineGun>(MachineGun({ 0, 0 }, Utils::CENTER));
		AddEntity(NewWeapon);
		NewWeapon->Init(world);
		
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
			SoundManager::GetInstance()->PlayAudio("PlayerDeath");
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
	glm::vec3 SpawnPosition = { -1, 2, 0 };
	for (auto& player : GameManager::GetInstance()->vPlayerInfo)
	{
		// Add player
		glm::vec4 KnockbackColour = GetPlaceColour(player.second.FullGamePlace);		
		std::shared_ptr<UIText> KnockbackPercentage(new UIText(glm::vec2(140 + 330 * player.first, Camera::GetInstance()->SCR_HEIGHT - 35), Utils::BOTTOM_LEFT, KnockbackColour, "100%", "Resources/Fonts/Roboto-Medium.ttf", 45, Utils::CENTER));
		AddUIElement(KnockbackPercentage);
		std::shared_ptr<UIImage> KnockbackIcon(new UIImage(glm::vec2(50 + 330 * player.first, Camera::GetInstance()->SCR_HEIGHT - 35), Utils::CENTER, 0, {1.0f, 1.0f, 1.0f, 1.0f}, 50, 50, Menu::GetSkinPath(player.second.Skin), 1));
		AddUIElement(KnockbackIcon);
		std::shared_ptr<Player> PlayerEnt = std::make_shared<Player>(Player(SpawnPosition, player.second.PlayerID));
		AddEntity(PlayerEnt, true);
		PlayerEnt->Init(world);
		Players.insert(std::pair<int, std::shared_ptr<Player>>(player.second.PlayerID, PlayerEnt));
		SpawnPosition.x += 1;
		// Add Player Controller
		std::shared_ptr<PlayerController> newPlayerController = std::make_shared<PlayerController>(PlayerController(player.second.PlayerID, std::dynamic_pointer_cast<Level>(this->shared_from_this())));
		PlayerControllers.insert(std::pair<int, std::shared_ptr<PlayerController>>(player.second.PlayerID, newPlayerController));
		AddEntity(newPlayerController);
		player.second.KnockbackText = KnockbackPercentage;
		player.second.CurrentGamePlace = 0;
		IngameHUD.push_back(KnockbackPercentage);
		IngameHUD.push_back(KnockbackIcon);
	}
}

void BackToMenu()
{
	SceneManager::GetInstance()->SwitchScene("Menu");
}

void Resume()
{
	std::shared_ptr<Level> LevelRef = std::dynamic_pointer_cast<Level>(SceneManager::GetInstance()->GetCurrentScene());
	LevelRef->TogglePause();
}

void Level::ApplyCollision(std::shared_ptr<Entity> Object, std::shared_ptr<Entity> Collided)
{
	std::shared_ptr<Player> Player1 = std::dynamic_pointer_cast<Player>(Object);
	std::shared_ptr<Player> Player2 = std::dynamic_pointer_cast<Player>(Collided);
	std::shared_ptr<DropoutBlock> DropBlock = std::dynamic_pointer_cast<DropoutBlock>(Collided);
	std::shared_ptr<Weapon> SpeedyGun = std::dynamic_pointer_cast<Weapon>(Collided);
	std::shared_ptr<SpikeHazard> Spike = std::dynamic_pointer_cast<SpikeHazard>(Collided);
	std::shared_ptr<Bomb> Bombuu = std::dynamic_pointer_cast<Bomb>(Collided);
	std::shared_ptr<Bullet> BigOldMetalKiller = std::dynamic_pointer_cast<Bullet>(Collided);

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
		Players.erase(PlayerId);
		PlayerKnockedOut(PlayerId);
	}
	else if (Player1 && Collided->body && Bombuu)
	{
		std::cout << "Collision with bomb" << std::endl;

		glm::vec2 Direction = glm::vec2(Player1->transform.Position.x - Bombuu->transform.Position.x, Player1->transform.Position.y - Bombuu->transform.Position.y);
		
		Player1->ApplyKnockback((glm::vec2(Direction.x * 20, Direction.y * 20)), false);

		DestroyEntity(Bombuu);
		

		/*
		int PlayerId = Player1->GetID();
		DestroyEntity(Player1);
		Players.erase(PlayerId);
		PlayerKnockedOut(PlayerId);
		DestroyEntity(Bombuu);
		*/
	}
	else if (Player1 && Collided->body && SpeedyGun) // OR if a bullet is the first object
	{
		std::cout << "Gun Collision" << std::endl;
		Player1->EquipWeapon(SpeedyGun);
		
	}

	if (Collided->body && BigOldMetalKiller)
	{
		if (Player1 && Player1 != BigOldMetalKiller->GetCurrentPlayer())
		{
			Player1->ApplyKnockback(glm::vec2(BigOldMetalKiller->body->GetLinearVelocity().x, BigOldMetalKiller->body->GetLinearVelocity().y), true);
		}
		if (Player1 != BigOldMetalKiller->GetCurrentPlayer())
		{
			DestroyEntity(BigOldMetalKiller);
		}
		
	}
}

void Level::PlayerKnockedOut(int PlayerID)
{
	// Assign score/place
	std::shared_ptr<UIText> KnockbackText = GameManager::GetInstance()->vPlayerInfo[PlayerID].KnockbackText;
	KnockbackText->sText = "X";
	KnockbackText->Colour = { 0.9f, 0.1f, 0.1f, 1.0f };
	KnockbackText->iPSize = 80;
	KnockbackText->SetPosition(KnockbackText->GetPosition() + glm::vec2(-20, 0));
	GameManager::GetInstance()->vPlayerInfo[PlayerID].CurrentGamePlace = Players.size() + 1; 
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
	std::shared_ptr<UIImage> RoundBackImage(new UIImage(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, Camera::GetInstance()->SCR_HEIGHT / 2 - 200), Utils::CENTER, 0.0f, glm::vec4(0.3f, 0.3f, 0.3f, 0.8f), Camera::GetInstance()->SCR_WIDTH * 0.8, 180));
	std::shared_ptr<UIImage> OverallBackImage(new UIImage(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, Camera::GetInstance()->SCR_HEIGHT / 2 + 140), Utils::CENTER, 0.0f, glm::vec4(0.3f, 0.3f, 0.3f, 0.8f), Camera::GetInstance()->SCR_WIDTH * 0.8, 380));
	std::shared_ptr<UIText> RoundTitle(new UIText(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, Camera::GetInstance()->SCR_HEIGHT / 2 - 250.0f), 0, glm::vec4(0.9, 0.9, 0.9, 1.0), "Round " + std::to_string(GameManager::GetInstance()->CurrentRound), "Resources/Fonts/Roboto-Black.ttf", 80, Utils::CENTER));
	std::shared_ptr<UIText> OverallTitle(new UIText(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, Camera::GetInstance()->SCR_HEIGHT / 2), 0, glm::vec4(0.9, 0.9, 0.9, 1.0), "Overall", "Resources/Fonts/Roboto-Black.ttf", 80, Utils::CENTER));
	AddUIElement(RoundBackImage);
	AddUIElement(OverallBackImage);
	AddUIElement(RoundTitle);
	AddUIElement(OverallTitle);

	for (auto& HUDEle : IngameHUD)
	{
		HUDEle->SetActive(false);
	}

	// Have players stats, get from game manager, display each position, and each score
	for (auto& player : GameManager::GetInstance()->vPlayerInfo)
	{
		// Add player
		glm::vec4 PlayerColour = { 226.0f / 255.0f, 175.0f / 255.0f, 45.0f / 255.0f, 1.0f };//  Gold { 0.2, 0.7, 0.1, 1.0 }; // Green
		std::string PlaceMessage = "NONE";
		std::string AdditionMessage = "+0";
		switch (player.second.CurrentGamePlace)
		{
		case 1:
		{
			PlaceMessage = "1st";
			AdditionMessage = "+400";
			player.second.CurrentScore += 400;
			break;
		}
		case 2:
		{
			PlaceMessage = "2nd";
			AdditionMessage = "+300";
			player.second.CurrentScore += 300;
			PlayerColour = { 192.0f / 255.0f, 198.0f / 255.0f, 209.0f / 255.0f, 1.0f };// Silver { 0.2, 0.3, 1.0, 1.0 }; // Blue
			break;
		}
		case 3:
		{
			PlaceMessage = "3rd";
			AdditionMessage = "+200";
			player.second.CurrentScore += 200;
			PlayerColour = { 209.0f / 255.0f, 103.0f / 255.0f, 58.0f / 255.0f, 1.0f };// Bronze { 1.0, 0.7, 0.0, 1.0 }; // Yellow
			break;
		}
		case 4:
		{
			PlaceMessage = "4th";
			AdditionMessage = "+100";
			player.second.CurrentScore += 100;
			PlayerColour = { 0.6f, 0.6f, 0.6f, 1.0f };// Grey { 0.8, 0.1, 0.1, 1.0 }; // Red
			break;
		}
		default:
			PlaceMessage = "1st";
			AdditionMessage = "+400";
			player.second.CurrentScore += 400;			
			break;
		}
		std::shared_ptr<UIText> RoundPlayerPlacement(new UIText(glm::vec2(190 + 300 * player.first, Camera::GetInstance()->SCR_HEIGHT/2 - 180.0f), Utils::CENTER, PlayerColour, PlaceMessage, "Resources/Fonts/Roboto-Medium.ttf", 45, Utils::CENTER));
		AddUIElement(RoundPlayerPlacement);
		std::shared_ptr<UIText> RoundPlayerAddScore(new UIText(glm::vec2(190 + 300 * player.first, Camera::GetInstance()->SCR_HEIGHT / 2 - 130.0f), Utils::CENTER, PlayerColour, AdditionMessage, "Resources/Fonts/Roboto-Medium.ttf", 25, Utils::CENTER));
		AddUIElement(RoundPlayerAddScore);
	}

	// Overall Place and score
	for (auto& player : GameManager::GetInstance()->vPlayerInfo)
	{
		// Add player
		int Place = 1;
		for (auto& OtherPlayer : GameManager::GetInstance()->vPlayerInfo)
		{
			if (player.second.CurrentScore < OtherPlayer.second.CurrentScore && player.second.PlayerID != OtherPlayer.second.PlayerID) // If score is less than another player (and this player isin't the current)
				Place++;
		}
		player.second.FullGamePlace = Place;
		glm::vec4 PlayerColour = GetPlaceColour(Place);
		std::string PlaceMessage = "4th";
		switch (Place)
		{
		case 1:
		{
			PlaceMessage = "1st";
			break;
		}
		case 2:
		{
			PlaceMessage = "2nd";
			break;
		}
		case 3:
		{
			PlaceMessage = "3rd";
			break;
		}
		}

		std::shared_ptr<UIText> GamePlayerPlacement(new UIText(glm::vec2(190 + 300 * player.first, Camera::GetInstance()->SCR_HEIGHT / 2 + 80.0f), Utils::CENTER, PlayerColour, PlaceMessage, "Resources/Fonts/Roboto-Medium.ttf", 45, Utils::CENTER));
		AddUIElement(GamePlayerPlacement);

		std::shared_ptr<UIText> PlayerScore(new UIText(glm::vec2(190 + 300 * player.first, Camera::GetInstance()->SCR_HEIGHT / 2 + 140.0f), Utils::CENTER, PlayerColour, std::to_string(player.second.CurrentScore), "Resources/Fonts/Roboto-Medium.ttf", 35, Utils::CENTER));
		AddUIElement(PlayerScore);


		std::shared_ptr<UIImage> PlayerIcon(new UIImage(glm::vec2(190 + 300 * player.first, Camera::GetInstance()->SCR_HEIGHT / 2 + 220), Utils::CENTER, 0.0f, glm::vec4(1.0f, 1.0f, 1.0f, 0.8f), 100, 100, Menu::GetSkinPath(player.second.Skin), 1));
		AddUIElement(PlayerIcon);
	}

	std::shared_ptr<UIText> StartToContinue(new UIText(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, Camera::GetInstance()->SCR_HEIGHT / 2 + 300.0f), Utils::CENTER, { 0.9f, 0.9f, 0.9f, 1.0f }, "Press start to go to next round", "Resources/Fonts/Roboto-Regular.ttf", 30, Utils::CENTER));
	AddUIElement(StartToContinue);
	// Generate random new gamemode
	// Display next gamemode (GetGamemodeString())
		
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
		RandomSpawnBomb();
	}
		break;
	default:
		break;
	}
}

void Level::SpawnBomb()
{
	glm::vec2 RandomPos = { 0.0f, 0.0f };
	RandomPos.x = rand() % int((MaxPosition.x - MinPosition.x) * 1000);
	RandomPos.x /= 1000.0f;
	RandomPos.x += MinPosition.x;
	RandomPos.y = MaxPosition.y;

	std::shared_ptr<class Bomb> NewBombu;
	NewBombu = std::make_shared<Bomb>(Bomb(RandomPos, Utils::CENTER));
	AddEntity(NewBombu);
	NewBombu->Init(world);
}

void Level::RandomSpawnBomb()
{
	BombSpawnTime -= Time::dTimeDelta;
	if (BombSpawnTime <= 0.0f)
	{
		int RangeSize = (MaxBombSpawnTime - MinBombSpawnTime) * 1000;
		BombSpawnTime = (rand() % RangeSize) / 1000 + MinBombSpawnTime;
		SpawnBomb();
		std::cout << "New random time " << BombSpawnTime << std::endl;
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
	NewWeapon->Init(world);
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

void Level::AddBlock(glm::vec2 Pos, float Width, float Height, Utils::EANCHOR anchor, const char * ImagePath)
{
	if (anchor == Utils::CENTER_LEFT)
		Pos.x -= 0.25;
	else if (anchor == Utils::CENTER_RIGHT)
		Pos.x += 0.25;
	else if (anchor == Utils::TOP_CENTER)
		Pos.y += 0.25;
	int DrawMode = 1;
	if (Height / Width > 1)
		DrawMode = 2;
	std::shared_ptr<Entity> NewPlatform = std::make_shared<Entity>(Entity({ { Pos, 0 } ,{ 0, 0, 0 },{ 1, 1, 1 } }, anchor));
	std::shared_ptr<Plane> NewPlatformImage = std::make_shared<Plane>(Plane(Width, Height, { 0.5f, 0.7f, 0.9f, 1.0f }, "Resources/Images/Platform.png", DrawMode, false));
	NewPlatform->AddMesh(NewPlatformImage);
	AddEntity(NewPlatform, true);
	NewPlatform->SetupB2BoxBody(world, b2_staticBody, false, false);
}

void Level::AddSpike(glm::vec2 Pos)
{
	std::shared_ptr<SpikeHazard> SpikeHazzard = std::make_shared<SpikeHazard>(SpikeHazard({ {Pos, 3} ,{ 0, 0, 0 },{ 1, 1, 1 } }, Utils::CENTER));
	SpikeHazzard->Init(world);
	AddEntity(SpikeHazzard, true);
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
			GameManager::GetInstance()->CurrentRound++;
			if (GameManager::GetInstance()->CurrentRound > GameManager::GetInstance()->NumRounds)
			{
				GameManager::GetInstance()->CurrentRound = 1;
				SceneManager::GetInstance()->SwitchScene("Menu");
			}
		}
		else
		{
			TogglePause();
			// unpause
		}
	}
	else if (_ControllerInput == BOTTOM_FACE_BUTTON)
	{
		if (CurrentSelectedButton->IsActive())
		{
			CurrentSelectedButton->Pressed();
		}
	}
}

void Level::ControllerInputAxis(InputDirection NewInput)
{
	if (!CurrentSelectedButton->IsActive()) return;
	CurrentSelectedButton->HoverOverride = false;
	CurrentSelectedButton->Update();

	for (int i = 0; i < PauseElements.size(); i++)
	{
		if (PauseElements[i] == CurrentSelectedButton)
		{
			CurrentSelectedButton = nullptr;
			while (CurrentSelectedButton == nullptr)
			{
				if (NewInput == DOWN || NewInput == RIGHT)
				{
					i++;
					if (i >= PauseElements.size()) i = 0;
				}
				else
				{
					i--;
					if (i < 0) i = PauseElements.size() - 1;
				}
				std::shared_ptr<UIButton> IsButton = std::dynamic_pointer_cast<UIButton>(PauseElements[i]);
				if (IsButton)
				{
					CurrentSelectedButton = IsButton;
					CurrentSelectedButton->HoverOverride = true;
					CurrentSelectedButton->Update();
				}
			}
			break;
		}
	}
}

glm::vec4 Level::GetPlaceColour(int Place)
{
	glm::vec4 PlayerColour = { 0.6f, 0.6f, 0.6f, 1.0f };// Grey { 0.8, 0.1, 0.1, 1.0 }; // Red
	std::string PlaceMessage = "4th";
	switch (Place)
	{
	case 1:
	{
		PlaceMessage = "1st";
		PlayerColour = { 226.0f / 255.0f, 175.0f / 255.0f, 45.0f / 255.0f, 1.0f };//  Gold { 0.2, 0.7, 0.1, 1.0 }; // Green
		break;
	}
	case 2:
	{
		PlaceMessage = "2nd";
		PlayerColour = { 192.0f / 255.0f, 198.0f / 255.0f, 209.0f / 255.0f, 1.0f };// Silver { 0.2, 0.3, 1.0, 1.0 }; // Blue
		break;
	}
	case 3:
	{
		PlaceMessage = "3rd";
		PlayerColour = { 209.0f / 255.0f, 103.0f / 255.0f, 58.0f / 255.0f, 1.0f };// Bronze { 1.0, 0.7, 0.0, 1.0 }; // Yellow
		break;
	}
	}
	return PlayerColour;
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
	void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData1 && bodyUserData2)
	{
		Entity* IsEntity1 = reinterpret_cast<Entity*>(bodyUserData1);
		Entity* IsEntity2 = reinterpret_cast<Entity*>(bodyUserData2);

		if (IsEntity1 && IsEntity2 && IsEntity1->GetEntityValue() > -1 && IsEntity2->GetEntityValue() > -1)
		{
			std::shared_ptr<Weapon> SpeedyGun = std::dynamic_pointer_cast<Weapon>(IsEntity1->shared_from_this());
			std::shared_ptr<Weapon> SpeedyGun2 = std::dynamic_pointer_cast<Weapon>(IsEntity2->shared_from_this());
			if (SpeedyGun || SpeedyGun2)
			{
				contact->SetEnabled(false);
			}

			std::shared_ptr<Bullet> SpeedyBullet = std::dynamic_pointer_cast<Bullet>(IsEntity1->shared_from_this());
			std::shared_ptr<Bullet> SpeedyBullet2 = std::dynamic_pointer_cast<Bullet>(IsEntity2->shared_from_this());
			if (SpeedyBullet || SpeedyBullet)
			{
				contact->SetEnabled(false);
			}
		}
	}
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
