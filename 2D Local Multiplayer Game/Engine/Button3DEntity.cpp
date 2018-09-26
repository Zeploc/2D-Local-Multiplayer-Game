//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name    	:    Entity.cpp
// Description    	:    main implementation for Entity
// Author       	:    Alex Coultas
// Mail         	:    alex.cou7417@mediadesign.school.nz
//

// This Includes //
#include "Button3DEntity.h"

// Engine Includes //
#include "Cube.h"'
#include "Camera.h"
#include "Input.h"


// Static Variables //
bool Button3DEntity::bButtonPressedThisFrame = false;

Button3DEntity::Button3DEntity(Utils::Transform _Transform, Utils::EANCHOR _Anchor, float fWidth, float fHeight, float fDepth, glm::vec4 _Colour, glm::vec4 _HightlightColour, void(*func)())
	: Entity(_Transform, _Anchor), FuncCall(func)
{
	std::shared_ptr<Cube> ButtonCubeMesh = std::make_shared<Cube>(Cube(fWidth, fHeight, fDepth, _Colour));
	EntityMesh = ButtonCubeMesh;
	btnColour = _Colour;
	btnHighlightColour = _HightlightColour;
}

Button3DEntity::Button3DEntity(Utils::Transform _Transform, Utils::EANCHOR _Anchor, float fWidth, float fHeight, float fDepth, glm::vec4 _Colour, glm::vec4 _HightlightColour, const char * Texturepath, void(*func)())
	: Entity(_Transform, _Anchor), FuncCall(func)
{
	std::shared_ptr<Cube> ButtonCubeMesh = std::make_shared<Cube>(Cube(fWidth, fHeight, fDepth, _Colour, Texturepath));
	EntityMesh = ButtonCubeMesh;
	btnColour = _Colour;
	btnHighlightColour = _HightlightColour;
}


Button3DEntity::~Button3DEntity()
{
}

void Button3DEntity::Update()
{
	if (!bActive) return;
	glm::vec3 HalfDimensionvec = glm::vec3(EntityMesh->m_fWidth / 2.0f, EntityMesh->m_fHeight / 2.0f, EntityMesh->m_fDepth / 2.0f);
	bool bHit = CheckHit(glm::vec3(-HalfDimensionvec.x, -HalfDimensionvec.y, HalfDimensionvec.z), glm::vec3(HalfDimensionvec.x, HalfDimensionvec.y, HalfDimensionvec.z))
		|| CheckHit(glm::vec3(-HalfDimensionvec.x, -HalfDimensionvec.y, -HalfDimensionvec.z), glm::vec3(HalfDimensionvec.x, HalfDimensionvec.y, -HalfDimensionvec.z))
		|| CheckHit(glm::vec3(-HalfDimensionvec.x, -HalfDimensionvec.y, -HalfDimensionvec.z), glm::vec3(HalfDimensionvec.x, -HalfDimensionvec.y, HalfDimensionvec.z))
		|| CheckHit(glm::vec3(-HalfDimensionvec.x, HalfDimensionvec.y, -HalfDimensionvec.z), glm::vec3(HalfDimensionvec.x, HalfDimensionvec.y, HalfDimensionvec.z))
		|| CheckHit(glm::vec3(-HalfDimensionvec.x, -HalfDimensionvec.y, -HalfDimensionvec.z), glm::vec3(-HalfDimensionvec.x, HalfDimensionvec.y, HalfDimensionvec.z))
		|| CheckHit(glm::vec3(HalfDimensionvec.x, -HalfDimensionvec.y, -HalfDimensionvec.z), glm::vec3(HalfDimensionvec.x, HalfDimensionvec.y, HalfDimensionvec.z));
	
	if (bHit)
	{
		EntityMesh->bStencil = true;
		if (Input::GetInstance()->MouseState[Input::MOUSE_LEFT] == Input::InputState::INPUT_FIRST_PRESS && !bButtonPressedThisFrame)
		{
			bPressed = true;
			bButtonPressedThisFrame = true;
			if (FuncCall != nullptr) FuncCall();
		}
		EntityMesh->Colour = btnHighlightColour;
	}	
	else
	{
		EntityMesh->Colour = btnColour;
		EntityMesh->bStencil = false;
	}
}

bool Button3DEntity::CheckHit(glm::vec3 BottomLeftOffset, glm::vec3 TopRightOffset)
{
	glm::vec3 rayDirection = Camera::GetInstance()->ScreenToWorldDirection(Input::GetInstance()->MousePos);

	glm::vec3 AnchoredPosition = Utils::GetAncoredPosition(transform.Position, glm::vec3(EntityMesh->m_fWidth, EntityMesh->m_fHeight, EntityMesh->m_fDepth), EntityAnchor);
	glm::vec3 lb = BottomLeftOffset + AnchoredPosition;
	glm::vec3 rt = TopRightOffset + AnchoredPosition;
	lb = glm::vec4(lb, 1.0f) * GetModel();
	rt = glm::vec4(rt, 1.0f) * GetModel();

	glm::vec3 DirFrac = 1.0f / rayDirection;

	float t1 = (lb.x - Camera::GetInstance()->GetCameraPosition().x) * DirFrac.x;
	float t2 = (rt.x - Camera::GetInstance()->GetCameraPosition().x) * DirFrac.x;
	float t3 = (lb.y - Camera::GetInstance()->GetCameraPosition().y) * DirFrac.y;
	float t4 = (rt.y - Camera::GetInstance()->GetCameraPosition().y) * DirFrac.y;
	float t5 = (lb.z - Camera::GetInstance()->GetCameraPosition().z) * DirFrac.z;
	float t6 = (rt.z - Camera::GetInstance()->GetCameraPosition().z) * DirFrac.z;

	float tmin = std::fmax(std::fmax(std::fmin(t1, t2), std::fmin(t3, t4)), std::fmin(t5, t6));
	float tmax = std::fmin(std::fmin(std::fmax(t1, t2), std::fmax(t3, t4)), std::fmax(t5, t6));
	float t;

	// if tmax < 0, ray (line) is intersecting AABB, but the whole AABB is behind us
	if (tmax < 0)
	{
		t = tmax;
	}
	// if tmin > tmax, ray doesn't intersect AABB
	else if (tmin > tmax)
	{
		t = tmax;
	}
	else
	{
		t = tmin;
		return true;
	}

	return false;
}
