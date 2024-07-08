#ifndef BOARD_H
#define BOARD_H
#include "CharStack.h"


//defining the slot struct 
struct slot
{
	slot * next;
	slot * prev;
	CharStack slotStack;
	slot (){
		prev = nullptr;
		next = nullptr;
	}
};

//definitions of board class
class Board
{
private:
	slot * head;//begining of the list
	slot * tail;//end of the list
	int xCnt;//number of x
	int oCnt;//number of o
public:
	Board();//def
	bool noMove(char player, int move);//check if there is a move 
	int validMove(char player, int start, int amount, int direction);//check if the move player want to do is valid
	void movePiece(int source, int target);//simply makes the move
	void printBoard();//prints the board
	int evaluateGame();//check who win or the game is a tie
	bool targetSlotFull(int index);//checks if the slot in the given index is full
	void destroySlot(int index);//delte the slot
	void createSlotBegin(char ch, int num);//creates a slot at the beging (it becames head)
	void createSlotEnd(char ch, int num);//creates a slot at the end (it becames tail)
	void createEmptySlotEnd();//creates an empty slot at the end (it becames tail)
	void clearBoard();//deletes all the board
};

#endif