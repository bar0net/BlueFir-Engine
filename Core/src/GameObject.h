#ifndef BF_CORE_GAMEOBJECT
#define BF_CORE_GAMEOBJECT

#include "LogSystem.h"
#include <unordered_map>
#include <vector>

namespace bluefir::core
{
	class Component;
	enum class ComponentType;
	
	class GameObject
	{
	public:
		GameObject() 
		{
			transform_ = new Transform(this);
			components_[ComponentType::TRANSFORM].push_back(transform_);
		}
		virtual ~GameObject() 
		{
			for (auto it = components_.begin(); it != components_.end(); ++it)
			{
				for (auto jt = it->second.rbegin(); jt != it->second.rend(); ++jt)
					delete *jt;
				it->second.clear();
			}
			components_.clear();
		}

		template <class T>
		T* AddComponent()
		{
			if (T::Type() == ComponentType::TRANSFORM)
			{
				return LOGERROR("Cannot create additional transforms.");
			}
			T* component = new T(this);
			components_[T::Type()].push_back(component);
			return component;
		}

		template <class T>
		const std::vector<T*>* GetComponents() const
		{
			auto it = components_.find(T::Type());
			if (it == components_.end())
			{
				LOGWARNING("GameObject %i doesn't have components of type %i", id_, (int)T::Type());
				return nullptr;
			}
			else return (std::vector<T*>*)(&(it->second));
		}

		template <class T>
		T* GetComponent() const
		{
			return (*GetComponents<T>())[0];
		};


		template <class T>
		void RemoveComponent(T* component)
		{
			if (T::Type() == ComponentType::TRANSFORM)
			{
				return LOGERROR("Cannot delete transforms.");
			}
			auto it = components_.find(T::Type());
			if (it == components_.end())
			{
				LOGWARNING("GameObject %i doesn't have components of type %i", id_, (int)T::Type());
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

	public:
		Transform* transform_ = nullptr;

	private:
		std::unordered_map<ComponentType, std::vector<Component*>> components_;
		int id_ = 0;
	};
}

#endif // !BF_CORE_GAMEOBJECT

