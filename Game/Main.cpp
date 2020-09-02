#include "pch.h"
#include "Graphics/Texture.h"
#include "Engine.h"
#include "Objects/GameObject.h"
#include "Components/PlayerComponent.h"
#include "Components/EnemyComponent.h"
#include"Components/AudioComponent.h"
#include "Core/Json.h"
#include "Objects/ObjectFactory.h"
#include "Objects/Scene.h"
#include "TileMap.h"
using namespace nc;

nc::Engine engine;
Scene scene;

int main(int, char**)
{
	
	engine.Startup();
	
	ObjectFactory::Instance().Initialize();
	ObjectFactory::Instance().Register("PlayerComponent", new nc::Creator<nc::PlayerComponent, nc::Object>);
	ObjectFactory::Instance().Register("EnemyComponent", new nc::Creator<nc::EnemyComponent, nc::Object>);

	rapidjson::Document document; 
	nc::json::Load("scene.txt", document);

	scene.Create(&engine);
	scene.Read(document);

	TileMap tileMap;
	nc::json::Load("tileMap.txt", document);
	tileMap.Read(document);
	tileMap.Create(&scene);

	//for (size_t i = 0; i < 10; i++)
	//{
	//	GameObject* gameobject = ObjectFactory::Instance().Create<GameObject>("ProtoCoin");
	//	gameobject->m_transform.position = Vector2{ random(0,800),random(200,400) };
	//	//gameobject->m_transform.angle = random(0, 360);
	//	scene.AddGameObject(gameobject);
	//}


	SDL_Event event;
	bool quit = false;
	while (!quit)
	{

		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;	
			break;
		}

		engine.Update();
		scene.Update();

		quit = (engine.GetSystem <InputSystem>()->GetButtonState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eButtonState::PRESSED);
	
		engine.GetSystem <Renderer>()->Begin();


		scene.Draw();

		engine.GetSystem <Renderer>()->End();
	}

	scene.Destroy();
	engine.Shutdown();


	return 0;
}


