//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name    	:    Menu.cpp
// Description    	:    main implementation for Menu
// Author       	:    Alex Coultas
// Mail         	:    alex.cou7417@mediadesign.school.nz
//


// This Includes //
#include "Menu.h"

// Engine Includes //
#include "Engine\UIButton.h"
#include "Engine/SceneManager.h"
#include "Engine/CXBOXController.h"
#include "Engine/Time.h"
#include "Engine/SoundManager.h"

// Local Includes //
#include "LevelManager.h"
#include "MenuPlayerController.h"
#include "GameManager.h"
#include "Level.h"

// TEMP
#include <iostream>

// Prototpyes //
void SelectPlayersBtn();
void ControlsScreenBtn();
void CreditsScreenBtn();
void ExitGameBtn();

Menu::Menu() : Scene("Menu")
{
	SoundManager::GetInstance()->AddAudio("Resources/Sounds/MainMusic.mp3", false, "MainTrack");
	SoundManager::GetInstance()->SetChannelVolume("MainTrack", 0.15);

	// Menu Elements
	std::shared_ptr<UIText> Title(new UIText(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, 100.0f), 0, glm::vec4(0.9, 0.9, 0.9, 1.0), "Local Multiplayer Game", "Resources/Fonts/Roboto-Black.ttf", 100, Utils::CENTER));
	std::shared_ptr<UIButton> StartBtn(new UIButton(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, Camera::GetInstance()->SCR_HEIGHT / 2), Utils::CENTER, 0.0f, glm::vec4(0.3f, 0.3f, 0.3f, 1.0f), glm::vec4(0.7f, 0.7f, 0.7f, 1.0f), 480, 70, SelectPlayersBtn));
	StartBtn->AddText("START GAME", "Resources/Fonts/Roboto-Thin.ttf", 34, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), Utils::CENTER, { 0, 0 });
	std::shared_ptr<UIButton> ControlsBtn(new UIButton(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, Camera::GetInstance()->SCR_HEIGHT / 2 + 80), Utils::CENTER, 0.0f, glm::vec4(0.3f, 0.3f, 0.3f, 1.0f), glm::vec4(0.7f, 0.7f, 0.7f, 1.0f), 480, 70, ControlsScreenBtn));
	ControlsBtn->AddText("CONTROLS", "Resources/Fonts/Roboto-Thin.ttf", 34, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), Utils::CENTER, { 0, 0 });
	std::shared_ptr<UIButton> CreditsBtn(new UIButton(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, Camera::GetInstance()->SCR_HEIGHT / 2 + 160), Utils::CENTER, 0.0f, glm::vec4(0.3f, 0.3f, 0.3f, 1.0f), glm::vec4(0.7f, 0.7f, 0.7f, 1.0f), 480, 70, CreditsScreenBtn));
	CreditsBtn->AddText("CREDITS", "Resources/Fonts/Roboto-Thin.ttf", 34, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), Utils::CENTER, { 0, 0 });
	std::shared_ptr<UIButton> QuitBtn(new UIButton(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, Camera::GetInstance()->SCR_HEIGHT / 2 + 240), Utils::CENTER, 0.0f, glm::vec4(0.3f, 0.3f, 0.3f, 1.0f), glm::vec4(0.7f, 0.7f, 0.7f, 1.0f), 480, 70, ExitGameBtn));
	QuitBtn->AddText("QUIT GAME", "Resources/Fonts/Roboto-Thin.ttf", 34, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), Utils::CENTER, { 0, 0 });
	std::shared_ptr<UIImage> BackImage(new UIImage(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, Camera::GetInstance()->SCR_HEIGHT / 2), Utils::CENTER, 0.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), Camera::GetInstance()->SCR_WIDTH, Camera::GetInstance()->SCR_HEIGHT, "Resources/Images/Block.png", 2));
	std::shared_ptr<UIImage> UIIMG(new UIImage(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, 100.0f), Utils::CENTER, 0.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 600, 100, "Resources/Box.png", 2));
	
	AddUIElement(BackImage);
	AddUITextElement(Title);
	AddUIElement(StartBtn);
	AddUIElement(ControlsBtn);
	AddUIElement(CreditsBtn);
	AddUIElement(QuitBtn);

	MenuElements.push_back(Title);
	MenuElements.push_back(StartBtn);
	MenuElements.push_back(ControlsBtn);
	MenuElements.push_back(CreditsBtn);
	MenuElements.push_back(QuitBtn);

	StartBtn->SetPressSound("Resources/Sounds/menu-click.wav");
	ControlsBtn->SetPressSound("Resources/Sounds/menu-click.wav");
	CreditsBtn->SetPressSound("Resources/Sounds/menu-click.wav");
	QuitBtn->SetPressSound("Resources/Sounds/menu-click.wav");
	SoundManager::GetInstance()->SetChannelVolume("UIC", 0.1);

	CurrentSelectedButton = StartBtn;
	CurrentSelectedButton->HoverOverride = true;

	// Player Select Elements
	std::shared_ptr<UIText> PlayerTitle(new UIText(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, 100.0f), 0, glm::vec4(0.9, 0.9, 0.9, 1.0), "Player Select", "Resources/Fonts/Roboto-Black.ttf", 80, Utils::CENTER));
	StartTimerText = std::make_shared<UIText>(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, Camera::GetInstance()->SCR_HEIGHT - 100.0f), 0, glm::vec4(0.9, 0.9, 0.9, 1.0), "Starting in 3...", "Resources/Fonts/Roboto-Regular.ttf", 40, Utils::CENTER);
	StartTimerText->SetActive(false);

	for (int i = 0; i < 4; i++)
	{
		PlayerStatus NewPlayerStatus;
		float XPos = Camera::GetInstance()->SCR_WIDTH / 2 - 450 + 300 * i;
		std::shared_ptr<UIText> PlayerLabel(new UIText(glm::vec2(XPos, Camera::GetInstance()->SCR_HEIGHT / 2 - 150), 0, glm::vec4(0.9, 0.9, 0.9, 1.0), "Player " + std::to_string(i + 1), "Resources/Fonts/Roboto-Regular.ttf", 25, Utils::CENTER));
		AddUIElement(PlayerLabel);
		PlayerSelectElements.push_back(PlayerLabel);
		std::shared_ptr<UIText> PlayerJoin(new UIText(glm::vec2(XPos, Camera::GetInstance()->SCR_HEIGHT / 2 - 100), 0, glm::vec4(0.9, 0.9, 0.9, 1.0), "Press Start to join", "Resources/Fonts/Roboto-Thin.ttf", 25, Utils::CENTER));
		AddUIElement(PlayerJoin);
		PlayerSelectElements.push_back(PlayerJoin);
		std::shared_ptr<UIText> PlayerReady(new UIText(glm::vec2(XPos, Camera::GetInstance()->SCR_HEIGHT / 2 + 200), 0, glm::vec4(0.9, 0.9, 0.9, 1.0), "Ready", "Resources/Fonts/Roboto-Bold.ttf", 25, Utils::CENTER));
		AddUIElement(PlayerReady);
		PlayerSelectElements.push_back(PlayerReady);
		std::shared_ptr<UIImage> PlayerImage(new UIImage(glm::vec2(XPos, Camera::GetInstance()->SCR_HEIGHT / 2 + 50), Utils::CENTER, 0, { 1.0f, 1.0f, 1.0f, 1.0f }, 200, 200, "Resources/Images/office-square.png", 1));
		AddUIElement(PlayerImage);
		PlayerSelectElements.push_back(PlayerImage);
		PlayerReady->SetActive(false);

		NewPlayerStatus.PlayerJoinedText = PlayerJoin;
		NewPlayerStatus.PlayerReadyText = PlayerReady;
		NewPlayerStatus.PlayerImage = PlayerImage;
		NewPlayerStatus.CurrentSkin = OfficeSquare;
		vPlayerStatus.push_back(NewPlayerStatus);
	}

	AddUIElement(PlayerTitle);
	AddUIElement(StartTimerText);
	PlayerSelectElements.push_back(StartTimerText);
	PlayerSelectElements.push_back(PlayerTitle);

	// Controls Elements
	std::shared_ptr<UIText> ControlsTitle(new UIText(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, 100.0f), 0, glm::vec4(0.9, 0.9, 0.9, 1.0), "Controls", "Resources/Fonts/Roboto-Black.ttf", 80, Utils::CENTER));
	std::shared_ptr<UIImage> ControlsImage(new UIImage(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, Camera::GetInstance()->SCR_HEIGHT / 2), Utils::CENTER, 0.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), Camera::GetInstance()->SCR_WIDTH * 0.6, Camera::GetInstance()->SCR_HEIGHT * 0.7, "Resources/Images/Controls.png", 2));
	std::shared_ptr<UIText> BToBack(new UIText(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, Camera::GetInstance()->SCR_HEIGHT - 100.0f), 0, glm::vec4(0.7, 0.7, 0.7, 1.0), "B to go back", "Resources/Fonts/Roboto-Regular.ttf", 40, Utils::CENTER));

	AddUIElement(ControlsTitle);
	AddUIElement(ControlsImage);
	AddUIElement(BToBack);
	ControlsElements.push_back(ControlsTitle);
	ControlsElements.push_back(ControlsImage);
	ControlsElements.push_back(BToBack);

	// Credits Elements
	std::shared_ptr<UIText> CreditsTitle(new UIText(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, 100.0f), 0, glm::vec4(0.9, 0.9, 0.9, 1.0), "Credits", "Resources/Fonts/Roboto-Black.ttf", 80, Utils::CENTER));
	std::shared_ptr<UIImage> CreditsImage(new UIImage(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, Camera::GetInstance()->SCR_HEIGHT / 2), Utils::CENTER, 0.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), Camera::GetInstance()->SCR_WIDTH * 0.7, Camera::GetInstance()->SCR_HEIGHT * 0.7, "Resources/Images/Credits.png", 2));

	AddUIElement(CreditsTitle);
	AddUIElement(CreditsImage);
	CreditsElements.push_back(CreditsImage);
	CreditsElements.push_back(CreditsTitle);
	CreditsElements.push_back(BToBack);

	std::shared_ptr<UIText> BToBackPlayerSelect(new UIText(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, Camera::GetInstance()->SCR_HEIGHT - 50.0f), 0, glm::vec4(0.7, 0.7, 0.7, 1.0), "B to go back", "Resources/Fonts/Roboto-Regular.ttf", 40, Utils::CENTER));
	AddUIElement(BToBackPlayerSelect);

	PlayerSelectElements.push_back(BToBackPlayerSelect);

	// Adding Menu Controllers
	for (int i = 0; i < 4; i++)
	{
		std::shared_ptr<MenuPlayerController> NewMenuPlayer = std::make_shared<MenuPlayerController>(i);
		AddEntity(NewMenuPlayer, true);
	}

	UsedSkins.insert(std::pair<PlayerSkin, bool>(OfficeSquare, false));
	UsedSkins.insert(std::pair<PlayerSkin, bool>(SmexyHexy, false));
	UsedSkins.insert(std::pair<PlayerSkin, bool>(GuyAngle, false));
	UsedSkins.insert(std::pair<PlayerSkin, bool>(Rhombage, false));
}

