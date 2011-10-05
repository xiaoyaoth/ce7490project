#ifndef BASE_H_
#define BASE_H_

#ifndef BASENO
#define BASENO 20
#endif

#include <string>
#include <sstream>

using namespace std;//omit this may cause TOSTRING function erronous

class Base{
private:
	int occupiedChannel;
	int baseID;
	static Base * blist;
public:
	Base();
	Base(int bid);
	int getOccupiedChannel();
	int getBaseID();
	void setBaseID(int bid);
	void incOccupiedChannel();
	void decOccupiedChannel();
	string toString();

	static Base* getBlist();
};
#endif
