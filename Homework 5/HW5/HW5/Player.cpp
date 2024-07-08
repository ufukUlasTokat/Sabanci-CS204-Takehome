#include "Player.h"
#include <iostream>
using namespace std;

Player:: Player(Board& b, string n, int initial):object(b)
{
	name = n;
	balance = initial;
	position = object.getter();
}

int Player:: move(int steps){
	int count = 0;
	for(int i=0;i<steps;i++){
		position = position->next;
		if(position==object.getter()){
			count++;
		}
	}
	if(count!=0){
		return 1;
	}
	else{
		return 0;
	}
}

Node* Player:: where_am_I(){
	return position;
}

void Player:: pay_to_player(Player &otherPlayer, int money){
	balance = balance-money;
	otherPlayer.balance = otherPlayer.balance + money;
}

int Player:: get_balance(){
	return balance;
}

void Player:: deposit_money(int add){
	balance = balance+add;
}

void Player:: buy_slot(int price){
	position->owner= name;
	balance = balance-price;
}

bool Player:: is_bankrupt(){
	if(balance<0){
		return true;
	}
	else{
		return false;
	}
}

void Player:: display(){
	Node *temp = object.getter();
	while(temp != position){
		cout<<"      ";
		temp = temp->next;
	}
	cout<<name<<" "<<balance<<endl;
}