#include "pch.h"
#include "GameObject.h"
#include "Components/Component.h"
#include "Components/RenderComponent.h"
#include "ObjectFactory.h"

namespace nc {

    bool GameObject::Create(void* data)
    {
        m_engine = static_cast<Engine*>(data);
        return true;

    }
    void GameObject::Destroy()
    {
        RemoveAllComponents();
    }

    void GameObject::Read(const rapidjson::Value& value)
    {
        json::Get(value, "name", m_name);

        json::Get(value, "position", m_transform.position);
        json::Get(value, "scale", m_transform.scale);
        json::Get(value, "angle", m_transform.angle);

        const rapidjson::Value& componentsValue = value["Components"]; 
        if (componentsValue.IsArray())
        { ReadComponents(componentsValue); }
    }

    void GameObject::AddComponent(Component* component)
    {
        m_components.push_back(component);
    }
    void GameObject::RemoveComponent(Component* component)
    {
        auto iter = std::find(m_components.begin(), m_components.end(), component);
        if (iter != m_components.end())
        {
            (*iter)->Destroy();
            delete (*iter);

        }

    }
    void GameObject::RemoveAllComponents()
    {
        for (auto component : m_components)
        {
            component->Destroy();
            delete component;
        }
        m_components.clear();
    }

    void GameObject::ReadComponents(const rapidjson::Value& value)
    {
        for (rapidjson::SizeType i = 0; i < value.Size(); i++) 
        {
            const rapidjson::Value& componentValue = value[i];
            if (componentValue.IsObject()) 
            {
                std::string typeName;
                json::Get(componentValue, "type", typeName);
                Component* component = ObjectFactory::Instance().Create<Component>(typeName);
                if (component)
                 {
                        component->Create(m_engine);
                        component->Read(componentValue);
                        AddComponent(component);
                }
            }
        }
    }

    void GameObject::Update()
    {
        for (auto component : m_components)
        {
            component->Update();
        }
    }
    void GameObject::Draw()
    {
        for (auto component : m_components)
        {
            RenderComponent* component = GetComponent<RenderComponent>();
            if (component)
            {
                component->Draw();
            }
        }
    }
}