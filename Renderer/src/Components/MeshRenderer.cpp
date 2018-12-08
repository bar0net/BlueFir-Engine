#include "MeshRenderer.h"

#include "BaseMacros.h"
#include "../ModuleRenderer.h"

#include "GameObject.h"
#include "Components/Transform.h"

bluefir::core::MeshRenderer::MeshRenderer(const GameObject * gameObject) : Component(gameObject)
{
	ASSERT(gameObject);
}

bluefir::core::MeshRenderer::~MeshRenderer()
{
}

void bluefir::core::MeshRenderer::Update()
{
	float model[16];
	gameObject_->transform->ModelMatrix(model);
	modules::ModuleRenderer::getInstance().Draw(model, mesh_ID_, shader_ID_);
}
