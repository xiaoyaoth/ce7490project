// SequentialSimulator.cpp : Defines the entry point for the console application.
//

#define _USE_MATH_DEFINES /*the #define must come before the #include.*/
#define SAMPLENO 100000

#include "Base.h"
#include "Event.h"
#include "EventList.h"
#include "CallHandoverEvent.h"
#include "CallInitiationEvent.h"
#include "CallTerminationEvent.h"
#include "stochastic.h"

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
void parseData_stochastic(string rec);
void testQueue();
void transferJiongData();
void mainLogic();
void mainLogic_stochastic();
void generate01();
void generateExponential();
void generateTriangle();
void generateNormal();
double generateData(int,double);

//ofstream outdata("1.txt");

int _tmain(int argc, _TCHAR* argv[])
{
	//transferJiongData();
	//mainLogic_deterministic();
	mainLogic_stochastic();
	//generate01();
	//generateExponential();
	//generateTriangle();
	//generateNormal();
	return 0;
}

void mainLogic_deterministic(){

//	stochastic();
	
	Base * blist = Base::getBlist();
	for(int i=0; i<BASENO; i++){
		blist[i].setBaseID(i);
		blist[i].initializeReservation();
		//cout<<blist[i].toString();
	}

	ifstream fin;
	fin.open("da.txt");
	ofstream fout("out.txt");

	if(!fin)
		cout<<"file not exist"<<endl;
	string rec; //one record
	getline(fin, rec);
	getline(fin, rec);
	parseData(rec);

	//fout<<"EventID\tType\tarvlNo\ttime\tbaseID\tspeed\tdura\tposition"<<std::endl;
	Event * cur = EventList::getNextEvent();
	while(cur!=NULL){
		cur->handleEvent(blist);
		//if(cur->getArrivalNo() == 1)
		fout<<cur->getOutput(blist);

		if(!fin.eof()){
			getline(fin, rec);
			parseData(rec);
		}
		cur = EventList::getNextEvent(); 
	}
	cout<<Event::getResult();
	fout<<Event::getResult();
	fin.close();
	fout.close();
	
}

void mainLogic(){

//	stochastic();
	
	Base * blist = Base::getBlist();
	for(int i=0; i<BASENO; i++){
		blist[i].setBaseID(i);
		blist[i].initializeReservation();
		//cout<<blist[i].toString();
	}

	ifstream fin;
	fin.open("da.txt");
	ofstream fout("out.txt");

	if(!fin)
		cout<<"file not exist"<<endl;
	string rec; //one record
	getline(fin, rec);
	getline(fin, rec);
	parseData_stochastic(rec);

	//fout<<"EventID\tType\tarvlNo\ttime\tbaseID\tspeed\tdura\tposition"<<std::endl;
	int j = 0,re_num=1;
	Event * cur = EventList::getNextEvent();
	while(cur!=NULL){
		cur->handleEvent(blist);
		//if(cur->getArrivalNo() == 1)
		fout<<cur->getOutput(blist);
		if(re_num<500)
		{
			getline(fin, rec);
			parseData_stochastic(rec);
            re_num++;
   		}
		/*
		if(!fin.eof()){
			getline(fin, rec);
			parseData_stochastic(rec);
		}
		*/
		cur = EventList::getNextEvent(); 
	}
	cout<<Event::getResult();
	fout<<Event::getResult();
	fin.close();
	fout.close();
	
	/*
	Base * blist = Base::getBlist();
	for(int i=0; i<BASENO; i++){
		blist[i].setBaseID(i);
		//cout<<blist[i].toString();
	}

	ifstream fin;
	fin.open("data.txt");
	ofstream fout("out.txt");

	if(!fin)
		cout<<"file not exist"<<endl;
	string rec; //one record
	getline(fin, rec);
	parseData(rec);

	//fout<<"EventID\tType\tarvlNo\ttime\tbaseID\tspeed\tdura\tposition"<<std::endl;
	int j = 0;
	Event * cur = EventList::getNextEvent();
	while(cur!=NULL){
		cur->handleEvent(blist);
		fout<<cur->getOutput(blist);
		if(!fin.eof()){
			getline(fin, rec);
			parseData(rec);
		}
		cur = EventList::getNextEvent(); 
	}
	cout<<Event::getResult();
	fout<<Event::getResult();
	fin.close();
	fout.close();
	*/
}



