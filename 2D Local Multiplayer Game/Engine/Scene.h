//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name		:    Scene.h
// Description		:    Header file outlining the Class
// Author			:    Alex Coultas
// Mail				:    alex.cou7417@mediadesign.school.nz
//

// Library Includes //
#include <string>
#include <vector>
#include <memory>

// OpenGL Library Includes //
#include "Entity.h"
#include "UIElement.h"
#include "UIText.h"


#pragma once
class Scene : public std::enable_shared_from_this<Scene>
{
public:
	Scene(std::string sSceneName);
	~Scene();

	void DeleteScene();
	virtual void RenderScene();

	void AddEntity(std::shared_ptr<Entity> _Entity);
	std::shared_ptr<Entity> AddEntity(Utils::Transform _Transform, float _fWidth, float _fHeight, Utils::EANCHOR _Anchor, glm::vec4 _Colour);
	std::shared_ptr<Entity> AddEntity(Utils::Transform _Transform, float _fWidth, float _fHeight, Utils::EANCHOR _Anchor, glm::vec4 _Colour, const char* TextureSource, int iCount, bool bHorizontal);
	void DestroyEntity(std::shared_ptr<Entity> _Entity);

	void AddUIElement(std::shared_ptr<UIElement> Element);
	void AddUITextElement(std::shared_ptr<UIText> Element);
	void AddUITextElement(glm::vec2 _Position, float _fRotation, glm::vec4 _Colour, std::string _sText, std::string font, int iPSize, Utils::EANCHOR _Anchor);
	void DestroyUIElement(std::shared_ptr<UIElement> _Element);
	
	virtual void Update();
	virtual void OnLoadScene() {};

	bool operator==(const Scene& rhs)const;

	std::string SceneName;
	std::vector<std::shared_ptr<Entity>> Entities;
	std::vector<std::shared_ptr<UIElement>> UIElements;
};

