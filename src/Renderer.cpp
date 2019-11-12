#include "Renderer.hpp"
#include <SFML/Graphics.hpp>

class SFMLRenderer : public Renderer {
	sf::Sprite renderSprite;
	sf::Texture sfmlLogo;
	void Initialize() {
		sfmlLogo.loadFromFile("content/sfml.png");
	}
	void Render(sf::RenderWindow& window, const Drawable& drawable) {
		if(drawable.TextureId == 0)
			renderSprite.setTexture(sfmlLogo);
		renderSprite.setPosition(drawable.Position);
		window.draw(renderSprite);
	}
};

std::unique_ptr<Renderer> Renderer::CreateBestRenderer() {
	return std::make_unique<SFMLRenderer>();
}