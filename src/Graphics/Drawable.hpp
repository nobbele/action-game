#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "Vector2.hpp"

class Drawable {
	public:
	const int TextureId;
	Vector2f Position = Vector2f(0,0);

	// Set in Renderer::Draw so this will be 0 before the first drawn frame
	Vector2f Size = Vector2f(0,0);

	inline Drawable(int textureId = 0) : TextureId(textureId) {}
};

#endif