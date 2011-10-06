#include "EventList.h"
#include <iostream>
#include <queue>

Event * EventList::head = NULL; /*initialize the static member "head" */
Event * EventList::currPtr = NULL; /*initialize the static member "ptr" */

EventList::EventList(Event *e){
	head = e;
	currPtr = e;
}

void EventList::insert(Event * e){
	Event * temp = currPtr;
	if(temp == NULL){
		head = e;
		currPtr = e;
		return;
	}else if(e->getTime()<head->getTime()){
		e->setNextEventPtr(head);
		head = e;
		return;
	}
	while(temp->getNextEventPtr() != NULL){
		if(e->getTime() > temp->getTime() 
			&& e->getTime()< temp->getNextEventPtr()->getTime()){
				e->setNextEventPtr(temp->getNextEventPtr());
				temp->setNextEventPtr(e);
				return;
		}
		temp = temp->getNextEventPtr();
	}
	temp->setNextEventPtr(e);
	return;
}

Event * EventList::getNextEvent(){
	if(currPtr->getNextEventPtr() != NULL){
		currPtr = currPtr->getNextEventPtr();
		return currPtr;
	}else
		return NULL;
}

Event * EventList::getHead(){
	return head;
}
