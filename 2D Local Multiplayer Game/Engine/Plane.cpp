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
#include "Plane.h"

// OpenGL Library //
#include <SOIL.h>

// Engine Includes //
#include "Utils.h"
#include "Shader.h"
#include "Time.h"

/************************************************************
#--Description--#:  Constructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	Takes contructor values
#--Return--#: 		NA
************************************************************/
Plane::Plane(float fWidth, float fHeight, glm::vec4  _Colour)
{
	m_fWidth = fWidth;
	m_fHeight = fHeight;
	float fHalfWidth = m_fWidth / 2;
	float fHalfHeight = m_fHeight / 2;
	Points[0] = { -fHalfWidth, fHalfHeight, 0 };
	Points[1] = { fHalfWidth, fHalfHeight, 0 };
	Points[2] = { fHalfWidth, -fHalfHeight, 0 };
	Points[3] = { -fHalfWidth, -fHalfHeight, 0 };
	m_iIndicies = 6;
	Colour = _Colour;
	TextureSource = "";
	bHasTexture = false;
	BindPlane();
	m_eShape = Utils::PLANE;
	program = Shader::Programs["BaseProgram"];

	SetInitialStates();
}

/************************************************************
#--Description--#:  Constructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	Takes contructor values
#--Return--#: 		NA
************************************************************/
Plane::Plane(float fWidth, float fHeight, glm::vec4 _Colour, const char * _TextureSource, glm::vec4 _UVCoords)
{
	m_fWidth = fWidth;
	m_fHeight = fHeight;
	float fHalfWidth = m_fWidth / 2;
	float fHalfHeight = m_fHeight / 2;
	Points[0] = { -fHalfWidth, fHalfHeight, 0 };
	Points[1] = { fHalfWidth, fHalfHeight, 0 };
	Points[2] = { fHalfWidth, -fHalfHeight, 0 };
	Points[3] = { -fHalfWidth, -fHalfHeight, 0 };
	m_iIndicies = 6;
	Colour = _Colour;
	TextureSource = _TextureSource;
	UVCoords = _UVCoords;
	bHasTexture = true;
	BindPlane();
	m_eShape = Utils::PLANE;
	program = Shader::Programs["BaseProgram"];

	SetInitialStates();
}

/************************************************************
#--Description--#:  Constructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	Takes contructor values
#--Return--#: 		NA
************************************************************/
Plane::Plane(float _fWidth, float _fHeight, glm::vec4 _Colour, const char * _TextureSource, glm::vec2 v2FrameCounts, int _iFPS)
{
	m_fWidth = _fWidth;
	m_fHeight = _fHeight;
	float fHalfWidth = m_fWidth / 2;
	float fHalfHeight = m_fHeight / 2;
	Points[0] = { -fHalfWidth, fHalfHeight, 0 };
	Points[1] = { fHalfWidth, fHalfHeight, 0 };
	Points[2] = { fHalfWidth, -fHalfHeight, 0 };
	Points[3] = { -fHalfWidth, -fHalfHeight, 0 };
	m_iIndicies = 6;
	Colour = _Colour;
	TextureSource = _TextureSource;
	bHasTexture = true;
	AnimationInfo.iFPS = _iFPS;
	m_fFrameCheck = 1.0f / AnimationInfo.iFPS;
	CollisionBox.fHeight = m_fHeight;
	CollisionBox.fWidth = m_fWidth;
	m_eShape = Utils::PLANE;

	// Get Image Dimensions
	int width, height;
	unsigned char* image = SOIL_load_image(_TextureSource, &width, &height, 0, SOIL_LOAD_RGBA);
	SOIL_free_image_data(image);
	AnimationInfo.v2FrameCount = v2FrameCounts;
	AnimationInfo.v2EndFrame = v2FrameCounts;
	AnimationInfo.v2FrameSize = { (width / v2FrameCounts.x) / width, (height / v2FrameCounts.y) / height };

	UVCoords = glm::vec4(0, AnimationInfo.v2FrameSize.x, 0, AnimationInfo.v2FrameSize.y);

	BindPlane();
	program = Shader::Programs["BaseProgram"];

	SetInitialStates();
}

