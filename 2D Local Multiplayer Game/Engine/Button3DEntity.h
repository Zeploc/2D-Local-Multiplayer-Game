//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name		:    Button3DEntity.h
// Description		:    Header file outlining the Class
// Author			:    Alex Coultas
// Mail				:    alex.cou7417@mediadesign.school.nz
//

#pragma once
// This Includes //
#include "Entity.h"

class Button3DEntity :	public Entity
{
public:
	Button3DEntity(Utils::Transform _Transform, Utils::EANCHOR _Anchor, float fWidth, float fHeight, float fDepth, glm::vec4 _Colour, glm::vec4 _HightlightColour, void(*func)());
	Button3DEntity(Utils::Transform _Transform, Utils::EANCHOR _Anchor, float fWidth, float fHeight, float fDepth, glm::vec4 _Colour, glm::vec4 _HightlightColour, const char * Texturepath, void(*func)());
	~Button3DEntity();


	virtual void Update() override;

	bool bPressed = false;

	static bool bButtonPressedThisFrame;

private:
	using GMVoidFunc = void(*)();

	GMVoidFunc FuncCall = nullptr;

	bool CheckHit(glm::vec3 BottomLeftOffset, glm::vec3 TopRightOffset);

	glm::vec4 btnColour;
	glm::vec4 btnHighlightColour;
};

