//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name		:    Camera.h
// Description		:    Header file outlining the Class
// Author			:    Alex Coultas
// Mail				:    alex.cou7417@mediadesign.school.nz
//

// OpenGL Library Includes //
#include <glew.h>
#include <glut.h>
#include <glm/common.hpp>
#include <glm/matrix.hpp>

// Engine Includes //
#include "Utils.h"

#pragma once
class Camera
{
public:

	enum PROJECTIONMODE
	{
		ORTHAGRAPHIC = 1,
		PERSPECTIVE
	};

	unsigned int SCR_WIDTH = 800;
	unsigned int SCR_HEIGHT = 800;

	glm::mat4 view;
	glm::mat4 projection;

	void Init(int ScreenWidth, int ScreenWidthheight, glm::vec3 CamPos, glm::vec3 ForwardVec, glm::vec3 UpVec);
	void Update();

	void SetMVP(Utils::Transform _transform, GLuint program);
	void SwitchProjection(PROJECTIONMODE _Mode);
	PROJECTIONMODE ReturnDimensionMode() { return m_ProjectionMode; };

	void SetWindowScale(float _fNewScale);
	void SetCameraForwardVector(glm::vec3 _Forward) {
		cameraFront = _Forward;	};

	glm::vec3 ScreenToWorldDirection(glm::vec2 _ScreenPosition);

	// Getters
	glm::vec3 GetCameraPosition() { return cameraPos; };
	glm::vec3 GetCameraForwardVector() { return cameraFront; };
	glm::vec3 GetCameraUpVector() { return cameraUp; };

	void SetCameraPos(glm::vec3 NewPos) { cameraPos = NewPos; };

	void MoveCamera(glm::vec3 _Movement);
private:

	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;


	PROJECTIONMODE m_ProjectionMode = ORTHAGRAPHIC;

	float fWindowScale = 200;
	float fMaxViewClipping = 2000.0f;

	// Singleton
public:
	static Camera* GetInstance();
	static void DestoryInstance();


private:
	static Camera* m_pCamera;
	Camera();
	~Camera();
	Camera(Camera const&);              // Don't Implement
	void operator=(Camera const&); // Don't implement


};

