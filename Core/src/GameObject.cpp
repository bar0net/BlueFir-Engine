#include "GameObject.h"

#include "Components/Transform.h"

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
