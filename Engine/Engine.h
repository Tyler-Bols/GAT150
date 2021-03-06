#pragma once
#include "Graphics/Renderer.h"
#include "Resources/ResourceManager.h"
#include "Physics/PhysicsSystem.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Core/Timer.h"
#include <vector>

namespace nc
{
	class System;
	class Engine
	{
	public:
		bool Startup();
		void Shutdown();

		void Update();


		template<typename T>
		T* GetSystem();
		

		nc::FrameTimer& GetTimer() { return m_timer; }

	protected:
		std::vector<System*> m_systems;
		nc::FrameTimer m_timer;
	};


}
	template<typename T>
	inline T* nc::Engine::GetSystem()	{
		T* result = nullptr;
		for (auto system : m_systems)
		{
			result = dynamic_cast<T*>(system);
			if (result != nullptr) break;
		}
		return result;
	}