//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name		:    Utils.h
// Description		:    Header file outlining the Class
// Author			:    Alex Coultas
// Mail				:    alex.cou7417@mediadesign.school.nz
//

// Library Includes //
#include <string>
#include <memory>

// OpenGL Library Includes //
#include <glm/common.hpp>

// Forward Declarations //
class Entity;

#pragma once
class Utils
{
public:
	struct AnimInfo
	{
		glm::vec2 v2FrameSize;
		glm::vec2 v2FrameCount;
		glm::vec2 v2CurrentFrame = { 0, 0 };
		glm::vec2 v2StartFrame = { 0, 0 };
		glm::vec2 v2EndFrame = { 0, 0 };
		int iFPS = 30;
		void Advance()
		{
			v2CurrentFrame.x++;
			if (v2CurrentFrame.x > v2FrameCount.x || v2CurrentFrame.x > v2EndFrame.x)
			{
				v2CurrentFrame.x = 0;
				v2CurrentFrame.y++;
				if (v2CurrentFrame.y > v2FrameCount.y || v2CurrentFrame.y > v2EndFrame.y)
				{
					v2CurrentFrame = v2StartFrame;
				}
			}
		}
	};

	typedef struct CollisionInfo2D
	{
		float fHeight;
		float fWidth;
		glm::vec2 v2Offset = glm::vec2();
	} Col2DI;

	struct Transform
	{
		glm::vec3 Position;
		glm::vec3 Rotation;
		glm::vec3 Scale;
	};

	enum EANCHOR
	{
		TOP_LEFT,
		TOP_CENTER,
		TOP_RIGHT,
		CENTER_LEFT,
		CENTER,
		CENTER_RIGHT,
		BOTTOM_LEFT,
		BOTTOM_CENTER,
		BOTTOM_RIGHT
	};
	
	enum EMESHTYPE
	{
		NONE,
		PLANE,
		PYRAMID,
		CUBE,
		SPHERE,
		MODEL
	};

	static glm::vec3 GetAncoredPosition(glm::vec3 position, glm::vec3 Dimensions, EANCHOR _AnchorType);
	static glm::vec3 GetAncoredPosition2D(glm::vec2 position, glm::vec2 Dimensions, EANCHOR _AnchorType);
	static glm::vec3 GetTextAncoredPosition(glm::vec2 position, glm::vec2 Dimensions, EANCHOR _AnchorType);

	static bool isColliding2D(std::shared_ptr<Entity> Entity1, std::shared_ptr<Entity> Entity2);
	//static bool isColliding2D(Entity* Entity1, std::shared_ptr<Entity> Entity2);

	static bool CheckCollision2D(std::shared_ptr<Entity> Entity1, std::shared_ptr<Entity> Entity2, glm::vec2 Movement);
	//static bool CheckCollision2D(Entity* Entity1, std::shared_ptr<Entity> Entity2, glm::vec2 Movement);
		
	static glm::vec2 GetDistance2D(std::shared_ptr<Entity> Entity1, std::shared_ptr<Entity> Entity2);
	//static glm::vec2 GetDistance2D(Entity* Entity1, std::shared_ptr<Entity> Entity2);
	//static glm::vec2 FindTextDimenions(std::string text);

	static glm::vec2 GetDifference2D(std::shared_ptr<Entity> Entity1, std::shared_ptr<Entity> Entity2);

	static int AddEntityID();

	static std::shared_ptr<Entity> WorldCubeMap;

private:
	static int iEntityNumber;
};

