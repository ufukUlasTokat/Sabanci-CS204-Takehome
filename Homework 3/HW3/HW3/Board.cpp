#include <iostream>
#include "Board.h"
#include <vector>
using namespace std;


//a function that determine the number of slots in the board
int size(slot* head){
	slot *size = head;
	int count =0;
	while(size!=NULL){
		count++;
		size = size->next;
	}
	return count;
}


//default constructor initilaze the private members
Board:: Board(){
	head = nullptr;
	tail = nullptr;
	xCnt = 0;
	oCnt = 0;
}

//checks all pieces of the players to determie at least one can move with the given die or not
bool Board::noMove(char player, int move){
	
	slot* nomove = head; //a slot for check slots of the player
	slot* nomovedirection2 = head; //a slot for check every possible target of the player
	CharStack nomovestack;//a charstack to check slots without deleting them
	char ch;
	tail;
	int loop = 0;
	int length = size(head);


	//a loop passing thourgh all slots
	while(loop<length){
		nomovestack = nomove->slotStack;
		while(!nomovestack.isEmpty()){
			nomovestack.pop(ch);			
		}
		if(ch==player){

			//direction 1
			int i;
			for(i=0;i<move;i++){
				if(nomove == tail){
					break;
				}
				nomove = nomove->next;
			}

			if( i == move){
				nomovestack = nomove->slotStack;
				while(!nomovestack.isEmpty()){
					nomovestack.pop(ch);			
				}
				if(ch==player || ch == ' '){
					return false; //there is a possible move
				}
			}			
			for(int k=0;k<i;k++){
				nomove = nomove->prev;
			}

			//direction 0
			for(i=0;i<move;i++){
				if(nomovedirection2 == head){
					break;
				}
				nomovedirection2 = nomovedirection2->prev;
			}
			if(i == move){
				nomovestack = nomovedirection2->slotStack;
				while(!nomovestack.isEmpty()){
					nomovestack.pop(ch);			
				}
				if(ch==player || ch == ' '){
					return false; //there is a possible move
				}
				
			}
			for(int k=0;k<i;k++){
				nomovedirection2 = nomovedirection2->next;
			}

		}		
		nomovedirection2 = nomovedirection2->next;
		nomove = nomove->next;
		loop++;
	}
	return true; //there is no possible move
	
}


// a function checks if the slot is belong to player
bool find(CharStack stack, char player){
	int count = 0;
	while(!stack.isEmpty()){
		char ch;
		stack.pop(ch);
		if(ch == player){
			count++;
		}
	}
	if(count == 0){
		return false;//slot is not belong to player
	}
	return true;//slot is belong to player
}

//checks the validty of the move player want to do
int Board::validMove(char player, int start, int amount, int direction){
	slot *validindex = head;//a slot for the start
	slot *validtarget = head;//a slot for the target
	CharStack validind;//a slot for the start
	CharStack validtar;//a slot for the target 

	int move;
	int sizeofboard = size(head);

	//a if checks start index in boundry
	if(start<sizeofboard){

		//a loop to find slot of the given index
		for(int i=0; i<start;i++){
			validindex = validindex->next;
		}validind = validindex->slotStack;

		//a if checks start slot belongs to palyer
		if(find(validind,player)){
			//in left direction determines the index of target
			if(direction == 0 && start-amount>=0){
				move = start-amount;
				//find the target slot
				for(int i=move;i>0;i--){
					validtarget = validtarget->next;
				}validtar = validtarget->slotStack;
			}
			
			//in right direction determines the index of target
			else if(direction == 1 && start+amount<sizeofboard){
				move = start+amount;
				//find the target slot
				for(int i=0;i<move;i++){
					validtarget = validtarget->next;
				}validtar = validtarget->slotStack;
			}
			else{
				return 2;//target does not with in the boundry
			}
			char ch;
			while(!validtar.isEmpty()){	
				validtar.pop(ch);
			}
			//a if checks the target slot is valid
			if(ch != player && ch != ' '){
				return 3;//target slot is not valid
			}
		}
		else{
			return 4;//start slot does not belong to player
		}	
	}
	else{
		return 1;//start slot does not in the boundry
	}
	return 0;//move is valid
}

