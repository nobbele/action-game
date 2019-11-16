#include "Main.hpp"
#include "Renderer.hpp"
#include "Entity.hpp"
#include "EventHandler.hpp"
#include "GameSystem.hpp"

int main()
{
	GameSystem& system = GameSystem::GetInstance();
	system.renderer->Initialize();

	std::vector<Entity> entities;
	entities.push_back(Entity());

	while (system.renderer->IsOpen())
	{
		system.eventHandler->PollEvents();

		system.renderer->StartRender();
		for(const auto& entity : entities)
			system.renderer->Draw(entity);
		system.renderer->EndRender();
	}

	return 0;
}
