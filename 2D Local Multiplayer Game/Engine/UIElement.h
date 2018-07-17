//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name		:    UIElement.h
// Description		:    Header file outlining the Class
// Author			:    Alex Coultas
// Mail				:    alex.cou7417@mediadesign.school.nz
//

// OpenGL Library Includes //
#include <glm\common.hpp>

// Engine Includes //
#include "Camera.h"


#pragma once
class UIElement : public std::enable_shared_from_this<UIElement>
{
public:
	UIElement(glm::vec2 _Position, float _fRotation, glm::vec4 _Colour);
	~UIElement();
	
	virtual void DrawUIElement();
	void BaseUpdate();
	virtual void Update();

	virtual void SetPosition(glm::vec2 _NewPosition);
	void Rotate(float fAngle);
	void SetRotation(float _fRotation);

	virtual void SetActive(bool _bIsActive);
	bool IsActive() { return bActive; };

	glm::vec2 GetPosition();

	float fRotation;
	glm::vec4 Colour;

protected:
	bool bActive = true;
	glm::vec2 position;
};

