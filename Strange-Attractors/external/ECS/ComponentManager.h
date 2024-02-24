#ifndef COMPONENT_MANAGER
#define COMPONENT_MANAGER

#include "ECS_Types.h"
#include "ComponentArray.h"

namespace ECS
{
	class ComponentManager
	{
	public:
		template<class T>
		void RegisterComponent()
		{
			const char* typeName = typeid(T).name();
			assert(m_componentTypes.find(typeName) == m_componentTypes.end() && "Registering component type more than once.");

			m_componentTypes.insert({ typeName, m_nextComponentTypeID });
			m_componentArrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });
			++m_nextComponentTypeID;
		}
		template<class T>
		ComponentTypeID GetComponentType()
		{
			const char* typeName = typeid(T).name();
			assert(m_componentTypes.find(typeName) != m_componentTypes.end() && "Component not registered before use.");
			return m_componentTypes[typeName];
		}
		template<class T>
		void AddComponent(const EntityID& entityID, const T& component)
		{
			GetComponentArray<T>()->InsertData(entityID, component);
		}
		template<class T>
		void RemoveComponent(const EntityID& entityID)
		{
			GetComponentArray<T>()->RemoveData(entityID);
		}
		template<class T>
		T& GetComponent(const EntityID& entityID)
		{
			return GetComponentArray<T>()->GetData(entityID);
		}
		void EntityDestroyed(const EntityID& entityID)
		{
			for (auto const& pair : m_componentArrays)
			{
				auto const& component = pair.second;
				component->EntityDestroyed(entityID);
			}
		}
	private:
		std::unordered_map<const char*, ComponentTypeID> m_componentTypes;
		std::unordered_map<const char*, std::shared_ptr<IComponentArray>> m_componentArrays;

		ComponentTypeID m_nextComponentTypeID;

		template<class T>
		std::shared_ptr<ComponentArray<T>> GetComponentArray()
		{
			const char* typeName = typeid(T).name();
			assert(m_componentTypes.find(typeName) != m_componentTypes.end() && "Component not registered before use.");
			return std::static_pointer_cast<ComponentArray<T>>(m_componentArrays[typeName]);
		}
	};
}

#endif
