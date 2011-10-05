#ifndef EVENT_H_
#define EVENT_H_

#ifndef NULL
#define NULL 0
#endif

#ifndef RADIUS
#define RADIUS 1
#endif

#ifndef DIAMETER
#define DIAMETER 2
#endif

#ifndef POS
#define POS 1
#endif

#include <iostream>
#include <sstream>
#include "Base.h"

using namespace std;

class Event{

protected:

	/*Event attribute*/
	float time;
	int baseID;
	Event * nextEvent;
	int eid;

	static int counter;

	/*statistics, declared as static*/
	static int block; // count for call-block
	static int drop; // count of call-drop
	static int handover; //count of handover
	static int total; //total event amount

public:

	Event();
	Event(float time, int baseID);
	float getTime();
	int getBaseID();
	Event * getNextEventPtr();
	void setNextEventPtr(Event * e);
	int getEventID();

	virtual void handleEvent(Base blist[]);
	virtual string getOutput();
};
#endif