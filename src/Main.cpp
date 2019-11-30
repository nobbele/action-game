#include "Main.hpp"
#include "Entity.hpp"
#include "EventHandler.hpp"
#include "GameSystem.hpp"
#include "World.hpp"
#include <Box2D/Box2D.h>

// TODO
// Add Box2D

int main()
{
	GameSystem& system = GameSystem::GetInstance();
	system.renderer->Initialize();

	World world(b2Vec2(0.0f, -9.81f));
	world.Entities.push_back(Entity(world));

	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	while (system.renderer->IsOpen())
	{
		system.eventHandler->PollEvents();

		world.PhysicsWorld.Step(timeStep, velocityIterations, positionIterations);

		for(auto& entity : world.Entities) {
			Vector2f pos = (Vector2f)entity.Body->GetPosition() * PIXELS_PER_METER;
			std::cout << pos << std::endl;
		}

		system.renderer->StartRender();
		for(auto& entity : world.Entities)
			system.renderer->Draw(entity);
		system.renderer->EndRender();
	}

	return 0;
}
