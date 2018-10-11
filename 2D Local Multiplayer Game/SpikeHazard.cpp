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
	const char* Texture = "Resources/Images/Spikes.png";
	float Width = 0.5f;
	float Height = 0.5f;
	glm::vec4 UVCoords = glm::vec4{ 0, 1, 0, 1 };

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
