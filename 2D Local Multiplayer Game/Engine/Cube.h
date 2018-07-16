//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name    	:    Cube.h
// Description    	:    Header file outlining the Class
// Author       	:    Alex Coultas
// Mail         	:    alex.cou7417@mediadesign.school.nz
//

#pragma once
// This Includes //
#include "Mesh.h"

class Cube :	public Mesh
{
public:
	Cube(float fWidth, float fHeight, float fDepth, glm::vec4 Colour);
	Cube(float fWidth, float fHeight, float fDepth, glm::vec4 Colour, const char *  TextureSource, glm::vec4 UVCoords = glm::vec4(0, 1, 0, 1));
	~Cube();

	void BindCube();
	void Rebind();
	void SetLit(bool _bIsLit);

	void Render(Utils::Transform Newtransform);
	void Update();	
};

