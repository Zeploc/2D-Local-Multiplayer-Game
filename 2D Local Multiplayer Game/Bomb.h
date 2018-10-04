#pragma once

#include "Engine\Entity.h"

class Bomb : public Entity
{
public:
	Bomb(glm::vec2 Position, Utils::EANCHOR _Anchor);
	~Bomb();

	virtual void Update() override;
	void Init(b2World& world);
	bool Explosion();

private:

	bool bExploded = false;

	float ExplosionTime = 3.0f;
	float CurrentTimer = 0.0f;

	std::shared_ptr<Entity> BombEntity;
};
