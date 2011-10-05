#include "Event.h"
#include "EventList.h"

int Event::drop = 0;
int Event::handover = 0;
int Event::total = 0;
int Event::block = 0;

int Event::counter = 0;

Event::Event(float t, int bid){
	time = t;
	baseID = bid;
	nextEvent = NULL;
	eid = counter++;

	EventList::insert(this);
	Event::total++;
}

Event::Event(){
}

float Event::getTime(){
	return time;
}

int Event::getBaseID(){
	return baseID;
}

int Event::getEventID(){
	return eid;
}

void Event::setNextEventPtr(Event * e){
	nextEvent = e;
}

Event * Event::getNextEventPtr(){
	return nextEvent;
}

void Event::handleEvent(Base blist[]){
	std::cout<<"general func of handling event"<<std::endl;
}

string Event::getOutput(){
	stringstream ss;
	ss<<"vitual"<<"\t"<<time<<"\t"<<baseID<<std::endl;
	return ss.str();
}

/* http://en.wikipedia.org/wiki/Virtual_function 
what does the const mean in the C++ description of virtual function*/

