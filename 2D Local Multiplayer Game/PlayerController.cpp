//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name    	:    Player Controller.cpp
// Description    	:    Controller for individual player
// Author       	:    Alex Coultas
// Mail         	:    alex.cou7417@mediadesign.school.nz
//

// This Includes //
#include "PlayerController.h"

// Engine Includes //
#include "Engine/CXBOXController.h"
#include "Engine/Input.h"

// Local Includes //
#include "Level.h"


PlayerController::PlayerController(int PlayerID, std::shared_ptr<Level> LevelRef)
	: Entity({ {0, 0, 0} ,{ 0, 0, 0 },{ 1, 1, 1 } }, Utils::CENTER)
{
	ControllerID = PlayerID;
	CurrentLevel = LevelRef;
}


PlayerController::~PlayerController()
{

}

void PlayerController::Update()
{
	Entity::Update();

	if (ControllerID < 0) return;
	XBOXController* Controller = Input::GetInstance()->Players[ControllerID];
	if (Controller)
	{
		if (Controller->IsConnected())
		{
			for (int i = 0; i < 14; i++)
			{
				if (Controller->ControllerButtons[i] == Input::INPUT_FIRST_PRESS)
				{
					CurrentLevel->PControllerInput(InputController(i));
				}
			}
		}
	}
}
