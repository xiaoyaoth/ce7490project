#include "CallTerminationEvent.h"

CallTerminationEvent::CallTerminationEvent(float t, int bid, int ano)
	:Event(t, bid, ano)
{
	prevCallReserved = false;
	print = true;
}

CallTerminationEvent::CallTerminationEvent(float t, int bid, int ano, bool rc)
	:Event(t, bid, ano)
{
	prevCallReserved = rc;
	print = true;
}

void CallTerminationEvent::handleEvent(Base blist[]){
	if(SCHEME == 0)
		scheme0(blist);
	else
		scheme1(blist);
}

void CallTerminationEvent::scheme0(Base blist[]){
	Base * base = &blist[baseID];
	base->decOccupiedChannel();
	Event::success++;
	return;
}

void CallTerminationEvent::scheme1(Base blist[]){
	Base * base = &blist[baseID];
	base->decOccupiedChannel();
	if(prevCallReserved == true){
		base->toggleReservation();
	}
	Event::success++;
	return;
}