//makes the move
void Board::movePiece(int source,int target){
	slot *from = head;//a slot for start
	slot *to =  head;//a slotfor target
	
	//finds the starting slot
	for(int i=0; i<source ; i++){
		from = from->next;
	}
	char ch;
	int k = 0;
	bool stop = true;
	//finds top of the start slot
	while(k<4 && stop){
		from->slotStack.pop(ch);
		if(ch != ' '){
			stop = false;
		}
		k++;
	}
	//finds the target slot
	while(k!=0){
		from->slotStack.push(' ');
		k--;
	}
	//finds the top of the target slot
	for(int i=0; i<target ; i++){
		to = to->next;
	}

	k = 0;
	stop = true;
	int count = 0;
	//make the move
	while(k<4 && stop){
		char ch2;
		to->slotStack.pop(ch2);
		
		if(ch2 == ' '){
			count++;
		}
		else{
			to->slotStack.push(ch2);
			stop = false;
			while(k>1){
			to->slotStack.push(' ');
			k--;
			}
		}
		k++;
	}
	if(count == 4){
		to->slotStack.push(ch);
		while(k>1){
			to->slotStack.push(' ');
			k--;
		}
		
	}
}

//checks whether the slot is full or not 
//to do it checks only the top of the slot
bool Board::targetSlotFull(int index){
	  slot *target = head;
	  CharStack targeted;
	  for(int i=0;i<index;i++){
		  target = target->next;
	  }
	  targeted = target->slotStack;
	  char ch;
	  targeted.pop(ch);
	  if(ch!=' '){
		return true;//slot is full
	  }
	  return false;//slot is not full
}

//destroy only one slot 
void Board::destroySlot(int index){
	slot* destroy = head;
	
	//finds the slot to destroy
	for(int i=0;i<index;i++){
		destroy = destroy->next;
	}

	char ch; 
	destroy->slotStack.pop(ch);

	//changes the couts
	if(ch == 'x'){
		xCnt = xCnt-4;
	}
	else{
		oCnt = oCnt-4;
	}

	//remove the slot from list an delete it
	if(destroy == head){//if slot is head
		head = head->next;
		head->prev = nullptr;
		delete destroy;
	}
	else if(destroy == tail){//if slot is tail
		tail = tail->prev;
		tail->next = nullptr;
		delete destroy;
	}
	else{
		destroy->prev->next = destroy->next;
		destroy->next->prev = destroy->prev;
		delete destroy;
	}
}

//simply clears all the board
void Board::clearBoard(){
	int length = size(head);
	
	for(int i=length-1;i>=0;i--){
		slot* del = head;
		head = head->next;
		delete del;
	}
	
}

//checks winner by comparing counts
int Board::evaluateGame(){
	if(xCnt < oCnt){
		return 1;//x win
	}
	else if(xCnt > oCnt){
		return 2;//o win
	}
	else{
		return 3;//tie
	}
}

//add a slot to begining
void Board::createSlotBegin(char ch, int num){
	//creates a slot 
	slot *newhead = new slot();
	for(int i = 0; i<num;i++){
		newhead->slotStack.push(ch);
		if(ch=='x'){
			xCnt++;
		}
		else if(ch=='o'){
			oCnt++;
		}
	}
	for(int k=0; k<4-num;k++){
		newhead->slotStack.push(' ');
	}
	//add it into list
	//and make it head
	if(head != NULL){
		head->prev = newhead;
		newhead->next = head;
		head = newhead;
	}
	else{
		tail = newhead;
		head = newhead;
	}
}
//add a slot to end
void Board::createSlotEnd(char ch,int num){
	//creates a slot 
	slot *newtail = new slot();
	for(int i = 0; i<num;i++){
		newtail->slotStack.push(ch);
		if(ch=='x'){
			xCnt++;
		}
		else if(ch=='o'){
			oCnt++;
		}
	}
	for(int k=0; k<4-num;k++){
		newtail->slotStack.push(' ');
	}
	//add it into list
	//and make it tail
	if(tail != NULL){
		tail->next = newtail;
		newtail->prev = tail;
		tail = newtail;
	}
	else{
		tail = newtail;
		head = newtail;
	}
}
//add an empty slot to end
void Board:: createEmptySlotEnd(){
	//creates an empty slot 
	slot *newtail = new slot();
	for(int i = 0; i<4;i++){
		newtail->slotStack.push(' ');
	}
	//add it into list
	//and make it tail
	if(tail != NULL){
		tail->next = newtail;
		newtail->prev = tail;
		tail = newtail;
	}
	else{
		tail = newtail;
		head = newtail;
	}
}


//prints the board 
void Board:: printBoard(){
	slot * print = head;
	CharStack printing = print->slotStack; 
	int i=0;

	//a loop to move in slots
	while(i<4){
		//aloop to move in list
		while(print!=tail->next){
			printing = print->slotStack;
			char ch;
			int k = i;
			while(k>=0){
				printing.pop(ch);
				k--;
			}
			cout<<ch;
			print = print->next;
			
		}
		cout<<endl;
		print = head;
		i++;
	}
	int length = size(head);
	for(int i=0;i<length;i++){
		cout<<"^";
	}cout<<endl;
}






