#ifndef AG_ENTITY_H
#define AG_ENTITY_H

#include "Graphics/Drawable.hpp"
#include "World.hpp"
#include <Box2D/Box2D.h>

class Entity : public Drawable {
	public:
	inline Entity(World& world) : Drawable(0) {
		BodyDef.type = b2_dynamicBody;
		BodyDef.position.Set(0, 0);
		b2Body* body = world.PhysicsWorld.CreateBody(&BodyDef);

		DynamicBox.SetAsBox(1.0f, 1.0f);

		FixtureDef.shape = &DynamicBox;
		FixtureDef.density = 1.0f;
		FixtureDef.friction = 0.3f;

		body->CreateFixture(&FixtureDef);
	}

	inline Vector2f GetPosition() {
		b2Vec2 pos = Body->GetPosition();
		return pos;
	}

	b2BodyDef BodyDef;
	b2PolygonShape DynamicBox;
	b2FixtureDef FixtureDef;
	b2Body* Body;
};

#endif