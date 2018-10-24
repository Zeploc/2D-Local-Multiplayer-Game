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
	SoundManager::GetInstance()->AddAudio("Resources/Sounds/8-Bit-Mayhem.mp3", true, "MainTrack");
	SoundManager::GetInstance()->SetChannelVolume("MainTrack", 0.15);
	SoundManager::GetInstance()->AddAudio("Resources/Sounds/Puzzle-Dreams-2.mp3", true, "MenuTrack");

	SoundManager::GetInstance()->SetChannelVolume("MenuTrack", 0.15);
	SoundManager::GetInstance()->PlayAudio("MenuTrack");
	// Menu Elements
	//std::shared_ptr<UIText> Title(new UIText(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, 100.0f), 0, glm::vec4(0.9, 0.9, 0.9, 1.0), "Local Multiplayer Game", "Resources/Fonts/Roboto-Black.ttf", 100, Utils::CENTER));
	
	std::shared_ptr<UIImage> Title1(new UIImage(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, 150.0f), Utils::CENTER, 0.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1000, 115, "Resources/Images/Title.png", 1));

	std::shared_ptr<UIButton> StartBtn(new UIButton(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, Camera::GetInstance()->SCR_HEIGHT / 2), Utils::CENTER, 0.0f, "Resources/Images/Play.png", glm::vec4(0.7f, 0.7f, 0.7f, 1.0f), 480, 70, SelectPlayersBtn));
	//StartBtn->AddText("START GAME", "Resources/Fonts/Roboto-Thin.ttf", 34, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), Utils::CENTER, { 0, 0 });
	
	std::shared_ptr<UIButton> ControlsBtn(new UIButton(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, Camera::GetInstance()->SCR_HEIGHT / 2 + 80), Utils::CENTER, 0.0f, "Resources/Images/Controls1.png", glm::vec4(0.7f, 0.7f, 0.7f, 1.0f), 480, 70, ControlsScreenBtn));
	//ControlsBtn->AddText("CONTROLS", "Resources/Fonts/Roboto-Thin.ttf", 34, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), Utils::CENTER, { 0, 0 });
	
	std::shared_ptr<UIButton> CreditsBtn(new UIButton(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, Camera::GetInstance()->SCR_HEIGHT / 2 + 160), Utils::CENTER, 0.0f, "Resources/Images/Credits1.png", glm::vec4(0.7f, 0.7f, 0.7f, 1.0f), 480, 70, CreditsScreenBtn));
	//CreditsBtn->AddText("CREDITS", "Resources/Fonts/Roboto-Thin.ttf", 34, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), Utils::CENTER, { 0, 0 });
	
	std::shared_ptr<UIButton> QuitBtn(new UIButton(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, Camera::GetInstance()->SCR_HEIGHT / 2 + 240), Utils::CENTER, 0.0f, "Resources/Images/Quit.png", glm::vec4(0.7f, 0.7f, 0.7f, 1.0f), 480, 70, ExitGameBtn));
	//QuitBtn->AddText("QUIT GAME", "Resources/Fonts/Roboto-Thin.ttf", 34, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), Utils::CENTER, { 0, 0 });
	
	std::shared_ptr<UIImage> BackImage(new UIImage(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, Camera::GetInstance()->SCR_HEIGHT / 2), Utils::CENTER, 0.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), Camera::GetInstance()->SCR_WIDTH, Camera::GetInstance()->SCR_HEIGHT, "Resources/Images/TitleBack.png", 1));
	std::shared_ptr<UIImage> UIIMG(new UIImage(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, 100.0f), Utils::CENTER, 0.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 600, 100, "Resources/Box.png", 1));
	
	AddUIElement(BackImage);
	//AddUITextElement(Title);
	AddUIElement(Title1);
	AddUIElement(StartBtn);
	AddUIElement(ControlsBtn);
	AddUIElement(CreditsBtn);
	AddUIElement(QuitBtn);

	MenuElements.push_back(Title1);
	MenuElements.push_back(StartBtn);
	MenuElements.push_back(ControlsBtn);
	MenuElements.push_back(CreditsBtn);
	MenuElements.push_back(QuitBtn);

	StartBtn->SetPressSound("Resources/Sounds/Button.mp3");
	ControlsBtn->SetPressSound("Resources/Sounds/Button.mp3");
	CreditsBtn->SetPressSound("Resources/Sounds/Button.mp3");
	QuitBtn->SetPressSound("Resources/Sounds/Button.mp3");
	SoundManager::GetInstance()->SetChannelVolume("Resources/Sounds/Button.mp3", 0.1);

	CurrentSelectedButton = StartBtn;
	CurrentSelectedButton->HoverOverride = true;

	// Player Select Elements
	std::shared_ptr<UIText> PlayerTitle(new UIText(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, 100.0f), 0, glm::vec4(0.1, 0.9, 0.1, 1.0), "Player Select", "Resources/Fonts/Roboto-Black.ttf", 80, Utils::CENTER));
	StartTimerText = std::make_shared<UIText>(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, Camera::GetInstance()->SCR_HEIGHT - 100.0f), 0, glm::vec4(0.9, 0.9, 0.9, 1.0), "Starting in 3...", "Resources/Fonts/Roboto-Regular.ttf", 40, Utils::CENTER);
	StartTimerText->SetActive(false);

	for (int i = 0; i < 4; i++)
	{
		PlayerStatus NewPlayerStatus;
		float XPos = Camera::GetInstance()->SCR_WIDTH / 2 - 450 + 300 * i;
		std::shared_ptr<UIText> PlayerLabel(new UIText(glm::vec2(XPos, Camera::GetInstance()->SCR_HEIGHT / 2 - 150), 0, glm::vec4(0.9, 0.9, 0.9, 1.0), "Player " + std::to_string(i + 1), "Resources/Fonts/Roboto-Regular.ttf", 25, Utils::CENTER));
		AddUIElement(PlayerLabel);
		PlayerSelectElements.push_back(PlayerLabel);
		std::shared_ptr<UIText> PlayerJoin(new UIText(glm::vec2(XPos, Camera::GetInstance()->SCR_HEIGHT / 2 - 120), 0, glm::vec4(0.9, 0.9, 0.9, 1.0), "Press Start to join", "Resources/Fonts/Roboto-Thin.ttf", 25, Utils::CENTER));
		AddUIElement(PlayerJoin);
		PlayerSelectElements.push_back(PlayerJoin);
		std::shared_ptr<UIText> PlayerReady(new UIText(glm::vec2(XPos, Camera::GetInstance()->SCR_HEIGHT / 2 + 200), 0, glm::vec4(0.9, 0.9, 0.9, 1.0), "Ready", "Resources/Fonts/Roboto-Bold.ttf", 25, Utils::CENTER));
		AddUIElement(PlayerReady);
		PlayerSelectElements.push_back(PlayerReady);
		std::shared_ptr<UIImage> PlayerImage(new UIImage(glm::vec2(XPos, Camera::GetInstance()->SCR_HEIGHT / 2 + 0), Utils::CENTER, 0, { 1.0f, 1.0f, 1.0f, 1.0f }, 200, 200, "Resources/Images/office-square.png", 1));
		AddUIElement(PlayerImage);
		PlayerSelectElements.push_back(PlayerImage);
		std::shared_ptr<UIImage> ButtonHintImage(new UIImage(glm::vec2(XPos, Camera::GetInstance()->SCR_HEIGHT / 2 + 150), Utils::CENTER, 0, { 1.0f, 1.0f, 1.0f, 1.0f }, 70, 60, GetInputImagePath(SPECIAL_BUTTON_RIGHT), 1));
		AddUIElement(ButtonHintImage);
		PlayerSelectElements.push_back(ButtonHintImage);
		std::shared_ptr<UIImage> LeftHintImage(new UIImage(glm::vec2(XPos - 60, Camera::GetInstance()->SCR_HEIGHT / 2 + 150), Utils::CENTER, 0, { 1.0f, 1.0f, 1.0f, 1.0f }, 70, 65, GetInputImagePath(LEFT_BUMPER), 1));
		AddUIElement(LeftHintImage);
		PlayerSelectElements.push_back(LeftHintImage);
		std::shared_ptr<UIImage> RightHintImage(new UIImage(glm::vec2(XPos + 60, Camera::GetInstance()->SCR_HEIGHT / 2 + 150), Utils::CENTER, 0, { 1.0f, 1.0f, 1.0f, 1.0f }, 70, 65, GetInputImagePath(RIGHT_BUMPER), 1));
		AddUIElement(RightHintImage);
		PlayerSelectElements.push_back(RightHintImage);
		PlayerReady->SetActive(false);

		NewPlayerStatus.PlayerJoinedText = PlayerJoin;
		NewPlayerStatus.PlayerReadyText = PlayerReady;
		NewPlayerStatus.PlayerImage = PlayerImage;
		NewPlayerStatus.ButtonHintImage = ButtonHintImage;
		NewPlayerStatus.LeftHintImage = LeftHintImage;
		NewPlayerStatus.RightHintImage = RightHintImage;
		NewPlayerStatus.CurrentSkin = OfficeSquare;
		vPlayerStatus.push_back(NewPlayerStatus);
	}

	AddUIElement(PlayerTitle);
	AddUIElement(StartTimerText);
	PlayerSelectElements.push_back(StartTimerText);
	PlayerSelectElements.push_back(PlayerTitle);

	// Controls Elements
	std::shared_ptr<UIImage> ControlsTitle1(new UIImage(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, 100.0f), Utils::CENTER, 0.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 500, 70, "Resources/Images/ControlsTitle.png", 1));

	//std::shared_ptr<UIText> ControlsTitle(new UIText(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, 100.0f), 0, glm::vec4(0.9, 0.9, 0.9, 1.0), "Controls", "Resources/Fonts/Roboto-Black.ttf", 80, Utils::CENTER));
	std::shared_ptr<UIImage> ControlsImage(new UIImage(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, Camera::GetInstance()->SCR_HEIGHT / 2), Utils::CENTER, 0.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), Camera::GetInstance()->SCR_WIDTH * 0.6, Camera::GetInstance()->SCR_HEIGHT * 0.7, "Resources/Images/Controls.png", 1));
	//std::shared_ptr<UIText> BToBack(new UIText(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, Camera::GetInstance()->SCR_HEIGHT - 100.0f), 0, glm::vec4(0.7, 0.7, 0.7, 1.0), "B to go back", "Resources/Fonts/Roboto-Regular.ttf", 40, Utils::CENTER));
	std::shared_ptr<UIImage> BToGoBack(new UIImage(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, Camera::GetInstance()->SCR_HEIGHT - 50), Utils::CENTER, 0.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 500, 70, "Resources/Images/Back.png", 1));


	AddUIElement(ControlsTitle1);
	//AddUIElement(ControlsTitle);
	AddUIElement(ControlsImage);
	//AddUIElement(BToBack);
	AddUIElement(BToGoBack);
	ControlsElements.push_back(ControlsTitle1);
	//ControlsElements.push_back(ControlsTitle);
	ControlsElements.push_back(ControlsImage);
	//ControlsElements.push_back(BToBack);
	ControlsElements.push_back(BToGoBack);

	// Credits Elements
	std::shared_ptr<UIImage> CreditsTitle1(new UIImage(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, 100.0f), Utils::CENTER, 0.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 500, 70, "Resources/Images/CreditsTitle.png", 1));
	//std::shared_ptr<UIText> CreditsTitle(new UIText(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, 100.0f), 0, glm::vec4(0.9, 0.9, 0.9, 1.0), "Credits", "Resources/Fonts/Roboto-Black.ttf", 80, Utils::CENTER));

	std::shared_ptr<UIImage> CreditsImage(new UIImage(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, Camera::GetInstance()->SCR_HEIGHT / 2), Utils::CENTER, 0.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), Camera::GetInstance()->SCR_WIDTH * 0.7, Camera::GetInstance()->SCR_HEIGHT * 0.7, "Resources/Images/Credits.png", 1));

	//AddUIElement(CreditsTitle);
	AddUIElement(CreditsImage);
	AddUIElement(CreditsTitle1);
	CreditsElements.push_back(CreditsImage);
	CreditsElements.push_back(CreditsTitle1);
	//CreditsElements.push_back(CreditsTitle);
	//CreditsElements.push_back(BToBack);
	CreditsElements.push_back(BToGoBack);

	std::shared_ptr<UIText> BToBackPlayerSelect(new UIText(glm::vec2(Camera::GetInstance()->SCR_WIDTH / 2, Camera::GetInstance()->SCR_HEIGHT - 50.0f), 0, glm::vec4(0.1, 0.1, 0.9, 1.0), "B to go back", "Resources/Fonts/Roboto-Regular.ttf", 30, Utils::CENTER));
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
		if (Input == SPECIAL_BUTTON_RIGHT || (Input == BOTTOM_FACE_BUTTON && !vPlayerStatus[ID].IsPlaying) || (Input == RIGHT_FACE_BUTTON && !vPlayerStatus[ID].IsReady && vPlayerStatus[ID].IsPlaying))
		{
			if (Input != RIGHT_FACE_BUTTON) vPlayerStatus[ID].IsPlaying = !vPlayerStatus[ID].IsPlaying;
			else vPlayerStatus[ID].IsPlaying = false;
			if (vPlayerStatus[ID].IsPlaying)
			{
				vPlayerStatus[ID].PlayerJoinedText->sText = "Joined";
				vPlayerStatus[ID].PlayerImage->SetActive(true);
				vPlayerStatus[ID].ButtonHintImage->SetImage(GetInputImagePath(BOTTOM_FACE_BUTTON), 85, 60);
				vPlayerStatus[ID].LeftHintImage->SetActive(true);
				vPlayerStatus[ID].RightHintImage->SetActive(true);
				StartTime = 3;
				StartTimerText->SetActive(false);
				UpdateImageStatus(ID);
			}
			else
			{
				vPlayerStatus[ID].PlayerJoinedText->sText = "Press Start to join";
				vPlayerStatus[ID].PlayerReadyText->SetActive(false);
				vPlayerStatus[ID].PlayerImage->SetActive(false);
				vPlayerStatus[ID].LeftHintImage->SetActive(false);
				vPlayerStatus[ID].RightHintImage->SetActive(false);
				vPlayerStatus[ID].ButtonHintImage->SetImage(GetInputImagePath(SPECIAL_BUTTON_RIGHT), 70, 60);
				vPlayerStatus[ID].IsReady = false;
				StartTime = 3;
				StartTimerText->SetActive(false);
				UsedSkins[vPlayerStatus[ID].CurrentSkin] = false;
			}
		}
		else if (Input == RIGHT_FACE_BUTTON && !vPlayerStatus[ID].IsPlaying)
		{
			SwitchScreens(MENU);
		}
		else if (Input == BOTTOM_FACE_BUTTON || Input == RIGHT_FACE_BUTTON)
		{
			// Check if the player is trying to ready up or unready
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
				vPlayerStatus[ID].LeftHintImage->SetActive(false);
				vPlayerStatus[ID].RightHintImage->SetActive(false);
				UsedSkins[vPlayerStatus[ID].CurrentSkin] = true;
				vPlayerStatus[ID].ButtonHintImage->SetImage(GetInputImagePath(RIGHT_FACE_BUTTON), 85, 60);
			}
			else
			{
				vPlayerStatus[ID].IsReady = false;
				vPlayerStatus[ID].PlayerReadyText->SetActive(false);
				vPlayerStatus[ID].LeftHintImage->SetActive(true);
				vPlayerStatus[ID].RightHintImage->SetActive(true);
				UsedSkins[vPlayerStatus[ID].CurrentSkin] = false;
				vPlayerStatus[ID].ButtonHintImage->SetImage(GetInputImagePath(BOTTOM_FACE_BUTTON), 85, 60);
				// Set any of the images with this skin back
			}

			for (int pId = 0; pId < vPlayerStatus.size(); pId++)
			{
				if (pId == ID) continue; // Dont check same player
				if (vPlayerStatus[pId].CurrentSkin == vPlayerStatus[ID].CurrentSkin && vPlayerStatus[pId].IsPlaying)
				{
					UpdateImageStatus(pId);
				}
			}
			CheckPlayersToStartTimer();

		}
		else if ((Input == LEFT_BUMPER || Input == RIGHT_BUMPER) && vPlayerStatus[ID].IsPlaying && !vPlayerStatus[ID].IsReady)
		{
			int Dir = 1;
			if (Input == LEFT_BUMPER) Dir = -1;
			//vPlayerStatus[ID].CurrentSkin = PlayerSkin((int)vPlayerStatus[ID].CurrentSkin + Dir);
			int CurrentSkin = (int)vPlayerStatus[ID].CurrentSkin;
			CurrentSkin += Dir;
			if (CurrentSkin < 0) CurrentSkin = 3;
			else if (CurrentSkin > 3) CurrentSkin = 0;
			vPlayerStatus[ID].CurrentSkin = PlayerSkin(CurrentSkin);
			UpdateImageStatus(ID);
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
		PStat.LeftHintImage->SetActive(false);
		PStat.RightHintImage->SetActive(false);
	}

	for (auto& CSkin : UsedSkins)
	{
		CSkin.second = false;
	}
	StartTimerText->SetActive(false);
}

