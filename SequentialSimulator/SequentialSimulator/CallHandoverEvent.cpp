#include "CallHandoverEvent.h"

CallHandoverEvent::CallHandoverEvent(float t, float s, int bid, float d, int ano)
	:Event(t, bid, ano)
{
	speed = s;
	duration = d;
	prevCallReserved = false;
}

CallHandoverEvent::CallHandoverEvent(float t, float s, int bid, float d, int ano, bool rc)
	:Event(t, bid, ano)
{
	speed = s;
	duration = d;
	prevCallReserved = rc;
}

void CallHandoverEvent::handleEvent(Base blist[]){
	if(SCHEME == 0)
		scheme0(blist);
	else
		scheme1(blist);
}

void CallHandoverEvent::scheme0(Base * blist){
	Base *base = &blist[baseID];
	//Base *prevBase = &blist[baseID-1];
	//prevBase->decOccupiedChannel();
	int oc = base->getOccupiedChannel(); //occupied channel amount
	if(oc<10){//not all the channel occupied
		base->incOccupiedChannel();
		float handoverTS = time+3600*DIAMETER/speed;
		float terminationTS = time + duration;
		if(handoverTS<terminationTS){
			if(baseID+1<20)
				new CallHandoverEvent(handoverTS, speed, baseID+1, terminationTS-handoverTS, arrivalNo);
			CallTerminationEvent *cte = new CallTerminationEvent(handoverTS+0.0001, baseID, arrivalNo);
			cte->print = false;
		} else
			new CallTerminationEvent(terminationTS, baseID, arrivalNo);
	}else //all the channel occupied
		Event::drop++;
	return;
}

void CallHandoverEvent::scheme1(Base * blist){
	Base *base = &blist[baseID];
	//Base *prevBase = &blist[baseID-1];
	//prevBase->decOccupiedChannel();
	//if(prevCallReserved == true)
	//	prevBase->toggleReservation(); //?

	int oc = base->getOccupiedChannel();
	bool rco = base->isReservedChannelOccupied();//reservedChannleOccupied
	bool rc = false; // define whether this newly-generated handover here is a reserved call or not;
	if(oc<10){//not all the channel occupied
		if(oc == 9 && rco == false){
			base->toggleReservation();
			rc = true;
		}
		base->incOccupiedChannel();
		float handoverTS = time+3600*DIAMETER/speed;
		float terminationTS = time + duration;
		if(handoverTS<terminationTS){
			if(baseID+1<20)
				new CallHandoverEvent(handoverTS, speed, baseID+1, terminationTS-handoverTS, arrivalNo, rc);
			CallTerminationEvent *cte = new CallTerminationEvent(handoverTS, baseID, arrivalNo, rc);
			cte->print = false;
		} else
			new CallTerminationEvent(terminationTS, baseID, arrivalNo, rc);
	}else //all the channel occupied
		Event::drop++;
	return;
}

