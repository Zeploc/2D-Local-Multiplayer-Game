
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name		:    UIImage.h
// Description		:    Header file outlining the Class
// Author			:    Alex Coultas
// Mail				:    alex.cou7417@mediadesign.school.nz
//


#pragma once

// OpenGL Library Includes //
#include <glew.h>
#include <freeglut.h>

// Engine Includes //
#include "Utils.h"
#include "UIElement.h"

class UIImage :	public UIElement
{
public:	
	UIImage(glm::vec2 _Position, Utils::EANCHOR _anchor, float _fRotation, glm::vec4 _Colour, int _iWidth, int _iHeight);
	UIImage(glm::vec2 _Position, Utils::EANCHOR _anchor, float _fRotation, glm::vec4 _Colour, int _iWidth, int _iHeight, const char *  TextureSource, int _DrawMode);
	~UIImage();

	void DrawUIElement();
	Utils::EANCHOR GetAnchor() { return ImageAnchor; };
	int GetWidth() { return iWidth; };
	int GetHeight() { return iHeight; };

	static glm::vec2 GetPositionFromAnchor(glm::vec2 _Position, Utils::EANCHOR _anchor, int _iWidth, int _iHeight);

private:
	GLuint VAO;
	GLuint texture;

	bool bHasTexture = false;
	Utils::EANCHOR ImageAnchor;
	int iWidth;
	int iHeight;
};

