#ifndef ENTITY_MANAGER
#define ENTITY_MANAGER

#include "ECS_Types.h"

namespace ECS
{
	class EntityManager
	{
	public:
		EntityManager()
			:
			m_availableEntities(),
			m_livingEntityCount(0)
		{
			for (EntityID entityID = 0; entityID < MAX_ENTITIES; ++entityID)
			{
				m_availableEntities.push(entityID);
			}
		}

		const EntityID& CreateEntity()
		{
			assert(m_livingEntityCount < MAX_ENTITIES && "Too many entities in existence.");

			EntityID entityID = m_availableEntities.front();
			m_availableEntities.pop();
			++m_livingEntityCount;

			return entityID;
		}

		void DestroyEntity(const EntityID& entityID)
		{
			assert(entityID < MAX_ENTITIES && "Entity out of range.");

			m_signatures[entityID].reset();
			m_availableEntities.push(entityID);
			--m_livingEntityCount;
		}

		void SetSignature(const EntityID& entityID, const Signature& signature)
		{
			assert(entityID < MAX_ENTITIES && "Entity out of range.");
			m_signatures[entityID] = signature;
		}

		const Signature& GetSignature(const EntityID& entityID)
		{
			assert(entityID < MAX_ENTITIES && "Entity out of range.");
			return m_signatures[entityID];
		}
	private:
		std::queue<EntityID> m_availableEntities;
		std::array<Signature, MAX_ENTITIES> m_signatures;
		uint32_t m_livingEntityCount;
	};
};

#endif
