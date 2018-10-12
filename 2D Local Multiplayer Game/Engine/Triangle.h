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

class Triangle : public Mesh
{
public:
	Triangle(glm::vec3 _Point1, glm::vec3 _Point2, glm::vec3 _Point3, glm::vec4 Colour);
	Triangle(glm::vec3 CenterPoint, float Width, glm::vec4 Colour);
	~Triangle();

	void BindTriangle();
	virtual void Rebind();

	virtual void Render(Utils::Transform Newtransform) override;
	virtual void Update();

	glm::vec3 Point1;
	glm::vec3 Point2;
	glm::vec3 Point3;
};

