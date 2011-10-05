#include "Base.h"
#include <iostream>

Base::Base(){
	baseID = 0;
	occupiedChannel = 0;
}

Base::Base(int bid){
	occupiedChannel = 0;
	baseID = bid;
}

int Base::getOccupiedChannel(){
	return occupiedChannel;
}

int Base::getBaseID(){
	return baseID;
}

void Base::setBaseID(int bid){
	baseID = bid;
}

void Base::incOccupiedChannel(){
	occupiedChannel++;
}

void Base::decOccupiedChannel(){
	occupiedChannel--;
}

void Base::print(){
	std::cout<<"baseID:"<<baseID<<" oc:"<<occupiedChannel<<std::endl;
}