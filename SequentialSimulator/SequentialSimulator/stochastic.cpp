#include "stochastic.h"

void stochastic()
{
	float inter_arritime,arritime=0,duration,position,speed;
	ofstream fout("Da.txt");
	fout<<"arriveno"<<"\tarritime"<<"\tduration"<<"\tposition"<<"\tspeed"<<"\n";

	ofstream fout_intertime("intersta.txt");
	ofstream fout_dura("durasta.txt");
	ofstream fout_position("postionsta.txt");
	ofstream fout_speed("speedsta.txt");
	//fout<<arritime<<"\t"<<duration<<"\n";
	float r1,r2,u1,u2;
	int i,j,count=10000;

	int interti[10],dura[100],distri[40],sp[40];
	for(i=0;i<10;i++)
		interti[i]=0;
	for(i=0;i<100;i++)
		dura[i]=0;
	for(i=0;i<40;i++)
	{
		distri[i]=0;
		sp[i]=0;
	}

	srand((int)time(0));
    for(i=0;i<count;i++)
	{
	r1=(float)random(10000)/(float)10000;
	r2=(float)random(10000)/(float)10000;
	inter_arritime=r1;
	j=inter_arritime/0.1;
	if((j<10)&&(j>=0))
	interti[j]++;
	arritime+=inter_arritime;//generate the call arrive time

	duration=(-160)*log(r1);//generate the duration of the call
	j=duration/10;
	if((j<100)&&(j>=0))
		dura[j]++;

	if(r1<=0.75)//generate the position of the arriving car
		position=sqrt(1200*r1);
	else
		position=40-20*sqrt(1-r1);
	 j=(int)position;
	 if((j<40)&&(j>=0))
	  distri[j]++;
	u1=r1;
	u2=r2;
	speed=100+9*cos(2*pi*u1)*sqrt((-2)*log(u2));
	j=(int)speed;
	if((j<120)&&(j>=80))
	sp[j-80]++;
	//speed = miu+sigma*cos(2*M_PI*r1)*sqrt(-2*log10(r2));
	fout<<i+1<<"\t\t"<<arritime<<"\t\t"<<duration<<"\t\t"<<position<<"\t\t"<<speed<<endl;
	
	}
	for(i=0;i<10;i++)
		fout_intertime<<(float)interti[i]/count<<",";
	for(i=0;i<100;i++)
		fout_dura<<(float)dura[i]/count<<",";
	for(i=0;i<40;i++)
	{
		fout_position<<(float)distri[i]/count<<",";
		fout_speed<<(float)sp[i]/count<<",";
	}
	fout.close();
	fout_intertime.close();
	fout_position.close();
	fout_speed.close();
}