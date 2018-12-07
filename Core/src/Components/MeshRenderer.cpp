#include "MeshRenderer.h"

#include "BaseMacros.h"

bluefir::core::MeshRenderer::MeshRenderer(const GameObject * gameObject) : Component(gameObject)
{
	ASSERT(gameObject);
}

bluefir::core::MeshRenderer::~MeshRenderer()
{
}

void bluefir::core::MeshRenderer::Update()
{
}
