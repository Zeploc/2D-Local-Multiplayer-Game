#pragma once
#include "Engine\Entity.h"

class MenuPlayerController : public Entity
{
public:
	MenuPlayerController(int _ControllerID);
	~MenuPlayerController();

	virtual void Update() override;

private:
	int ControllerID = -1;

	glm::vec2 CurrentDirection = { 0, 0 };
};

