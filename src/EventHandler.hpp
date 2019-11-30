#ifndef AG_EVENTHANDLER_H
#define AG_EVENTHANDLER_H

#include "Graphics/Renderer.hpp"

class EventHandler {
public:
	EventHandler(__attribute__((unused)) Renderer& renderer) { }

	enum class Event {
		Resize
	};
	using EventCallbackFunction = std::function<void()>;
	using Subscription = std::unordered_multimap<Event, EventCallbackFunction>::iterator;
	inline Subscription Subscribe(Event e, EventCallbackFunction callback) {
		return EventCallbackMap.insert({e, callback});
	}
	inline void Unsubscribe(Subscription sub) {
		EventCallbackMap.erase(sub);
	}
	virtual void PollEvents() = 0;

	static std::unique_ptr<EventHandler> CreateBestEventHandler(Renderer& renderer);
protected:
	std::unordered_multimap<Event, EventCallbackFunction> EventCallbackMap;
};

#endif