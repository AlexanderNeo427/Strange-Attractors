#ifndef COMPONENT_ARRAY
#define COMPONENT_ARRAY

#include "ECS_Types.h"

namespace ECS
{
	class IComponentArray
	{
	public:
		virtual ~IComponentArray() = default;
		virtual void EntityDestroyed(const EntityID& entityID) = 0;
	};

	template<class T>
	class ComponentArray : public IComponentArray
	{
	public:
		void InsertData(const EntityID& entityID, const T& component)
		{
			assert(m_entityToIndexMap.find(entityID) == m_entityToIndexMap.end() && "Component added to same entityID more than once.");

			size_t newIndex = m_size;
			m_entityToIndexMap[entityID] = newIndex;
			m_indexToEntityMap[newIndex] = entityID;
			m_componentArray[newIndex] = component;
			++m_size;
		}
		void RemoveData(const EntityID& entityID)
		{
			assert(m_entityToIndexMap.find(entityID) != m_entityToIndexMap.end() && "Removing non-existent component.");

			size_t indexOfRemovedEntity = m_entityToIndexMap[entityID];
			size_t indexOfLastElement = m_size - 1;
			m_componentArray[indexOfRemovedEntity] = m_componentArray[indexOfLastElement];

			EntityID entityOfLastElement = m_indexToEntityMap[indexOfLastElement];
			m_entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
			m_indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

			m_entityToIndexMap.erase(entityID);
			m_indexToEntityMap.erase(indexOfLastElement);

			--m_size;
		}
		T& GetData(const EntityID& entityID)
		{
			assert(m_entityToIndexMap.find(entityID) != m_entityToIndexMap.end() && "Retrieving non-existent component.");
			return m_componentArray[m_entityToIndexMap[entityID]];
		}
		void EntityDestroyed(const EntityID& entityID) override
		{
			if (m_entityToIndexMap.find(entityID) != m_entityToIndexMap.end())
			{
				RemoveData(entityID);
			}
		}
	private:
		std::array<T, MAX_ENTITIES> m_componentArray;
		std::unordered_map<EntityID, size_t> m_entityToIndexMap;
		std::unordered_map<size_t, EntityID> m_indexToEntityMap;
		size_t m_size;
	};
};

#endif
