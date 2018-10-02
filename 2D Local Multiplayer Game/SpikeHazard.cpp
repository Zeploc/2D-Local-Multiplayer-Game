#include "SpikeHazard.h"


// Engine Includes //
#include "Engine/Plane.h"
#include "Engine/SceneManager.h"
#include "Engine/Scene.h"

#include <iostream>
#include "Engine\Input.h"


SpikeHazard::SpikeHazard(Utils::Transform _Transform, Utils::EANCHOR _Anchor)
	: Entity(_Transform,_Anchor)
{
	const char* Texture = "Resources/Images/Block.png";
	float Width = 1.0f;
	float Height = 1.0f;
	glm::vec4 UVCoords = glm::vec4{ 1,1,1,1 };

	std::shared_ptr<Plane> SpikePlane = std::make_shared<Plane>(Plane(Width, Height, { 1.0f, 1.0f, 1.0f, 1.0f }, Texture, UVCoords));
	AddMesh(SpikePlane);
}

SpikeHazard::~SpikeHazard()
{
}

void SpikeHazard::Init(b2World & _world)
{
	SetupB2BoxBody(_world, b2_staticBody, false);
}

void SpikeHazard::Update()
{
	Entity::Update();
}
