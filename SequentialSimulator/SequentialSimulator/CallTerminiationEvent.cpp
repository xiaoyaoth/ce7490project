#include "CallTerminationEvent.h"

CallTerminationEvent::CallTerminationEvent(float t, int bid)
	:Event(t, bid)
{
}

void CallTerminationEvent::handleEvent(Base blist[]){
	Base * base = &blist[baseID];
	base->decOccupiedChannel();
	Event::success++;
	return;
}

string CallTerminationEvent::getOutput(){
	stringstream ss;
	//ss<<this->getEventID()<<"\t"<<"Termi\t\t"<<time<<"\t"<<baseID<<std::endl;
	ss<<"i'm terminator"<<"\t"<<time<<endl;
	return ss.str();
}