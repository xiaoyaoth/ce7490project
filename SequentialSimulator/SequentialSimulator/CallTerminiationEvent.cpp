#include "CallTerminationEvent.h"

CallTerminationEvent::CallTerminationEvent(float t, int bid)
	:Event(t, bid)
{
}

void CallTerminationEvent::handleEvent(Base blist[]){
	Base base = blist[baseID];
	base.decOccupiedChannel();
	Event::success++;
	return;
}

string CallTerminationEvent::getOutput(){
	stringstream ss;
	ss<<this->getEventID()<<"\t\t"<<"Termi\t\t\t\t"<<time<<"\t\t"<<baseID<<std::endl;
	return ss.str();
}