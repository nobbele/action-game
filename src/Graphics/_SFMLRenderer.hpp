#ifndef AG_SFMLRENDERER_H
#define AG_SFMLRENDERER_H

#include "Renderer.hpp"

class SFMLRenderer : public Renderer {
public:
	sf::Sprite renderSprite;
	std::unordered_map<unsigned int, sf::Texture> spriteMap;
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(1280,720), "Action Game");
	void Initialize();
	void StartRender();
	void Draw(entt::registry& reg);
	void EndRender();
	void Quit();
	bool IsOpen();

	Vector2f GetTextureSize(uint id) const;

	void ChangeView(unsigned int width, unsigned int height);
};

#endif