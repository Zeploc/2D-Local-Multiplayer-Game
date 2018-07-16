//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name		:    UISlider.h
// Description		:    Header file outlining the Class
// Author			:    Alex Coultas
// Mail				:    alex.cou7417@mediadesign.school.nz
//

#pragma once


// Engine Includes //
#include "UIElement.h"
#include "UIImage.h"
#include "UIButton.h"

class UISlider : public UIElement
{
public:
	UISlider(glm::vec2 _Position, float _fRotation, glm::vec4 _HandleColour, glm::vec4 _SliderColour, int _iSliderLength, int _iSliderThickness, int _iHandleHeight, int _iHandleWidth, Utils::EANCHOR _Anchor, std::string _sTitle);
	~UISlider();

	void DrawUIElement();
	void Update();
	void SetActive(bool _bIsActive);

	float GetValue();

	UIButton SliderBar;
	UIButton SliderHandle;

	std::string sTitle;

	float GetMinimumPosition() { return fMinimumPosition; };
	void SetMinimumPosition(float _fMinimumPosition);
	void SetMaximumPosition(float _fMaximumPosition); 
	void SetStartPosition(float _fStartPosition);
	void SetLockSize(float _fLockSize);

private:
	float fMinimumPosition = 0.0f;
	float fMaximumPosition = 1.0f;
	float fLockSize = 0.01f;
};

