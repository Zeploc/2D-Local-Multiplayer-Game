//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name    	:    ParticleSystem.cpp
// Description    	:    main implementation for ParticleSystem
// Author       	:    Alex Coultas
// Mail         	:    alex.cou7417@mediadesign.school.nz
//

// Library Includes //
#include <random>

// OpenGL Library Includes //

// Engine Includes //
#include "Time.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Plane.h"

// This Includes //
#include "ParticleSystem.h"

/************************************************************
#--Description--#:  Constructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	Takes contructor values
#--Return--#: 		NA
************************************************************/
ParticleSystem::ParticleSystem(Utils::Transform _Transform, const char* _CharName)
	: Entity(_Transform, Utils::CENTER)
{
	m_vParticlePaths.push_back(_CharName);
}

/************************************************************
#--Description--#:  Destructor function
#--Author--#: 		Alex Coultas
#--Parameters--#:	NA
#--Return--#: 		NA
************************************************************/
ParticleSystem::~ParticleSystem()
{

}

/************************************************************
#--Description--#:	Add new particle type path
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Path
#--Return--#: 		NA
************************************************************/
void ParticleSystem::AddParticleType(const char * _Charname)
{
	m_vParticlePaths.push_back(_Charname);
}

/************************************************************
#--Description--#:	Set particle size range
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Vector 2 new size range
#--Return--#: 		NA
************************************************************/
void ParticleSystem::SetSizeRange(glm::vec2 _v2SizeRange)
{
	m_v2SizeRange = _v2SizeRange;
}

/************************************************************
#--Description--#:	Set particle speed range
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Vector 2 new speed range
#--Return--#: 		NA
************************************************************/
void ParticleSystem::SetSpeedRange(glm::vec2 _v2SpeedRange)
{
	m_v2SpeedRange = _v2SpeedRange;
}

/************************************************************
#--Description--#:	Set particle delay range
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Vector 2 new delay range
#--Return--#: 		NA
************************************************************/
void ParticleSystem::SetDelayRange(glm::vec2 _v2DelayRange)
{
	m_v2DelayRange = _v2DelayRange;
}

/************************************************************
#--Description--#:	Set particle falloff distance range
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Vector 2 new falloff distance range
#--Return--#: 		NA
************************************************************/
void ParticleSystem::SetFalloffRange(glm::vec2 _v2FalloffRange)
{
	m_v2FalloffRange = _v2FalloffRange;
}

/************************************************************
#--Description--#:	Set particle falloff time range
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Vector 2 new falloff time range
#--Return--#: 		NA
************************************************************/
void ParticleSystem::SetFalloffTime(glm::vec2 _v2FalloffTime)
{
	m_v2FalloffTime = _v2FalloffTime;
}

/************************************************************
#--Description--#:	Set particle direction range
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Vector 2 new direction range
#--Return--#: 		NA
************************************************************/
void ParticleSystem::SetDirectionRange(glm::vec2 _v2DirectionRangeX, glm::vec2 _v2DirectionRangeY)
{
	m_v2DirectionRangeX = _v2DirectionRangeX;
	m_v2DirectionRangeY = _v2DirectionRangeY;
}

/************************************************************
#--Description--#:	Set particle gravity
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Vector 2 new gravity
#--Return--#: 		NA
************************************************************/
void ParticleSystem::SetGravity(float _fGravity)
{
	m_fGravity = _fGravity;
}

/************************************************************
#--Description--#:	Set particle liftime
#--Author--#: 		Alex Coultas
#--Parameters--#: 	Vector 2 new lifetime
#--Return--#: 		NA
************************************************************/
void ParticleSystem::SetLifeTime(float _fLifetime)
{
	m_fLifeTime = _fLifetime;
}

/************************************************************
#--Description--#:	Get a number between a range
#--Author--#: 		Alex Coultas
#--Parameters--#: 	minimum and maximum range ends
#--Return--#: 		Random float within defined range
************************************************************/
float ParticleSystem::RandomBetweenRange(float _fMin, float _fMax)
{
	int fRandRangeSize = int(abs(_fMax - _fMin) * 1000.0f);
	if (fRandRangeSize != 0)
		return (float)(rand() % fRandRangeSize) / 1000 + _fMin;
	else
		return _fMin;
}

