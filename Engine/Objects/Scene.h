#pragma once
#include "Object.h"
namespace nc
{
	class Engine;
	class GameObject;

	class Scene : public Object
	{
	public:

		virtual bool Create(void* data = nullptr);
		virtual void Destroy();

		void Read(const rapidjson::Value& value);
		void ReadGameObjects(const rapidjson::Value& value);
		void ReadPrototypes(const rapidjson::Value& value);

		void Update();
		void Draw();

		GameObject* Find(const std::string& name);

		void AddGameObject(GameObject* gameObject); 
		void RemoveGameObject(GameObject* gameObject); 
		void RemoveAllGameObjects();

	protected:
		Engine* m_engine{ nullptr }; 
		std::list<GameObject*> m_gameObjects;

	};


}