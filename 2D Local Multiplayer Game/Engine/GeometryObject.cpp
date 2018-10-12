//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name    	:    Level.cpp
// Description    	:    Plane Mesh
// Author       	:    Alex Coultas
// Mail         	:    alex.cou7417@mediadesign.school.nz
//

// This Includes //
#include "GeometryObject.h"

// OpenGL Library //
#include <SOIL.h>

// Engine Includes //
#include "Utils.h"
#include "Shader.h"
#include "Time.h"
#include "Camera.h"

/************************************************************
#--Description--#:  Constructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	Takes contructor values
#--Return--#: 		NA
************************************************************/
GeometryObject::GeometryObject(glm::vec4  _Colour)
{
	m_fWidth = 1;
	m_fHeight = 1;
	m_iIndicies = 1;
	Colour = _Colour;
	TextureSource = "";
	bHasTexture = false;
	BindGeometryObject();
	m_eShape = Utils::GEOMETRY;
	program = Shader::Programs["GeometryShader"];

	SetInitialStates();
}

/************************************************************
#--Description--#:  Destructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	NA
#--Return--#: 		NA
************************************************************/
GeometryObject::~GeometryObject()
{
}

/************************************************************
#--Description--#: 	Binds plane with sepcified attributes
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void GeometryObject::BindGeometryObject()
{
	
	GLfloat vertices[] = {
		// Position						// Color		
		0.0f, 0.0f, 0.0f,				 Colour.r, Colour.g, Colour.b, Colour.a, //passing in 1 point
	};

	// If no texture, texture source is equal to ""
	vao = Shader::CreateBuffer("", texture, true);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

}

/************************************************************
#--Description--#: 	Rebinds the vao with the colour (not texture)
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void GeometryObject::Rebind()
{
	BindGeometryObject();
}


/************************************************************
#--Description--#:	Render Current Mesh to the screen
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void GeometryObject::Render(Utils::Transform Newtransform)
{
	glUseProgram(program);
	if (bHasTexture)
	{
		glEnable(GL_BLEND);
	}
	else
	{
		glDisable(GL_BLEND);
	}
	glFrontFace(GL_CW);
	glDisable(GL_CULL_FACE);
	//Mesh::Render(Newtransform);

	Camera::GetInstance()->SetMVP(Newtransform, program);

	glBindVertexArray(vao);
	glDrawArrays(GL_POINTS, 0, 1);
	glBindVertexArray(0);
}

