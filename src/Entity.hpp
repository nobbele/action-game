#ifndef AG_ENTITY_H
#define AG_ENTITY_H

#include "Graphics/Drawable.hpp"
#include <Box2D/Box2D.h>

class World;

class Entity : public Drawable {
	public:
	inline Vector2f GetPosition() const {
		return Vector2f(Body->GetPosition()) * PIXELS_PER_METER;
	}
	inline float GetRotation() const {
		return (Body->GetAngle() * 180) / 3.14159265358979f;
	}
	inline Vector2f GetVelocity() const {
		return Body->GetLinearVelocity();
	}

	inline void SetPosition(Vector2f vec) {
		Body->SetTransform(vec / PIXELS_PER_METER, Body->GetAngle());
	}

	b2FixtureDef FixtureDef;
	b2Body* Body;
};

#endif