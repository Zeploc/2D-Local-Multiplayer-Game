//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name    	:    Plane.h
// Description    	:    Header file outlining the Class
// Author       	:    Alex Coultas
// Mail         	:    alex.cou7417@mediadesign.school.nz
//

#pragma once
// This Includes //
#include "Mesh.h"

class FrameBuffer : public Mesh
{
public:
	FrameBuffer();

	~FrameBuffer();

	void BindFrameBuffer();
	void Rebind();

	void Render();

	GLuint renderTexture;
	GLuint framebuffer;

	
};

