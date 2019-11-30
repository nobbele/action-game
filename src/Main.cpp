#include "Main.hpp"
#include "World.hpp"
#include "Entity.hpp"
#include "EventHandler.hpp"
#include "GameSystem.hpp"
#include <Box2D/Box2D.h>

int main()
{
	GameSystem& system = GameSystem::GetInstance();
	Renderer& renderer = system.GetRenderer();
	renderer.Initialize();
	EventHandler& eventHandler = system.GetEventHandler();

	World world(b2Vec2(0.0f, 9.81f));

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, 8.0f);

	b2Body* groundBody = world.PhysicsWorld.CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(1.0f, 1.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);

	Entity& ent = world.Entities.emplace_back(world.PhysicsWorld);
	system.GetEventHandler().Subscribe(EventHandler::Event::KeyDown, [&ent](EventHandler::EventParameter& _p) {
		EventHandler::KeyDownEventParameter& param = (EventHandler::KeyDownEventParameter&)_p;
		std::cout << param.Key << std::endl;
		if(param.Key == EventHandler::KeyEventParameter::EKey::ESC) {
			ent.SetPosition(Vector2f(0, 0));
		}
	});

	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 8;
	int32 positionIterations = 3;

	while (renderer.IsOpen())
	{
		eventHandler.PollEvents();

		world.PhysicsWorld.Step(timeStep, velocityIterations, positionIterations);

		renderer.StartRender();
		for(auto& entity : world.Entities)
			renderer.Draw(entity);
		renderer.EndRender();
	}

	return 0;
}
