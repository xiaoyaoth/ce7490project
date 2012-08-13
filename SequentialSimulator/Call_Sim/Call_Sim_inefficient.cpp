// Call_Sim_inefficient.cpp : Defines the entry point for the console application.
//

#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <queue>
#include <time.h>
using namespace std;

#define MODE 1

#define INIT 0
#define HANDO 1
#define TERMI 2
#define DEAD 3
#define END -1

char *DATAFILE;
int N;
int CSC;

typedef struct pair{
	float time;
	int index;
} p_t;

struct comp{
	bool operator() (p_t e1, p_t e2){
		return e1.time > e2.time;
	}
};

class EventList
{
private:
	priority_queue<p_t, vector<p_t>, comp> queue;
public:
	EventList(p_t e){
		this->queue.empty();
		queue.push(e);
	}
	EventList(){
		this->queue.empty();
	}
	void insert(p_t e){
		this->queue.push(e);
	}
	void insert(float time, int index){
		p_t e={time, index};
		this->queue.push(e);
	}
	p_t getNextEvent(){
		if(this->queue.size()>0){
			p_t ret = queue.top();
			this->queue.pop();
			return ret;
		} else{
			p_t nullpair={END,END};
			return nullpair;
		}
	}
	int size(){
		return queue.size();
	}
};

typedef struct host_arrays
{
	int *h_baseId, *h_no, *h_etype;
	float *h_time;
	float *h_duration,*h_speed,*h_pos;
	int* h_init;
} ha_t;

void parseData(string rec, int &index, int i, ha_t* ha, EventList* el)
{
	char * cstr, *p;
	cstr = new char[rec.size()+1];
	strcpy(cstr, rec.c_str());

#if MODE==0
	p=strtok (cstr,"\t");
	const int no = atoi(p); //no

	p=strtok(NULL,"\t");
	float time = (float)atof(p);//time

	p=strtok(NULL,"\t");
	int baseId = atoi(p)-1; //baseid
	float pos = baseId*2+1;//pos
	float nextPos = ((int)(pos/2)+1)*2;//next pos

	p=strtok(NULL,"\t");
	float duration = (float)atof(p);//duration

	p=strtok(NULL,"\t");
	const float speed = (float)atof(p);//speed

	float termiPos = pos+duration*speed/3600;
	if(termiPos>40)
		termiPos = 40;
#else
	p=strtok (cstr,"\t");
	const int no = atoi(p); //no

	p=strtok(NULL,"\t");
	float time = (float)atof(p);//time

	p=strtok(NULL,"\t");
	float duration = (float)atof(p);//duration

	p=strtok(NULL,"\t");
	float pos = (float)atof(p);
	int baseId = pos/2;
	float nextPos = ((int)(pos/2)+1)*2;//next pos

	p=strtok(NULL,"\t");
	const float speed = (float)atof(p);//speed

	float termiPos = pos+duration*speed/3600;
	if(termiPos>40)
		termiPos = 40;;
#endif
	ha->h_baseId[index]=baseId;
	ha->h_etype[index]=INIT;
	ha->h_no[index]=no;
	ha->h_time[index]=time;
	el->insert(time, index);
	//fout<<no<<": "<<index<<"_I_"<<baseId<<"_"<<time<<" ";
	index+=1;	

	while(nextPos<termiPos){
		ha->h_baseId[index]=baseId=baseId+1;
		ha->h_etype[index]=HANDO;
		ha->h_no[index]=no;
		ha->h_time[index]=time=time+(nextPos-pos)/speed*3600;
		pos = nextPos;
		nextPos = nextPos+2;
		el->insert(time,index);
		//fout<<index<<"_H_"<<baseId<<"_"<<time<<" ";
		index+=1;
	}

	ha->h_baseId[index]=baseId;
	ha->h_etype[index]=TERMI;
	ha->h_no[index]=no;
	ha->h_time[index]=time=time+(termiPos-pos)/speed*3600;
	el->insert(time, index);
	//fout<<index<<"_T_"<<baseId<<"_"<<time<<endl;
	index+=1;
}

int init(ha_t* ha, EventList* el)
{
	ifstream fin;
	fin.open(DATAFILE);
	if(!fin)
		cout<<"file not exist"<<endl;
	string rec;

	ha->h_baseId = (int*)malloc(CSC*sizeof(int));
	ha->h_duration = (float*)malloc(CSC*sizeof(float));
	ha->h_speed = (float*)malloc(CSC*sizeof(float));
	ha->h_pos = (float*)malloc(CSC*sizeof(float));
	ha->h_no = (int*)malloc(CSC*sizeof(int));
	ha->h_time = (float*)malloc(CSC*sizeof(float));
	ha->h_etype = (int*)malloc(CSC*sizeof(int));
	ha->h_init = (int*)malloc(N*sizeof(int));

	int i = 0;
	int index = 0;

	while(!fin.eof()){
		getline(fin,rec);
		parseData(rec, index, i, ha, el);
		i++;
	}
	free(ha->h_duration);
	free(ha->h_pos);
	free(ha->h_speed);
	free(ha->h_init);
	fin.close();
	return index;
}

void process(){
	//ofstream out("naive.txt");
	ha_t ha;
	EventList *el = new EventList();
	init(&ha, el);
	cout<<el->size()<<endl;
	int brate=0, drate=0;
	int *base = (int*)malloc(20*sizeof(int));
	for(int i=0; i<20; i++)
		base[i]=0;
	p_t e = el->getNextEvent();
	while(e.time != END){
		int index = e.index;
		int baseId = ha.h_baseId[index];
		int etype = ha.h_etype[index];
		int no = ha.h_no[index];
		int takenup = base[baseId];
		switch(etype){
		case TERMI:
			base[baseId]--;
			break;
		case INIT:
			if(takenup < 10)
				base[baseId]++;
			else{
				//out<<index<<" "<<baseId<<" "<<no<<endl;
				//out.flush();
				brate++;
				int tempno = ha.h_no[++index];
				while(tempno==no){
					ha.h_etype[index]=DEAD;
					tempno = ha.h_no[++index];
				}
			}
			break;
		case HANDO:
			base[baseId-1]--;
			if(takenup < 10)
				base[baseId]++;
			else{
				//out<<index<<" "<<baseId<<" "<<no<<endl;
				//out.flush();
				drate++;
				int tempno = ha.h_no[++index];
				while(tempno==no){
					ha.h_etype[index]=DEAD;
					tempno = ha.h_no[++index];
				}
			}
			break;
		case DEAD:
			break;
		}
		e = el->getNextEvent();
	}
	cout<<brate<<" "<<drate<<endl;
//	out.close();
}

int main(int argc, char** argv)
{
	DATAFILE = argv[1];
	N = atoi(argv[2]);
	CSC = N*10;
	clock_t start;
	start = clock();
	process();
	cout<<clock()-start;
	return 0;
}

