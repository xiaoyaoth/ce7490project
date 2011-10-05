// SequentialSimulator.cpp : Defines the entry point for the console application.
//
#include "Event.h"
#include "EventList.h"
#include "CallHandoverEvent.h"
#include "CallInitiationEvent.h"
#include "CallTerminationEvent.h"
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

/*use ctrl+F5 to pause the execution at the end*/
/*linker problem is solved. the problem is caused because I didn't implement the function*/
void parseData(string rec);

int _tmain(int argc, _TCHAR* argv[])
{
	const int BASE_AMOUNT = 20;
	Base blist[BASE_AMOUNT];
	for(int i = 0; i<BASE_AMOUNT; i++){
		blist[i].setBaseID(i);
	}

	ifstream fin;
	fin.open("data.txt");
	ofstream fout("out.txt");

	if(!fin)
		cout<<"file not exist"<<endl;
	string rec; //one record
	getline(fin, rec);
	parseData(rec);

	fout<<"EventID\tType\tarvlNo\ttime\tbaseID\tspeed\tdura\tposition"<<std::endl;
	int i = 0;
	Event * cur = EventList::getHead();
	while(cur!=NULL){
		cur->handleEvent(blist);
		fout<<cur->getOutput();
		if(!fin.eof()){
			getline(fin, rec);
			parseData(rec);
		}
		cur = EventList::getNextEvent(); /**/
	}

	cout<<Event::getResult();
	fout<<Event::getResult();
	fin.close();
	fout.close();

	return 0;
}

void parseData(string rec){
	char * cstr, *p;
	int no, baseID;
	float time, duration, speed;

	cstr = new char[rec.size()+1];
	strcpy_s(cstr, rec.size()+1, rec.c_str());

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

	new CallInitiationEvent(time, speed, baseID, POS, duration, no);
	return;
}

