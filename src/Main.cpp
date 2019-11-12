#include "Main.hpp"
#include "Renderer.hpp"
#include "Entity.hpp"

int main()
{
	std::cout << "Hello World!" << std::endl;

	sf::RenderWindow window(sf::VideoMode(640,480), "SFML works!");
#ifdef SFML_SYSTEM_WINDOWS
	__windowsHelper.setIcon(window.getSystemHandle());
#endif

	std::unique_ptr<Renderer> renderer = Renderer::CreateBestRenderer();
	renderer->Initialize();

	std::vector<Entity> entities;
	entities.push_back(Entity());

	sf::Event event;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		for(const auto& entity : entities) {
			renderer->Render(window, entity);
		}
		window.display();
	}

	return 0;
}
