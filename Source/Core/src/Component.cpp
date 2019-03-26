#include "Component.h"

#include "GameObject.h"

bluefir::core::Component::Component(const GameObject * gameObject, ComponentType type) : gameObject_(gameObject), type_(type)
{
}

bluefir::core::Component::~Component()
{
}

void bluefir::core::Component::PreUpdate()
{
}

void bluefir::core::Component::Update()
{
}

void bluefir::core::Component::PostUpdate()
{
}