Menu::~Menu()
{

}

void Menu::Update()
{
	Scene::Update();

	if (StartTimerText->IsActive())
	{
		StartTime -= Time::dTimeDelta;
		StartTimerText->sText = "Starting in " + std::to_string((int)ceil(StartTime)) + "...";
		if (StartTime <= 0)
		{
			StartGame();
		}
	}
}

void Menu::OnLoadScene()
{
	Scene::OnLoadScene();

	// Setting Screen
	SwitchScreens(Menu::MENU);
}

void Menu::PlayerControllerInput(int ID, InputController Input)
{
	if (PlayerSelectElements[0]->IsActive())
	{
		if (Input == SPECIAL_BUTTON_RIGHT || (Input == BOTTOM_FACE_BUTTON && !vPlayerStatus[ID].IsPlaying) || (Input == RIGHT_FACE_BUTTON && !vPlayerStatus[ID].IsReady))
		{
			if (Input != RIGHT_FACE_BUTTON) vPlayerStatus[ID].IsPlaying = !vPlayerStatus[ID].IsPlaying;
			else vPlayerStatus[ID].IsPlaying = false;
			if (vPlayerStatus[ID].IsPlaying)
			{
				vPlayerStatus[ID].PlayerJoinedText->sText = "Joined";
				vPlayerStatus[ID].PlayerImage->SetActive(true);
			}
			else
			{
				vPlayerStatus[ID].PlayerJoinedText->sText = "Press Start to join";
				vPlayerStatus[ID].PlayerReadyText->SetActive(false);
				vPlayerStatus[ID].PlayerImage->SetActive(false);
				vPlayerStatus[ID].IsReady = false;
			}
		}
		else if (Input == BOTTOM_FACE_BUTTON || Input == RIGHT_FACE_BUTTON)
		{
			// Check if the player is trrying to ready up or unready
			bool AttemptReadyUp = true;
			if (Input == RIGHT_FACE_BUTTON || vPlayerStatus[ID].IsReady)
				AttemptReadyUp = false;

			// Check if they are tryng to ready up on an invalid skin
			if (AttemptReadyUp && UsedSkins[vPlayerStatus[ID].CurrentSkin] == true)
			{
				return;
			}

			if (AttemptReadyUp)
			{
				vPlayerStatus[ID].IsReady = true;
				vPlayerStatus[ID].PlayerReadyText->SetActive(true);
				UsedSkins[vPlayerStatus[ID].CurrentSkin] = true;
			}
			else
			{
				vPlayerStatus[ID].IsReady = false;
				vPlayerStatus[ID].PlayerReadyText->SetActive(false);
				UsedSkins[vPlayerStatus[ID].CurrentSkin] = false;
				/// Set any of the images with this skin back
			}

			for (int pId = 0; pId < vPlayerStatus.size(); pId++)
			{
				if (pId == ID) continue; // Dont check same player
				if (vPlayerStatus[pId].CurrentSkin == vPlayerStatus[ID].CurrentSkin && vPlayerStatus[pId].IsPlaying)
				{
					float Alpha = 1.0f;

					if (UsedSkins[vPlayerStatus[pId].CurrentSkin])
						Alpha = 0.3f;

					glm::vec2 Pos = vPlayerStatus[pId].PlayerImage->GetPosition();
					const char* NewImage = GetSkinPath(vPlayerStatus[pId].CurrentSkin);

					DestroyUIElement(vPlayerStatus[pId].PlayerImage);
					vPlayerStatus[pId].PlayerImage = std::make_shared<UIImage>(UIImage(Pos, Utils::CENTER, 0, { 1.0f, 1.0f, 1.0f, Alpha }, 200, 200, NewImage, 2));
					AddUIElement(vPlayerStatus[pId].PlayerImage);
					PlayerSelectElements.push_back(vPlayerStatus[pId].PlayerImage);
				}
			}
			CheckPlayersToStartTimer();

			/*if (Input != RIGHT_FACE_BUTTON) vPlayerStatus[ID].IsReady = !vPlayerStatus[ID].IsReady;
			else vPlayerStatus[ID].IsReady = false;
			if (vPlayerStatus[ID].IsReady)
			{
				UsedSkins[vPlayerStatus[ID].CurrentSkin] = true;
			}
			else
			{
				UsedSkins[vPlayerStatus[ID].CurrentSkin] = false;
			}*/
		}
		else if ((Input == LEFT_BUTTON || Input == RIGHT_BUTTON) && vPlayerStatus[ID].IsPlaying && !vPlayerStatus[ID].IsReady)
		{
			int Dir = 1;
			if (Input == LEFT_BUTTON) Dir = -1;
			//vPlayerStatus[ID].CurrentSkin = PlayerSkin((int)vPlayerStatus[ID].CurrentSkin + Dir);
			int CurrentSkin = (int)vPlayerStatus[ID].CurrentSkin;
			CurrentSkin += Dir;
			if (CurrentSkin < 0) CurrentSkin = 3;
			else if (CurrentSkin > 3) CurrentSkin = 0;
			vPlayerStatus[ID].CurrentSkin = PlayerSkin(CurrentSkin);
			const char* NewImage = GetSkinPath(vPlayerStatus[ID].CurrentSkin);
			
			float Alpha = 1.0f;

			if (UsedSkins[vPlayerStatus[ID].CurrentSkin])
				Alpha = 0.3f;
			glm::vec2 Pos = vPlayerStatus[ID].PlayerImage->GetPosition();
			DestroyUIElement(vPlayerStatus[ID].PlayerImage);
			vPlayerStatus[ID].PlayerImage = std::make_shared<UIImage>(UIImage(Pos, Utils::CENTER, 0, { 1.0f, 1.0f, 1.0f, Alpha }, 200, 200, NewImage, 2));
			AddUIElement(vPlayerStatus[ID].PlayerImage);
			PlayerSelectElements.push_back(vPlayerStatus[ID].PlayerImage);
		}

	}
	else if (Input == RIGHT_FACE_BUTTON)
	{
		if (ControlsElements[0]->IsActive() || CreditsElements[0]->IsActive())
		{
			SwitchScreens(MENU);
		}
	}
	else if (Input == BOTTOM_FACE_BUTTON)
	{
		CurrentSelectedButton->Pressed();
	}
}

