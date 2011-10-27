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
#include <iostream>
#include <fstream>
#include <string>
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


	ofstream fout0("0.txt");
	ofstream fout1("1.txt");
	ofstream fout2("2.txt");
	ofstream fout3("3.txt");

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
		
		if(debug){
		if(cur->getBaseID()/6 == 0)
			fout0<<cur->getOutput(blist);
		else if(cur->getBaseID()/6 == 1)
			fout1<<cur->getOutput(blist);
		else if(cur->getBaseID()/6 == 2)
			fout2<<cur->getOutput(blist);
		else if(cur->getBaseID()/6 == 3)
			fout3<<cur->getOutput(blist);
		}
		//cout<<cur->getOutput(blist);
		
		if(!fin.eof()){
			getline(fin, rec);
			parseData(rec);
		}
		delete cur;
		cur = EventList::getNextEvent();
	}

	cout<<Event::getResult();
	//fout<<Event::getResult();
	fin.close();
	//fout.close();
	
	if(debug){
	fout0.close();
	fout1.close();
	fout2.close();
	fout3.close();
	}
	
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

void transferJiongData(){
	ifstream fin;
	fin.open("chiData.txt");
	ofstream fout("chiDataOut.txt");
	string rec;
	while(!fin.eof()){
		getline(fin, rec);
		char * cstr, *p;
		float time;
		cstr = new char[rec.size()+1];
		strcpy_s(cstr,rec.size()+1, rec.c_str());
		p = strtok(cstr, "\t");
		if(strcmp(p, "i'm initiater")== 0)
			fout<<"i\t";
		else if(strcmp(p, "i'm handover")== 0)
			fout<<"h\t";
		else if(strcmp(p, "i'm terminator")== 0)
			fout<<"t\t";
		p = strtok(NULL, "\t");
		time = atof(p);
		fout<<time<<endl;
	}
	fin.close();
	fout.close();
}

void generate01(){
	ofstream fout("stoch_01.txt");
	srand((unsigned) time(NULL));
	int i = 0;
	while(++i<=SAMPLENO){
		fout<<(double)rand()/RAND_MAX<<endl;
	}
}

void generateExponential(){
	ofstream fout("stoch_exponential.txt");
	srand((unsigned) time(NULL));
	const double lambda = 0.00625;
	int i = 0;
	double x,r;
	while(++i<=SAMPLENO){
		r = (double)rand()/RAND_MAX;
		x = -1/lambda*log(r);
		fout<<x<<endl;
	}
}

void generateTriangle(){
	ofstream fout("stoch_triangle.txt");
	srand((unsigned) time(NULL));
	int i = 0;
	double x,r;
	while(++i<=SAMPLENO){
		r = (double)rand()/RAND_MAX;
		if(r>=0&&r<0.75)
			x = sqrt(1200*r);
		else
			x = 40 - 20*sqrt(1-r);
		fout<<x<<" "<<r<<endl;
	}
}

void generateNormal(){
	ofstream fout("stoch_normal.txt");
	srand((unsigned) time(NULL));
	int i = 0;
	const double miu = 100;
	const double sigma = 9;
	double x, r1, r2;
	while(++i<=SAMPLENO){
		r1 = (double)rand()/RAND_MAX;
		r2 = (double)rand()/RAND_MAX;
		x = miu+sigma*cos(2*M_PI*r1)*sqrt(-2*log10(r2));
		fout<<x<<endl;
	}
}


