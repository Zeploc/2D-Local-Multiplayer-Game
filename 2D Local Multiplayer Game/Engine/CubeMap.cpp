//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name    	:    Level.cpp
// Description    	:    main implementation for Level
// Author       	:    Alex Coultas
// Mail         	:    alex.cou7417@mediadesign.school.nz
//

// This Includes //
#include "CubeMap.h"

// Local Includes //

// Engine Includes //
#include "Shader.h"
#include "Camera.h"

// OpenGL Includes //
#include <SOIL.h>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

/************************************************************
#--Description--#:  Constructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	Takes contructor values
#--Return--#: 		NA
************************************************************/
CubeMap::CubeMap(float fWidth, float fHeight, float fDepth, char *  _TextureSources[6])
{
	TextureSources[0] = _TextureSources[0];
	TextureSources[1] = _TextureSources[1];
	TextureSources[2] = _TextureSources[2];
	TextureSources[3] = _TextureSources[3];
	TextureSources[4] = _TextureSources[4];
	TextureSources[5] = _TextureSources[5];
	m_iIndicies = 36;
	m_fWidth = fWidth;
	m_fHeight = fHeight;
	m_fDepth = fDepth;
	bHasTexture = false;
	m_eShape = Utils::CUBE;
	BindCubeMap();
	program = Shader::Programs["CubeMapProgram"];
}


/************************************************************
#--Description--#:  Destructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	NA
#--Return--#: 		NA
************************************************************/
CubeMap::~CubeMap()
{
}

/************************************************************
#--Description--#: 	Binds pyramid with sepcified attributes
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void CubeMap::BindCubeMap()
{
	float fHalfWidth = m_fWidth / 2;
	float fHalfHeight = m_fHeight / 2;
	float fHalfDepth = m_fDepth / 2;

	GLfloat vertices[] = {
		// Positions								// Colors			
		// Front Face
		-fHalfWidth, fHalfHeight, fHalfDepth,	
		fHalfWidth, fHalfHeight, fHalfDepth,	
		fHalfWidth, -fHalfHeight, fHalfDepth,	
		-fHalfWidth, -fHalfHeight, fHalfDepth,	
		// Right Face
		fHalfWidth, fHalfHeight, fHalfDepth,	
		fHalfWidth, fHalfHeight, -fHalfDepth,	
		fHalfWidth, -fHalfHeight, -fHalfDepth,	
		fHalfWidth, -fHalfHeight, fHalfDepth,	
		// Back Face
		fHalfWidth, fHalfHeight, -fHalfDepth,	
		-fHalfWidth, fHalfHeight, -fHalfDepth,	
		-fHalfWidth, -fHalfHeight, -fHalfDepth,	
		fHalfWidth, -fHalfHeight, -fHalfDepth,	
		// Left Face
		-fHalfWidth, fHalfHeight, -fHalfDepth,	
		-fHalfWidth, fHalfHeight, fHalfDepth,	
		-fHalfWidth, -fHalfHeight, fHalfDepth,	
		-fHalfWidth, -fHalfHeight, -fHalfDepth,	
		// Top Face
		-fHalfWidth, fHalfHeight, -fHalfDepth,	
		fHalfWidth, fHalfHeight, -fHalfDepth,	
		fHalfWidth, fHalfHeight, fHalfDepth,	
		-fHalfWidth, fHalfHeight, fHalfDepth,	
		// Bottom Face
		-fHalfWidth, -fHalfHeight, fHalfDepth,	
		fHalfWidth, -fHalfHeight, fHalfDepth,	
		fHalfWidth, -fHalfHeight, -fHalfDepth,	
		-fHalfWidth, -fHalfHeight, -fHalfDepth	
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
	GLuint vbo;
	GLuint ebo;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	int width, height;
	unsigned char* image;
	for (GLuint i = 0; i < 6; i++)
	{
		std::string fullPathName = "Resources/Textures/CubeMap/";
		fullPathName.append(TextureSources[i]);
		image = SOIL_load_image(fullPathName.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB,	width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);	
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

/************************************************************
#--Description--#: 	Rebinds the vao with the colour (not texture)
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void CubeMap::Rebind()
{
	BindCubeMap();
}

/************************************************************
#--Description--#:	Render Current Mesh to the screen
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void CubeMap::Render(Utils::Transform Newtransform)
{
	glUseProgram(program);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	glDisable(GL_CULL_FACE);
	//glDisable(GL_BLEND);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
	glUniform1i(glGetUniformLocation(Shader::Programs["CubeMapProgram"], "cubeSampler"), 0);

	Camera::GetInstance()->SetMVP(Newtransform, program);
	
	glActiveTexture(GL_TEXTURE1);
	glUniform1i(glGetUniformLocation(program, "skybox"), 1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, m_iIndicies, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glDisable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}

/************************************************************
#--Description--#: 	Updated every frame
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void CubeMap::Update()
{
}