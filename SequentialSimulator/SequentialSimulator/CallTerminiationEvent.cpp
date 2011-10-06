#include "CallTerminationEvent.h"

CallTerminationEvent::CallTerminationEvent(float t, int bid, int ano)
	:Event(t, bid, ano)
{
}

void CallTerminationEvent::handleEvent(Base blist[]){
	Base * base = &blist[baseID];
	base->decOccupiedChannel();
	Event::success++;
	return;
}

string CallTerminationEvent::getOutput(Base blist[]){
	stringstream ss;
	//ss<<this->getEventID()<<"\t"<<"Termi\t\t"<<time<<"\t"<<baseID<<std::endl;
	ss<<"i'm terminator"<<"\t"<<time<<"\t"<<arrivalNo<<"\t"<<blist[baseID].toString()<<endl;
	return ss.str();
}