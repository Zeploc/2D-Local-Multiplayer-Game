#pragma once
#include "Engine\Entity.h"
class PlayerController : public Entity
{
public:
	PlayerController(int PlayerID);
	~PlayerController();

	virtual void Update() override;

private:
	int m_iPlayerID = -1;
};

