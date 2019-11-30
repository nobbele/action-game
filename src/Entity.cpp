#include "Entity.hpp"
#include "Graphics/Renderer.hpp"
#include <Box2D/Box2D.h>
#include "World.hpp"

Entity::Entity(World& world) : Drawable(0) {
	BodyDef.type = b2_dynamicBody;
	BodyDef.position.Set(0, 0);
	b2Body* body = world.PhysicsWorld.CreateBody(&BodyDef);

	DynamicBox.SetAsBox(1.0f, 1.0f);

	FixtureDef.shape = &DynamicBox;
	FixtureDef.density = 1.0f;
	FixtureDef.friction = 0.3f;

	body->CreateFixture(&FixtureDef);
}