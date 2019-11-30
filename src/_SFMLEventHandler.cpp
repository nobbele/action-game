#include "_SFMLEventHandler.hpp"
#include "EventHandler.hpp"
#include "Graphics/_SFMLRenderer.hpp"

SFMLEventHandler::SFMLEventHandler(Renderer& renderer)
	: EventHandler(renderer), window(static_cast<SFMLRenderer&>(renderer).window) {

}

void SFMLEventHandler::Raise(EventHandler::Event e, EventHandler::EventParameter&& param) {
	const auto [start, end] = EventCallbackMap.equal_range(e);
	for(auto it = start; it != end; it++) {
		it->second(param);
	}
}

EventHandler::KeyDownEventParameter sfToAgKeyDownEvent(sf::Event::KeyEvent e);

void SFMLEventHandler::PollEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window.close();
		else if (event.type == sf::Event::Resized)
			Raise(EventHandler::Event::Resize, EventHandler::EventParameter());
		else if (event.type == sf::Event::KeyPressed)
			Raise(EventHandler::Event::KeyDown, static_cast<EventHandler::EventParameter>(sfToAgKeyDownEvent(event.key)));
	}
}

EventHandler::KeyDownEventParameter sfToAgKeyDownEvent(sf::Event::KeyEvent e) {
	EventHandler::KeyDownEventParameter param;
	switch(e.code) {
		case sf::Keyboard::Key::Escape: {
			param.Key = EventHandler::KeyEventParameter::EKey::ESC;
		} break;
		default: {
			param.Key = EventHandler::KeyEventParameter::EKey::UNKNOWN;
		} break;
	}
	return param;
}