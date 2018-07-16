//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name    	:    Shader.cpp
// Description    	:    main implementation for Shader
// Author       	:    Alex Coultas
// Mail         	:    alex.cou7417@mediadesign.school.nz
//

// Library Includes //
#include <map>
#include <iostream>

// OpenGL Library Includes //
#include <soil\SOIL.h>
#include <ft2build.h>
#include FT_FREETYPE_H

// Engine Includes //
#include "ModelObject.h"
#include "LogManager.h"

// Local Includes //

// This Includes //
#include "Shader.h"


// Static Variables //
//GLuint Shader::program;
//GLuint Shader::Textureprogram;
//GLuint Shader::TextUIprogram;
//GLuint Shader::UIprogram;
//GLuint Shader::LitTextureprogram;
//GLuint Shader::CubeMapProgram;
//GLuint Shader::ModelProgram;
//GLuint Shader::ModelProgramLit;
//GLuint Shader::ReflectionProgram;


std::map<std::string, std::shared_ptr<ModelObject>> Shader::Models;
std::map<const char *, GLuint> Shader::Textures;
std::map<std::string, GLuint> Shader::Programs;


/************************************************************
#--Description--#:  Constructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	Takes contructor values
#--Return--#: 		NA
************************************************************/
Shader::Shader()
{
}

/************************************************************
#--Description--#:  Destructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	NA
#--Return--#: 		NA
************************************************************/
Shader::~Shader()
{
	CleanUp();
}

void Shader::CleanUp()
{
	for (auto& Model : Models)
	{
		Model.second = nullptr;
	}
	Models.clear();
	Textures.clear();
}

void Shader::AddProgram(std::string VertexShaderPath, std::string FragmentShaderPath, std::string ShaderName)
{
	ShaderLoader loader;
	Programs.insert(std::pair<std::string, GLuint>(ShaderName, loader.CreateProgram(VertexShaderPath.c_str(), FragmentShaderPath.c_str())));
	LogManager::GetInstance()->DisplayLogMessage("Loading Shader \"" + ShaderName + "\"");
}

