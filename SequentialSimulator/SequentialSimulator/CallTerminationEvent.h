#ifndef CALLTERMINATIONEVENT_H_
#define CALLTERMINATIONEVENT_H_

#include "Event.h"

class CallTerminationEvent : public Event
{
private:
	;
public:
	CallTerminationEvent(float t, int bid, int ano);
	void handleEvent(Base blist[]);
	string getOutput(Base blist[]);
};
#endif