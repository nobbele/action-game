#include "Main.hpp"
#include "Entity.hpp"
#include "EventHandler.hpp"
#include "GameSystem.hpp"
#include "World.hpp"

// TODO
// Add Box2D

int main()
{
	GameSystem& system = GameSystem::GetInstance();
	system.renderer->Initialize();

	World world;
	world.Entities.push_back(Entity());

	while (system.renderer->IsOpen())
	{
		system.eventHandler->PollEvents();

		system.renderer->StartRender();
		for(auto& entity : world.Entities)
			system.renderer->Draw(entity);
		system.renderer->EndRender();
	}

	return 0;
}
