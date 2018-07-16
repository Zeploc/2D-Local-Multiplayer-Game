//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name    	:    Pyramid.cpp
// Description    	:    Pyramid Mesh
// Author       	:    Alex Coultas
// Mail         	:    alex.cou7417@mediadesign.school.nz
//

// This Includes //
#include "Lighting.h"

// OpenGL Includes //
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

// Local Includes //
#include "Camera.h"

// Static variables //
glm::vec3 Lighting::m_v3SunDirection = {15, 2, 25 };

/************************************************************
#--Description--#:  Constructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	Takes contructor values
#--Return--#: 		NA
************************************************************/
Lighting::Lighting()
{
}

/************************************************************
#--Description--#:  Destructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	NA
#--Return--#: 		NA
************************************************************/
Lighting::~Lighting()
{
}

void Lighting::PassLightingToShader(GLuint program, LightInfo _LightInfo, Utils::Transform ModelTransform)
{
	glm::mat4 translate = glm::translate(glm::mat4(), ModelTransform.Position);
	glm::mat4 scale = glm::scale(glm::mat4(), ModelTransform.Scale);
	glm::mat4 rotation = glm::rotate(glm::mat4(), glm::radians(ModelTransform.Rotation.x), glm::vec3(1, 0, 0));
	rotation = glm::rotate(rotation, glm::radians(ModelTransform.Rotation.y), glm::vec3(0, 1, 0));
	rotation = glm::rotate(rotation, glm::radians(ModelTransform.Rotation.z), glm::vec3(0, 0, 1));
	glm::mat4 model = translate * rotation * scale;

	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniform3fv(glGetUniformLocation(program, "lightPos"), 1, glm::value_ptr(Lighting::m_v3SunDirection));
	glUniform3fv(glGetUniformLocation(program, "camPos"), 1, glm::value_ptr(Camera::GetInstance()->GetCameraPosition()));
	glUniform3fv(glGetUniformLocation(program, "lightColor"), 1, glm::value_ptr(_LightInfo.v3LightColour));
	glUniform1f(glGetUniformLocation(program, "ambientStr"), _LightInfo.fAmbientStrength);
	glUniform1f(glGetUniformLocation(program, "lightSpecStr"), _LightInfo.fLightSpecStrength);
	glUniform1f(glGetUniformLocation(program, "shininess"), _LightInfo.fShininess);

}
