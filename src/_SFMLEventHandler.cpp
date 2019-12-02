#include "_SFMLEventHandler.hpp"
#include "EventHandler.hpp"
#include "Graphics/_SFMLRenderer.hpp"

SFMLEventHandler::SFMLEventHandler(Renderer& renderer)
	: EventHandler(renderer), window(static_cast<SFMLRenderer&>(renderer).window) {

}

void SFMLEventHandler::Raise(EventHandler::Event e, const EventHandler::EventParameter&& param) {
	const auto [start, end] = EventCallbackMap.equal_range(e);
	for(auto it = start; it != end; it++) {
		it->second(param);
	}
}

EventHandler::EKey sfToAgKey(sf::Event::KeyEvent e);

void SFMLEventHandler::PollEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		} else if (event.type == sf::Event::Resized) {
			Raise(EventHandler::Event::Resize, EventHandler::EventParameter());
		} else if (event.type == sf::Event::KeyPressed) {
			EventHandler::EKey key = sfToAgKey(event.key);
			KeyMap[key] = true;
			Raise(EventHandler::Event::KeyDown, EventHandler::KeyDownEventParameter { key });
		} else if (event.type == sf::Event::KeyReleased) {
			EventHandler::EKey key = sfToAgKey(event.key);
			KeyMap[key] = false;
		}
	}
}

EventHandler::EKey sfToAgKey(sf::Event::KeyEvent e) {
	switch(e.code) {
		case sf::Keyboard::Key::Escape: {
			return EventHandler::EKey::ESC;
		} break;
		case sf::Keyboard::Key::Space: {
			return EventHandler::EKey::SPACE;
		} break;
		case sf::Keyboard::Key::A: {
			return EventHandler::EKey::A;
		} break;
		case sf::Keyboard::Key::D: {
			return EventHandler::EKey::D;
		} break;
		default: {
			return EventHandler::EKey::UNKNOWN;
		} break;
	}
}