//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name		:    UIText.h
// Description		:    Header file outlining the Class
// Author			:    Alex Coultas
// Mail				:    alex.cou7417@mediadesign.school.nz
//

#pragma once

// Library Includes //

#include <string>

// OpenGL Library Includes //
#include <glm/common.hpp>

// Engine Includes //
#include "UIElement.h"
#include "Utils.h"


class UIText : public UIElement
{
public:
	void DrawUIElement();

	UIText(glm::vec2 _Position, float _fRotation, glm::vec4 _Colour, std::string _sText, std::string Font, int _iPSize, Utils::EANCHOR _Anchor);
	UIText(glm::vec2 _Position, float _fRotation, glm::vec4 _Colour);
	~UIText();

	std::string sText;
	std::string sFont;
	int iPSize;
	Utils::EANCHOR Anchor;
};

