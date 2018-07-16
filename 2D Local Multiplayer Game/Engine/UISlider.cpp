//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name    	:    UISlider.cpp
// Description    	:    main implementation for UISlider
// Author       	:    Alex Coultas
// Mail         	:    alex.cou7417@mediadesign.school.nz
//

// Library Includes //
#include <iostream>

// OpenGL Library Includes //

// Engine Includes //
#include "Input.h"

// Local Includes //

// This Includes //
#include "UISlider.h"

// Static Variables //


/************************************************************
#--Description--#:  Constructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	Takes contructor values
#--Return--#: 		NA
************************************************************/
UISlider::UISlider(glm::vec2 _Position, float _fRotation, glm::vec4 _HandleColour, glm::vec4 _SliderColour, int _iSliderLength, int _iSliderThickness, int _iHandleHeight, int _iHandleWidth, Utils::EANCHOR _Anchor, std::string _sTitle)
	: UIElement(_Position, _fRotation, _HandleColour), SliderBar(_Position, _Anchor, 0, _SliderColour, glm::vec4(glm::vec3(_SliderColour), 0.5), _iSliderLength, _iSliderThickness, nullptr),
	SliderHandle(Utils::GetAncoredPosition2D(glm::vec2(_Position.x - _iSliderLength / 2, _Position.y), glm::vec2(_iSliderLength, _iSliderThickness), _Anchor), Utils::CENTER, 0, _HandleColour, glm::vec4(glm::vec3(_HandleColour), 0.5), _iHandleWidth, _iHandleHeight, nullptr),
	sTitle(_sTitle)
{
	SliderBar.AddText(sTitle + ": 0.00", "Resources/Fonts/Roboto-Thin.ttf", 25, glm::vec4(1, 1, 1, 1), Utils::BOTTOM_CENTER);
	SliderBar.TextComponent.SetPosition(SliderBar.TextComponent.GetPosition() + glm::vec2(0, -_iHandleHeight ));
}
/************************************************************
#--Description--#:  Destructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	NA
#--Return--#: 		NA
************************************************************/
UISlider::~UISlider()
{
}

/************************************************************
#--Description--#:	Render to the screen
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void UISlider::DrawUIElement()
{
	SliderBar.DrawUIElement();
	SliderHandle.DrawUIElement();
}

/************************************************************
#--Description--#: 	Updated every frame
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void UISlider::Update()
{
	glm::vec2 MousePos = Input::GetInstance()->MousePos;

	SliderBar.Update();
	SliderHandle.Update();

	if (SliderHandle.bPressed || SliderBar.bPressed)
	{
		float fSliderBarCenterPositionX = Utils::GetAncoredPosition2D(SliderBar.GetPosition(), glm::vec2(SliderBar.ImageComponent.GetWidth(), SliderBar.ImageComponent.GetHeight()), SliderBar.ImageComponent.GetAnchor()).x;
		float fSliderHandleCenterPositionY = Utils::GetAncoredPosition2D(SliderBar.GetPosition(), glm::vec2(SliderBar.ImageComponent.GetWidth(), SliderBar.ImageComponent.GetHeight()), SliderBar.ImageComponent.GetAnchor()).y;
		if (MousePos.x <= fSliderBarCenterPositionX + SliderBar.ImageComponent.GetWidth() / 2 &&
			MousePos.x >= fSliderBarCenterPositionX - SliderBar.ImageComponent.GetWidth() / 2)// //&&
			/*MousePos.y <= fSliderHandleCenterPositionY + SliderHandle.ImageComponent.GetHeight() / 2 &&
			MousePos.y >= fSliderHandleCenterPositionY - SliderHandle.ImageComponent.GetHeight() / 2)*/
		{
			SliderHandle.SetPosition(glm::vec2(MousePos.x, SliderHandle.GetPosition().y));
		}
		else
		{
			if (MousePos.x > fSliderBarCenterPositionX + SliderBar.ImageComponent.GetWidth() / 2)
			{
				SliderHandle.SetPosition(glm::vec2(fSliderBarCenterPositionX + SliderBar.ImageComponent.GetWidth() / 2, SliderHandle.GetPosition().y));
			}
			else
			{
				SliderHandle.SetPosition(glm::vec2(fSliderBarCenterPositionX - SliderBar.ImageComponent.GetWidth() / 2, SliderHandle.GetPosition().y));
			}
		}
		SliderBar.TextComponent.sText = sTitle + ": " + std::to_string(GetValue()).substr(0, 4);
		//std::cout << "Button is held\n";
	}
}

