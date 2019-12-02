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
	groundBodyDef.type = b2_staticBody;
	groundBodyDef.position.Set(0.0f, 7.0f);

	b2Body* groundBody = world.PhysicsWorld.CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(10.0f, 0.2f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &groundBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 1.0f;

	groundBody->CreateFixture(&fixtureDef);

	Entity& ent = world.CreateEntity();

	const int speed = 10;
	const int jumpSpeed = 100;

	eventHandler.Subscribe(EventHandler::Event::KeyDown, [&ent, &eventHandler, jumpSpeed](const EventHandler::EventParameter&) {
		if(eventHandler.KeyMap[EventHandler::EKey::SPACE]) {
			ent.Body->ApplyLinearImpulse(b2Vec2(0,-jumpSpeed), ent.Body->GetWorldCenter() , true);
		}
	});

	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 8;
	int32 positionIterations = 3;

	while (renderer.IsOpen())
	{
		eventHandler.PollEvents();

		if(eventHandler.KeyMap[EventHandler::EKey::D]) {
			ent.Body->ApplyLinearImpulse(b2Vec2(speed,0), ent.Body->GetWorldCenter() , true);
		}
		else if(eventHandler.KeyMap[EventHandler::EKey::A]) {
			ent.Body->ApplyLinearImpulse(b2Vec2(-speed,0), ent.Body->GetWorldCenter() , true);
		}

		world.PhysicsWorld.Step(timeStep, velocityIterations, positionIterations);

		renderer.StartRender();
		for(auto& entity : world.Entities)
			renderer.Draw(entity);
		renderer.EndRender();
	}

	return 0;
}
