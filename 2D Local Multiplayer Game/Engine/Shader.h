//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name		:    Shader.h
// Description		:    Header file outlining the Class
// Author			:    Alex Coultas
// Mail				:    alex.cou7417@mediadesign.school.nz
//

// Library Includes //
#include <string>
#include <map>
#include <memory>

// OpenGL Library Includes //
#include <glew.h>
#include <freeglut.h>
#include <glm/common.hpp>

// Engine Includes //
#include "Text.h"

class ModelObject;

#pragma once
class Shader
{
public:
	Shader();
	~Shader();
	static void CleanUp();

	static void AddProgram(std::string VertexShaderPath, std::string FragmentShaderPath, std::string ShaderName, std::string GeometryShaderPath = "");
	static void AddTessProgram(std::string VertexShaderPath, std::string FragmentShaderPath, std::string TessControlShaderPath, std::string TessEvalShaderPath, std::string ShaderName);

	
	static std::map<std::string, std::shared_ptr<ModelObject>> Models;
	static std::map<const char *, GLuint> Textures;
	static std::map<std::string, GLuint> Programs;
	
	static GLuint BindArray(float fWidth, float fHeight, glm::vec4 Colour);
	
	static GLuint BindUITextureArray(float fWidth, float fHeight, const char *  TextureSource, GLuint& Texture, int _DrawMode);
		
	static Text::cFont AddFont(std::string fontPath, int iPSize);

	static GLuint CreateBuffer(const char * TextureSource, GLuint & Texture, bool bAA, bool bHasNormals = false);

	static GLuint GetTexture(const char * TextureSource, bool bAA);
private:
};

