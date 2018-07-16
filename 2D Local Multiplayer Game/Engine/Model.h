//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// File Name    	:    Cube.h
// Description    	:    Header file outlining the Class
// Author       	:    Alex Coultas
// Mail         	:    alex.cou7417@mediadesign.school.nz
//

#pragma once
// This Includes //
#include "Mesh.h"

// Library Includes //
#include <memory>

// Engine Includes //
#include "ModelObject.h"

class Model : public Mesh
{
public:
	Model(glm::vec4 Colour, const char *  ModelSource);
	~Model();

	void BindModel();
	void Rebind();
	void SetLit(bool _bIsLit);

	void Render(Utils::Transform Newtransform);
	void Update();

	std::shared_ptr<ModelObject> pModelObject;
};

