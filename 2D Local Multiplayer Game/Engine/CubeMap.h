//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name    	:    UIManager.h
// Description    	:    Header file outlining the Class
// Author       	:    Alex Coultas
// Mail         	:    alex.cou7417@mediadesign.school.nz
//
#pragma once
// Local Includes
#include "Mesh.h"

class CubeMap :	public Mesh
{
public:
	CubeMap(float fWidth, float fHeight, float fDepth, char *  TextureSources[6]);
	~CubeMap();
	
	void BindCubeMap();
	void Rebind();

	void Render(Utils::Transform Newtransform);
	void Update();

	char * TextureSources[6];


};

