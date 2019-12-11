#ifndef AG_EVENTHANDLER_H
#define AG_EVENTHANDLER_H

#include "Graphics/Renderer.hpp"
#include <entt/entity/registry.hpp>

class EventHandler {
public:
	EventHandler(__attribute__((unused)) Renderer& renderer) { }

	enum class Event {
		Resize, KeyDown
	};

	struct EventParameter {
		virtual ~EventParameter() = default;
	};
	enum class EKey {
		UNKNOWN, ESC, SPACE, A, D
	};
	struct KeyDownEventParameter : public EventParameter {
		KeyDownEventParameter(EKey key) : key(key) {}
		EKey key;
	};

	using EventCallbackFunction = std::function<void(const EventParameter&)>;
	using Subscription = std::unordered_multimap<Event, EventCallbackFunction>::iterator;
	inline Subscription Subscribe(Event e, EventCallbackFunction callback) {
		return EventCallbackMap.insert({e, callback});
	}
	inline void Unsubscribe(Subscription sub) {
		EventCallbackMap.erase(sub);
	}
	virtual void PollEvents(entt::registry& reg) = 0;

	std::map<EKey, bool> KeyMap;

	static std::unique_ptr<EventHandler> CreateBestEventHandler(Renderer& renderer);
protected:
	std::unordered_multimap<Event, EventCallbackFunction> EventCallbackMap;
};

struct KeyDownEventHandler {
	std::function<void(const EventHandler::KeyDownEventParameter&)> f;
};

std::ostream& operator<<(std::ostream& os, const EventHandler::EKey key);

#endif