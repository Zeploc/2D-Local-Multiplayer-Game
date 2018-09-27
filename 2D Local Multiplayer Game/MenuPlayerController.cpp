
// This Includes //
#include "MenuPlayerController.h"

// Engine Includes //
#include "Engine/Input.h"
#include "Engine/CXBOXController.h"
#include "Engine/SceneManager.h"

// Local Includes //
#include "Menu.h"


// TEMP
#include <iostream>

MenuPlayerController::MenuPlayerController(int _ControllerID)
	: Entity({ {0, 0, 0} ,{ 0, 0, 0 },{ 1, 1, 1 } }, Utils::CENTER)
{
	ControllerID = _ControllerID;
	std::cout << "constructing\n";
}


MenuPlayerController::~MenuPlayerController()
{
}

void MenuPlayerController::Update()
{
	if (ControllerID < 0) return;
	XBOXController* PlayerController = Input::GetInstance()->Players[ControllerID];
	if (PlayerController)
	{
		if (PlayerController->IsConnected())
		{
			std::shared_ptr<Menu> MenuScene = std::dynamic_pointer_cast<Menu>(SceneManager::GetInstance()->GetCurrentScene());
			if (PlayerController->ControllerButtons[BOTTOM_FACE_BUTTON] == Input::INPUT_FIRST_PRESS)
			{
				MenuScene->SelectCurrentButton();
			}

			float LThumbX = PlayerController->GetState().Gamepad.sThumbLX;			
			if (abs(LThumbX) > 10000)
			{
				if (CurrentDirection.x < 1 && LThumbX > 10000)
				{
					CurrentDirection.x = 1;
					MenuScene->ControllerInputAxis(RIGHT);
				}
				else if (CurrentDirection.x > -1 && LThumbX < -10000)
				{
					CurrentDirection.x = -1;
					MenuScene->ControllerInputAxis(LEFT);
				}
			}
			else
				CurrentDirection.x = 0;

			float LThumbY = PlayerController->GetState().Gamepad.sThumbLY;
			if (abs(LThumbY) > 10000)
			{
				if (CurrentDirection.y < 1 && LThumbY > 10000)
				{
					CurrentDirection.y = 1;
					MenuScene->ControllerInputAxis(UP);
				}
				else if (CurrentDirection.y > -1 && LThumbY < -10000)
				{
					CurrentDirection.y = -1;
					MenuScene->ControllerInputAxis(DOWN);
				}
			}
			else
				CurrentDirection.y = 0;
		}
	}
}
