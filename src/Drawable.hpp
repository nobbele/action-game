#ifndef DRAWABLE_H
#define DRAWABLE_H

class Drawable {
	public:
	const int TextureId;
	sf::Vector2f Position = sf::Vector2f(0,0);
	inline Drawable(int textureId = 0) : TextureId(textureId) {}
};

#endif