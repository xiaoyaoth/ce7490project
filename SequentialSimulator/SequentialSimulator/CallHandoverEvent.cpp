#include "CallHandoverEvent.h"

CallHandoverEvent::CallHandoverEvent(float t, float s, int bid, float d, int ano)
	:Event(t, bid, ano)
{
	speed = s;
	duration = d;
}

void CallHandoverEvent::handleEvent(Base blist[]){
	Base *base = &blist[baseID];
	Base *prevBase = &blist[baseID-1];
	prevBase->decOccupiedChannel();
	int oc = base->getOccupiedChannel();
	if(oc<10){//not all the channel occupied
		base->incOccupiedChannel();
		float handoverTS = time+3600*DIAMETER/speed;
		float terminationTS = time + duration;
		if(handoverTS<terminationTS)
			if(baseID+1<20)
				new CallHandoverEvent(handoverTS, speed, baseID+1, terminationTS-handoverTS, arrivalNo);
			else
				new CallTerminationEvent(handoverTS, baseID, arrivalNo);
		else
			new CallTerminationEvent(terminationTS, baseID, arrivalNo);
	}else //all the channel occupied
		Event::drop++;
}

string CallHandoverEvent::getOutput(Base blist[]){
	stringstream ss;
	//ss<<this->getEventID()<<"\t"<<"Hando\t\t"<<time
	//	<<"\t"<<baseID<<"\t"<<speed<<"\t"<<duration<<std::endl;

	ss<<"h"<<"\t"<<time
		//<<"\t"<<arrivalNo<<"\t"<<blist[baseID].toString()
		<<endl;

	//ss<<arrivalNo<<"\t"<<time<<endl;
	return ss.str();
}
