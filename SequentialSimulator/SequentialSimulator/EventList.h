#ifndef EVENTLIST_H
#define EVENTLIST_H

#include "Event.h"
#include <queue>

class EventList
{
private:
	class compare{

	};
	static priority_queue<Event> queue;
	static Event * head;
	static Event * currPtr;
public:
	EventList(Event * e);
	EventList();
	static void insert(Event * e);
	static Event * getNextEvent();
	static Event * getHead();
};

#endif;