//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name		:    Cursor.h
// Description		:    Header file outlining the Class
// Author			:    Alex Coultas
// Mail				:    alex.cou7417@mediadesign.school.nz
//

#pragma once
// Engine Includes //
#include "UIImage.h"

class Cursor : public UIImage
{
public:
	Cursor(const char* _CursorImage);
	~Cursor();

	void Update();
	void SetInvisibleRange(glm::vec2 _v2NewRange);
	void SetVisibleRange(glm::vec2 _v2NewRange);

	glm::vec2 m_v2InvisibleRange = { 0, 0 };
	glm::vec2 m_v2VisibleRange = { 0, 0 };
};

