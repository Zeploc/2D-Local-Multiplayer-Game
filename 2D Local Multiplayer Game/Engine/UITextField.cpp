//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name    	:    UITextField.cpp
// Description    	:    A UI Text Entry field
// Author       	:    Alex Coultas
// Mail         	:    alex.cou7417@mediadesign.school.nz
//

// This Includes //
#include "UITextField.h"

// Library Includes //
#include <memory>
#include <conio.h>

// Engine Includes //
#include "Shader.h"
#include "Input.h"
#include "Time.h"

/************************************************************
#--Description--#:  Constructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	Takes contructor values
#--Return--#: 		NA
************************************************************/
UITextField::UITextField(glm::vec2 _Position, Utils::EANCHOR _anchor, float _fRotation, glm::vec4 _Colour, int iWidth, int iHeight, glm::vec4 _TextColour, std::string _DefaultValue, std::string _FontPath, int _iPSize, Utils::EANCHOR TextAnchor)
	: UIElement(UIImage::GetPositionFromAnchor(_Position, _anchor, iWidth, iHeight), _fRotation, _Colour), BackImage(_Position, _anchor, _fRotation, _Colour, iWidth, iHeight),
	FieldText(_Position, _fRotation, _TextColour, _DefaultValue, _FontPath, _iPSize, TextAnchor), sHintText(_DefaultValue)
{

}

/************************************************************
#--Description--#:  Constructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	Takes contructor values
#--Return--#: 		NA
************************************************************/
UITextField::UITextField(glm::vec2 _Position, Utils::EANCHOR _anchor, float _fRotation, const char * _ImagePath, int iWidth, int iHeight, glm::vec4 _TextColour, std::string _DefaultValue, std::string _FontPath, int _iPSize, Utils::EANCHOR TextAnchor)
	: UIElement(UIImage::GetPositionFromAnchor(_Position, _anchor, iWidth, iHeight), _fRotation, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)), BackImage(_Position, _anchor, _fRotation, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), iWidth, iHeight, _ImagePath, 1),
	FieldText(UIImage::GetPositionFromAnchor(_Position, TextAnchor, iWidth, iHeight), _fRotation, _TextColour, _DefaultValue, _FontPath, _iPSize, TextAnchor)
{

}

/************************************************************
#--Description--#:  Destructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	NA
#--Return--#: 		NA
************************************************************/
UITextField::~UITextField()
{
}

void UITextField::SetActive(bool _bIsActive)
{
	FieldText.SetActive(_bIsActive);
	BackImage.SetActive(_bIsActive);
}

void UITextField::ResetField()
{
	FieldText.sText = sHintText;
	FieldText.Colour.a = 0.5f;
}

/************************************************************
#--Description--#:	Render Scene to the screen
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void UITextField::DrawUIElement()
{
	if (!bActive) return;
	glUseProgram(Shader::Programs["TextUIprogram"]);
	BackImage.DrawUIElement();
	FieldText.DrawUIElement();
}

/************************************************************
#--Description--#: 	Updated every frame
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void UITextField::Update()
{
	glm::vec2 TopLeft = glm::vec2(position.x - BackImage.GetWidth() / 2, position.y - BackImage.GetHeight() / 2);
	glm::vec2 BottomRight = glm::vec2(position.x + BackImage.GetWidth() / 2, position.y + BackImage.GetHeight() / 2);
	if (Input::GetInstance()->MousePos.x > TopLeft.x && Input::GetInstance()->MousePos.x < BottomRight.x && Input::GetInstance()->MousePos.y < BottomRight.y && Input::GetInstance()->MousePos.y > TopLeft.y)
	{
		if (Input::GetInstance()->MouseState[Input::MOUSE_LEFT] == (Input::InputState::INPUT_HOLD | Input::InputState::INPUT_FIRST_PRESS))
		{
			SetFocussed(true);
			BackImage.Colour = { Colour.r/ 2, Colour.g / 2, Colour.b / 2, Colour.a };
		}
	}
	else if (Input::GetInstance()->MouseState[Input::MOUSE_LEFT] == (Input::InputState::INPUT_HOLD | Input::InputState::INPUT_FIRST_PRESS))
	{
		SetFocussed(false);
		BackImage.Colour = { Colour.r, Colour.g, Colour.b, Colour.a };
	}
	if (bIsFocussed && (Input::GetInstance()->bKBHit || Input::GetInstance()->KeyState[Input::GetInstance()->cLastKey] == Input::INPUT_HOLD))
	{		
		//FieldText.Colour.a = 1.0f;
		std::string NewText = FieldText.sText;
		char cNext = Input::GetInstance()->cLastKey;
		if (cNext == '\b' && dSpamDelay > fSpamTime)
		{
			dSpamDelay = 0;
			NewText = NewText.substr(0, NewText.length() - 1);
			//continue; // no good for the rest now we've deleted a character.
		}
		else if (cNext == '\n' || cNext == '\r')
		{
			//return true;
		}
		else if (Input::GetInstance()->KeyState[Input::GetInstance()->cLastKey] != Input::INPUT_HOLD)
		{
			if (bHintTextActive)
			{
				FieldText.sText = "";
				NewText = FieldText.sText;
				bHintTextActive = false;
			}
			if (!(int(cNext) < 32 || int(cNext) > 126))
			{
				NewText += cNext;
			}
		}
		
		FieldText.sText = NewText;
	}

	BackImage.Update();
	FieldText.Update();
	dSpamDelay += Time::dTimeDelta;
	//if (fSpamDelay > fSpamTime)
	//	fSpamDelay = 0;
}

void UITextField::SetFocussed(bool bNewFocus)
{
	bIsFocussed = bNewFocus;
	bHintTextActive = true;
	//if (!bIsFocussed) FieldText.sText = sHintText;
	//if (!bIsFocussed) bHintTextActive = true;

}
