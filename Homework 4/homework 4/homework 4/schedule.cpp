#include <iostream>
#include "schedule.h"
using namespace std;

//default constructor which defines the Schedule with row 
Schedule:: Schedule(){
	time_slots = 0;
	data = new string* [7]; 
}
//a parameterized constructor which makes a Schedule with 7 row and given slots 
Schedule:: Schedule(int columns){
	time_slots = columns;
	data = new string* [7]; 

	for (int i = 0; i<7; i++){
		data[i] = new string[columns];
		for (int k = 0; k<columns; k++){
			data[i][k] = "free";
		}
	}
}

//a deep copy constructor which copy the rhs to a new Schedule
Schedule::Schedule(const Schedule& rhs){
	time_slots = rhs.time_slots;
	data = new string*[7];
	for (int i = 0; i<7; i++){
		data[i] = new string [rhs.time_slots];
		for (int k = 0; k<rhs.time_slots; k++){
			data[i][k] = rhs.data[i][k];
		}
	}
			
}

//a destructor deletes the Schedule completely
Schedule:: ~Schedule(){
		delete [] data;
}

//an operator which copy the rigth Schedule toleft Shedule
Schedule & Schedule::operator=(const Schedule &rhs){
	if(this != &rhs)
    {
		time_slots = rhs.time_slots;

        for (int i = 0; i < 7; i++) {
			this->data[i]= rhs.data[i];
        }
    }
    return *this;
}

//an operator which makes the all slots of the day busy 
Schedule Schedule:: operator+(const Days& rhs) const{
	Schedule lhs = *this;
	for (int i = 0; i<time_slots; i++)
		lhs.data[rhs][i] = "busy";
	return lhs;
}
//an operator which makes all given slots in all days busy 
Schedule Schedule:: operator+(const int& rhs) const{
	Schedule lhs = *this;
	for (int i = 0; i<7; i++)
		lhs.data[i][rhs] = "busy";
	return lhs;
}

//an operator mhich finds the common free slots of two Schedule
//then make a new one with those free days
Schedule Schedule:: operator+(const Schedule& rhs) const{
	Schedule result(this->time_slots); 
	for (int i = 0; i<7; i++){
		for (int k = 0; k<this->time_slots; k++){
			if(this->data[i][k] == "free" && rhs.data[i][k] == "free"){
				result.data[i][k] = "free";
			}
			else{
				result.data[i][k] = "busy";
			}
		}
	}
	return result;//common free Schedule
}
//an operator mhich finds the common busy slots of two Schedule
//then make a new one with those busy days
Schedule Schedule:: operator*(const Schedule& rhs)const{
	Schedule result(this->time_slots); 
	for (int i = 0; i<7; i++){
		for (int k = 0; k<result.time_slots; k++){
			if(this->data[i][k] == "busy" && rhs.data[i][k] == "busy"){
				result.data[i][k] = "busy";
			}
			else{
				result.data[i][k] = "free";
			}
		}
	}
	return result;//common busy Schedule
}
//a constructor which returns the chosen day of the Schedule
string* Schedule:: operator[](const Days& rhs) const{
	return data[rhs];//day of Schedule
}
//a operator which compares two Schedule
bool operator<(const Schedule& lhs, const Schedule& rhs){
	int lhs_counter = 0;
	for (int i = 0; i<7; i++){
		for (int k = 0; k<lhs.getSlots(); k++){
			if(lhs.getData(i,k)=="busy"){
				lhs_counter++;
			}
		}
	}
	int rhs_counter = 0;
	for (int i = 0; i<7; i++){
		for (int k = 0; k<rhs.getSlots(); k++){
			if(rhs.getData(i,k)=="busy"){
				rhs_counter++;
			}
		}
	}

	if(lhs_counter < rhs_counter){
		return true;//lhs is smaller
	}
	else{
		return false;//lhs is larger
	}
}
//returns wanted slot of data of Schedule
string Schedule::getData(int i, int j) const{
    return data[i][j];
}

//returns the time_slots of Schedule
int Schedule:: getSlots() const{
	return time_slots;
}

//makes the Schedule an ostream 
ostream& operator << (ostream& out,const Schedule &rhs){
	string daynames[] = {"Mo", "Tu", "We", "Th" , "Fr", "Sa","Su"};
	for (int i = 0; i<7; i++){
		out << daynames[i] << ":" << " ";
		for (int k = 0; k<rhs.getSlots(); k++){
			out << rhs.getData(i,k)<<" ";
		}
		out << endl;
	}
	return out;
}
//makes Days an ostream 
ostream& operator << (ostream& out, Days day){
	string daynames[] = {"Monday", "Tuesday", "Wednesday", "Thursday" , "Friday", "Saturday","Sunday"};
	out << daynames[day];
	Days(Monday);
	return out;
}