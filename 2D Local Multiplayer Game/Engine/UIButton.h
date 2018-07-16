//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name		:    UIButton.h
// Description		:    Header file outlining the Class
// Author			:    Alex Coultas
// Mail				:    alex.cou7417@mediadesign.school.nz
//

#pragma once

// Library Includes //
#include <string>

// OpenGL Library Includes //
#include <glm\common.hpp>

// Engine Includes //
#include "UIElement.h"
#include "UIText.h"
#include "UIImage.h"



class UIButton : public UIElement
{
public:
	UIButton(glm::vec2 _Position, Utils::EANCHOR _anchor, float _fRotation, glm::vec4 _Colour, glm::vec4 _HightlightColour, int iWidth, int iHeight, void(*func)());
	UIButton(glm::vec2 _Position, Utils::EANCHOR _anchor, float _fRotation, const char* _ImagePath, glm::vec4 _HightlightColour, int iWidth, int iHeight, void(*func)());
	~UIButton();

	void AddText(std::string sText, std::string sFont, int iPSize, glm::vec4 TextColour, Utils::EANCHOR _Anchor);
	void AddText(std::string sText, std::string sFont, int iPSize, glm::vec4 TextColour, Utils::EANCHOR _Anchor, glm::vec2 _v2Offset);
	void AddHold(void(*func)());
	void AddRelease(void(*func)());
	void SetActive(bool _bIsActive);
	void SetPressSound(const char* _SoundPath);

	UIText TextComponent;
	UIImage ImageComponent;

	void DrawUIElement();
	void Update();
	void SetPosition(glm::vec2 _NewPosition);

	bool bPressed = false;

	static bool bButtonPressedThisFrame;

private:
	using GMVoidFunc = void(*)();

	GMVoidFunc FuncCall = nullptr;
	GMVoidFunc HoldFuncCall = nullptr;
	GMVoidFunc ReleaseFuncCall = nullptr;

	bool bHasText = false;

	glm::vec4 btnColour;
	glm::vec4 btnHighlightColour;

	const char* m_PressSoundPath = "";

};

