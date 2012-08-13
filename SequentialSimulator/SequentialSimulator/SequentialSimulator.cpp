// SequentialSimulator.cpp : Defines the entry point for the console application.
// Configuration Properties => C/C++ => Precompiled Headers.
//

#define _USE_MATH_DEFINES /*the #define must come before the #include.*/
#define SAMPLENO 3000
#define MODE 1

#include "Base.h"
#include "Event.h"
#include "EventList.h"
#include "CallHandoverEvent.h"
#include "CallInitiationEvent.h"
#include "CallTerminationEvent.h"
#include <iostream>
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
void mainLogic(char *filename);
ofstream fout("out.txt");

int main(int argc, char* argv[])
{
	clock_t time;
	time = clock();
	mainLogic(argv[1]);
	cout<<clock()-time<<endl;
	cout<<argv[1]<<endl;
	return 0;
}

void mainLogic(char *filename){
	remove("fini_seq.txt");
	remove("compres.txt");
	clock_t t1 = clock();
	bool debug = true;
	Base * blist = Base::getBlist();
	for(int i=0; i<BASENO; i++){
		blist[i].setBaseID(i);
		blist[i].initializeReservation();
	}

	ifstream fin;
	fin.open(filename);
	if(!fin)
		cout<<"file not exist"<<endl;
	string rec; //one record
	getline(fin, rec);
	parseData(rec);

	int j = 0;
	Event * cur = EventList::getNextEvent();
	while(cur!=NULL){
		cur->handleEvent(blist);
		if(!fin.eof()){
			getline(fin, rec);
			parseData(rec);
		}
		delete cur;
		cur = EventList::getNextEvent();
	}
	cout<<Event::getResult();
}

void parseData(string rec){
	char * cstr, *p;
	int no, baseID;
	float time, duration, speed;
	float position;

	cstr = new char[rec.size()+1];
	strcpy(cstr, rec.c_str());

#if MODE==1
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
	position = position - DIAMETER*baseID;
	p=strtok(NULL,"\t");
	speed = (float)atof(p);
	new CallInitiationEvent(time, speed, baseID, position, duration, no);
#else
	p=strtok (cstr,"\t");
	no = atoi(p);
	p=strtok(NULL,"\t");
	time = (float)atof(p);
	p=strtok(NULL,"\t");
	baseID = atoi(p) - 1;
	p=strtok(NULL,"\t");
	duration = (float)atof(p);
	p=strtok(NULL,"\t");
	speed = (float)atof(p);
	new CallInitiationEvent(time, speed, baseID, 1, duration, no);
#endif	
	return;
}