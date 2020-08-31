#pragma once
#include "Objects/Object.h"
#include "Math/Transform.h"
#include "Engine.h"
#include <bitset>
#include <list>
//#include <vector>
namespace nc 
{
	class Engine;
	class Component;
	class Scene;

	class GameObject : public Object
	{
	public:
		enum eFlags
		{
			ACTIVE,
			VISIBLE,
			DESTROY,
			TRANSIENT
		};


	public:
		GameObject() = default;
		GameObject(const GameObject& other);

		virtual bool Create(void* data = nullptr);
		virtual void Destroy();

		virtual Object* Clone() override{ return new GameObject{ *this }; }

		void Read(const rapidjson::Value& value);

		void Update();
		void Draw();


		void BeginContact(GameObject* gameObject);
		void EndContact(GameObject* gameObject);
		std::vector<GameObject*> GetObjectWithTag(const std::string& tag);

		template<typename T>
		T* GetComponent()
		{
			T* result{ nullptr };
				for (auto component : m_components)
				{
					result = dynamic_cast<T*>(component);
					if (result) break;
				}
				return result;
		}


		void AddComponent(Component* component);
		void RemoveComponent(Component* component);
		void RemoveAllComponents();
		void ReadComponents(const rapidjson::Value& value);
		
		friend class Component;
		friend class PhysicsComponent;

	public:
		Transform m_transform;
		Engine* m_engine{nullptr};
		Scene* m_scene{ nullptr };
		float m_lifetime{0};

		std::bitset<32> m_flags;

		std::string m_name;
		std::string m_tag;

	protected:
		std::vector<Component*> m_components;
		std::list<GameObject*> m_contacts;


		

	};

}
