#include "PlayerComponent.h"
#include "Components/PhysicsComponent.h"
#include "Components/AudioComponent.h"
#include "pch.h"

bool nc::PlayerComponent::Create(void* data)
{
	m_owner = static_cast<GameObject*>(data);
	m_owner->m_engine = static_cast<Engine*>(data);
	return true;

}

void nc::PlayerComponent::Destroy()
{
}

void nc::PlayerComponent::Update()
{
	
		if (m_owner->m_engine->GetSystem <InputSystem>()->GetButtonState(SDL_SCANCODE_A) == nc::InputSystem::eButtonState::HELD)
		{
			m_owner->m_transform.angle = m_owner->m_transform.angle - 10.0f * m_owner->m_engine->GetTimer().DeltaTime();
		}
		if (m_owner->m_engine->GetSystem <InputSystem>()->GetButtonState(SDL_SCANCODE_D) == nc::InputSystem::eButtonState::HELD)
		{
			m_owner->m_transform.angle = m_owner->m_transform.angle + 10.0f * m_owner->m_engine->GetTimer().DeltaTime();
		}

		nc::Vector2 force = { 0,0 };
		if (m_owner->m_engine->GetSystem <InputSystem>()->GetButtonState(SDL_SCANCODE_W) == nc::InputSystem::eButtonState::HELD)
		{
			force = nc::Vector2::forward * 50.0f;
		}
		force = nc::Vector2::Rotate(force, nc::DegreesToRadian(m_owner->m_transform.angle));

		PhysicsComponent* component = m_owner->GetComponent<PhysicsComponent>();
		if (component)
		{
			component->ApplyForce(force);
		}
		if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_SPACE) == nc::InputSystem::eButtonState::PRESSED)
		{ force.y = -400000;
		AudioComponent* audioComponent = m_owner->GetComponent<AudioComponent>(); 
		if (audioComponent) { audioComponent->Play(); } 
		}
}
