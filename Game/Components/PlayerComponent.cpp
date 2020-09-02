#include "PlayerComponent.h"
#include "Components/PhysicsComponent.h"
#include "Components/AudioComponent.h"
#include "Components/RigidBodyComponent.h"
#include "Components/SpriteComponent.h"
#include "Core/EventManager.h"
#include "pch.h"

bool nc::PlayerComponent::Create(void* data)
{
	m_owner = static_cast<GameObject*>(data);
	EventManager::Instance().Subscribe("CollisionEnter", std::bind(&PlayerComponent::onCollisionEnter, this, std::placeholders::_1), m_owner);
	EventManager::Instance().Subscribe("CollisionExit", std::bind(&PlayerComponent::onCollisionExit, this, std::placeholders::_1), m_owner);

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
		if (/*onGround &&*/ m_owner->m_engine->GetSystem <InputSystem>()->GetButtonState(SDL_SCANCODE_SPACE) == nc::InputSystem::eButtonState::PRESSED)
		{	force.y = -1500;
		AudioComponent* audiocomponent = m_owner->GetComponent<AudioComponent>();
		audiocomponent->SetSoundName("jump.wav");
		audiocomponent->Play();
		}

		

		RigidBodyComponent* component = m_owner->GetComponent<RigidBodyComponent>();
		if (component)
		{
			component->ApplyForce(force);

			Vector2 velocity = component->GetVelocity();
			SpriteComponent* spriteComponent = m_owner->GetComponent<SpriteComponent>();
			if (velocity.x <= -0.15f)spriteComponent->Flip();
			if (velocity.x >= 0.15f)spriteComponent->Flip(false);
		}


		/*auto coinContacts = m_owner->GetObjectWithTag("Coin");
		for (GameObject* contact : coinContacts)
		{
			contact->m_flags[GameObject::eFlags::DESTROY] = true;
		}
		auto enemyContacts = m_owner->GetObjectWithTag("Enemy");
		for (GameObject* contact : enemyContacts)
		{
			contact->m_flags[GameObject::eFlags::DESTROY] = true;
		}*/

}

void nc::PlayerComponent::onCollisionEnter(const Event& event)
{

	GameObject* gameobject = dynamic_cast<GameObject*>(event.sender);
	std::cout << "collision event: " << gameobject->m_name << std::endl;
	if (gameobject->m_tag == "Enemy")
	{
		AudioComponent* audiocomponent = m_owner->GetComponent<AudioComponent>();
		audiocomponent->SetSoundName("grunt.wav");
		audiocomponent->Play();
	}
	if (gameobject->m_tag == "Coin")
	{
		AudioComponent* audiocomponent = m_owner->GetComponent<AudioComponent>();
		audiocomponent->SetSoundName("coin.wav");
		audiocomponent->Play();
		gameobject->m_flags[GameObject::eFlags::DESTROY] = true;

	}

}

void nc::PlayerComponent::onCollisionExit(const Event& event)
{
	GameObject* gameobject = dynamic_cast<GameObject*>(event.sender);
	std::cout << "collision end: " << gameobject->m_name << std::endl;


}
