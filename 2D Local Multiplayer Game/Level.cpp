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
	std::shared_ptr<Player> PlayerEnt = std::make_shared<Player>(Player({0, 0, 0}, 0));
	AddEntity(PlayerEnt);

	std::shared_ptr<Player> Player2Ent = std::make_shared<Player>(Player({ 3, 2, 0 }, 1));
	AddEntity(Player2Ent);

	std::shared_ptr<Entity> NewEnt = std::make_shared<Entity>(Entity({ { 0, -1, 0 } ,{ 0, 0, 0 },{ 1, 1, 1 } }, Utils::CENTER));
	std::shared_ptr<Plane> NewImage = std::make_shared<Plane>(Plane(10.0f, 2.0f, { 0.3f, 0.4f, 0.9f, 1.0f }, "Resources/Images/Box.png"));
	NewEnt->AddMesh(NewImage);
	AddEntity(NewEnt);

	TestEntity = std::make_shared<Entity>(Entity({ { 2, -2, 0 } ,{ 0, 0, 0 },{ 1, 1, 1 } }, Utils::CENTER));
	std::shared_ptr<Plane> TestImage = std::make_shared<Plane>(Plane(2.0f, 2.0f, { 0.9f, 0.3f, 0.1f, 1.0f }, "Resources/Images/Box.png"));
	TestEntity->AddMesh(TestImage);
	AddEntity(TestEntity);

	std::shared_ptr<UIButton> QuitBtn(new UIButton(glm::vec2(10, Camera::GetInstance()->SCR_HEIGHT - 10), Utils::BOTTOM_LEFT, 0.0f, glm::vec4(0.3f, 0.3f, 0.3f, 1.0f), glm::vec4(0.7f, 0.7f, 0.7f, 1.0f), 480, 70, BackToMenu));
	QuitBtn->AddText("Back to Menu", "Resources/Fonts/Roboto-Thin.ttf", 34, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), Utils::CENTER, { 0, 0 });
	AddUIElement(QuitBtn);

	//bIsPersistant = true;	

	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -1.0f);
	NewEnt->transform.Position = glm::vec3(0.0f, -1.0f, 0.0f);

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = world.CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2PolygonShape groundBox;

	// The extents are the half-widths of the box.
	groundBox.SetAsBox(20.0f, 1.0f);


	// Add the ground fixture to the ground body.
	groundBody->CreateFixture(&groundBox, 0.0f);

	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 4.0f);
	body = world.CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;

	// Override the default friction.
	fixtureDef.friction = 0.3f;

	// Add the shape to the body.
	body->CreateFixture(&fixtureDef);

	timeStep = 1.0f / 60.0f;
}


Level::~Level()
{

}

void Level::Update()
{
	Scene::Update();
		
	world.Step(1.0f / 60.0f, 6, 2);
	b2Vec2 CubePos = body->GetPosition();
	TestEntity->transform.Position = glm::vec3(CubePos.x, CubePos.y, 0.0f);
	printf("%4.2f %4.2f %4.2f\n", CubePos.x, CubePos.y, body->GetAngle());
	//LogManager::GetInstance()->DisplayLogMessage("Cube Position " + std::to_string(CubePos.x) + ", " + std::to_string(CubePos.x) + " with rotation " + std::to_string(body->GetAngle()));

}

void Level::OnLoadScene()
{
	Scene::OnLoadScene();

}

void BackToMenu()
{
	SceneManager::GetInstance()->SwitchScene("Menu");
}