void Menu::ControllerInputAxis(InputDirection NewInput)
{
	CurrentSelectedButton->HoverOverride = false;
	
	for (int i = 0; i < MenuElements.size(); i++)
	{
		if (MenuElements[i] == CurrentSelectedButton)
		{
			CurrentSelectedButton = nullptr;
			while (CurrentSelectedButton == nullptr)
			{
				if (NewInput == DOWN || NewInput == RIGHT)
				{
					i++;
					if (i >= MenuElements.size()) i = 0;
				}
				else
				{
					i--;
					if (i < 0) i = MenuElements.size() - 1;
				}
				std::shared_ptr<UIButton> IsButton = std::dynamic_pointer_cast<UIButton>(MenuElements[i]);
				if (IsButton)
				{
					CurrentSelectedButton = IsButton;
					CurrentSelectedButton->HoverOverride = true;
				}
			}
			break;
		}
	}
}

void Menu::CheckPlayersToStartTimer()
{
	bool AllReady = true;
	int NumPlayers = 0;
	for (auto& PStat : vPlayerStatus)
	{
		if (PStat.IsPlaying)
		{
			NumPlayers++;
			if (!PStat.IsReady)
			{
				AllReady = false;
			}
		}
	}

	if (AllReady && NumPlayers >= 2)
	{
		StartTime = 3;
		StartTimerText->sText = "Starting in " + std::to_string((int)StartTime) + "...";
		StartTimerText->SetActive(true);
	}
	else
	{
		StartTime = 3;
		StartTimerText->SetActive(false);
	}
}