/************************************************************
#--Description--#:  Constructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	Takes contructor values
#--Return--#: 		NA
************************************************************/
Plane::Plane(float _fWidth, float _fHeight, glm::vec4 _Colour, const char * _TextureSource, int iCount, bool bHorizontal)
{
	m_fWidth = _fWidth;
	m_fHeight = _fHeight;
	float fHalfWidth = m_fWidth / 2;
	float fHalfHeight = m_fHeight / 2;
	Points[0] = { -fHalfWidth, fHalfHeight, 0 };
	Points[1] = { fHalfWidth, fHalfHeight, 0 };
	Points[2] = { fHalfWidth, -fHalfHeight, 0 };
	Points[3] = { -fHalfWidth, -fHalfHeight, 0 };
	m_iIndicies = 6;
	Colour = _Colour;
	TextureSource = _TextureSource;
	bHasTexture = true;
	CollisionBox.fHeight = m_fHeight;
	CollisionBox.fWidth = m_fWidth;
	m_eShape = Utils::PLANE;

	int width, height;
	unsigned char* image = SOIL_load_image(_TextureSource, &width, &height, 0, SOIL_LOAD_RGBA);
	SOIL_free_image_data(image);
	float fImageRatio = (float)width / (float)height;
	float fObjectRatio = _fHeight / _fWidth;
	float hSize = (float)(iCount);
	float vSize = (float)(iCount);
	if (bHorizontal)
	{
		vSize = iCount * fObjectRatio * fImageRatio;
	}
	else
	{
		hSize = iCount / fObjectRatio / fImageRatio;
	}

	UVCoords = glm::vec4(0, hSize, 0, vSize);
	BindPlane();
	program = Shader::Programs["BaseProgram"];

	SetInitialStates();
}

Plane::Plane(glm::vec3 _Points[4], glm::vec4 _Colour)
{
	for (int i = 0; i < 4; i++)
	{
		Points[i] = _Points[i];
	}


	m_fWidth = abs(Points[0].x - Points[2].x);
	m_fHeight = abs(Points[1].y - Points[3].y);
	m_iIndicies = 6;
	Colour = _Colour;
	TextureSource = "";
	bHasTexture = false;
	BindPlane();
	m_eShape = Utils::PLANE;
	program = Shader::Programs["BaseProgram"];

	SetInitialStates();
}

Plane::Plane(glm::vec3 _Points[4], glm::vec4 _Colour, const char * _TextureSource, glm::vec4 _UVCoords)
{
	for (int i = 0; i < 4; i++)
	{
		Points[i] = _Points[i];
	}
		

	m_fWidth = abs(Points[0].x - Points[2].x);
	m_fHeight = abs(Points[1].y - Points[3].y);
	m_iIndicies = 6;
	Colour = _Colour;
	TextureSource = _TextureSource;
	UVCoords = _UVCoords;
	bHasTexture = true;
	BindPlane();
	m_eShape = Utils::PLANE;
	program = Shader::Programs["BaseProgram"];

	SetInitialStates();
}

Plane::Plane(glm::vec3 _Points[4], glm::vec4 _Colour, const char * _TextureSource, int iCount, bool bHorizontal)
{
	for (int i = 0; i < 4; i++)
	{
		Points[i] = _Points[i];
	}


	m_fWidth = abs(Points[0].x - Points[2].x);
	m_fHeight = abs(Points[1].y - Points[3].y);
	float fHalfWidth = m_fWidth / 2;
	float fHalfHeight = m_fHeight / 2;
	m_iIndicies = 6;
	Colour = _Colour;
	TextureSource = _TextureSource;
	bHasTexture = true;
	CollisionBox.fHeight = m_fHeight;
	CollisionBox.fWidth = m_fWidth;
	m_eShape = Utils::PLANE;

	int width, height;
	unsigned char* image = SOIL_load_image(_TextureSource, &width, &height, 0, SOIL_LOAD_RGBA);
	SOIL_free_image_data(image);
	float fImageRatio = (float)width / (float)height;
	float fObjectRatio = m_fHeight / m_fWidth;
	float hSize = (float)(iCount);
	float vSize = (float)(iCount);
	if (bHorizontal)
	{
		vSize = iCount * fObjectRatio * fImageRatio;
	}
	else
	{
		hSize = iCount / fObjectRatio / fImageRatio;
	}

	UVCoords = glm::vec4(0, hSize, 0, vSize);
	BindPlane();
	program = Shader::Programs["BaseProgram"];

	SetInitialStates();
}

/************************************************************
#--Description--#:  Destructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	NA
#--Return--#: 		NA
************************************************************/
Plane::~Plane()
{
}

