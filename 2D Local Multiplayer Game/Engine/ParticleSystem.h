//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name		:    ParticleSystem.h
// Description		:    Header file outlining the Class
// Author			:    Alex Coultas
// Mail				:    alex.cou7417@mediadesign.school.nz
//

// Library Includes //
#include <vector>
#include <memory>

// OpenGL Library Includes //
#include <glm\common.hpp>

// Local Includes //
#include "Entity.h"

#pragma once
class ParticleSystem : public Entity
{
public:
	ParticleSystem(Utils::Transform _Transform, const char* _CharName);
	~ParticleSystem();

	void AddParticleType(const char* _Charname);
	void SetSizeRange(glm::vec2 _v2SizeRange);
	void SetSpeedRange(glm::vec2 _v2SpeedRange);
	void SetDelayRange(glm::vec2 _v2DelayRange);
	void SetFalloffRange(glm::vec2 _v2FalloffRange);
	void SetFalloffTime(glm::vec2 _v2FalloffTime);
	void SetDirectionRange(glm::vec2 _v2DirectionRangeX, glm::vec2 _v2DirectionRangeY);
	void SetGravity(float _fGravity);
	void SetLifeTime(float _fLifetime);
	
	static float RandomBetweenRange(float _fMin, float _fMax);

	void Update();
	void Render();

	struct Particle
	{
		std::shared_ptr<Entity> pEntity;
		float fSpeed;
		glm::vec2 v2Direction;
		float fFalloffDistance;
		float fFallOffTime;
		float fTimeLength;
	};
	
	std::vector<Particle> m_vParticles;
	std::vector<const char*> m_vParticlePaths;

private:
	glm::vec2 m_v2SizeRange = { 0.05, 0.2 };
	glm::vec2 m_v2DelayRange = { 0.1f, 0.2f };
	glm::vec2 m_v2SpeedRange = { 0.1f, 0.3f };
	glm::vec2 m_v2FalloffRange = { 0.5f, 1.0f };
	glm::vec2 m_v2FalloffTime = { 0.5f, 1.0f };
	glm::vec2 m_v2DirectionRangeX{ -1, 1 };
	glm::vec2 m_v2DirectionRangeY{ -1, 1 };
	float m_fGravity = 0.0f;
	float m_fLifeTime = 0.0f;

	float m_fCurrentLifeTime = 0;
	float m_fCurrentDelay = 0;
};

