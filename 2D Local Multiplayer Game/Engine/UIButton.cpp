//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name    	:    UIButton.cpp
// Description    	:    main implementation for UIButton
// Author       	:    Alex Coultas
// Mail         	:    alex.cou7417@mediadesign.school.nz
//

// Library Includes //

// OpenGL Library Includes //

// Engine Includes //
#include "Shader.h"
#include "Input.h"
#include "SoundManager.h"

// Local Includes //

// This Includes //
#include "UIButton.h"

// Static Variables //
bool UIButton::bButtonPressedThisFrame = false;

/************************************************************
#--Description--#:  Constructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	Takes contructor values
#--Return--#: 		NA
************************************************************/
UIButton::UIButton(glm::vec2 _Position, Utils::EANCHOR _anchor, float _fRotation, glm::vec4 _Colour, glm::vec4 _HightlightColour, int iWidth, int iHeight, void(*func)())
	: UIElement(UIImage::GetPositionFromAnchor(_Position, _anchor, iWidth, iHeight), _fRotation, _Colour), ImageComponent(_Position, _anchor, _fRotation, _Colour, iWidth, iHeight), FuncCall(func),
	TextComponent(UIImage::GetPositionFromAnchor(_Position, _anchor, iWidth, iHeight), _fRotation, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)), btnColour(_Colour), btnHighlightColour(_HightlightColour)
{
	SoundManager::GetInstance()->AddChannel("UIC");
}

/************************************************************
#--Description--#:  Constructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	Takes contructor values
#--Return--#: 		NA
************************************************************/
UIButton::UIButton(glm::vec2 _Position, Utils::EANCHOR _anchor, float _fRotation, const char * _ImagePath, glm::vec4 _HightlightColour, int iWidth, int iHeight, void(*func)())
	: UIElement(UIImage::GetPositionFromAnchor(_Position, _anchor, iWidth, iHeight), _fRotation, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)), ImageComponent(_Position, _anchor, _fRotation, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), iWidth, iHeight, _ImagePath, 1), FuncCall(func),
	TextComponent(UIImage::GetPositionFromAnchor(_Position, _anchor, iWidth, iHeight), _fRotation, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)), btnColour(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)), btnHighlightColour(_HightlightColour)
{
	SoundManager::GetInstance()->AddChannel("UIC");
}

/************************************************************
#--Description--#:  Destructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	NA
#--Return--#: 		NA
************************************************************/
UIButton::~UIButton()
{
}

/************************************************************
#--Description--#:  Add text component to Button
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Takes text, font, size, colour and draw anchor
#--Return--#: 		NA
************************************************************/
void UIButton::AddText(std::string sText, std::string sFont, int iPSize, glm::vec4 TextColour, Utils::EANCHOR _Anchor)
{
	TextComponent = UIText(position, fRotation, TextColour, sText, sFont, iPSize, _Anchor);
	bHasText = true;
}

/************************************************************
#--Description--#:  Add text component to Button with offset
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Takes text, font, size, colour, draw anchor and offset
#--Return--#: 		NA
************************************************************/
void UIButton::AddText(std::string sText, std::string sFont, int iPSize, glm::vec4 TextColour, Utils::EANCHOR _Anchor, glm::vec2 _v2Offset)
{
	TextComponent = UIText(position + _v2Offset, fRotation, TextColour, sText, sFont, iPSize, _Anchor);
	bHasText = true;
}

/************************************************************
#--Description--#:  Add hold function
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Takes pointer to function
#--Return--#: 		NA
************************************************************/
void UIButton::AddHold(void(*func)())
{
	HoldFuncCall = func;
}

/************************************************************
#--Description--#:  Add release function
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Takes pointer to function
#--Return--#: 		NA
************************************************************/
void UIButton::AddRelease(void(*func)())
{
	ReleaseFuncCall = func;
}

/************************************************************
#--Description--#:  Set UI button to active or not
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Boolean whether to set active or not
#--Return--#: 		NA
************************************************************/
void UIButton::SetActive(bool _bIsActive)
{
	UIElement::SetActive(_bIsActive);

	TextComponent.SetActive(_bIsActive);
	ImageComponent.SetActive(_bIsActive);
}

/************************************************************
#--Description--#:  Sets pressed sound
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Sound file path
#--Return--#: 		NA
************************************************************/
void UIButton::SetPressSound(const char * _SoundPath)
{
	m_PressSoundPath = _SoundPath;
	SoundManager::GetInstance()->AddAudio(_SoundPath, false, _SoundPath);
}

/************************************************************
#--Description--#:  Draw UI Element
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void UIButton::DrawUIElement()
{
	if (!bActive) return;
	glUseProgram(Shader::Programs["TextUIprogram"]);
	ImageComponent.DrawUIElement();
	if (bHasText) TextComponent.DrawUIElement();
}

/************************************************************
#--Description--#: 	Updated every frame
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void UIButton::Update()
{
	if (!bActive) return;
	glm::vec2 TopLeft = glm::vec2(position.x - ImageComponent.GetWidth() / 2, position.y - ImageComponent.GetHeight() / 2);
	glm::vec2 BottomRight = glm::vec2(position.x + ImageComponent.GetWidth() / 2, position.y + ImageComponent.GetHeight() / 2);
	if (Input::GetInstance()->MouseState[Input::MOUSE_LEFT] == Input::InputState::INPUT_FIRST_RELEASE)
	{
		if (ReleaseFuncCall != nullptr) ReleaseFuncCall();
		bPressed = false;
	}
	if (Input::GetInstance()->MousePos.x > TopLeft.x && Input::GetInstance()->MousePos.x < BottomRight.x && Input::GetInstance()->MousePos.y < BottomRight.y && Input::GetInstance()->MousePos.y > TopLeft.y)
	{
		ImageComponent.Colour = btnHighlightColour;
		if (Input::GetInstance()->MouseState[Input::MOUSE_LEFT] == Input::InputState::INPUT_HOLD && HoldFuncCall != nullptr)
		{
			HoldFuncCall();
		}
		else if (Input::GetInstance()->MouseState[Input::MOUSE_LEFT] == Input::InputState::INPUT_FIRST_PRESS && !bButtonPressedThisFrame)
		{
			if (m_PressSoundPath != "")
			{
				SoundManager::GetInstance()->PlayAudio(m_PressSoundPath, "FXC");
			}
			bPressed = true;
			bButtonPressedThisFrame = true;
			if (FuncCall != nullptr) FuncCall();
		}
		 
	}
	else
		ImageComponent.Colour = btnColour;
}

/************************************************************
#--Description--#:  Sets new position for button
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Vector 2 new position
#--Return--#: 		NA
************************************************************/
void UIButton::SetPosition(glm::vec2 _NewPosition)
{
	UIElement::SetPosition(_NewPosition);
	TextComponent.SetPosition(_NewPosition);
	ImageComponent.SetPosition(_NewPosition);
}
