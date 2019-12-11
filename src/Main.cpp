#include "Main.hpp"
#include "World.hpp"
#include "Entity.hpp"
#include "EventHandler.hpp"
#include "GameSystem.hpp"
#include <Box2D/Box2D.h>
#include <entt/entity/registry.hpp>

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

static b2Body* CreateEntityBody(b2World& world, const Renderer& renderer, int textureId) {
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 0.0f);
	bodyDef.fixedRotation = true;
	bodyDef.angularDamping = 0.1f;

	b2PolygonShape dynamicBox;
	Vector2f size = renderer.GetTextureSize(textureId);
	dynamicBox.SetAsBox(size.X / PIXELS_PER_METER, size.Y / PIXELS_PER_METER);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 1.0f;

	b2Body* body = world.CreateBody(&bodyDef);
	body->CreateFixture(&fixtureDef);

	return body;
}

static entt::entity createPlayer(entt::registry& registry, b2World& world, const Renderer& renderer) {
	auto ecs_ent = registry.create();

	const Drawing& drawing = registry.assign<Drawing>(ecs_ent, 0, Vector2f(1,1));
	registry.assign<Positioning>(ecs_ent);
	registry.assign<EntityPhysics>(ecs_ent).body = CreateEntityBody(world, renderer, drawing.textureId);

	const int jumpSpeed = 150;

	registry.assign<KeyDownEventHandler>(ecs_ent, [&registry, &ecs_ent](const EventHandler::KeyDownEventParameter& e) {
		if(e.key == EventHandler::EKey::SPACE) {
			EntityPhysics& phys = registry.get<EntityPhysics>(ecs_ent);
			phys.body->ApplyLinearImpulse(b2Vec2(0,-jumpSpeed), phys.body->GetWorldCenter(), true);
		}
	});

	return ecs_ent;
}

int main()
{
	GameSystem& system = GameSystem::GetInstance();
	Renderer& renderer = system.GetRenderer();
	renderer.Initialize();
	EventHandler& eventHandler = system.GetEventHandler();

	World world(b2Vec2(0.0f, 9.81f));

	createGround(world);

	entt::registry registry;

	entt::entity ecs_ent = createPlayer(registry, world.PhysicsWorld, renderer);

	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 8;
	int32 positionIterations = 3;

	clock_t current_ticks;
	float dt;
	int fps = 0;

	while (renderer.IsOpen())
	{
		current_ticks = clock();

		eventHandler.PollEvents(registry);

		world.PhysicsWorld.Step(timeStep, velocityIterations, positionIterations);

		registry.view<Positioning, EntityPhysics>().each([](Positioning& positioning, EntityPhysics& physics) {
			positioning.velocity = physics.body->GetLinearVelocity();
			positioning.position = physics.body->GetPosition();
			positioning.angle = (physics.body->GetAngle() * 180) / 3.14159265358979f;
		});

		EntityPhysics& phys = registry.get<EntityPhysics>(ecs_ent);
		Positioning& pos = registry.get<Positioning>(ecs_ent);
		float mov = 0;

		if(eventHandler.KeyMap[EventHandler::EKey::D]) {
			mov = 1;
		}
		else if(eventHandler.KeyMap[EventHandler::EKey::A]) {
			mov = -1;
		}

		const int speed = 6;

		if(mov != 0) {
			float change = (mov*speed) - pos.velocity.X;
			float impulse = phys.body->GetMass() * change;
			phys.body->ApplyLinearImpulse(b2Vec2(impulse, 0), phys.body->GetWorldCenter(), true);
		}

		renderer.StartRender();
		renderer.Draw(registry);
		renderer.EndRender();

		dt = (float)(clock() - current_ticks) / CLOCKS_PER_SEC;
		if(dt > 0)
        	fps = 1.0f / dt;
	}

	return 0;
}
