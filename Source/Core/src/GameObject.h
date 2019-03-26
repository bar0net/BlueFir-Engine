#ifndef BF_CORE_GAMEOBJECT
#define BF_CORE_GAMEOBJECT

#include "LogSystem.h"
#include "BaseMacros.h"

#include <unordered_map>
#include <vector>
#include <string>
#include <set>

#define TYPE_TRANSFORM 1

namespace bluefir::editor
{
	class PanelScene;
}


namespace bluefir::core
{
	class Component;
	enum class ComponentType;
	class Transform;
	
	class GameObject
	{
	public:
		GameObject();
		virtual ~GameObject();

		void PreUpdate();
		void Update();
		void PostUpdate();

		void SetParent(GameObject* parent);
		const GameObject* GetParent() const { return parent_; }

		template <class T> T* AddComponent();
		template <class T> T* GetComponent() const;
		template <class T> const std::vector<T*>* GetComponents() const;
		template <class T> void RemoveComponent(T* component);

	protected:
		void AddChild(GameObject* child);
		void RemoveChild(const GameObject* child);

	public:
		std::string name = "GameObject";
		Transform* transform = nullptr;
		
	private:
		std::unordered_map<int, std::vector<Component*>> components_;
		int id_ = 0;

		GameObject* parent_ = nullptr;
		std::vector<GameObject*> children_;


	public:
		friend editor::PanelScene;
	};
}

namespace bluefir::modules::scene
{
	// TODO: Improve this (?)
	static bluefir::core::GameObject* scene_root;
}

template <class T>
T* bluefir::core::GameObject::AddComponent()
{
	if (T::Type() == TYPE_TRANSFORM)
	{
		LOGERROR("Cannot create additional transforms.");
		return nullptr;
	}
	T* component = new T(this);
	components_[T::Type()].push_back(component);
	return component;
}

template <class T>
const std::vector<T*>* bluefir::core::GameObject::GetComponents() const
{
	auto it = components_.find(T::Type());
	if (it == components_.end())
	{
		LOGWARNING("GameObject %i doesn't have components of type %i", id_, T::Type());
		return nullptr;
	}
	else return (std::vector<T*>*)(&(it->second));
}


template <class T>
T* bluefir::core::GameObject::GetComponent() const
{
	return (*GetComponents<T>())[0];
};

template <class T>
void bluefir::core::GameObject::RemoveComponent(T* component)
{
	if (T::Type() == TYPE_TRANSFORM)
	{
		return LOGERROR("Cannot delete transforms.");
	}
	auto it = components_.find(T::Type());
	if (it == components_.end())
	{
		LOGWARNING("GameObject %i doesn't have components of type %i", id_, T::Type());
		return;
	}

	LOGINFO("Removing component of type %i from GameObject %i", T::Type(), id_);
	for (auto jt = it->second.begin(); jt != it->second.end(); ++jt)
	{
		if ((T*)(*jt) != component) continue;

		if (it->second.size() == 1) components_.erase(it);
		else it->second.erase(jt);
		delete component; component = nullptr;
		return;
	}
}

#endif // !BF_CORE_GAMEOBJECT