#include "EventList.h"
#include <iostream>

Event * EventList::head = NULL; /*initialize the static member "head" */
Event * EventList::ptr = NULL; /*initialize the static member "ptr" */

EventList::EventList(Event *e){
	head = e;
	ptr = e;
}

void EventList::insert(Event * e){
	Event * temp = head;
	if(temp == NULL){
		std::cout<<"head is null"<<std::endl;
		head = e;
		ptr = e;
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
	if(ptr->getNextEventPtr() != NULL){
		ptr = ptr->getNextEventPtr();
		return ptr;
	}else
		return NULL;
}

Event * EventList::getHead(){
	return head;
}
