#include "pch.h"
#include "SpriteComponent.h"
#include "Graphics/Texture.h"
using namespace nc;

bool nc::SpriteComponent::Create(void* data )
{
    m_owner = static_cast<GameObject*>(data);
    //m_owner->m_engine = static_cast<Engine*>(data);

    return true;


}

void nc::SpriteComponent::Destroy()
{
}

void nc::SpriteComponent::Read(const rapidjson::Value& value)
{
    json::Get(value, "texture", m_textureName);
    json::Get(value, "origin", m_origin);
    json::Get(value, "rect", m_rect);
}

void nc::SpriteComponent::Update()
{
}

void nc::SpriteComponent::Draw()
{
    Texture* texture = m_owner->m_engine->GetSystem<ResourceManager>()->Get<nc::Texture>(m_textureName, m_owner->m_engine->GetSystem<Renderer>());
    texture->Draw(m_rect, m_owner->m_transform.position, Vector2{ 1,1 } * m_owner->m_transform.scale, m_owner->m_transform.angle,m_origin);
    //{ 0,16,64,144 }
}
