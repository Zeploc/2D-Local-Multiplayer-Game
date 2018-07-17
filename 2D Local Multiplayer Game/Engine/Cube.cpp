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
#include "Cube.h"

// Engine Includes //
#include "Shader.h"

/************************************************************
#--Description--#:  Constructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	Takes contructor values
#--Return--#: 		NA
************************************************************/
Cube::Cube(float fWidth, float fHeight, float fDepth, glm::vec4 _Colour)
{
	m_fWidth = fWidth;
	m_fHeight = fHeight;
	m_fDepth = fDepth;
	Colour = _Colour;
	UVCoords = glm::vec4(0, 1, 0, 1);
	TextureSource = "";
	bHasTexture = false;
	m_iIndicies = 36;
	BindCube();
	m_eShape = Utils::CUBE;
	program = Shader::Programs["program"];

	SetInitialStates();
}

/************************************************************
#--Description--#:  Constructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	Takes contructor values
#--Return--#: 		NA
************************************************************/
Cube::Cube(float fWidth, float fHeight, float fDepth, glm::vec4 _Colour, const char * _TextureSource, glm::vec4 _UVCoords)
{
	m_fWidth = fWidth;
	m_fHeight = fHeight;
	m_fDepth = fDepth;
	Colour = _Colour;
	TextureSource = _TextureSource;
	UVCoords = _UVCoords;
	bHasTexture = true;
	m_iIndicies = 36;
	BindCube();
	m_eShape = Utils::CUBE;
	program = Shader::Programs["Textureprogram"];

	SetInitialStates();
}

/************************************************************
#--Description--#:  Destructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	NA
#--Return--#: 		NA
************************************************************/
Cube::~Cube()
{
}

