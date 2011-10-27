// SequentialSimulator.cpp : Defines the entry point for the console application.
// Configuration Properties => C/C++ => Precompiled Headers.
//

#define _USE_MATH_DEFINES /*the #define must come before the #include.*/
#define SAMPLENO 3000

#include "Base.h"
#include "Event.h"
#include "EventList.h"
#include "CallHandoverEvent.h"
#include "CallInitiationEvent.h"
#include "CallTerminationEvent.h"
#include <fstream>
#include <string>
#include <iostream>
#include <cstring>
#include <queue>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

/*use ctrl+F5 to pause the execution at the end*/
/*linker problem is solved. the problem is caused because I didn't implement the function*/
void parseData(string rec);
void testQueue();
void transferJiongData();
void mainLogic();
void generate01();
void generateExponential();
void generateTriangle();
void generateNormal();

int main(int argc, char* argv[])
{
	clock_t time;
	time = clock();
	//transferJiongData();
	mainLogic();
	cout<<clock()-time;
	//generate01();
	//generateExponential();
	//generateTriangle();
	return 0;
}

void mainLogic(){
	clock_t t1 = clock();
	bool debug = true;
	Base * blist = Base::getBlist();
	for(int i=0; i<BASENO; i++){
		blist[i].setBaseID(i);
		blist[i].initializeReservation();
		//cout<<blist[i].toString();
	}

	ifstream fin;
	fin.open("data.txt.100w");

	if(!fin)
		cout<<"file not exist"<<endl;
	string rec; //one record
	int i = 0;
	while(!fin.eof()){
		getline(fin, rec);
		parseData(rec);
		if(++i%100000==0)
			cout<<i<<endl;
	}
	clock_t t2 = clock();
	int j = 0;
	Event * cur = EventList::getNextEvent();
	while(cur!=NULL){
		cur->handleEvent(blist);
		delete cur;
		cur = EventList::getNextEvent();
	}
	clock_t t3 = clock();
	cout<<"time with io:"<<t3-t1<<endl;
	cout<<"time without io:"<<t3-t2<<endl;
	Event::getResult();
	fin.close();
}

void parseData(string rec){
	char * cstr, *p;
	int no, baseID;
	float time, duration, speed;
	float position;

	cstr = new char[rec.size()+1];
	strcpy(cstr, rec.c_str());

	p=strtok (cstr,"\t");
	no = atoi(p);
	if(no==1000000)
		cout<<no;
	p=strtok(NULL,"\t");
	time = (float)atof(p);
	p=strtok(NULL,"\t");
	duration = atof(p);
	p=strtok(NULL,"\t");
	position = (float)atof(p);
	baseID = position/DIAMETER;
	p=strtok(NULL,"\t");
	speed = (float)atof(p);

	new CallInitiationEvent(time, speed, baseID, position-baseID*DIAMETER, duration, no);
	return;
}