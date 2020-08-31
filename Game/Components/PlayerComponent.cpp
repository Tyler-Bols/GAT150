#include "PlayerComponent.h"
#include "Components/PhysicsComponent.h"
#include "Components/AudioComponent.h"
#include "Components/RigidBodyComponent.h"
#include "Components/SpriteComponent.h"
#include "pch.h"

bool nc::PlayerComponent::Create(void* data)
{
	m_owner = static_cast<GameObject*>(data);
	//m_owner->m_engine = static_cast<Engine*>(data);
	return true;

}

void nc::PlayerComponent::Destroy()
{
}

void nc::PlayerComponent::Update()
{
	auto contacts = m_owner->GetObjectWithTag("Floor");
	bool onGround = !contacts.empty();
		nc::Vector2 force = { 0,0 };
	
		if (m_owner->m_engine->GetSystem <InputSystem>()->GetButtonState(SDL_SCANCODE_A) == nc::InputSystem::eButtonState::HELD)
		{	force.x = -100;}
		if (m_owner->m_engine->GetSystem <InputSystem>()->GetButtonState(SDL_SCANCODE_D) == nc::InputSystem::eButtonState::HELD)
		{	force.x = 100;}
		if (onGround && m_owner->m_engine->GetSystem <InputSystem>()->GetButtonState(SDL_SCANCODE_SPACE) == nc::InputSystem::eButtonState::PRESSED)
		{	force.y = -1500;}

		

		RigidBodyComponent* component = m_owner->GetComponent<RigidBodyComponent>();
		if (component)
		{
			component->ApplyForce(force);

			Vector2 velocity = component->GetVelocity();
			SpriteComponent* spriteComponent = m_owner->GetComponent<SpriteComponent>();
			if (velocity.x <= -0.15f)spriteComponent->Flip();
			if (velocity.x >= 0.15f)spriteComponent->Flip(false);
		}


		auto coinContacts = m_owner->GetObjectWithTag("Coin");
		for (GameObject* contact : coinContacts)
		{
			contact->m_flags[GameObject::eFlags::DESTROY] = true;
		}
		auto enemyContacts = m_owner->GetObjectWithTag("Enemy");
		for (GameObject* contact : enemyContacts)
		{
			/*AudioComponent audioComponent = m_owner->GetComponent<AudioComponent>();
			if (audioComponent)
			{

			}*/
		}

		/*if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_SPACE) == nc::InputSystem::eButtonState::PRESSED)
		{ force.y = -400000;
		AudioComponent* audioComponent = m_owner->GetComponent<AudioComponent>(); 
		if (audioComponent) { audioComponent->Play(); } 
		}*/
}
