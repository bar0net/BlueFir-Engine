#include "Component.h"

#include "GameObject.h"

bluefir::core::Component::Component(const GameObject * gameObject) : gameObject_(gameObject)
{
}

bluefir::core::Component::~Component()
{
}
