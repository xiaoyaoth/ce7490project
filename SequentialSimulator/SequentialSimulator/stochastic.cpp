#include "stochastic.h"

void stochastic()
{
	float inter_arritime,arritime=0,duration,position,speed;
	ofstream fout("Da.txt");
	fout<<"arriveno"<<"\tarritime"<<"\tduration"<<"\tposition"<<"\tspeed"<<"\n";
	//fout<<arritime<<"\t"<<duration<<"\n";
	float r1,r2,u1,u2;
	int i,count=10000;
	srand((int)time(0));
    for(i=0;i<count;i++)
	{
	r1=(float)random(10000)/(float)10000;
	r2=(float)random(10000)/(float)10000;
	inter_arritime=r1;
	arritime+=inter_arritime;//generate the call arrive time
	duration=(-1)*log(1-r1)*160;//generate the duration of the call
	if(r1<=0.75)//generate the position of the arriving car
		position=sqrt(1200*r1);
	else
		position=40-20*sqrt(1-r1);

	u1=r1;
	u2=r2;
	speed=100+9*cos(2*pi*u1)*sqrt((-2)*log(u2));

	fout<<i+1<<"\t\t"<<arritime<<"\t\t"<<duration<<"\t\t"<<position<<"\t\t"<<speed<<endl;
	
	}
	fout.close();
}