/************************************************************
#--Description--#: 	Binds plane with sepcified attributes
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void Plane::BindPlane()
{
	float fHalfWidth = m_fWidth / 2;
	float fHalfHeight = m_fHeight / 2;
	
	GLfloat vertices[] = {
		// Positions						// Colors									// Tex Coords
		Points[0].x, Points[0].y, Points[0].z,		Colour.r, Colour.g, Colour.b, Colour.a,		// Top Left
		Points[1].x, Points[1].y, Points[1].z,		Colour.r, Colour.g, Colour.b, Colour.a,		// Top Right
		Points[2].x, Points[2].y, Points[2].z,		Colour.r, Colour.g, Colour.b, Colour.a,		// Bottom Right
		Points[3].x, Points[3].y, Points[3].z,		Colour.r, Colour.g, Colour.b, Colour.a,		// Bottom Left
	};

	GLfloat Texturedvertices[] = {
		// Positions						// Colors									// Tex Coords
		Points[0].x, Points[0].y, Points[0].z,		Colour.r, Colour.g, Colour.b, Colour.a,		UVCoords.x, UVCoords.z,	// Top Left
		Points[1].x, Points[1].y, Points[1].z,		Colour.r, Colour.g, Colour.b, Colour.a,		UVCoords.y, UVCoords.z, // Top Right
		Points[2].x, Points[2].y, Points[2].z,		Colour.r, Colour.g, Colour.b, Colour.a,		UVCoords.y, UVCoords.w, // Bottom Right
		Points[3].x, Points[3].y, Points[3].z,		Colour.r, Colour.g, Colour.b, Colour.a,		UVCoords.x, UVCoords.w, // Bottom Left
	};

	GLuint indices[] = {
		0, 1, 2, // First Triangle
		0, 2, 3 // Second Triangle
	};
	// If no texture, texture source is equal to ""
	vao = Shader::CreateBuffer(TextureSource, texture, true);
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
void Plane::Rebind()
{
	BindPlane();
}

void Plane::SetInitialStates()
{
	Mesh::SetInitialStates();
	// Set plane specific states
	m_PlaneInitialState.AnimationInfo = AnimationInfo;
	m_PlaneInitialState.m_dFPSCounter = m_dFPSCounter;
	m_PlaneInitialState.m_fFrameCheck = m_fFrameCheck;
	m_PlaneInitialState.CollisionBox = CollisionBox;
}

void Plane::Reset()
{
	Mesh::Reset();
	// Reset plane specific states
	AnimationInfo = m_PlaneInitialState.AnimationInfo;
	m_dFPSCounter = m_PlaneInitialState.m_dFPSCounter;
	m_fFrameCheck = m_PlaneInitialState.m_fFrameCheck;
	CollisionBox = m_PlaneInitialState.CollisionBox;
}

/************************************************************
#--Description--#:	Render Current Mesh to the screen
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void Plane::Render(Utils::Transform Newtransform)
{
	if (m_fFrameCheck > 0)
	{
		m_dFPSCounter += Time::dTimeDelta;
		if (m_dFPSCounter > m_fFrameCheck)
		{
			m_dFPSCounter = 0;// m_dFPSCounter - m_fFrameCheck;
			AnimationInfo.Advance();
		}
	}
	if (bHasTexture)
	{
		glUseProgram(program);
		glEnable(GL_BLEND);
		GLint UVCoordsLoc = glGetUniformLocation(Shader::Programs["BaseProgram"], "uTexCoordOffset");
		glUniform2f(UVCoordsLoc, AnimationInfo.v2CurrentFrame.x * AnimationInfo.v2FrameSize.x, AnimationInfo.v2CurrentFrame.y * AnimationInfo.v2FrameSize.y);
	}
	else
	{
		glUseProgram(program);
		glDisable(GL_BLEND);
	}
	glFrontFace(GL_CW);
	Mesh::Render(Newtransform);
}

/************************************************************
#--Description--#: 	Updated every frame
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void Plane::Update()
{
	if (m_fFrameCheck > 0) // Doesn't run, framecheck is 0?
	{
		m_dFPSCounter += Time::dTimeDelta;
		if (m_dFPSCounter > m_fFrameCheck)
		{
			m_dFPSCounter = 0;// m_dFPSCounter - m_fFrameCheck;
			AnimationInfo.Advance();
		}
	}
}
