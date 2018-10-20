// This Includes //
#include "Bomb.h"

// Engine Includes //
#include "Engine\Plane.h"
#include "Engine\Time.h"
#include "Engine\Scene.h"

// Local Includes //
#include "LevelManager.h"
#include "Level.h"
#include "Player.h"


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
		std::shared_ptr<Level> CurrentLevel = LevelManager::GetInstance()->GetCurrentActiveLevel();
		if (CurrentLevel) // If gets valid level
		{
			for (auto& player : CurrentLevel->Players) // Check through each player
			{
				glm::vec3 DirectionToPlayer = player.second->transform.Position - transform.Position;
				if (glm::length(DirectionToPlayer) < BombRange) // check if they are in range
				{
					player.second->ApplyKnockback(DirectionToPlayer); // Apply knockback to the player away
				}
			}
			CurrentLevel->DestroyEntity(this->shared_from_this());
		}
	}
	else
	{
		CurrentTimer += Time::dTimeDelta;
		if (CurrentTimer > ExplosionTime - ExplodeWarning && !bExplodeWarning)
		{
			bExplodeWarning = true;
			EntityMesh->Colour = { 1.0f, 0.3f, 0.3f, 1.0f };
			EntityMesh->Rebind();
		}
	}

}

void Bomb::Init(b2World& world)
{
	SetupB2CircleBody(world, b2_dynamicBody, true, true, 10.0f);
	
}
