#pragma once
#include "Objects/Object.h"
#include "Math/Transform.h"
#include "Engine.h"
#include <vector>
namespace nc 
{
	class Component;

	class GameObject : public Object
	{
	public:

		virtual bool Create(void* data = nullptr);
		virtual void Destroy();

		virtual Object* Clone() override{ return new GameObject{ *this }; }

		void Read(const rapidjson::Value& value);

		void Update();
		void Draw();

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
		std::string m_name;

	protected:
		std::vector<Component*> m_components;

		

	};

}