void Menu::UpdateImageStatus(int ID)
{
	float Alpha = 1.0f;
	if (UsedSkins[vPlayerStatus[ID].CurrentSkin])
		Alpha = 0.3f;
	vPlayerStatus[ID].PlayerImage->SetImage(GetSkinPath(vPlayerStatus[ID].CurrentSkin));
	vPlayerStatus[ID].PlayerImage->Colour.a = Alpha;
	vPlayerStatus[ID].ButtonHintImage->Colour.a = Alpha;
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
			SoundManager::GetInstance()->PauseAudio("MenuTrack");
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

const char * Menu::GetInputImagePath(InputController InputType)
{
	switch (InputType)
	{
	case DPAD_UP:
		break;
	case DPAD_DOWN:
		break;
	case DPAD_LEFT:
		break;
	case DPAD_RIGHT:
		break;
	case SPECIAL_BUTTON_RIGHT:
		return "Resources/Images/Buttons/Start_Button.png";
		break;
	case SPECIAL_BUTTON_LEFT:
		return "Resources/Images/Buttons/Select_Button.png";
		break;
	case LEFT_STICK_DOWN:
		break;
	case RIGHT_STICK_DOWN:
		break;
	case LEFT_BUMPER:
		return "Resources/Images/Buttons/LB.png";
		break;
	case RIGHT_BUMPER:
		return "Resources/Images/Buttons/RB.png";
		break;
	case BOTTOM_FACE_BUTTON:
		return "Resources/Images/Buttons/A.png";
		break;
	case RIGHT_FACE_BUTTON:
		return "Resources/Images/Buttons/B.png";
		break;
	case LEFT_FACE_BUTTON:
		return "Resources/Images/Buttons/X.png";
		break;
	case TOP_FACE_BUTTON:
		return "Resources/Images/Buttons/Y.png";
		break;
	default:
		break;
	}
	return "";
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
