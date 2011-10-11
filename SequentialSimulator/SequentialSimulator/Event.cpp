#include "Event.h"
#include "EventList.h"

int Event::drop = 0;
int Event::success = 0;
int Event::total = 0;
int Event::block = 0;

int Event::counter = 0;

Event::Event(float t, int bid, int ano){
	time = t;
	baseID = bid;
	arrivalNo = ano;
	nextEvent = NULL;

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

void Event::setNextEventPtr(Event * e){
	nextEvent = e;
}

Event * Event::getNextEventPtr(){
	return nextEvent;
}

void Event::handleEvent(Base blist[]){
	std::cout<<"general func of handling event"<<std::endl;
}

string Event::getOutput(Base blist[]){
	stringstream ss;
	ss<<"vitual"<<"\t"<<time<<"\t"<<blist[baseID].toString()<<std::endl;
	return ss.str();
}

string Event::getResult(){
	stringstream ss;
	int total=Event::success+Event::drop+Event::block;
	ss<<"success\tdrop\tblock\tdroprate\tblockrate"<<endl;
	ss<<Event::success<<"\t"<<Event::drop<<"\t"<<Event::block<<"\t"<<(double)(Event::drop)/total<<"\t"<<(double)Event::block/total<<"\t"<<endl;
	return ss.str();
}

int Event::getArrivalNo(){
	return arrivalNo;
}

/* http://en.wikipedia.org/wiki/Virtual_function 
what does the const mean in the C++ description of virtual function*/