void mainLogic_stochastic(){
	int no=1,count=0;
	double curtime=0;
	int s=0;
	ofstream fout("out.txt");
	Base * blist = Base::getBlist();
	for(int i=0; i<BASENO; i++){
		blist[i].setBaseID(i);
		blist[i].initializeReservation();
		//cout<<blist[i].toString();
	}
    curtime=generateData(no++,curtime);
	Event * cur = EventList::getNextEvent();
	while(cur!=NULL){
		cur->handleEvent(blist);
		fout<<cur->getOutput(blist);
		if(count<10)
		{
		  curtime=generateData(no++,curtime);
          count++;
   		}
		cur = EventList::getNextEvent(); 
	}
	cout<<Event::getResult();
	fout<<Event::getResult();
	fout.close();
	
}
double generateData(int number,double curtime)
{
	int no, baseID;
	double intertime, arritime,duration, speed,position,po,r1,r2;
	const double lambda = 0.00625;
	const double miu = 100;
	const double sigma = 9;
	ofstream foutdata;
    foutdata.open("a.txt",ios::app);
    if (foutdata.fail())
    {
     cout<<"open file error!\n";
     exit(0);
    }
	srand((unsigned)time(NULL));
	r1=(double)rand()/RAND_MAX;
	r2=(double)rand()/RAND_MAX;
	intertime=r1;//uniform distribution
	arritime=curtime+intertime;
	duration= -1/lambda*log(r1);//exponential distribution
	if(r1>=0&&r1<0.75)//triangle distribution
	  position = sqrt(1200*r1);
	else
	  position = 40 - 20*sqrt(1-r1);
	speed = miu+sigma*cos(2*M_PI*r1)*sqrt(-2*log10(r2));
	no=number;
	baseID=position/2;
	po=position-2*baseID;
	foutdata<<no<<"\t"<<arritime<<"\t"<<duration<<"\t"<<position<<"\t"<<speed<<"\t"<<endl;
	foutdata.close();
	new CallInitiationEvent(arritime, speed, baseID, po, duration, no);
    return arritime;
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

void parseData_stochastic(string rec){
	char * cstr, *p;
	int no, baseID;
	float time, duration, speed,position,po;

	cstr = new char[rec.size()+1];
	strcpy_s(cstr, rec.size()+1, rec.c_str());


	p=strtok (cstr,"\t");
	no = atoi(p);
	p=strtok(NULL,"\t");
	time = (float)atof(p);
	//p=strtok(NULL,"\t");
	//baseID = atoi(p) - 1;
	p=strtok(NULL,"\t");
	duration = (float)atof(p);
	p=strtok(NULL,"\t");
	position = (float)atof(p);
	p=strtok(NULL,"\t");
	speed = (float)atof(p);

	baseID=position/2;
	po=position-baseID*2;
	new CallInitiationEvent(time, speed, baseID, po, duration, no);

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
	ofstream fout_stastics("stoch_01_stastics.txt");
	int j,a[100],N=100;
	double data;
	for(j=0;j<N;j++)
		a[j]=0;
	srand((unsigned) time(NULL));
	int i = 0;
	while(++i<=SAMPLENO){
		data=(double)rand()/RAND_MAX;
		j=data/0.01;
		a[j]++;
		fout<<data<<endl;
	}

	for(j=0;j<N;j++)
     fout_stastics<<(double)a[j]/SAMPLENO<<",";

}

void stasticsUniform()
{
}

void generateExponential(){
	ofstream fout("stoch_exponential.txt");
	ofstream fout_stastics("stoch_exponential_stastics.txt");
	int j,a[100],N=100;
	double data;
	for(j=0;j<N;j++)
		a[j]=0;
	srand((unsigned) time(NULL));
	const double lambda = 0.00625;
	int i = 0;
	double x,r;
	while(++i<=SAMPLENO){
		r = (double)rand()/RAND_MAX;
		x = -1/lambda*log(r);
		j=x/10;
		if((j<100)&&(j>=0))
		 a[j]++;
		fout<<x<<endl;
	}
	for(j=0;j<N;j++)
    fout_stastics<<(double)a[j]/SAMPLENO<<",";
}

void generateTriangle(){
	ofstream fout("stoch_triangle.txt");
	ofstream fout_stastics("stoch_triangle_stastics.txt");
	int j,a[40],N=40;
	for(j=0;j<N;j++)
		a[j]=0;
	srand((unsigned) time(NULL));
	int i = 0;
	double x,r;
	while(++i<=SAMPLENO){
		r = (double)rand()/RAND_MAX;
		if(r>=0&&r<0.75)
			x = sqrt(1200*r);
		else
			x = 40 - 20*sqrt(1-r);
		j=(int)x;
		if((j<40)&&(j>=0))
		a[j]++;
		fout<<x<<" "<<r<<endl;
	}
	for(j=0;j<N;j++)
    fout_stastics<<(double)a[j]/SAMPLENO<<",";

}

void generateNormal(){
	ofstream fout("stoch_normal.txt");
	ofstream fout_stastics("stoch_normal_stastics.txt");
	int j,a[40],N=40;
	for(j=0;j<N;j++)
		a[j]=0;
	srand((unsigned) time(NULL));
	int i = 0;
	const double miu = 100;
	const double sigma = 9;
	double x, r1, r2;
	while(++i<=SAMPLENO){
		r1 = (double)rand()/RAND_MAX;
		r2 = (double)rand()/RAND_MAX;
		x = miu+sigma*cos(2*M_PI*r1)*sqrt(-2*log10(r2));
		j=(int)x;
		if((j<120)&&(j>=80))
		a[j-80]++;
		fout<<x<<endl;
	}

	for(j=0;j<N;j++)
     fout_stastics<<(double)a[j]/SAMPLENO<<",";

}


