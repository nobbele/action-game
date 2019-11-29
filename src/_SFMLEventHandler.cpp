#include "EventHandler.hpp"
#include "_SFMLEventHandler.hpp"
#include "Graphics/_SFMLRenderer.hpp"

SFMLEventHandler::SFMLEventHandler(Renderer& renderer)
	: EventHandler(renderer), window(static_cast<SFMLRenderer&>(renderer).window) {

}

void SFMLEventHandler::Raise(EventHandler::Event e) {
	const auto [start, end] = EventCallbackMap.equal_range(e);
	for(auto it = start; it != end; it++) {
		it->second();
	}
}

void SFMLEventHandler::PollEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window.close();
		if (event.type == sf::Event::Resized)
			Raise(EventHandler::Event::Resize);
	}
}
