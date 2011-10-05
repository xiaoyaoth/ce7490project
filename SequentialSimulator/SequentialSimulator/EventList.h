#ifndef EVENTLIST_H
#define EVENTLIST_H

#include "Event.h"

class EventList
{
private:
	static Event * head;
	static Event * ptr;
public:
	EventList(Event * e);
	EventList();
	static void insert(Event * e);
	static Event * getNextEvent();
	static Event * getHead();
};

#endif;