void Menu::ResetPlayerSelectScreen()
{
	for (auto& PStat : vPlayerStatus)
	{
		PStat.PlayerReadyText->SetActive(false);
		PStat.IsPlaying = false;
		PStat.IsReady = false;
		PStat.PlayerJoinedText->sText = "Press Start to join";
		PStat.PlayerImage->SetActive(false);
	}
	StartTimerText->SetActive(false);
}

void Menu::StartGame()
{
	GameManager::GetInstance()->RemovePlayers(); // Restart Players map
	for (int i = 0; i < vPlayerStatus.size(); i++)
	{
		if (vPlayerStatus[i].IsPlaying && vPlayerStatus[i].IsReady) // Add all readied players
		{
			PlayerInfo NewPlayerInfo;
			NewPlayerInfo.PlayerID = i; // Set player ID
			NewPlayerInfo.Skin = vPlayerStatus[i].CurrentSkin;
			GameManager::GetInstance()->vPlayerInfo.insert(std::pair<int, PlayerInfo>(i, NewPlayerInfo)); // Add to map
		}
	}
	LevelManager::GetInstance()->NewRound(GetRandomGamemode()); // New level
	
	SoundManager::GetInstance()->PlayAudio("MainTrack");
}

void Menu::SwitchScreens(MenuScreens NewScreen)
{
	for (auto& UIElem : MenuElements)
	{
		UIElem->SetActive(false);
	}
	for (auto& UIElem : PlayerSelectElements)
	{
		UIElem->SetActive(false);
	}
	for (auto& UIElem : ControlsElements)
	{
		UIElem->SetActive(false);
	}
	for (auto& UIElem : CreditsElements)
	{
		UIElem->SetActive(false);
	}

	switch (NewScreen)
	{
	case Menu::MENU:
	{
		for (auto& UIElem : MenuElements)
		{
			UIElem->SetActive(true);
		}
	}
		break;
	case Menu::PLAYERSELECT:
	{
		if (SkipPlayerSelect)
		{
			LevelManager::GetInstance()->NewRound(GetRandomGamemode()); // New level
			SoundManager::GetInstance()->PlayAudio("MainTrack");
			break;
		}
		for (auto& UIElem : PlayerSelectElements)
		{
			UIElem->SetActive(true);
		}
		ResetPlayerSelectScreen();
	}
	break;
	case Menu::CONTROLS:
	{
		for (auto& UIElem : ControlsElements)
		{
			UIElem->SetActive(true);
		}
	}
	break;
	case Menu::CREDITS:
	{
		for (auto& UIElem : CreditsElements)
		{
			UIElem->SetActive(true);
		}
	}
	break;
	default:
		break;
	}
}

