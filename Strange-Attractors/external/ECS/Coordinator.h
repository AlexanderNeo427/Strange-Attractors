#ifndef COORDINATOR
#define COORDINATOR

#include "ECS_Types.h"
#include "ComponentManager.h"
#include "EntityManager.h"
#include "SystemManager.h"

namespace ECS
{
	class Coordinator
	{
	public:
		static Coordinator& Instance()
		{
			static Coordinator s_instance;
			return s_instance;
		}
	public:
		void Init()
		{
			m_componentManager = std::make_unique<ComponentManager>();
			m_entityManager    = std::make_unique<EntityManager>();
			m_systemManager    = std::make_unique<SystemManager>();
		}

		EntityID CreateEntity()
		{
			return m_entityManager->CreateEntity();
		}

		void DestroyEntity(const EntityID& entity)
		{
			m_entityManager->DestroyEntity(entity);
			m_componentManager->EntityDestroyed(entity);
			m_systemManager->EntityDestroyed(entity);
		}

		template<class T>
		void RegisterComponent()
		{
			m_componentManager->RegisterComponent<T>();
		}

		template<class T>
		void AddComponent(const EntityID& entity, const T& component)
		{
			m_componentManager->AddComponent<T>(entity, component);

			auto signature = m_entityManager->GetSignature(entity);
			signature.set(m_componentManager->GetComponentType<T>(), true);
			m_entityManager->SetSignature(entity, signature);

			m_systemManager->EntitySignatureChanged(entity, signature);
		}

		template<class T>
		void RemoveComponent(const EntityID& entity)
		{
			m_componentManager->RemoveComponent<T>(entity);

			ECS::Signature signature = m_entityManager->GetSignature(entity);
			signature.set(m_componentManager->GetComponentType<T>(), false);
			m_entityManager->SetSignature(entity, signature);

			m_systemManager->EntitySignatureChanged(entity, signature);
		}

		template<class T>
		T& GetComponent(const EntityID& entity)
		{
			return m_componentManager->GetComponent<T>(entity);
		}

		template<class T>
		ComponentTypeID GetComponentTypeID()
		{
			return m_componentManager->GetComponentType<T>();
		}

		template<class T>
		std::shared_ptr<T> RegisterSystem()
		{
			return m_systemManager->RegisterSystem<T>();
		}

		template<class T>
		void SetSystemSignature(const Signature& signature)
		{
			m_systemManager->SetSignature<T>(signature);
		}
	private:
		Coordinator() {}

		std::unique_ptr<ComponentManager> m_componentManager;
		std::unique_ptr<EntityManager>	  m_entityManager;
		std::unique_ptr<SystemManager>    m_systemManager;
	};
}

#endif
