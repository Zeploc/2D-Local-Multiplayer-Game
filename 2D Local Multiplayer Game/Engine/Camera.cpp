//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name    	:    Camera.cpp
// Description    	:    main implementation for Camera
// Author       	:    Alex Coultas
// Mail         	:    alex.cou7417@mediadesign.school.nz
//

// Library Includes //
#include <iostream>
#include <algorithm>    // std::max

// OpenGL Library Includes //
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc/matrix_transform.hpp>
#include <glm\gtx\string_cast.hpp>

// Engine Includes //
#include "Input.h"
#include "Shader.h"
#include "Time.h"

// This Includes //
#include "Camera.h"

// Static Variables //
Camera* Camera::m_pCamera = nullptr;

/************************************************************
#--Description--#: 	Initialises the camera to the screen size and camera vectors
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Takes in screen size and camera vectors
#--Return--#: 		NA
************************************************************/
void Camera::Init(int ScreenWidth, int ScreenWidthheight, glm::vec3 CamPos, glm::vec3 ForwardVec, glm::vec3 UpVec)
{
	SCR_WIDTH = ScreenWidth;
	SCR_HEIGHT = ScreenWidthheight;
	cameraPos = CamPos;
	cameraFront = ForwardVec;
	cameraUp = UpVec;
	
	//projection = glm::perspective(90.0f, (float)SCR_WIDTH /	(float)SCR_HEIGHT, 0.1f, 100.0f);

	float HalfWidth = (float)SCR_WIDTH / fWindowScale;
	float HalfHeight = (float)SCR_HEIGHT / fWindowScale;
	projection = glm::ortho(-HalfWidth, HalfWidth, -HalfHeight, HalfHeight, 0.1f, 100.0f);
	view = glm::lookAt(cameraPos,
		cameraPos + cameraFront,
		cameraUp);
}

/************************************************************
#--Description--#: 	Updated every frame
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void Camera::Update()
{
	/*if (m_ProjectionMode == PERSPECTIVE && m_bFPS)
		FPSControls();*/
	view = glm::lookAt(cameraPos,
		cameraPos + cameraFront,
		cameraUp);	
}

/************************************************************
#--Description--#: 	Moves the camera
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void Camera::MoveCamera(glm::vec3 _Movement)
{
	cameraPos += _Movement;
	//SetMVP(Utils::Transform());
}

/************************************************************
#--Description--#: 	Sets the window projection scale
#--Author--#: 		Alex Coultas
#--Parameters--#: 	New flaot scale
#--Return--#: 		NA
************************************************************/
void Camera::SetWindowScale(float _fNewScale)
{
	fWindowScale = _fNewScale;
	float HalfWidth = (float)SCR_WIDTH / fWindowScale;
	float HalfHeight = (float)SCR_HEIGHT / fWindowScale;
	projection = glm::ortho(-HalfWidth, HalfWidth, -HalfHeight, HalfHeight, 0.1f, fMaxViewClipping);
}

glm::vec3 Camera::ScreenToWorldDirection(glm::vec2 _ScreenPosition)
{
	float x = (2.0f * _ScreenPosition.x) / SCR_WIDTH - 1.0f;
	float y = 1.0f - (2.0f * _ScreenPosition.y) / SCR_HEIGHT;
	glm::vec2 ray_nds = { x, y};

	glm::vec4 ray_clip = glm::vec4(ray_nds.x, ray_nds.y, -1.0f, 1.0f);

	glm::vec4 ray_eye = glm::inverse(projection) * ray_clip;
	ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0f, 0.0f);

	glm::vec3 ray_wor = glm::inverse(view) * ray_eye;

	ray_wor = glm::normalize(ray_wor);
	return ray_wor;
}


/************************************************************
#--Description--#: 	Passes in the new mvp to the current program shader
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Takes in the transforms vectors
#--Return--#: 		NA
************************************************************/
void Camera::SetMVP(Utils::Transform _transform, GLuint program)
{
	glm::mat4 translate = glm::translate(glm::mat4(), _transform.Position);
	glm::mat4 scale = glm::scale(glm::mat4(), _transform.Scale);
	glm::mat4 rotation = glm::rotate(glm::mat4(), glm::radians(_transform.Rotation.x), glm::vec3(1, 0, 0));
	rotation = glm::rotate(rotation, glm::radians(_transform.Rotation.y), glm::vec3(0, 1, 0));
	rotation = glm::rotate(rotation, glm::radians(_transform.Rotation.z), glm::vec3(0, 0, 1));
	
	glm::mat4 model = translate * rotation * scale;
	
	glm::mat4 MVP = projection * view * model;
	GLint MVPLoc = glGetUniformLocation(program, "MVP");
	glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, glm::value_ptr(MVP));
}


/************************************************************
#--Description--#:  Change projection type
#--Author--#: 		Alex Coultas
#--Parameters--#:	Takes int mode
#--Return--#: 		NA
************************************************************/
void Camera::SwitchProjection(PROJECTIONMODE _Mode)
{
	m_ProjectionMode = _Mode;
	switch (m_ProjectionMode)
	{
	case 1:
	{
		float HalfWidth = (float)SCR_WIDTH / 200;
		float HalfHeight = (float)SCR_HEIGHT / 200;
		projection = glm::ortho(-HalfWidth, HalfWidth, -HalfHeight, HalfHeight, 0.1f, fMaxViewClipping);
		break;
	}
	case 2:
	{
		float HalfWidth = (float)SCR_WIDTH / 200;
		float HalfHeight = (float)SCR_HEIGHT / 200;
		projection = glm::perspective(45.0f, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, fMaxViewClipping);
		break;
	}
	default:
		break;
	}
}

/************************************************************
#--Description--#:  Constructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	Takes contructor values
#--Return--#: 		NA
************************************************************/
Camera::Camera()
{
}

/************************************************************
#--Description--#:  Destructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	NA
#--Return--#: 		NA
************************************************************/
Camera::~Camera()
{
}

/************************************************************
#--Description--#:  Retrieves static instance pointer to this class
#--Author--#: 		Alex Coultas
#--Parameters--#:	NA
#--Return--#: 		Returns static pointer to self
************************************************************/
Camera * Camera::GetInstance()
{
	if (!m_pCamera) // null or doesn't exist
		m_pCamera = new Camera;
	return m_pCamera;
}

/************************************************************
#--Description--#:  Destroys static instance pointer to this class
#--Author--#: 		Alex Coultas
#--Parameters--#:	NA
#--Return--#: 		NA
************************************************************/
void Camera::DestoryInstance()
{
	if (m_pCamera)
		delete m_pCamera;
	m_pCamera = nullptr;
}