const char* Menu::GetSkinPath(PlayerSkin Skin)
{
	switch (Skin)
	{
	case OfficeSquare:
	{
		return "Resources/Images/office-square.png";
		break;
	}
	case SmexyHexy:
	{
		return "Resources/Images/SmexyHexy.png";
		break;
	}
	case GuyAngle:
	{
		return "Resources/Images/Guyangle.png";
		break;
	}
	case Rhombage:
	{
		return "Resources/Images/Rhombage.png";
		break;
	}
	default:
		std::cout << "Couldn't find skin path\n";
		return "";
		break;
	}
}

void SelectPlayersBtn()
{
	std::shared_ptr<Menu> MenuScene = std::dynamic_pointer_cast<Menu>(SceneManager::GetInstance()->GetCurrentScene());
	if (MenuScene)
	{
		MenuScene->SwitchScreens(Menu::PLAYERSELECT);
	}
}

void ExitGameBtn()
{
	glutLeaveMainLoop();
}

void ControlsScreenBtn()
{
	std::shared_ptr<Menu> MenuScene = std::dynamic_pointer_cast<Menu>(SceneManager::GetInstance()->GetCurrentScene());
	if (MenuScene)
	{
		MenuScene->SwitchScreens(Menu::CONTROLS);
	}
}

void CreditsScreenBtn()
{
	std::shared_ptr<Menu> MenuScene = std::dynamic_pointer_cast<Menu>(SceneManager::GetInstance()->GetCurrentScene());
	if (MenuScene)
	{
		MenuScene->SwitchScreens(Menu::CREDITS);
	}
}
