#include "CallTerminationEvent.h"

CallTerminationEvent::CallTerminationEvent(float t, int bid)
	:Event(t, bid)
{
}

void CallTerminationEvent::handleEvent(Base blist[]){
	Base base = blist[baseID];
	base.decOccupiedChannel();
}

string CallTerminationEvent::getOutput(){
	stringstream ss;
	ss<<this->getEventID()<<"\t"<<"termination\t\t"<<time<<"\t"<<baseID<<std::endl;
	return ss.str();
}