#pragma once
#include "Weapon.h"
class Shotgun :
	public Weapon
{
public:
	Shotgun(glm::vec2 Position, Utils::EANCHOR _Anchor);
	~Shotgun();


	virtual void Fire() override;


	

};

