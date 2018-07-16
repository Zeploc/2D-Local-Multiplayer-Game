//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name    	:    Lighting.h
// Description    	:    Header file outlining the Class
// Author       	:    Alex Coultas
// Mail         	:    alex.cou7417@mediadesign.school.nz
//

// OpenGL Library //
#include <glm\common.hpp>
#include <glew.h>
#include <freeglut.h>

// Local Libraries //
#include "Utils.h"

struct LightInfo
{
	glm::vec3 v3AmbientColour = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 v3LightColour = glm::vec3(1.0f, 1.0f, 1.0f);
	float fAmbientStrength = 0.1f;
	float fLightSpecStrength = 1.0f;
	float fShininess = 32.0f;
};

#pragma once
class Lighting
{
public:
	Lighting();
	~Lighting();

	static glm::vec3 m_v3SunDirection;

	static void PassLightingToShader(GLuint program, LightInfo _LightInfo, Utils::Transform ModelTransform);
};