/************************************************************
#--Description--#:  Set whether the UI Slider is active
#--Author--#: 		Alex Coultas
#--Parameters--#:	boolena whether its set active
#--Return--#: 		NA
************************************************************/
void UISlider::SetActive(bool _bIsActive)
{
	UIElement::SetActive(_bIsActive);
	SliderBar.SetActive(_bIsActive);
	SliderHandle.SetActive(_bIsActive);
}

/************************************************************
#--Description--#:  retrieves value of slider
#--Author--#: 		Alex Coultas
#--Parameters--#:	NA
#--Return--#: 		float value of slider
************************************************************/
float UISlider::GetValue()
{
	float fSliderBarLeftPositionX = Utils::GetAncoredPosition2D(SliderBar.GetPosition(), glm::vec2(SliderBar.ImageComponent.GetWidth(), SliderBar.ImageComponent.GetHeight()), SliderBar.ImageComponent.GetAnchor()).x - SliderBar.ImageComponent.GetWidth() / 2;
	float fSliderHandleDistance = SliderHandle.GetPosition().x - fSliderBarLeftPositionX;
	float fPercentage = fSliderHandleDistance / (float)SliderBar.ImageComponent.GetWidth() - fMinimumPosition;
	float fPercentageWithOffset = (fPercentage + fMinimumPosition) * (fMaximumPosition - fMinimumPosition);
	float fRawValue = fPercentageWithOffset + fMinimumPosition;
	// Round to closest lock number
	float HigherNumber = 0;
	while (HigherNumber < fRawValue)
	{
		HigherNumber += fLockSize;
	}
	if(HigherNumber - fRawValue <= fLockSize / 2)
	{
		if (HigherNumber > fMaximumPosition)
			fRawValue = fMaximumPosition;
		else
			fRawValue = HigherNumber;
	}
	else
	{		
		fRawValue -= fLockSize - (HigherNumber - fRawValue);
		if (HigherNumber < fMinimumPosition || fRawValue <= 0)
			fRawValue = fMinimumPosition;
	}
	return fRawValue;
}

/************************************************************
#--Description--#:  Set minimum position
#--Author--#: 		Alex Coultas
#--Parameters--#:	Takes in minmum value to set
#--Return--#: 		NA
************************************************************/
void UISlider::SetMinimumPosition(float _fMinimumPosition)
{
	fMinimumPosition = _fMinimumPosition;
	if (fMinimumPosition > GetValue())SliderBar.TextComponent.sText = sTitle + ": " + std::to_string(fMinimumPosition).substr(0, 4);
}

/************************************************************
#--Description--#:  Set maximum position
#--Author--#: 		Alex Coultas
#--Parameters--#:	Takes in maximum value to set
#--Return--#: 		NA
************************************************************/
void UISlider::SetMaximumPosition(float _fMaximumPosition)
{
	fMaximumPosition = _fMaximumPosition;
	if (fMaximumPosition < GetValue())SliderBar.TextComponent.sText = sTitle + ": " + std::to_string(fMaximumPosition).substr(0, 4);
}

/************************************************************
#--Description--#:  Set start position
#--Author--#: 		Alex Coultas
#--Parameters--#:	Takes in start value to set
#--Return--#: 		NA
************************************************************/
void UISlider::SetStartPosition(float _fStartPosition)
{
	if (_fStartPosition > fMaximumPosition) _fStartPosition = fMaximumPosition;
	else if (_fStartPosition < fMinimumPosition) _fStartPosition = fMinimumPosition;
	SliderBar.TextComponent.sText = sTitle + ": " + std::to_string(_fStartPosition).substr(0, 4);
	float fSliderBarLeftPositionX = Utils::GetAncoredPosition2D(SliderBar.GetPosition(), glm::vec2(SliderBar.ImageComponent.GetWidth(), SliderBar.ImageComponent.GetHeight()), SliderBar.ImageComponent.GetAnchor()).x - SliderBar.ImageComponent.GetWidth() / 2;
	float fSliderHandleDistance = fSliderBarLeftPositionX + (float)SliderBar.ImageComponent.GetWidth() * _fStartPosition / fMaximumPosition;
	SliderHandle.SetPosition(glm::vec2(fSliderHandleDistance, SliderHandle.GetPosition().y));

}

/************************************************************
#--Description--#:  Set lock size
#--Author--#: 		Alex Coultas
#--Parameters--#:	Takes in lock size value to set
#--Return--#: 		NA
************************************************************/
void UISlider::SetLockSize(float _fLockSize)
{
	fLockSize = _fLockSize;
}