/************************************************************
#--Description--#: 	Updated every frame
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void ParticleSystem::Update()
{
	// Decrease timer
	m_fCurrentDelay -= (float)Time::dTimeDelta;
	m_fCurrentLifeTime += (float)Time::dTimeDelta;
	if (m_fCurrentDelay <= 0 && (m_fLifeTime == 0 || m_fCurrentLifeTime <= m_fLifeTime))
	{
		// Generate New Random Time
		m_fCurrentDelay = RandomBetweenRange(m_v2DelayRange.x, m_v2DelayRange.y);

		// Random Speed
		float fNewSpeed = RandomBetweenRange(m_v2SpeedRange.x, m_v2SpeedRange.y);
		// Random Direction
		glm::vec2 v2NewDirection = { RandomBetweenRange(m_v2DirectionRangeX.x, m_v2DirectionRangeX.y), RandomBetweenRange(m_v2DirectionRangeY.x, m_v2DirectionRangeY.y) };
		// Random Size
		float fNewSize = RandomBetweenRange(m_v2SizeRange.x, m_v2SizeRange.y);
		// Random Falloff Distance
		float fNewFalloffDistance = RandomBetweenRange(m_v2FalloffRange.x, m_v2FalloffRange.y);
		// Random Falloff Time
		float fNewFalloffTime = RandomBetweenRange(m_v2FalloffTime.x, m_v2FalloffTime.y);
		// Random path from paths
		int iRandPath = rand() % m_vParticlePaths.size();

		std::shared_ptr<Entity> NewParticleEntity = std::make_shared<Entity>(transform, Utils::CENTER);
		std::shared_ptr<Plane> NewParticlePlaneMesh = std::make_shared<Plane>(fNewSize, fNewSize, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), m_vParticlePaths[iRandPath]);
		NewParticleEntity->AddMesh(NewParticlePlaneMesh);

		Particle NewParticle = { NewParticleEntity, fNewSpeed,  v2NewDirection, fNewFalloffDistance, fNewFalloffTime, 0.0f };
		m_vParticles.push_back(NewParticle);
		SceneManager::GetInstance()->GetCurrentScene()->AddEntity(NewParticle.pEntity);
	}
	
	if (m_vParticles.size() > 1)
	{
		for (auto iter = m_vParticles.begin(); iter != m_vParticles.end();)
		{
			(*iter).fTimeLength += (float)Time::dTimeDelta;
			(*iter).pEntity->Translate(glm::vec3(0, -m_fGravity * Time::dTimeDelta, 0));
			(*iter).pEntity->Translate(glm::vec3((*iter).v2Direction * (*iter).fSpeed * (float)Time::dTimeDelta, 0));
			
			glm::vec2 v2Distance = Utils::GetDistance2D((*iter).pEntity, this->shared_from_this());
			if (sqrt(pow(v2Distance.x, 2) + pow(v2Distance.y, 2)) >= (*iter).fFalloffDistance || (*iter).fTimeLength > (*iter).fFallOffTime)
			{				
				SceneManager::GetInstance()->GetCurrentScene()->DestroyEntity((*iter).pEntity);
				iter = m_vParticles.erase(iter);
			}
			else
				++iter;
		}
	}
	else if(!m_vParticles.empty())
	{
		m_vParticles[0].fTimeLength += (float)Time::dTimeDelta;
		m_vParticles[0].pEntity->Translate(glm::vec3(m_vParticles[0].v2Direction * m_vParticles[0].fSpeed * (float)Time::dTimeDelta, 0));
		m_vParticles[0].pEntity->Translate(glm::vec3(0, -m_fGravity * Time::dTimeDelta, 0));
		glm::vec2 v2Distance = Utils::GetDistance2D(m_vParticles[0].pEntity, this->shared_from_this());
		
		if (sqrt(pow(v2Distance.x, 2) + pow(v2Distance.y, 2)) >= m_vParticles[0].fFalloffDistance || m_vParticles[0].fTimeLength > m_vParticles[0].fFallOffTime)
		{
			SceneManager::GetInstance()->GetCurrentScene()->DestroyEntity(m_vParticles[0].pEntity);
			m_vParticles.clear();
		}
	}
	else if (m_fCurrentLifeTime >= m_fLifeTime) // empty and time finished
	{
		SceneManager::GetInstance()->GetCurrentScene()->DestroyEntity(this->shared_from_this());
	}
}

/************************************************************
#--Description--#:	Render to the screen
#--Author--#: 		Alex Coultas
#--Parameters--#: 	NA
#--Return--#: 		NA
************************************************************/
void ParticleSystem::Render()
{
	for (auto it : m_vParticles)
	{
		it.pEntity->DrawEntity();
	}
}
