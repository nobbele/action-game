#include "World.hpp"

Entity& World::CreateEntity() {
	Entity& entity = this->Entities.emplace_back();

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 0.0f);
	bodyDef.fixedRotation = true;
	bodyDef.angularDamping = 0.1f;

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(entity.GetSize().X / PIXELS_PER_METER, entity.GetSize().Y / PIXELS_PER_METER);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 1.0f;

	entity.Body = this->PhysicsWorld.CreateBody(&bodyDef);
	entity.Body->CreateFixture(&fixtureDef);

	return entity;
}