//GLuint Shader::BindPyramidArray(float fWidth, float fHeight, float fDepth, glm::vec4 Colour)
//{
//	float fHalfWidth = fWidth / 2;
//	float fHalfHeight = fHeight / 2;
//	float fHalfDepth = fDepth / 2;
//
//	GLfloat vertices[] = {
//		// Positions								// Colors			
//		-fHalfWidth, -fHalfHeight, -fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,
//		fHalfWidth, -fHalfHeight, -fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,
//		fHalfWidth, -fHalfHeight, fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,
//		-fHalfWidth, -fHalfHeight, fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,
//
//		0, fHalfHeight, 0,							Colour.r, Colour.g, Colour.b, Colour.a // Top Point
//
//	};
//
//	GLuint indices[] = {
//		0, 4, 3, // Side 1
//		3, 4, 2, // Side 2
//		2, 4, 1, // Side 3
//		1, 4, 0, // Side 4
//
//		3, 2, 1, // Bottom Triangle 1
//		3, 1, 0 // Bottom Triangle 1
//	};
//	GLuint TempTexture;
//
//	GLuint vao = CreateBuffer("", TempTexture);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//	return vao;
//}
//
//GLuint Shader::BindPyramidArray(float fWidth, float fHeight, float fDepth, glm::vec4 Colour, const char * TextureSource, GLuint & Texture, glm::vec4 UVCoords)
//{
//	float fHalfWidth = fWidth / 2;
//	float fHalfHeight = fHeight / 2;
//	float fHalfDepth = fDepth / 2;
//
//	GLfloat vertices[] = {
//		// Positions								// Colors			
//		-fHalfWidth, -fHalfHeight, -fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		UVCoords.x, UVCoords.z,
//		fHalfWidth, -fHalfHeight, -fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		UVCoords.y, UVCoords.z,
//		fHalfWidth, -fHalfHeight, fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		UVCoords.y, UVCoords.w,
//		-fHalfWidth, -fHalfHeight, fHalfDepth,		Colour.r, Colour.g, Colour.b, Colour.a,		UVCoords.x, UVCoords.w,
//
//		0, fHalfHeight, 0,							Colour.r, Colour.g, Colour.b, Colour.a,		UVCoords.y / 2, UVCoords.w,// Top Point
//
//	};
//
//	GLuint indices[] = {
//		0, 4, 3, // Side 1
//		3, 4, 2, // Side 2
//		2, 4, 1, // Side 3
//		1, 4, 0, // Side 4
//
//		3, 2, 1, // Bottom Triangle 1
//		3, 1, 0 // Bottom Triangle 1
//	};
//
//	GLuint vao = CreateBuffer(TextureSource, Texture);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//	return vao;
//}
//
//GLuint Shader::BindSphereArray(float fWidth, float fHeight, float fDepth, glm::vec4 Colour, int & IndiceCount)
//{
//	const int sections = 20;
//	const int vertexAttrib = 12;
//	const int indexPerQuad = 6;
//
//	double phi = 0;
//	double theta = 0;
//
//	float vertices[(sections) * (sections)* vertexAttrib];
//	int offset = 0;
//	for (int i = 0; i < sections; i++)
//	{
//		theta = 0;
//
//		for (int j = 0; j < sections; j++)
//		{
//			float x = cos(phi) * sin(theta);
//			float y = cos(theta);
//			float z = sin(phi) * sin(theta);
//
//			vertices[offset++] = x * fWidth;
//			vertices[offset++] = y * fHeight;
//			vertices[offset++] = z * fDepth;
//
//			vertices[offset++] = Colour.x;
//			vertices[offset++] = Colour.y;
//			vertices[offset++] = Colour.z;
//			vertices[offset++] = Colour.a;
//
//			vertices[offset++] = (float)i / (sections - 1);
//			vertices[offset++] = (float)j / (sections - 1);
//
//			vertices[offset++] = 0.0f;
//			vertices[offset++] = 0.0f;
//			vertices[offset++] = 1.0f;
//
//			theta += (3.14159265359 / (sections - 1));
//			//theta += (M_PI / (sections - 1));
//		}
//
//		//phi += (2 * M_PI) / (sections - 1);
//		phi += (2 * 3.14159265359) / (sections - 1);
//	}
//
//
//	GLuint indices[(sections) * (sections)* indexPerQuad];
//	offset = 0;
//	for (int i = 0; i < sections; i++)
//	{
//		for (int j = 0; j < sections; j++)
//		{
//			indices[offset++] = (((i + 1) % sections) * sections) + ((j + 1) % sections);
//			indices[offset++] = (((i + 1) % sections) * sections) + (j);
//			indices[offset++] = (i * sections) + (j);
//
//			indices[offset++] = (i * sections) + ((j + 1) % sections);
//			indices[offset++] = (((i + 1) % sections) * sections) + ((j + 1) % sections);
//			indices[offset++] = (i * sections) + (j);
//		}
//	}
//
//	GLuint VBO, EBO, VAO;
//
//	glGenVertexArrays(1, &VAO);
//	glBindVertexArray(VAO);
//
//	glGenBuffers(1, &VBO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	glGenBuffers(1, &EBO);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexAttrib * sizeof(GLfloat), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, vertexAttrib * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(1);
//
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertexAttrib * sizeof(GLfloat), (void*)(7 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(2);
//
//	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, vertexAttrib * sizeof(GLfloat), (void*)(9 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(3);
//
//	IndiceCount = sizeof(indices) / sizeof(GLuint);
//
//	return VAO;
//}
//
//GLuint Shader::BindSphereArray(float fWidth, float fHeight, float fDepth, glm::vec4 Colour, const char * TextureSource, GLuint & Texture, int& IndiceCount, glm::vec4 UVCoords)
//{
//	float radius = 1.0f;
//
//	const int sections = 30;
//	const int vertexAttrib = 12;
//	const int indexPerQuad = 6;
//
//	double phi = 0;
//	double theta = 0;
//
//	float vertices[(sections) * (sections)* vertexAttrib];
//	int offset = 0;
//	for (int i = 0; i < sections; i++)
//	{
//		theta = 0;
//
//		for (int j = 0; j < sections; j++)
//		{
//			float x = cos(phi) * sin(theta);
//			float y = cos(theta);
//			float z = sin(phi) * sin(theta);
//
//			vertices[offset++] = x * radius;
//			vertices[offset++] = y * radius;
//			vertices[offset++] = z * radius;
//
//			vertices[offset++] = Colour.r;
//			vertices[offset++] = Colour.g;
//			vertices[offset++] = Colour.b;
//			vertices[offset++] = Colour.a;
//
//			vertices[offset++] = (float)i / (sections - 1);
//			vertices[offset++] = (float)j / (sections - 1);
//
//			vertices[offset++] = x;
//			vertices[offset++] = y;
//			vertices[offset++] = z;
//
//			theta += (3.14159265359 / (sections - 1));
//			//theta += (M_PI / (sections - 1));
//		}
//
//		//phi += (2 * M_PI) / (sections - 1);
//		phi += (2 * 3.14159265359) / (sections - 1);
//	}
//
//
//	GLuint indices[(sections) * (sections)* indexPerQuad];
//	offset = 0;
//	for (int i = 0; i < sections; i++)
//	{
//		for (int j = 0; j < sections; j++)
//		{
//			indices[offset++] = (((i + 1) % sections) * sections) + ((j + 1) % sections);
//			indices[offset++] = (((i + 1) % sections) * sections) + (j);
//			indices[offset++] = (i * sections) + (j);
//
//			indices[offset++] = (i * sections) + ((j + 1) % sections);
//			indices[offset++] = (((i + 1) % sections) * sections) + ((j + 1) % sections);
//			indices[offset++] = (i * sections) + (j);
//		}
//	}
//
//	GLuint VBO, EBO, VAO, texture;
//
//	glGenVertexArrays(1, &VAO);
//	glBindVertexArray(VAO);
//
//	glGenBuffers(1, &VBO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	glGenBuffers(1, &EBO);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexAttrib * sizeof(GLfloat), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, vertexAttrib * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(1);
//
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertexAttrib * sizeof(GLfloat), (void*)(7 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(2);
//
//	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, vertexAttrib * sizeof(GLfloat), (void*)(9 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(3);
//
//	IndiceCount = sizeof(indices) / sizeof(GLuint);
//
//	glGenTextures(1, &texture);
//	glBindTexture(GL_TEXTURE_2D, texture);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	int width, height;
//	unsigned char* image = SOIL_load_image(TextureSource, &width, &height, 0, SOIL_LOAD_RGBA);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
//
//	glGenerateMipmap(GL_TEXTURE_2D);
//	SOIL_free_image_data(image);
//	glBindTexture(GL_TEXTURE_2D, 0);
//
//	Texture = texture;
//	//GLuint vao = CreateBuffer("", TempTexture);
//	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//	return VAO;
//}
//
///************************************************************
//#--Description--#: 	Binds plane
//#--Author--#: 		Alex Coultas
//#--Parameters--#: 	Takes in size and colour
//#--Return--#: 		New vao gluint
//************************************************************/
GLuint Shader::BindArray(float fWidth, float fHeight, glm::vec4 Colour)
{
	float fHalfWidth = fWidth / 2;
	float fHalfHeight = fHeight / 2;

	GLfloat vertices[] = {
		// Positions						// Colors			
		-fHalfWidth, fHalfHeight, 0.0f,		Colour.r, Colour.g, Colour.b, Colour.a,
		fHalfWidth, fHalfHeight, 0.0f,		Colour.r, Colour.g, Colour.b, Colour.a,
		fHalfWidth, -fHalfHeight, 0.0f,		Colour.r, Colour.g, Colour.b, Colour.a,
		-fHalfWidth, -fHalfHeight, 0.0f,	Colour.r, Colour.g, Colour.b, Colour.a,

	};

	GLuint indices[] = {
		0, 1, 2, // First Triangle
		0, 2, 3 // Second Triangle
	};
	GLuint TempTexture;

	GLuint vao = CreateBuffer("", TempTexture, true);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	return vao;
}

///************************************************************
//#--Description--#: 	Binds plane with animated texture
//#--Author--#: 		Alex Coultas
//#--Parameters--#: 	Takes in size, colour, texture source, ref texture gluint and animation info
//#--Return--#: 		New vao gluint
//************************************************************/
//GLuint Shader::BindArray(float fWidth, float fHeight, glm::vec4 Colour, const char * TextureSource, GLuint & Texture, glm::vec2 v2FrameCounts, Utils::AnimInfo& Anim)
//{
//	// Get Image Dimensions
//	int width, height;
//	unsigned char* image = SOIL_load_image(TextureSource, &width, &height, 0, SOIL_LOAD_RGBA);
//	SOIL_free_image_data(image);
//	Anim.v2FrameCount = v2FrameCounts;
//	Anim.v2EndFrame = v2FrameCounts;
//	Anim.v2FrameSize = { (width / v2FrameCounts.x) / width, (height / v2FrameCounts.y) / height };
//
//
//	float fHalfWidth = fWidth / 2;
//	float fHalfHeight = fHeight / 2;
//
//	GLfloat vertices[] = {
//		// Positions						// Colors									// Tex Coords
//		-fHalfWidth, fHalfHeight, 0.0f,		Colour.r, Colour.g, Colour.b, Colour.a,		0, 0,	// Top Left
//		fHalfWidth, fHalfHeight, 0.0f,		Colour.r, Colour.g, Colour.b, Colour.a,		Anim.v2FrameSize.x, 0, // Top Right
//		fHalfWidth, -fHalfHeight, 0.0f,		Colour.r, Colour.g, Colour.b, Colour.a,		Anim.v2FrameSize.x, Anim.v2FrameSize.y, // Bottom Right
//		-fHalfWidth, -fHalfHeight, 0.0f,	Colour.r, Colour.g, Colour.b, Colour.a,		0, Anim.v2FrameSize.y, // Bottom Left
//	};
//	//GLfloat vertices[] = {
//	//	// Positions						// Colors									// Tex Coords
//	//	-fHalfWidth, fHalfHeight, 0.0f,		Colour.r, Colour.g, Colour.b, Colour.a,	// Top Left
//	//	fHalfWidth, fHalfHeight, 0.0f,		Colour.r, Colour.g, Colour.b, Colour.a, // Top Right
//	//	fHalfWidth, -fHalfHeight, 0.0f,		Colour.r, Colour.g, Colour.b, Colour.a, // Bottom Right
//	//	-fHalfWidth, -fHalfHeight, 0.0f,	Colour.r, Colour.g, Colour.b, Colour.a, // Bottom Left
//	//};
//
//	GLuint vao = CreateBuffer(TextureSource, Texture);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//	return vao;
//}
//
///************************************************************
//#--Description--#: 	Binds plane with texture with specified UV coords
//#--Author--#: 		Alex Coultas
//#--Parameters--#: 	Takes in size, colour, texture source, ref texture gluint and texture coords
//#--Return--#: 		New vao gluint
//************************************************************/
//GLuint Shader::BindArray(float fWidth, float fHeight, glm::vec4 Colour, const char * TextureSource, GLuint& Texture, glm::vec4 UVCoords)
//{
//	float fHalfWidth = fWidth / 2;
//	float fHalfHeight = fHeight / 2;
//
//	GLfloat vertices[] = {
//		// Positions						// Colors									// Tex Coords
//		-fHalfWidth, fHalfHeight, 0.0f,		Colour.r, Colour.g, Colour.b, Colour.a,		UVCoords.x, UVCoords.z,	// Top Left
//		fHalfWidth, fHalfHeight, 0.0f,		Colour.r, Colour.g, Colour.b, Colour.a,		UVCoords.y, UVCoords.z, // Top Right
//		fHalfWidth, -fHalfHeight, 0.0f,		Colour.r, Colour.g, Colour.b, Colour.a,		UVCoords.y, UVCoords.w, // Bottom Right
//		-fHalfWidth, -fHalfHeight, 0.0f,	Colour.r, Colour.g, Colour.b, Colour.a,		UVCoords.x, UVCoords.w, // Bottom Left
//	};
//	GLuint indices[] = {
//		0, 1, 2, // First Triangle
//		0, 2, 3 // Second Triangle
//	};
//	GLuint TempTexture;
//
//	GLuint vao = CreateBuffer(TextureSource, Texture);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//	return vao;
//}
//
///************************************************************
//#--Description--#: 	Binds plane with texture tiling style
//#--Author--#: 		Alex Coultas
//#--Parameters--#: 	Takes in size, colour, texture source, ref texture gluint and tile number and direction
//#--Return--#: 		New vao gluint
//************************************************************/
//GLuint Shader::BindArray(float fWidth, float fHeight, glm::vec4 Colour, const char * TextureSource, GLuint& Texture, int iNum, bool bHorizontal)
//{
//	int width, height;
//	unsigned char* image = SOIL_load_image(TextureSource, &width, &height, 0, SOIL_LOAD_RGBA);
//	SOIL_free_image_data(image);
//	float fImageRatio = (float)width / (float)height;
//	float fObjectRatio = fHeight / fWidth;
//	float hSize = iNum;
//	float vSize = iNum;
//	if (bHorizontal)
//	{
//		vSize = iNum * fObjectRatio * fImageRatio;
//	}
//	else
//	{
//		hSize = iNum / fObjectRatio / fImageRatio;
//	}
//
//	glm::vec4 UVCoords = glm::vec4(0, hSize, 0, vSize);
//
//	float fHalfWidth = fWidth / 2;
//	float fHalfHeight = fHeight / 2;
//
//	GLfloat vertices[] = {
//		// Positions		 // Colors					// Tex Coords
//		// Square
//		-fHalfWidth, fHalfHeight, 0.0f,		Colour.r, Colour.g, Colour.b, Colour.a,		UVCoords.x, UVCoords.z,// Top Left
//		fHalfWidth, fHalfHeight, 0.0f,		Colour.r, Colour.g, Colour.b, Colour.a,		UVCoords.y, UVCoords.z, // Top Right
//		fHalfWidth, -fHalfHeight, 0.0f,		Colour.r, Colour.g, Colour.b, Colour.a,		UVCoords.y, UVCoords.w, // Bottom Right
//		-fHalfWidth, -fHalfHeight, 0.0f,	Colour.r, Colour.g, Colour.b, Colour.a,		UVCoords.x, UVCoords.w, // Bottom Left
//	};
//	GLuint indices[] = {
//		0, 1, 2, // First Triangle
//		0, 2, 3 // Second Triangle
//	};
//	GLuint TempTexture;
//
//	GLuint vao = CreateBuffer(TextureSource, Texture);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//	return vao;
//}

/************************************************************
#--Description--#: 	Binds UI Image with texture tiling style
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Takes in size, colour, texture source, ref texture gluint and draw mode
#--Return--#: 		New vao gluint
************************************************************/
GLuint Shader::BindUITextureArray(float fWidth, float fHeight, glm::vec4 Colour, const char * TextureSource, GLuint & Texture, int _DrawMode)
{		
	GLuint vao;
	GLuint vbo;
	GLuint ebo;
	GLuint texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image(TextureSource, &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
			
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	Texture = texture;
	glBindTexture(GL_TEXTURE_2D, 0);
	
	glm::vec4 UVCoords = glm::vec4(0, 1, 0, 1);
	if (_DrawMode == 1)
	{
		float yValue = (fHeight / fWidth) *  ((float)width / (float)height);
		UVCoords = glm::vec4(0, 1, 0, yValue);
	}
	else if (_DrawMode == 2)
	{
		float xValue = (fWidth / fHeight) *  ((float)height / (float)width);
		UVCoords = glm::vec4(0, xValue, 0, 1);
	}
	float fHalfWidth = fWidth / 2;
	float fHalfHeight = fHeight / 2;

	GLfloat vertices[] = {
		// Positions				// Tex Coords
		-fHalfWidth, fHalfHeight,	UVCoords.x, UVCoords.z,// Top Left
		fHalfWidth, fHalfHeight,	UVCoords.y, UVCoords.z, // Top Right
		fHalfWidth, -fHalfHeight,	UVCoords.y, UVCoords.w, // Bottom Right
		-fHalfWidth, -fHalfHeight,	UVCoords.x, UVCoords.w, // Bottom Left
	};
	GLuint indices[] = {
		0, 1, 2, // First Triangle
		0, 2, 3 // Second Triangle
	};

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBindTexture(GL_TEXTURE_2D, texture);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	return vao;
}

/************************************************************
#--Description--#: 	Adds font
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Takes in font path and font size
#--Return--#: 		New font struct info
************************************************************/
Text::cFont Shader::AddFont(std::string fontPath, int iPSize)
{
	for (auto it : Text::Fonts)
	{
		if (it.sPathName == fontPath && it.fPSize == iPSize)
		{
			return it;
		}
	}


	// Initiate the font Lib
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;		
	}
	// Each character is called a glyph and Face is the collection of glyphs
	FT_Face face;
	// Load font as face;
	if (FT_New_Face(ft, fontPath.c_str(), 0, &face))
	{
		std::cout << "ERROR::FREETYPE: Failed to Load font" << std::endl;
	}
	// Set size to load glyph as
	FT_Set_Pixel_Sizes(face, 0, iPSize);
	// Disable byte-alignment restriction
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	Text::cFont newFont;
	newFont.sPathName = fontPath;
	newFont.fPSize = iPSize;
	// Load the first 128 characters of the ASCII set
	for (GLubyte c = 0; c < 128; c++)
	{
		// Load the character glyph into face
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// Generate texture for character
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_ALPHA,
			GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Now to store character for later use
		Text::Character character = { texture,
			glm::ivec2((GLuint)face->glyph->bitmap.width, (GLuint)face->glyph->bitmap.rows),
			glm::ivec2((GLuint)face->glyph->bitmap_left, (GLuint)face->glyph->bitmap_top),
			(GLuint)face->glyph->advance.x
		};
		newFont.Characters.insert(std::pair<GLchar, Text::Character>(c, character));
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	// Destroy FreeType once we are finished
	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	//Configure VAO/VBO for texture quads
	glGenVertexArrays(1, &newFont.VAO);
	glBindVertexArray(newFont.VAO);

	glGenBuffers(1, &newFont.VBO);
	glBindBuffer(GL_ARRAY_BUFFER, newFont.VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	Text::Fonts.push_back(newFont);
	return newFont;
}

/************************************************************
#--Description--#: 	Creates the buffer with an option of binding texture
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Takes texture path and texture gluint ref
#--Return--#: 		New vao gluint
************************************************************/
GLuint Shader::CreateBuffer(const char * TextureSource, GLuint & Texture, bool bAA, bool bHasNormals)
{
	GLuint vao;
	GLuint vbo;
	GLuint ebo;
	GLuint texture;
	bool bTextureExists = false;
	for (auto& it : Textures)
	{
		if (it.first == TextureSource)
		{
			Texture = it.second;
			texture = it.second;
			bTextureExists = true;
		}
	}

	if (TextureSource != "")
	{
		if (bTextureExists == false)
		{
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			if (bAA)
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			}
			else
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			}

			int width, height;
			unsigned char* image = SOIL_load_image(TextureSource, &width, &height, 0, SOIL_LOAD_RGBA);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

			glGenerateMipmap(GL_TEXTURE_2D);
			SOIL_free_image_data(image);
			glBindTexture(GL_TEXTURE_2D, 0);


			Textures.insert(std::pair<const char*, GLuint>(TextureSource, texture));
			LogManager::GetInstance()->DisplayLogMessage("Adding Texture, \"" + std::string(TextureSource) + "\", Total Texture Count : " + std::to_string(Textures.size()));
			Texture = texture;
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, texture);
		}
	}

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	if (TextureSource != "")
	{
		if (bHasNormals)
		{
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (GLvoid*)0);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (GLvoid*)(7 * sizeof(GLfloat)));
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(GLfloat), (GLvoid*)(9 * sizeof(GLfloat)));
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);
			glEnableVertexAttribArray(3);
		}
		else
		{
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)0);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(7 * sizeof(GLfloat)));
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);
		}
	}
	else
	{
		if (bHasNormals)
		{
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(GLfloat), (GLvoid*)0);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(GLfloat), (GLvoid*)(7 * sizeof(GLfloat)));
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(3);
		}
		else
		{
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)0);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
		}
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	return vao;
}
