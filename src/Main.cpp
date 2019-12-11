#include "Main.hpp"
#include "World.hpp"
#include "Entity.hpp"
#include "EventHandler.hpp"
#include "GameSystem.hpp"
#include <Box2D/Box2D.h>

static void createGround(World& world) {
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
}

int main()
{
	GameSystem& system = GameSystem::GetInstance();
	Renderer& renderer = system.GetRenderer();
	renderer.Initialize();
	EventHandler& eventHandler = system.GetEventHandler();

	World world(b2Vec2(0.0f, 9.81f));

	createGround(world);

	Entity& ent = world.CreateEntity();

	const int speed = 5;
	const int jumpSpeed = 150;

	eventHandler.Subscribe(EventHandler::Event::KeyDown, [&ent, &eventHandler, jumpSpeed](const EventHandler::EventParameter& e) {
		if(static_cast<const EventHandler::KeyDownEventParameter&>(e).key == EventHandler::EKey::SPACE) {
			ent.ApplyLinearImpulse(b2Vec2(0,-jumpSpeed));
		}
	});

	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 8;
	int32 positionIterations = 3;

	while (renderer.IsOpen())
	{
		eventHandler.PollEvents();

		Vector2f vel = ent.GetVelocity();

		if(eventHandler.KeyMap[EventHandler::EKey::D]) {
			ent.SetVelocity(b2Vec2(speed, vel.Y));
		}
		else if(eventHandler.KeyMap[EventHandler::EKey::A]) {
			ent.SetVelocity(b2Vec2(-speed, vel.Y));
		}

		world.PhysicsWorld.Step(timeStep, velocityIterations, positionIterations);

		renderer.StartRender();
		for(auto& entity : world.Entities)
			renderer.Draw(entity);
		renderer.EndRender();
	}

	return 0;
}
