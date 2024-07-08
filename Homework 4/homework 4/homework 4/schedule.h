#ifndef SCHEDULE_H
#define SCHEDULE_H
#include <iostream>
#include <string>
using namespace std;

//enum for days
enum Days {Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday};

//a 2D array class 
class Schedule{

private: 
	int time_slots;
	string** data;

public:
	Schedule();//default constructer
	Schedule(int slots);//paramterized constructer
	Schedule(const Schedule&);//deep copy constructor
	~Schedule();//destructor
	Schedule& operator=(const Schedule &rhs);//copy operator

    Schedule operator+(const Days& rhs) const;//makes the given day busy in every time slots
    Schedule operator+(const int& rhs) const;//makes the given slot in all days busy
    Schedule operator+(const Schedule& rhs) const;//common the free slots in two Schedule
    Schedule operator*(const Schedule& rhs) const;//common the busy slots in two Schedule
	string* operator[](const Days& rhs)const;//gives the time slots of the given day
	
	string getData(int i, int j) const;//get data out
	int getSlots() const;//gets slot out
};
	
	bool operator<(const Schedule&lhs, const Schedule& rhs);//compares two Schedule
	ostream& operator<<(ostream& out, const Schedule &rhs);//makes the Schedule a ostream
	ostream& operator<<(ostream& out, Days day);//makes the day a ostream


#endif