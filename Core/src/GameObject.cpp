#include "GameObject.h"

#include "Component.h"
#include "Components/Transform.h"

#include "BaseMacros.h"

bluefir::core::GameObject::GameObject()
{
	components_[TYPE_TRANSFORM].push_back(transform = new Transform(this));
}

bluefir::core::GameObject::~GameObject()
{
	for (auto it = components_.begin(); it != components_.end(); ++it)
	{
		for (auto jt = it->second.rbegin(); jt != it->second.rend(); ++jt)
			delete *jt;
		it->second.clear();
	}
	components_.clear();
}

void bluefir::core::GameObject::PreUpdate()
{
	// PreUpdate all components
	for (auto it = components_.begin(); it != components_.end(); ++it)
	{
		for (auto jt = it->second.begin(); jt != it->second.end(); ++jt)
			(*jt)->PreUpdate();
	}

	// PreUpdate Children
	for (auto it = children_.begin(); it != children_.end(); ++it)
		(*it)->PreUpdate();
}

void bluefir::core::GameObject::Update()
{
	// Update all components
	for (auto it = components_.begin(); it != components_.end(); ++it)
	{
		for (auto jt = it->second.begin(); jt != it->second.end(); ++jt)
			(*jt)->Update();
	}

	// Update Children
	for (auto it = children_.begin(); it != children_.end(); ++it)
		(*it)->Update();
}

void bluefir::core::GameObject::PostUpdate()
{
	// PostUpdate all components
	for (auto it = components_.begin(); it != components_.end(); ++it)
	{
		for (auto jt = it->second.begin(); jt != it->second.end(); ++jt)
			(*jt)->PostUpdate();
	}

	// PostUpdate Children
	for (auto it = children_.begin(); it != children_.end(); ++it)
		(*it)->PostUpdate();
}

void bluefir::core::GameObject::SetParent(GameObject * parent)
{
	if (parent_) parent_->RemoveChild(this);

	if(parent) parent_ = parent;
	else parent_ = &modules::scene::scene_root;

	if (parent_) parent_->AddChild(this);

	transform->ToLocalCoordinates();
}

void bluefir::core::GameObject::AddChild(GameObject * child)
{
	ASSERT(child);
	children_.push_back(child);
}

void bluefir::core::GameObject::RemoveChild(const GameObject * child)
{
	ASSERT(child);

	for (auto it = children_.begin(); it != children_.end(); ++it)
	{
		if ((*it) == child)
		{
			(*it) = nullptr;
			children_.erase(it);
			return;
		}
	}

	LOGWARNING("While trying to remove a child, reached the end of the children list without finding the target.");
}
