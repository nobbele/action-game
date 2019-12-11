#ifndef AG_ENTITY_H
#define AG_ENTITY_H

#include "Graphics/Drawable.hpp"
#include <Box2D/Box2D.h>

struct Drawing {
	int textureId;
	Vector2f scale;
};

struct Positioning {
	Vector2f velocity;
	Vector2f position;
	float angle;
};

struct EntityPhysics {
	b2Body* body;
	float mass;
};

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
	inline Vector2f GetCenter() const {
		return Body->GetWorldCenter();
	}
	inline b2Body* GetBody() const {
		return Body;
	}

	inline void SetPosition(Vector2f vec) {
		Body->SetTransform(vec / PIXELS_PER_METER, Body->GetAngle());
	}
	inline void SetVelocity(Vector2f vec) {
		Body->SetLinearVelocity(vec);
	}
	inline void ApplyLinearImpulse(Vector2f vec, bool wake = true) {
		Body->ApplyLinearImpulse(vec, GetCenter(), wake);
	}

	inline void SetBody(b2Body* body)  {
		Body = body;
	}

	protected:
	b2FixtureDef FixtureDef;
	b2Body* Body;
};

#endif