/************************************************************
#--Description--#: 	Binds pyramid with sepcified attributes
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void Cube::BindCube()
{
	float fHalfWidth = m_fWidth / 2;
	float fHalfHeight = m_fHeight / 2;
	float fHalfDepth = m_fDepth / 2;
	
	GLfloat Texturedvertices[] = {
		// Positions								// Colors									// UV Cords		// Normals
		// Front Face
		-fHalfWidth, fHalfHeight, fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		0.0f, 0.0f,		0.0f, 0.0f, 1.0f,
		fHalfWidth, fHalfHeight, fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		1.0f, 0.0f,		0.0f, 0.0f, 1.0f,
		fHalfWidth, -fHalfHeight, fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		1.0f, 1.0f,		0.0f, 0.0f, 1.0f,
		-fHalfWidth, -fHalfHeight, fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		0.0f, 1.0f,		0.0f, 0.0f, 1.0f,
		// Right Face
		fHalfWidth, fHalfHeight, fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		0.0f, 0.0f,		1.0f, 0.0f, 0.0f,
		fHalfWidth, fHalfHeight, -fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		1.0f, 0.0f,		1.0f, 0.0f, 0.0f,
		fHalfWidth, -fHalfHeight, -fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		1.0f, 1.0f,		1.0f, 0.0f, 0.0f,
		fHalfWidth, -fHalfHeight, fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		0.0f, 1.0f,		1.0f, 0.0f, 0.0f,
		// Back Face
		fHalfWidth, fHalfHeight, -fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		0.0f, 0.0f,		0.0f, 0.0f, -1.0f,
		-fHalfWidth, fHalfHeight, -fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		1.0f, 0.0f,		0.0f, 0.0f, -1.0f,
		-fHalfWidth, -fHalfHeight, -fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		1.0f, 1.0f,		0.0f, 0.0f, -1.0f,
		fHalfWidth, -fHalfHeight, -fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		0.0f, 1.0f,		0.0f, 0.0f, -1.0f,
		// Left Face
		-fHalfWidth, fHalfHeight, -fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		0.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
		-fHalfWidth, fHalfHeight, fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		1.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
		-fHalfWidth, -fHalfHeight, fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		1.0f, 1.0f,		-1.0f, 0.0f, 0.0f,
		-fHalfWidth, -fHalfHeight, -fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		0.0f, 1.0f,		-1.0f, 0.0f, 0.0f,
		// Top Face
		-fHalfWidth, fHalfHeight, -fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
		fHalfWidth, fHalfHeight, -fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f,
		fHalfWidth, fHalfHeight, fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
		-fHalfWidth, fHalfHeight, fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
		// Bottom Face
		-fHalfWidth, -fHalfHeight, fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		fHalfWidth, -fHalfHeight, fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		1.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		fHalfWidth, -fHalfHeight, -fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		1.0f, 1.0f,		0.0f, -1.0f, 0.0f,
		-fHalfWidth, -fHalfHeight, -fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		0.0f, 1.0f,		0.0f, -1.0f, 0.0f

	};
	GLfloat vertices[] = {
		// Positions								// Colors									// Normals
		// Front Face
		-fHalfWidth, fHalfHeight, fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		1.0f, 0.0f, 1.0f,
		fHalfWidth, fHalfHeight, fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		0.0f, 0.0f, 1.0f,
		fHalfWidth, -fHalfHeight, fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		0.0f, 0.0f, 1.0f,
		-fHalfWidth, -fHalfHeight, fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		0.0f, 0.0f, 1.0f,
		// Right Face
		fHalfWidth, fHalfHeight, fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		1.0f, 0.0f, 0.0f,
		fHalfWidth, fHalfHeight, -fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		1.0f, 0.0f, 0.0f,
		fHalfWidth, -fHalfHeight, -fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		1.0f, 0.0f, 0.0f,
		fHalfWidth, -fHalfHeight, fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		1.0f, 0.0f, 0.0f,
		// Back Face
		fHalfWidth, fHalfHeight, -fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		0.0f, 0.0f, -1.0f,
		-fHalfWidth, fHalfHeight, -fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		0.0f, 0.0f, -1.0f,
		-fHalfWidth, -fHalfHeight, -fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		0.0f, 0.0f, -1.0f,
		fHalfWidth, -fHalfHeight, -fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		0.0f, 0.0f, -1.0f,
		// Left Face
		-fHalfWidth, fHalfHeight, -fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		-1.0f, 0.0f, 0.0f,
		-fHalfWidth, fHalfHeight, fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		-1.0f, 0.0f, 0.0f,
		-fHalfWidth, -fHalfHeight, fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		-1.0f, 0.0f, 0.0f,
		-fHalfWidth, -fHalfHeight, -fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		-1.0f, 0.0f, 0.0f,
		// Top Face
		-fHalfWidth, fHalfHeight, -fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		0.0f, 1.0f, 0.0f,
		fHalfWidth, fHalfHeight, -fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		0.0f, 1.0f, 0.0f,
		fHalfWidth, fHalfHeight, fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		0.0f, 1.0f, 0.0f,
		-fHalfWidth, fHalfHeight, fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		0.0f, 1.0f, 0.0f,
		// Bottom Face
		-fHalfWidth, -fHalfHeight, fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		0.0f, -1.0f, 0.0f,
		fHalfWidth, -fHalfHeight, fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		0.0f, -1.0f, 0.0f,
		fHalfWidth, -fHalfHeight, -fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		0.0f, -1.0f, 0.0f,
		-fHalfWidth, -fHalfHeight, -fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		0.0f, -1.0f, 0.0f


	};

	GLuint indices[] = {
		// Front Face
		0, 1, 2,
		0, 2, 3,
		// Right Face
		4, 5, 6,
		4, 6, 7,
		// Back Face
		8, 9, 10,
		8, 10, 11,
		// Left Face
		12, 13, 14,
		12, 14, 15,
		// Top Face
		16, 17, 18,
		16, 18, 19, 
		// Bottom Face
		20, 21, 22,
		20, 22, 23
	};

	vao = Shader::CreateBuffer(TextureSource, texture, true, true);
	if (TextureSource != "")
		glBufferData(GL_ARRAY_BUFFER, sizeof(Texturedvertices), Texturedvertices, GL_STATIC_DRAW);
	else
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

/************************************************************
#--Description--#: 	Rebinds the vao with the colour (not texture)
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void Cube::Rebind()
{
	BindCube();
}


void Cube::SetLit(bool _bIsLit)
{
	Mesh::SetLit(_bIsLit);
	if (bIsLit)
	{
		program = Shader::Programs["LitTextureprogram"];
	}
	else
	{
		if (bHasTexture)
		{
			program = Shader::Programs["Textureprogram"];
		}
		else
		{
			program = Shader::Programs["program"];
		}
	}
}

/************************************************************
#--Description--#:	Render Current Mesh to the screen
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void Cube::Render(Utils::Transform Newtransform)
{
	glUseProgram(program);
	glFrontFace(GL_CW);
	glUniform1i(glGetUniformLocation(program, "bIsTex"), bHasTexture);
	Lighting::PassLightingToShader(program, LightProperties, Newtransform);
	if (bHasTexture)
	{
		glEnable(GL_BLEND);
	}
	else
	{
		//glDisable(GL_BLEND);
	}
	Mesh::Render(Newtransform);
}

/************************************************************
#--Description--#: 	Updated every frame
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void Cube::Update()
{
}
