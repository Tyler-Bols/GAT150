#pragma once
#include "Core/System.h"
#include "Box2d/box2d.h"
#include "Objects/GameObject.h"
namespace nc
{
	class GameObject;
	class PhysicsSystem : public System
	{
	public:
		struct RigidBodyData
		{
		Vector2 size;
		float density{ 1 };
		float friction{ 1 };
		float restitution{ 0.3f };
		float gravityScale{ 1 };
		bool lockAngle{ false };
		bool isDynamic{ false };
		bool isSensor{ false };
		};
	public:

		virtual bool Startup() override;

		virtual void Shutdown() override;

		virtual void Update() override;

		b2Body* CreateBody(const Vector2& position, const Vector2& size, float density, bool isDynamic = true);
		b2Body* CreateBody(const Vector2& position, float angle, const RigidBodyData& data , GameObject* gameObject);
		void DestroyBody(b2Body* body);

		static Vector2 WorldToScreen(const Vector2& world) { return world * 32.0f; }
		static Vector2 ScreenToWorld(const Vector2& screen) { return screen * (1.f / 32.0f); }

	protected:
		class ContactListener* m_contactListener{ nullptr };
		b2World* m_world{ nullptr };
	};
}
