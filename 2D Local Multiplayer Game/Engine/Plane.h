//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name    	:    Plane.h
// Description    	:    Header file outlining the Class
// Author       	:    Alex Coultas
// Mail         	:    alex.cou7417@mediadesign.school.nz
//

#pragma once
// This Includes //
#include "Mesh.h"

class Plane : public Mesh
{
public:
	Plane(float fWidth, float fHeight, glm::vec4 Colour);
	Plane(float fWidth, float fHeight, glm::vec4 Colour, const char *  TextureSource, glm::vec4 UVCoords = glm::vec4(0, 1, 0, 1));
	Plane(float _fWidth, float _fHeight, glm::vec4 _Colour, const char * TextureSource, glm::vec2 v2FrameCounts, int _iFPS);
	Plane(float _fWidth, float _fHeight, glm::vec4 _Colour, const char * TextureSource, int iCount, bool bHorizontal);
	~Plane();

	void BindPlane();
	void Rebind();
	virtual void SetInitialStates();
	virtual void Reset() override;

	void Render(Utils::Transform Newtransform);
	void Update();

	Utils::AnimInfo AnimationInfo;
	double m_dFPSCounter = 0;
	double m_fFrameCheck = 0;
	Utils::Col2DI CollisionBox;

protected:
	struct PlaneInitialState
	{
		Utils::AnimInfo AnimationInfo;
		double m_dFPSCounter;
		double m_fFrameCheck;
		Utils::Col2DI CollisionBox;
	};

	PlaneInitialState m_PlaneInitialState;
};

