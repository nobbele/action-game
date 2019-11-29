#include "Renderer.hpp"
#include "_SFMLRenderer.hpp"
#include <SFML/Graphics.hpp>
#include "GameSystem.hpp"

const unsigned int targetWidth = 1920;
const unsigned int targetHeight = 1080;

sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight);

sf::Texture background;

void SFMLRenderer::Initialize() {
#ifdef SFML_SYSTEM_WINDOWS
__windowsHelper.setIcon(window.getSystemHandle());
#endif

	const auto [w, h] = window.getSize();

	sf::View view;
    view.setSize(targetWidth, targetHeight);
    view.setCenter(targetWidth / 2, targetHeight / 2 );
    view = getLetterboxView(view, w, h);

	GameSystem::GetInstance().eventHandler->Subscribe(EventHandler::Event::Resize, [this]() {
		const auto [w, h] = window.getSize();
		window.setView(getLetterboxView(window.getView(), w, h));
	});

	spriteMap.insert({0, sf::Texture()}).first->second.loadFromFile("content/sfml.png");
	sf::Image image;
	image.create(targetWidth, targetHeight, sf::Color::Blue);
	background.create(targetWidth, targetHeight);
	background.update(image);
}
void SFMLRenderer::StartRender() {
	window.clear();
	renderSprite.setTexture(background);
	renderSprite.setPosition(sf::Vector2f(0,0));
	window.draw(renderSprite);
}
void SFMLRenderer::Draw(Drawable& drawable) {
    sf::Texture tex = spriteMap[drawable.TextureId];
	renderSprite.setTexture(tex);
    const sf::Vector2f pos = drawable.Position;
	renderSprite.setPosition(pos);

    sf::Vector2u size = tex.getSize();
    sf::Vector2f scale = renderSprite.getScale();
    drawable.Size.X = size.x * scale.x;
    drawable.Size.Y = size.y * scale.y;

    std::cout << "px size: " << drawable.Size << std::endl;
    std::cout << "m size: " << drawable.Size / PIXELS_PER_METER << std::endl;

	window.draw(renderSprite);
}
void SFMLRenderer::EndRender() {
	window.display();
}
void SFMLRenderer::Quit() {

}
bool SFMLRenderer::IsOpen() {
	return window.isOpen();
}

// https://github.com/SFML/SFML/wiki/Source%3A-Letterbox-effect-using-a-view
sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight) {

    // Compares the aspect ratio of the window to the aspect ratio of the view,
    // and sets the view's viewport accordingly in order to archieve a letterbox effect.
    // A new view (with a new viewport set) is returned.

    float windowRatio = windowWidth / (float) windowHeight;
    float viewRatio = view.getSize().x / (float) view.getSize().y;
    float sizeX = 1;
    float sizeY = 1;
    float posX = 0;
    float posY = 0;

    bool horizontalSpacing = true;
    if (windowRatio < viewRatio)
        horizontalSpacing = false;

    // If horizontalSpacing is true, the black bars will appear on the left and right side.
    // Otherwise, the black bars will appear on the top and bottom.

    if (horizontalSpacing) {
        sizeX = viewRatio / windowRatio;
        posX = (1 - sizeX) / 2.f;
    }

    else {
        sizeY = windowRatio / viewRatio;
        posY = (1 - sizeY) / 2.f;
    }

    view.setViewport( sf::FloatRect(posX, posY, sizeX, sizeY) );

    return view;
}