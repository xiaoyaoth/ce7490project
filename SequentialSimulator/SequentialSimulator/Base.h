#ifndef BASE_H_
#define BASE_H_

class Base{
private:
	int occupiedChannel;
	int baseID;
public:
	Base();
	Base(int bid);
	int getOccupiedChannel();
	int getBaseID();
	void setBaseID(int bid);
	void incOccupiedChannel();
	void decOccupiedChannel();
};
#endif
