//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name    	:    Cube.cpp
// Description    	:    Cube Mesh
// Author       	:    Alex Coultas
// Mail         	:    alex.cou7417@mediadesign.school.nz
//

// This Includes //
#include "Triangle.h"

// Engine Includes //
#include "Shader.h"


/************************************************************
#--Description--#:  Constructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	Takes contructor values
#--Return--#: 		NA
************************************************************/
Triangle::Triangle(glm::vec3 _Point1, glm::vec3 _Point2, glm::vec3 _Point3, glm::vec4 _Colour)
{
	Point1 = _Point1;
	Point2 = _Point2;
	Point3 = _Point3;
	glm::vec3 CenterPoint;
	CenterPoint.x = (Point1.x + Point2.x + Point3.x) / 3;
	CenterPoint.y = (Point1.y + Point2.y + Point3.y) / 3;
	CenterPoint.z = (Point1.z + Point2.z + Point3.z) / 3;
	m_fWidth = glm::length(CenterPoint - Point1);
	m_fHeight = m_fWidth;
	m_fDepth = 0;
	Colour = _Colour;
	TextureSource = "";
	bHasTexture = false;
	m_iIndicies = 3;
	BindTriangle();
	m_eShape = Utils::TRIANGLE;
	program = Shader::Programs["BaseProgram"];

	SetInitialStates();
}

Triangle::Triangle(glm::vec3 CenterPoint, float Width, glm::vec4 _Colour)
{
	Point1 = CenterPoint + glm::vec3(0, Width, 0);
	Point2 = CenterPoint + glm::vec3(1, -0.5, 0) * Width;
	Point3 = CenterPoint + glm::vec3(-1, -0.5, 0) * Width;
	m_fWidth = Width;
	m_fHeight = Width;
	m_fDepth = 0;
	Colour = _Colour;
	TextureSource = "";
	bHasTexture = false;
	m_iIndicies = 3;
	BindTriangle();
	m_eShape = Utils::TRIANGLE;
	program = Shader::Programs["BaseProgram"];

	SetInitialStates();
}

/************************************************************
#--Description--#:  Destructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	NA
#--Return--#: 		NA
************************************************************/
Triangle::~Triangle()
{
}

void Triangle::BindTriangle()
{
	GLfloat vertices[] = {
		// Positions								// Colors									// Normals
		Point1.x, Point1.y, Point1.z,		Colour.r, Colour.g, Colour.b, Colour.a,//		1.0f, 0.0f, 1.0f,
		Point2.x, Point2.y, Point2.z,		Colour.r, Colour.g, Colour.b, Colour.a,//		0.0f, 0.0f, 1.0f,
		Point3.x, Point3.y, Point3.z,		Colour.r, Colour.g, Colour.b, Colour.a,	//	0.0f, 0.0f, 1.0f,
	};

	GLuint indices[] =
	{
		0, 1, 2,
	};

	vao = Shader::CreateBuffer(TextureSource, texture, true, false);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void Triangle::Rebind()
{
	BindTriangle();
}

void Triangle::Render(Utils::Transform Newtransform)
{
	glUseProgram(program);
	glFrontFace(GL_CW);
	glUniform1i(glGetUniformLocation(program, "bIsTex"), bHasTexture);
	Lighting::PassLightingToShader(program, LightProperties, Newtransform);
	glDisable(GL_BLEND);
	Mesh::Render(Newtransform);
}

void Triangle::Update()
{
}
