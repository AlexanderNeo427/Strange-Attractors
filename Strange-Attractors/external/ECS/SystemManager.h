#ifndef SYSTEM_MANAGER
#define SYSTEM_MANAGER

#include "ECS_Types.h"

namespace ECS
{
	struct System
	{
		std::set<EntityID> m_entities;
	};

	class SystemManager
	{
	public:
		template<class T>
		std::shared_ptr<T> RegisterSystem()
		{
			const char* typeName = typeid(T).name();
			assert(m_systems.find(typeName) == m_systems.end() && "Registering system more than once.");

			auto system = std::make_shared<T>();
			m_systems.insert({ typeName, system });

			return system;
		}

		template<class T> 
		void SetSignature(const Signature& signature)
		{
			const char* typeName = typeid(T).name();
			assert(m_systems.find(typeName) != m_systems.end() && "System used before registered.");
			m_signatures.insert({ typeName, signature });
		}

		void EntityDestroyed(const EntityID& entityID)
		{
			for (auto const& pair : m_systems)
			{
				std::shared_ptr<ECS::System> const& system = pair.second;
				system->m_entities.erase(entityID);
			}
		}

		void EntitySignatureChanged(const EntityID& entityID, const Signature& entitySignature)
		{
			for (auto const& pair : m_systems)
			{
				auto const& type = pair.first;
				std::shared_ptr<ECS::System> const& system = pair.second;
				ECS::Signature const& systemSignature = m_signatures[type];

				if ((entitySignature & systemSignature) == systemSignature)
				{
					system->m_entities.insert(entityID);
				}
				else
				{
					system->m_entities.erase(entityID);
				}
			}
		}
	private:
		std::unordered_map<const char*, Signature> m_signatures;
		std::unordered_map<const char*, std::shared_ptr<System>> m_systems;
	};
};

#endif
