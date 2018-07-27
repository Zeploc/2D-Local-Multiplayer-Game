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

// Local Includes //
#include "Player.h"

// Library Includes //
#include <iostream>

// Prototypes
void BackToMenu();

Level::Level(std::string sSceneName) : Scene(sSceneName)
{
	std::shared_ptr<Player> PlayerEnt = std::make_shared<Player>(Player({0, 0, 0}, 0));
	AddEntity(PlayerEnt);

	std::shared_ptr<Player> Player2Ent = std::make_shared<Player>(Player({ 3, 2, 0 }, 1));
	AddEntity(Player2Ent);

	std::shared_ptr<Entity> NewEnt = std::make_shared<Entity>(Entity({ { -2, 2, 0 } ,{ 0, 0, 0 },{ 1, 1, 1 } }, Utils::CENTER));
	std::shared_ptr<Plane> NewImage = std::make_shared<Plane>(Plane(0.5f, 0.5f, { 0.3f, 0.4f, 0.9f, 1.0f }, "Resources/Images/Box.png"));
	NewEnt->AddMesh(NewImage);
	AddEntity(NewEnt);

	TestEntity = std::make_shared<Entity>(Entity({ { 2, -2, 0 } ,{ 0, 0, 0 },{ 1, 1, 1 } }, Utils::CENTER));
	std::shared_ptr<Plane> TestImage = std::make_shared<Plane>(Plane(0.5f, 0.5f, { 0.9f, 0.3f, 0.1f, 1.0f }, "Resources/Images/Box.png"));
	TestEntity->AddMesh(TestImage);
	AddEntity(TestEntity);

	std::shared_ptr<UIButton> QuitBtn(new UIButton(glm::vec2(10, Camera::GetInstance()->SCR_HEIGHT - 10), Utils::BOTTOM_LEFT, 0.0f, glm::vec4(0.3f, 0.3f, 0.3f, 1.0f), glm::vec4(0.7f, 0.7f, 0.7f, 1.0f), 480, 70, BackToMenu));
	QuitBtn->AddText("Back to Menu", "Resources/Fonts/Roboto-Thin.ttf", 34, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), Utils::CENTER, { 0, 0 });
	AddUIElement(QuitBtn);

	//bIsPersistant = true;
	std::shared_ptr<Entity> CubeCollision = std::make_shared<Entity>(Entity(Utils::Transform{ { 0.0f, 0.0f, 0.0f },{ 30, 45, 0 },{ 1, 1, 1 } }, Utils::BOTTOM_CENTER));
	std::shared_ptr<Cube> CubeCollisionMesh = std::make_shared<Cube>(Cube(2.0f, 2.0f, 2.0f, { 0.1, 0.3, 0.7, 1.0f }, "Resources/Images/Box.png"));
	CubeCollision->AddMesh(CubeCollisionMesh);
	CubeCollisionMesh->AddCollisionBounds(2.0f, 2.0f, 2.0f, CubeCollision);
	CubeCollisionMesh->SetLit(true);
	CubeCollisionMesh->SetReflection(true);
	AddEntity(CubeCollision);

	SphereRaycastTest = std::make_shared<Entity>(Entity(Utils::Transform{ { 4.0f, 2.0f, -1.0f },{ 0, 0, 0 },{ 1, 1, 1 } }, Utils::CENTER));
	std::shared_ptr<Sphere> SphereMesh = std::make_shared<Sphere>(Sphere(1.0f, 1.0f, 1.0f, { 0.1f, 0.8f, 0.3f, 1.0f }));
	SphereRaycastTest->AddMesh(SphereMesh);
	SphereMesh->SetLit(true);
	SphereMesh->SetReflection(true);
	AddEntity(SphereRaycastTest);

	LocationBox = std::make_shared<Entity>(Entity(Utils::Transform{ { 0.0f, 0.0f, 0.0f },{ 0, 0, 0 },{ 1, 1, 1 } }, Utils::BOTTOM_CENTER));
	std::shared_ptr<Cube> BoxMesh = std::make_shared<Cube>(Cube(0.4f, 0.4f, 0.4f, { 0.9, 0.1, 0.1, 1.0f }));
	LocationBox->AddMesh(BoxMesh);
	AddEntity(LocationBox);
}


Level::~Level()
{

}

void Level::Update()
{
	Scene::Update();

	if (Input::GetInstance()->KeyState[13] == Input::INPUT_FIRST_PRESS)
	{
		Input::GetInstance()->ToggleCursorVisible();
		Camera::GetInstance()->ToggleSpectatorControls();
	}

	if (Input::GetInstance()->MouseState[Input::MOUSE_LEFT] == Input::INPUT_FIRST_PRESS || Input::GetInstance()->MouseState[Input::MOUSE_LEFT] == Input::INPUT_HOLD)
	{
		glm::vec3 v = SphereRaycastTest->transform.Position - Camera::GetInstance()->GetCameraPosition();

		glm::vec3 rayDirection = Camera::GetInstance()->ScreenToWorldDirection(Input::GetInstance()->MousePos);

		float a = glm::dot(rayDirection, rayDirection);
		float b = 2.0f * glm::dot(v, rayDirection);
		float c = glm::dot(v, v) - SphereRaycastTest->EntityMesh->m_fWidth * SphereRaycastTest->EntityMesh->m_fWidth;
		float d = b * b - 4 * a * c;

		if (d > 0)
		{
			float x1 = (-b - sqrt(d)) / 2;
			float x2 = (-b + sqrt(d)) / 2;

			float XPos = Camera::GetInstance()->GetCameraPosition().x + rayDirection.x * -x2;
			float YPos = Camera::GetInstance()->GetCameraPosition().y + rayDirection.y * -x2;
			float ZPos = Camera::GetInstance()->GetCameraPosition().z + rayDirection.z * -x2;
			LocationBox->transform.Position = { XPos, YPos, ZPos };

			std::cout << "Position hit [" << XPos << ", " << YPos << ", " << ZPos << "]" << std::endl;
			if (x1 >= 0 && x2 >= 0)
			{
				std::cout << "Ray cast hit!\n";
			}
			else if ((x1 < 0 && x2 >= 0))
			{
				std::cout << "Ray cast hit from inside!\n";
			}
			else if (abs(x1 - x2) <= 0.3f)
			{
				std::cout << "Ray cast hitting edge!!\n";
			}
			else
			{
				std::cout << "Ray cast hit!\n";
			}
		}
		else if (d <= 0)
		{
			std::cout << "Ray cast missed!\n";
		}
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
