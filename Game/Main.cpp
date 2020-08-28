#include "pch.h"
#include "Graphics/Texture.h"
#include "Engine.h"
#include "Objects/GameObject.h"
#include "Components/PlayerComponent.h"
#include "Core/Json.h"
#include "Objects/ObjectFactory.h"
#include "Objects/Scene.h"
using namespace nc;

nc::Engine engine;
Scene scene;

int main(int, char**)
{
	
	engine.Startup();
	
	ObjectFactory::Instance().Initialize();
	ObjectFactory::Instance().Register("PlayerComponent", new nc::Creator<nc::PlayerComponent, nc::Object>);

	rapidjson::Document document; 
	nc::json::Load("scene.txt", document);

	scene.Create(&engine);
	scene.Read(document);

	//nc::Texture* background = engine.GetSystem<ResourceManager>()->Get<nc::Texture>("background.png", engine.GetSystem <Renderer>());

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

		//background->Draw({ 0,0 }, { 1.0f,1.0f },0);

		scene.Draw();

		engine.GetSystem <Renderer>()->End();
	}

	scene.Destroy();
	engine.Shutdown();


	return 0;
}


