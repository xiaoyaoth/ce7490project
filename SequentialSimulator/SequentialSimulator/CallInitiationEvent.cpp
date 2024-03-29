#include "CallInitiationEvent.h"
#include <fstream>

CallInitiationEvent::CallInitiationEvent(float t, float s, int bid, float p, float d, int no)
	:Event(t, bid, no)
{
	speed = s;
	position = p;
	duration = d;
}

void CallInitiationEvent::handleEvent(Base blist[]){
	if(SCHEME == 0)
		scheme0(blist);
	else
		scheme1(blist);
}

void CallInitiationEvent::scheme0(Base blist[]){
	Base *base = &blist[baseID];
	int oc = base->getOccupiedChannel(); //occupied channel 
	//cout<<base->toString();
	if(oc<10){
		base->incOccupiedChannel();
		float handoverTS = time + 3600*(DIAMETER-position)/speed;
		float terminationTS = time + duration;
		if(handoverTS<terminationTS){
			if(baseID+1<20)
				new CallHandoverEvent(handoverTS, speed, baseID+1, terminationTS-handoverTS, arrivalNo);
			CallTerminationEvent *cte = new CallTerminationEvent(handoverTS, baseID, arrivalNo);
			cte->print = false;
		} else
			new CallTerminationEvent(terminationTS, baseID, arrivalNo);
	}else{
		//std::fstream out1;
		//out1.open("fini_seq.txt", std::ios::out | std::ios::app);
		//out1<<"I baseId:"<<baseID<<" ano:"<<arrivalNo<<" time:"<<time<<endl;
		Event::block++;
	}
	return;
}

void CallInitiationEvent::scheme1(Base blist[]){
	Base * base = &blist[baseID];
	int oc = base->getOccupiedChannel(); //occupied channel amount
	bool rco = base->isReservedChannelOccupied();//reservedChannleOccupied
	int avc; //availabe channel amount
	if(rco)
		avc = 10-oc;
	else
		avc = 9-oc;
	if(avc>0){
		base->incOccupiedChannel();
		float handoverTS = time + 3600*(DIAMETER-position)/speed;
		float terminationTS = time + duration;
		if(handoverTS<terminationTS){
			if(baseID+1<20)
				new CallHandoverEvent(handoverTS, speed, baseID+1, terminationTS-handoverTS, arrivalNo, false);
		CallTerminationEvent *cte = new CallTerminationEvent(handoverTS, baseID, arrivalNo, false);
		cte->print = false;
		} else
			new CallTerminationEvent(terminationTS, baseID, arrivalNo, false);
	}else
		Event::block++;
	return;
}

string CallInitiationEvent::getOutput(Base blist[]){
	stringstream ss;
	//ss<<this->getEventID()<<"\t"<<"Init\t"<<arrivalNo<<"\t"<<time<<"\t"
	//	<<baseID<<"\t"<<speed<<"\t"<<duration<<"\t"<<position<<std::endl;
	//if(this->baseID == 13)
	ss<<"i"<<"\t"<<time
		<<"\t"<<arrivalNo
		<<"\t"<<blist[baseID].toString()<<endl;

	//ss<<arrivalNo<<"\t"<<time<<endl;
	return ss.str();
}
