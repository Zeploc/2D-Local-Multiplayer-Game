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

// Library Includes //
#include <iostream>


// Prototypes
void BackToMenu();

Level::Level(std::string sSceneName) : Scene(sSceneName), world(b2Vec2(0.0f, -10.0f))
{
	// Not collide with bodys with a group index 0f -1
	b2Filter NoPlayerCollisionFilter;
	NoPlayerCollisionFilter.groupIndex = 0;
	
	std::shared_ptr<Entity> BottomPlatform = std::make_shared<Entity>(Entity({ { 0, -3.0f, 0 } ,{ 0, 0, 0 },{ 1, 1, 1 } }, Utils::CENTER));
	std::shared_ptr<Plane> NewImage = std::make_shared<Plane>(Plane(10.0f, 1.0f, { 0.3f, 0.4f, 0.9f, 1.0f }, "Resources/Images/Box.png", 1, false));
	BottomPlatform->AddMesh(NewImage);
	AddEntity(BottomPlatform);
	BottomPlatform->SetupB2BoxBody(world, b2_staticBody, false, false);
	Box2DCollisionObjects.push_back(BottomPlatform->body);

	std::shared_ptr<Entity> MiddlePlatform = std::make_shared<Entity>(Entity({ { 0, 1.0f, 0 } ,{ 0, 0, 0 },{ 1, 1, 1 } }, Utils::CENTER));
	std::shared_ptr<Plane> MiddlePlatformImage = std::make_shared<Plane>(Plane(6.0f, 0.5f, { 0.3f, 0.4f, 0.9f, 1.0f }, "Resources/Images/Box.png", 1, false));
	MiddlePlatform->AddMesh(MiddlePlatformImage);
	AddEntity(MiddlePlatform);
	MiddlePlatform->SetupB2BoxBody(world, b2_staticBody, false, false);
	Box2DCollisionObjects.push_back(MiddlePlatform->body);

	std::shared_ptr<Entity> LeftPlatform = std::make_shared<Entity>(Entity({ { -5.0f, -1.0f, 0 } ,{ 0, 0, 0 },{ 1, 1, 1 } }, Utils::CENTER));
	std::shared_ptr<Plane> LeftPlatformImage = std::make_shared<Plane>(Plane(3.0f, 0.5f, { 0.3f, 0.4f, 0.9f, 1.0f }, "Resources/Images/Box.png", 1, false));
	LeftPlatform->AddMesh(LeftPlatformImage);
	AddEntity(LeftPlatform);
	LeftPlatform->SetupB2BoxBody(world, b2_staticBody, false, false);
	Box2DCollisionObjects.push_back(LeftPlatform->body);

	std::shared_ptr<Entity> RightPlatform = std::make_shared<Entity>(Entity({ { 5.0f, -1.0f, 0 } ,{ 0, 0, 45 },{ 1, 1, 1 } }, Utils::CENTER));
	std::shared_ptr<Plane> RightPlatformImage = std::make_shared<Plane>(Plane(3.0f, 0.5f, { 0.3f, 0.4f, 0.9f, 1.0f }, "Resources/Images/Box.png", 1, false));
	RightPlatform->AddMesh(RightPlatformImage);
	AddEntity(RightPlatform);
	RightPlatform->SetupB2BoxBody(world, b2_staticBody, false, false);
	Box2DCollisionObjects.push_back(RightPlatform->body);

	CircleEntity = std::make_shared<Entity>(Entity({ { 5.0f, 2.0f, 0 } ,{ 0, 0, 45 },{ 1, 1, 1 } }, Utils::CENTER));
	std::shared_ptr<Plane> CircleImage = std::make_shared<Plane>(Plane(0.5f, 0.5f, { 0.3f, 0.4f, 0.9f, 1.0f }, "Resources/Images/Box.png"));
	CircleEntity->AddMesh(CircleImage);
	AddEntity(CircleEntity);
	CircleEntity->SetupB2CircleBody(world, b2_dynamicBody, true, true, 10.0f);
	Box2DCollisionObjects.push_back(CircleEntity->body);

	std::shared_ptr<Entity> DynamicBoxEntity = std::make_shared<Entity>(Entity({ { 0, 4, 0 } ,{ 0, 0, 20 },{ 1, 1, 1 } }, Utils::CENTER));
	std::shared_ptr<Plane> TestImage = std::make_shared<Plane>(Plane(0.5f, 0.5f, { 0.9f, 0.3f, 0.1f, 1.0f }, "Resources/Images/Box.png"));
	DynamicBoxEntity->AddMesh(TestImage);
	AddEntity(DynamicBoxEntity);
	DynamicBoxEntity->SetupB2BoxBody(world, b2_dynamicBody, true, true, 10.0f);
	Box2DCollisionObjects.push_back(DynamicBoxEntity->body);

	std::shared_ptr<Entity> DynamicBoxEntity2 = std::make_shared<Entity>(Entity({ { 4, 3, 0 } ,{ 0, 0, -10 },{ 1, 1, 1 } }, Utils::CENTER));
	DynamicBoxEntity2->AddMesh(TestImage);
	AddEntity(DynamicBoxEntity2);
	DynamicBoxEntity2->SetupB2BoxBody(world, b2_dynamicBody, true, true, 10.0f);
	Box2DCollisionObjects.push_back(DynamicBoxEntity2->body);

	std::shared_ptr<Entity> DynamicBoxEntity3 = std::make_shared<Entity>(Entity({ { -1, -1, 0 } ,{ 0, 0, -10 },{ 1, 1, 1 } }, Utils::CENTER));
	DynamicBoxEntity3->AddMesh(TestImage);
	AddEntity(DynamicBoxEntity3);
	DynamicBoxEntity3->SetupB2BoxBody(world, b2_dynamicBody, true, true, 10.0f);
	Box2DCollisionObjects.push_back(DynamicBoxEntity3->body);


	std::shared_ptr<Player> PlayerEnt = std::make_shared<Player>(Player({ 0, -2, 0 }, 0));
	AddEntity(PlayerEnt);
	PlayerEnt->SetupB2BoxBody(world, b2_dynamicBody, false, true, 5.0f, 0.0f);
	Box2DCollisionObjects.push_back(PlayerEnt->body);
	Players.push_back(PlayerEnt);
	PlayerEnt->body->GetFixtureList()->SetFilterData(NoPlayerCollisionFilter);

	std::shared_ptr<Player> Player2Ent = std::make_shared<Player>(Player({ 4, 2, 0 }, 1));
	AddEntity(Player2Ent);
	Player2Ent->SetupB2BoxBody(world, b2_dynamicBody, false, true, 5.0f, 0.0f);
	Box2DCollisionObjects.push_back(Player2Ent->body);
	Players.push_back(Player2Ent);
	Player2Ent->body->GetFixtureList()->SetFilterData(NoPlayerCollisionFilter);

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
	//KnockbackPercentage1->DrawUIElement();
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
	Scene::Update();
	
	world.Step(Time::dTimeDelta, 6, 2);

	float RangeOutsideClosetView = 0.0f;

	auto Endit = Players.end();

	if (Input::GetInstance()->KeyState[(unsigned char)'l'] == Input::INPUT_FIRST_PRESS)
	{
		CircleEntity->body->SetAngularVelocity(20);
	}

	for (auto it = Players.begin(); it != Endit;)
	{
		if ((*it)->transform.Position.x < -CameraCloseRange || (*it)->transform.Position.x > CameraCloseRange)
		{
			float PDist = abs((*it)->transform.Position.x) - CameraCloseRange;
			if (PDist > RangeOutsideClosetView) RangeOutsideClosetView = PDist;
		}
		// Check if they've fallen out
		if ((*it)->transform.Position.y < PlayerFalloutYPosition)
		{
			DestroyEntity(*it);
			it = Players.erase(it);
			Endit = Players.end();
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
			Player2->ApplyKnockback(glm::vec2(Player1->body->GetLinearVelocity().x, Player1->body->GetLinearVelocity().y));
		}
		else if(Player2->GetIsRolling() == true)
		{
			Player1->ApplyKnockback((glm::vec2(Player2->body->GetLinearVelocity().x, Player2->body->GetLinearVelocity().y)));
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
