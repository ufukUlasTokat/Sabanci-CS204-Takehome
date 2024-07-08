#include "Board.h"
#include <iostream>
using namespace std;

Node:: Node(){
	owner = "None";
	next = NULL;
}

Node:: Node(string o, Node * p){
	owner = o;
	next = p;
}
Board:: Board(){
	first = new Node();
}
Board:: ~Board(){
	while(first->next != first){
		Node *temp = first->next;
		delete temp;
		first->next = first->next->next;
	}
	delete first;
}
Board:: Board(int slots){
	Node * temp = new Node();
	first = temp;
	for(int i=1; i<slots;i++){
		temp->next = new Node();
		temp = temp->next;
	}
	temp->next = first;
}

void Board:: display(){
	if(first->owner=="None"){
		cout<< first->owner;
	}
	else{
		cout<<first->owner<<" ";
	}
	Node* temp = first->next;
	int count=0;
	while(temp->next != first){
		cout<<"->";
		if(temp->owner=="None"){
			cout<< temp->owner;
		}
		else{
			cout<<temp->owner<<" ";
		}
		temp = temp->next;
		count++;
	}
	cout<<"->";
	cout<<temp->owner;

	cout<<endl;

	cout<<"^   ";
	for(int i=0;i<count;i++){
		cout<<"      ";
	}
	cout<<"     |";

	cout<<endl;

	cout<<"|---";
	for(int i=0;i<count;i++){
		cout<<"-<----";
	}
	cout<<"-<---v";

	cout<<endl;
	
}

string Board:: who_owns(Node * slot){
	return slot->owner;
}

Node* Board:: getter(){
	return first;
}