// This Includes //
#include "Bomb.h"

// Engine Includes //
#include "Engine\Plane.h"
#include "Engine\Time.h"
#include "Engine\Scene.h"


Bomb::Bomb(glm::vec2 Position, Utils::EANCHOR _Anchor)
	: Entity({ glm::vec3(Position, 1) ,{ 0, 0, 0 },{ 1, 1, 1 } }, _Anchor)
{
	const char* texture = "Resources/Images/Bomb.png";

	std::shared_ptr<Plane> BombImage = std::make_shared<Plane>(Plane(0.5f, 0.5f, { 1.0f, 1.0f, 1.0f, 1.0f }, texture));
	BombImage->bCullFace = false;
	AddMesh(BombImage);
}


Bomb::~Bomb()
{
	
}

bool Bomb::Explosion()
{
	return bExploded;
}

void Bomb::Update()
{
	Entity::Update();
	if (CurrentTimer > ExplosionTime)
	{
		bExploded = true;
	}
	else
	{
		CurrentTimer += Time::dTimeDelta;
	}

}

void Bomb::Init(b2World& world)
{
	SetupB2CircleBody(world, b2_dynamicBody, true, true, 10.0f);
	
}
