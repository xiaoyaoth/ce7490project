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
#include "stdafx.h"
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

int _tmain(int argc, _TCHAR* argv[])
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
	bool debug = true;
	Base * blist = Base::getBlist();
	for(int i=0; i<BASENO; i++){
		blist[i].setBaseID(i);
		blist[i].initializeReservation();
		//cout<<blist[i].toString();
	}

	ifstream fin;
	fin.open("data.txt");

	if(!fin)
		cout<<"file not exist"<<endl;
	string rec; //one record
	getline(fin, rec);
	parseData(rec);

	//fout<<"EventID\tType\tarvlNo\ttime\tbaseID\tspeed\tdura\tposition"<<std::endl;
	int j = 0;
	Event * cur = EventList::getNextEvent();
	while(cur!=NULL){
		//cout<<cur->getOutput(blist);
		cur->handleEvent(blist);
		
		if(!fin.eof()){
			getline(fin, rec);
			parseData(rec);
		}
		delete cur;
		cur = EventList::getNextEvent();
	}

	Event::getResult();
	//fout<<Event::getResult();
	fin.close();
	//fout.close();
}

void parseData(string rec){
	char * cstr, *p;
	int no, baseID;
	float time, duration, speed;
	float position;

	cstr = new char[rec.size()+1];
	strcpy_s(cstr, rec.size()+1, rec.c_str());

	p=strtok (cstr,"\t");
	no = atoi(p);
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