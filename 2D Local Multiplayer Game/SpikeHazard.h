#pragma once
#include "Engine\Entity.h"

class SpikeHazard :
	public Entity
{

public:
	SpikeHazard(Utils::Transform _Transform, Utils::EANCHOR _Anchor);
	~SpikeHazard();

	void Init(b2World& _world);

	virtual void Update() override;
};

