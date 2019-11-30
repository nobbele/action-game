#ifndef AG_DRAWABLE_H
#define AG_DRAWABLE_H

#include "Vector2.hpp"
#include "GameSystem.hpp"
#include "Renderer.hpp"

class Drawable {
	public:
	const int TextureId;
	Vector2f Scale = Vector2f(1,1);

	inline Drawable(int textureId = 0) : TextureId(textureId), size(GameSystem::GetInstance().GetRenderer().GetTextureSize(textureId)) { }

	inline Vector2f GetSize() const {
		return size * Scale;
	}

	virtual Vector2f GetPosition() const = 0;

	private:
	Vector2f size = Vector2f(0,0);
};

#endif