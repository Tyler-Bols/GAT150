#include "pch.h"
#include "Scene.h"
#include "GameObject.h"
#include "ObjectFactory.h"

bool nc::Scene::Create(void* data)
{
    m_engine = static_cast<Engine*>(data);
    return true;
}

void nc::Scene::Destroy()
{
    RemoveAllGameObjects();
}

void nc::Scene::Read(const rapidjson::Value& value)
{
    if (value.HasMember("GameObjects"))
    {
        const rapidjson::Value& objectsValue = value["GameObjects"];
        if (objectsValue.IsArray())
        {
            ReadGameObjects(objectsValue); 
        }
    
    }
}

void nc::Scene::ReadGameObjects(const rapidjson::Value& value)
{
    for (rapidjson::SizeType i = 0; i < value.Size(); i++)
    {
        const rapidjson::Value& objectValue = value[i];
        if (objectValue.IsObject())
        {
            std::string typeName;
            json::Get(objectValue, "type", typeName);
            nc::GameObject* gameObject = nc::ObjectFactory::Instance().Create<GameObject>(typeName);
            if (gameObject)
            {
                gameObject->Create(m_engine);
                gameObject->Read(objectValue);
                gameObject->m_engine = m_engine;
                AddGameObject(gameObject);
            }

        }

    }

}

void nc::Scene::ReadPrototypes(const rapidjson::Value& value)
{
    for (rapidjson::SizeType i = 0; i < value.Size(); i++)
     {
    const rapidjson::Value& objectValue = value["GameObject"];
    if (objectValue.IsObject())
    {
        std::string typeName;
        json::Get(objectValue, "type", typeName);
        nc::GameObject* gameObject = nc::ObjectFactory::Instance().Create<GameObject>(typeName);
        if (gameObject)
        {
            gameObject->Create(m_engine);
            gameObject->Read(objectValue);
            gameObject->m_engine = m_engine;
            ObjectFactory::Instance().Register(gameObject->m_name, new Prototype<Object>(gameObject));
        }

    }

    }

}


void nc::Scene::Update()
{
    for (auto gameObject : m_gameObjects)
    {
        gameObject->Update();

    }
}

void nc::Scene::Draw()
{
    for (auto gameObject : m_gameObjects)
    {
        gameObject->Draw();

    }

}

nc::GameObject* nc::Scene::Find(const std::string& name)
{
    for (auto gameObject : m_gameObjects)
    {
        if (gameObject->m_name == name)
        {

            return gameObject;
        }

    }
    return nullptr;
}

void nc::Scene::AddGameObject(GameObject* gameObject)
{
    m_gameObjects.push_back(gameObject);
}

void nc::Scene::RemoveGameObject(GameObject* gameObject)
{
    auto iter = std::find(m_gameObjects.begin(), m_gameObjects.end(), gameObject);
    if (iter != m_gameObjects.end())
    {
        (*iter)->Destroy();
        delete(*iter);
        m_gameObjects.erase(iter);

    }

}

void nc::Scene::RemoveAllGameObjects()
{
    for (auto gameObject : m_gameObjects)
    {
        gameObject->Destroy();
        delete gameObject;
    }
    m_gameObjects.clear();
}
