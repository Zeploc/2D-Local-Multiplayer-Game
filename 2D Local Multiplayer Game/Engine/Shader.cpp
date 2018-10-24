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

void Shader::AddProgram(std::string VertexShaderPath, std::string FragmentShaderPath, std::string ShaderName, std::string GeometryShaderPath)
{
	ShaderLoader loader;
	Programs.insert(std::pair<std::string, GLuint>(ShaderName, loader.CreateProgram(VertexShaderPath.c_str(), FragmentShaderPath.c_str(), GeometryShaderPath.c_str())));
	LogManager::GetInstance()->DisplayLogMessage("Loading Shader \"" + ShaderName + "\"");
}

void Shader::AddTessProgram(std::string VertexShaderPath, std::string FragmentShaderPath, std::string TessControlShaderPath, std::string TessEvalShaderPath, std::string ShaderName)
{
	ShaderLoader loader;
	Programs.insert(std::pair<std::string, GLuint>(ShaderName, loader.CreateTessProgram(VertexShaderPath.c_str(), FragmentShaderPath.c_str(), TessControlShaderPath.c_str(), TessEvalShaderPath.c_str())));
	LogManager::GetInstance()->DisplayLogMessage("Loading Shader \"" + ShaderName + "\"");
}

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

/************************************************************
#--Description--#: 	Binds UI Image with texture tiling style
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Takes in size, colour, texture source, ref texture gluint and draw mode
#--Return--#: 		New vao gluint
************************************************************/
GLuint Shader::BindUITextureArray(float fWidth, float fHeight, const char * TextureSource, GLuint & Texture, int _DrawMode)
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

	Texture = GetTexture(TextureSource, bAA);

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

GLuint Shader::GetTexture(const char * TextureSource, bool bAA)
{
	GLuint texture = 0;

	bool bTextureExists = false;
	for (auto& it : Textures)
	{
		if (it.first == TextureSource)
		{
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
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, texture);
		}
	}

	return texture;
}