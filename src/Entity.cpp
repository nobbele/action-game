#include "Entity.hpp"
#include "Graphics/Renderer.hpp"
#include <Box2D/Box2D.h>
#include "World.hpp"

Entity::Entity(b2World& world) : Drawable(0) {
b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 0.0f);
	Body = world.CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(GetSize().X / PIXELS_PER_METER, GetSize().Y / PIXELS_PER_METER);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	Body->CreateFixture(&fixtureDef);
}