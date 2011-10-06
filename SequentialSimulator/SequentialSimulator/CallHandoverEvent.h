#ifndef CALLHANDOVEREVENT_H_
#define CALLHANDOVEREVENT_H_

#include "Event.h"
#include "CallTerminationEvent.h"

class CallHandoverEvent : public Event
{
private:
	float speed;
	float duration;
public:
	CallHandoverEvent(float t, float s, int bid, float d, int ano);
	void handleEvent(Base blist[]);
	string getOutput(Base blist[]);
};

#endif