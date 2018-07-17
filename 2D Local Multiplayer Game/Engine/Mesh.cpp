//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name    	:    Entity.cpp
// Description    	:    Mesh Component for entity
// Author       	:    Alex Coultas
// Mail         	:    alex.cou7417@mediadesign.school.nz
//

// This Includes //
#include "Mesh.h"

// Engine Includes //
#include "Camera.h"
#include "CollisionBounds.h"
#include "Shader.h"


/************************************************************
#--Description--#:  Constructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	Takes contructor values
#--Return--#: 		NA
************************************************************/
Mesh::Mesh()
{
	MeshInitialState.bIsLit = bIsLit;
	MeshInitialState.bReflection = bReflection;
	MeshInitialState.m_fDepth = m_fDepth;
	MeshInitialState.LightProperties = LightProperties;
}

/************************************************************
#--Description--#:  Constructor function with texture
#--Author--#: 		Alex Coultas
#--Parameters--#:	Takes contructor values
#--Return--#: 		NA
************************************************************/
Mesh::~Mesh()
{
	//if (MeshCollisionBounds) delete MeshCollisionBounds;
	MeshCollisionBounds = nullptr;
}

/************************************************************
#--Description--#:	Render Current Mesh to the screen
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void Mesh::Render(Utils::Transform Newtransform)
{
	// ABOVE CALLED FROM DERIVED RENDER
	if (bHasTexture)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
	
	}
	if (bReflection)
	{		
		glActiveTexture(GL_TEXTURE1);
		glUniform1i(glGetUniformLocation(program, "skybox"), 1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, Utils::WorldCubeMap->EntityMesh->texture);
		glUniform1f(glGetUniformLocation(program, "ReflectionSize"), 0.1f);

	}
	glEnable(GL_CULL_FACE);
	Camera::GetInstance()->SetMVP(Newtransform, program);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, m_iIndicies, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::SetInitialStates()
{
	MeshInitialState.m_eShape = m_eShape;
	MeshInitialState.m_fWidth = m_fWidth;
	MeshInitialState.m_fHeight = m_fHeight;
	MeshInitialState.m_fDepth = m_fDepth;
	MeshInitialState.Colour = Colour;
	MeshInitialState.program = program;
	MeshInitialState.vao = vao;
	MeshInitialState.texture = texture;
	MeshInitialState.TextureSource = TextureSource;
	MeshInitialState.UVCoords = UVCoords;
	MeshInitialState.bHasTexture = bHasTexture;
	MeshInitialState.m_iIndicies = m_iIndicies;
}

void Mesh::Reset()
{
	// Reset all mesh variables
	m_eShape = MeshInitialState.m_eShape;
	m_fWidth = MeshInitialState.m_fWidth;
	m_fDepth = MeshInitialState.m_fDepth;
	Colour = MeshInitialState.Colour;
	program = MeshInitialState.program;
	vao = MeshInitialState.vao;
	texture = MeshInitialState.texture;
	TextureSource = MeshInitialState.TextureSource;
	UVCoords = MeshInitialState.UVCoords;
	bHasTexture = MeshInitialState.bHasTexture;
	m_iIndicies = MeshInitialState.m_iIndicies;
	LightProperties = MeshInitialState.LightProperties;
	bIsLit = MeshInitialState.bIsLit;
	bReflection = MeshInitialState.bReflection;
	// Reset Mesh Collision Bounds
	if (MeshCollisionBounds) MeshCollisionBounds->Reset();
}

void Mesh::SetReflection(bool _bReflecting, bool _bIsInitialState)
{
	bReflection = _bReflecting;
	if (bReflection)
		program = Shader::Programs["ReflectionProgram"];
	else
	{
		if (bIsLit)
		{
			program = Shader::Programs["LitTextureprogram"];
		}
		else
		{
			program = Shader::Programs["program"];
		}
	}
	if (_bIsInitialState)
		MeshInitialState.bReflection = bReflection;
}

void Mesh::AddCollisionBounds(float fWidth, float fHeight, float fDepth, std::shared_ptr<Entity> _EntityRef)
{
	MeshCollisionBounds = std::make_shared<CollisionBounds>(fWidth, fHeight, fDepth, _EntityRef);
}

void Mesh::AddCollisionBounds(std::shared_ptr<CollisionBounds> NewCollision)
{
	MeshCollisionBounds = NewCollision;
}
