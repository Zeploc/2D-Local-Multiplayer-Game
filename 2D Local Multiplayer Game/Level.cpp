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
//#include <Box2D/Dynamics/b2World.h>

// Local Includes //
#include "Player.h"

// Library Includes //
#include <iostream>


// Prototypes
void BackToMenu();

Level::Level(std::string sSceneName) : Scene(sSceneName), world(b2Vec2(0.0f, -10.0f))
{
	std::shared_ptr<Player> PlayerEnt = std::make_shared<Player>(Player({0, -2, 0}, 0));
	AddEntity(PlayerEnt);
	PlayerEnt->SetupB2Body(world, b2_dynamicBody, false, true, 1.0f, 0.0f);
	Box2DCollisionObjects.push_back(PlayerEnt->body);
	Players.push_back(PlayerEnt);

	std::shared_ptr<Player> Player2Ent = std::make_shared<Player>(Player({ 3, 2, 0 }, 1));
	AddEntity(Player2Ent);
	Player2Ent->SetupB2Body(world, b2_dynamicBody, false, true, 1.0f, 0.0f);
	Box2DCollisionObjects.push_back(Player2Ent->body);
	Players.push_back(Player2Ent);

	std::shared_ptr<Entity> BottomPlatform = std::make_shared<Entity>(Entity({ { 0, -3.0f, 0 } ,{ 0, 0, 0 },{ 1, 1, 1 } }, Utils::CENTER));
	std::shared_ptr<Plane> NewImage = std::make_shared<Plane>(Plane(10.0f, 1.0f, { 0.3f, 0.4f, 0.9f, 1.0f }, "Resources/Images/Box.png", 1, false));
	BottomPlatform->AddMesh(NewImage);
	AddEntity(BottomPlatform);
	BottomPlatform->SetupB2Body(world, b2_staticBody, false, false);
	Box2DCollisionObjects.push_back(BottomPlatform->body);

	std::shared_ptr<Entity> MiddlePlatform = std::make_shared<Entity>(Entity({ { 0, 1.5f, 0 } ,{ 0, 0, 0 },{ 1, 1, 1 } }, Utils::CENTER));
	std::shared_ptr<Plane> MiddlePlatformImage = std::make_shared<Plane>(Plane(6.0f, 0.5f, { 0.3f, 0.4f, 0.9f, 1.0f }, "Resources/Images/Box.png", 1, false));
	MiddlePlatform->AddMesh(MiddlePlatformImage);
	AddEntity(MiddlePlatform);
	MiddlePlatform->SetupB2Body(world, b2_staticBody, false, false);
	Box2DCollisionObjects.push_back(MiddlePlatform->body);

	std::shared_ptr<Entity> LeftPlatform = std::make_shared<Entity>(Entity({ { -5.0f, -0.5f, 0 } ,{ 0, 0, 0 },{ 1, 1, 1 } }, Utils::CENTER));
	std::shared_ptr<Plane> LeftPlatformImage = std::make_shared<Plane>(Plane(3.0f, 0.5f, { 0.3f, 0.4f, 0.9f, 1.0f }, "Resources/Images/Box.png", 1, false));
	LeftPlatform->AddMesh(LeftPlatformImage);
	AddEntity(LeftPlatform);
	LeftPlatform->SetupB2Body(world, b2_staticBody, false, false);
	Box2DCollisionObjects.push_back(LeftPlatform->body);

	std::shared_ptr<Entity> RightPlatform = std::make_shared<Entity>(Entity({ { 5.0f, -0.5f, 0 } ,{ 0, 0, 0 },{ 1, 1, 1 } }, Utils::CENTER));
	std::shared_ptr<Plane> RightPlatformImage = std::make_shared<Plane>(Plane(3.0f, 0.5f, { 0.3f, 0.4f, 0.9f, 1.0f }, "Resources/Images/Box.png", 1, false));
	RightPlatform->AddMesh(RightPlatformImage);
	AddEntity(RightPlatform);
	RightPlatform->SetupB2Body(world, b2_staticBody, false, false);
	Box2DCollisionObjects.push_back(RightPlatform->body);

	std::shared_ptr<Entity> DynamicBoxEntity = std::make_shared<Entity>(Entity({ { 0, 4, 0 } ,{ 0, 0, 20 },{ 1, 1, 1 } }, Utils::CENTER));
	std::shared_ptr<Plane> TestImage = std::make_shared<Plane>(Plane(0.5f, 0.5f, { 0.9f, 0.3f, 0.1f, 1.0f }, "Resources/Images/Box.png"));
	DynamicBoxEntity->AddMesh(TestImage);
	AddEntity(DynamicBoxEntity);
	DynamicBoxEntity->SetupB2Body(world, b2_dynamicBody, true, true, 10.0f);
	Box2DCollisionObjects.push_back(DynamicBoxEntity->body);

	std::shared_ptr<Entity> DynamicBoxEntity2 = std::make_shared<Entity>(Entity({ { 4, 3, 0 } ,{ 0, 0, -10 },{ 1, 1, 1 } }, Utils::CENTER));
	DynamicBoxEntity2->AddMesh(TestImage);
	AddEntity(DynamicBoxEntity2);
	DynamicBoxEntity2->SetupB2Body(world, b2_dynamicBody, true, true, 10.0f);
	Box2DCollisionObjects.push_back(DynamicBoxEntity2->body);

	std::shared_ptr<Entity> DynamicBoxEntity3 = std::make_shared<Entity>(Entity({ { -1, -1, 0 } ,{ 0, 0, -10 },{ 1, 1, 1 } }, Utils::CENTER));
	DynamicBoxEntity3->AddMesh(TestImage);
	AddEntity(DynamicBoxEntity3);
	DynamicBoxEntity3->SetupB2Body(world, b2_dynamicBody, true, true, 10.0f);
	Box2DCollisionObjects.push_back(DynamicBoxEntity3->body);


	std::shared_ptr<UIButton> QuitBtn(new UIButton(glm::vec2(10, Camera::GetInstance()->SCR_HEIGHT - 10), Utils::BOTTOM_LEFT, 0.0f, glm::vec4(0.3f, 0.3f, 0.3f, 1.0f), glm::vec4(0.7f, 0.7f, 0.7f, 1.0f), 480, 70, BackToMenu));
	QuitBtn->AddText("Back to Menu", "Resources/Fonts/Roboto-Thin.ttf", 34, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), Utils::CENTER, { 0, 0 });
	AddUIElement(QuitBtn);

	//bIsPersistant = true;	
	world.SetGravity(b2Vec2(0.0f, -gravity));

	//// Define the ground body.
	//b2BodyDef groundBodyDef;
	//groundBodyDef.position.Set(0.0f, -3.0f);
	//NewEnt->transform.Position = glm::vec3(0.0f, -3.0f, 0.0f);

	//// Call the body factory which allocates memory for the ground body
	//// from a pool and creates the ground box shape (also from a pool).
	//// The body is also added to the world.
	//b2Body* groundBody = world.CreateBody(&groundBodyDef);
	//// Define the ground box shape.
	//b2PolygonShape groundBox;
	//// The extents are the half-widths of the box.
	//groundBox.SetAsBox(20.0f, 1.0f);
	//// Add the ground fixture to the ground body.
	//groundBody->CreateFixture(&groundBox, 0.0f);
	

	timeStep = 1.0f / 60.0f;
}


Level::~Level()
{

}

void Level::Update()
{
	Scene::Update();
		
	world.Step(1.0f / 60.0f, 6, 2);
	for (auto& CollisionObject : Box2DCollisionObjects)
	{
		b2Vec2 CubePos = CollisionObject->GetPosition();
		/*CollisionObject.EntityObject->transform.Position = glm::vec3(CubePos.x, CubePos.y, 0.0f);
		CollisionObject.EntityObject->transform.Rotation.z = (CollisionObject.body->GetAngle() / b2_pi) * 180;*/
		//printf("%4.2f %4.2f %4.2f\n", CubePos.x, CubePos.y, (CollisionObject->GetAngle() / b2_pi) * 180);
	}	
}

void Level::OnLoadScene()
{
	Scene::OnLoadScene();

}

void BackToMenu()
{
	SceneManager::GetInstance()->SwitchScene("Menu");
}
