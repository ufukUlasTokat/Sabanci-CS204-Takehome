#include <iostream>
#include "feedback.h"
#include <vector>
using namespace std;

//defining a node struct
struct node{
	int digit;
	node * next;
};

//defining linked list class with neccecary functions
class linkedList{

public:
	node* head;

	linkedList(){
		head = NULL;
	}

	//checks if the given int is in the list
	bool check(int value){
		node* check = head;
		while(check!=NULL){
			if(check->digit == value){
				return false;
			}
			check = check->next;
		}
		return true;
	}

	//adds given int to the list
	void adding(int value){
		if(check(value)){
			node* newNode = new node();
			newNode->digit = value;
			newNode->next = head;
			head = newNode;
		}
		return;
	}

	//deletes the given int from the list
	void remove(int value){
		if(check(value)==false){
			node* del = head;
			while(del!=NULL){
				if (del->digit == value) {
					delete del;
				}
				del = del->next;
			}
		}
		return;
	}

	//delete all elements from the list
	void empty(){
		node* del = head;
		while(del!=NULL){
			del->digit = -1;
			del = del->next;
		}
		return;
	}

	//sent all elements of the list out
	void printl(){
		node* temp = head;
		while(temp!=NULL){
			if(temp->digit!=-1){
				if(size()==1){
					cout<<temp->digit;
				}
				else{
					cout<<temp->digit<<" ";
				}
			}
			temp =temp->next;
		}
		return;
	}

	//adds every element but not the given int
	void addallwithout(int value){
		for(int k=9; k>=0;k--){
			if(k!=value){
				adding(k);
			}
		}
	}

	//sorts the list
	void sorting(){
		node* pointer1 = head;
		int temp = 0;
		while(pointer1!=NULL){
			node* pointer2 = pointer1->next;
			while(pointer2!=NULL){
				if(pointer1->digit > pointer2->digit){
					temp=pointer1->digit;
					pointer1->digit = pointer2->digit;
					pointer2->digit = temp;
				}
				pointer2 = pointer2->next;
			}
			pointer1 = pointer1->next;
		}
	}

	//determines the size of the list
	int size(){
		node* sizer = head;
		int count = 0;
		while(sizer!=NULL){
			if(sizer->digit!=-1){
				count++;
			}
			sizer = sizer->next;
		}
		return count;
	}

	//finds the number that is not in the impossible list
	int find(){
		
		int result=0;
		for(int i=0;i<10;i++){
			int count=0;
			node* check = head;
			while(check!=NULL){
				if(check->digit != i){
					count++;
				}
				check = check->next;
			}
			if(count==size()){
				return i;
			}
			
		}
		return 0;
	}
};




int main(){

	//getting inputs
	int id;
	string guess;
	cout<<"Please enter a game ID."<<endl;
	cin>>id;
	
	//forming the lists
	vector<vector<linkedList>> lists;
	for(int i=0;i<3;i++){
		vector<linkedList> temp;
		for(int k=0;k<2;k++){
			linkedList templ;
			temp.push_back(templ);
		}
		lists.push_back(temp);
	}

	

	bool flag = true;
	while(flag == true){
		cout<<"Enter your guess."<<endl;
		cin>>guess;

		// input check
		char slot1 = guess[0];
		char slot2 = guess[1];
		char slot3 = guess[2];

		int counter=0;
		for(int i=0;i<3;i++){
			if(guess[i]-'0'>=0 &&guess[i]-'0'<=9){
				counter++;
			}
		}


		//main process of code
		if(slot1!=slot2 && slot1!=slot3 && slot2!=slot3 && counter==3){
			string result = get_the_feedback(guess,id);
			for(int i=0;i<3;i++){

				//determining the indexses
				int other1;
				int other2;
				if(i==0){
					other1 = 1;
					other2 = 2;
				}
				else if(i==1){
					other1 = 0;
					other2 = 2;
				}
				else if(i==2){
					other1 = 0;
					other2 = 1;
				}


				//making the changes on lists
				int slot = guess[i]-'0';
				if(result[i]=='G'){
					lists[i][1].adding(slot);
					lists[i][0].addallwithout(slot);
					lists[other1][0].adding(slot);
					lists[other2][0].adding(slot);
					lists[other1][1].remove(slot);
					lists[other2][1].remove(slot);
	
				}
				else if(result[i]=='Y'){
					lists[i][1].remove(slot);
					lists[i][0].adding(slot);
					if(lists[other1][0].check(slot)){
						lists[other1][1].adding(slot);
					}
					if(lists[other2][0].check(slot)){
						lists[other2][1].adding(slot);
					}
				}
				else if(result[i]=='R'){
					
					lists[i][0].adding(slot);
					if(result[other1]!='G'){
						lists[other1][0].adding(slot);
					}
					if(result[other2]!='G'){
						lists[other2][0].adding(slot);
					}
	
				}
			}

			//sorting the lists
			lists[0][0].sorting();
			lists[0][1].sorting();
			lists[1][0].sorting();
			lists[1][1].sorting();
			lists[2][0].sorting();
			lists[2][1].sorting();

			//output
			cout<<"Linked lists:"<<endl;
			cout<<"Slot: 1"<<endl;
			cout<<"Impossibles: ";
			lists[0][0].printl();
			cout<<endl;
			cout<<"Possibles: ";
			lists[0][1].printl();
			cout<<endl<<endl;


			cout<<"Slot: 2"<<endl;
			cout<<"Impossibles: ";
			lists[1][0].printl();
			cout<<endl;
			cout<<"Possibles: ";
			lists[1][1].printl();
			cout<<endl<<endl;


			cout<<"Slot: 3"<<endl;
			cout<<"Impossibles: ";
			lists[2][0].printl();
			cout<<endl;
			cout<<"Possibles: ";
			lists[2][1].printl();
			cout<<endl<<endl;;
		}

		else{
			cout<<"Invalid guess. ";

		}

		//final check
		if(lists[0][0].size()==9 && lists[1][0].size()==9 &&  lists[2][0].size()==9){
			cout<<"The secret number is: ";
			cout<<lists[0][0].find();
			cout<<lists[1][0].find();
			cout<<lists[2][0].find();
			cout<<endl<<"Congrats! Now, deleting the lists...";
			flag = false;
		}
		
	}

	
	return 0;
}
