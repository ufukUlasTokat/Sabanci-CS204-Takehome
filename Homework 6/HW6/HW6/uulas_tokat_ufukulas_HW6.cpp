#include <iostream>
#include "IntQueueHW6.h"
#include <thread>
#include <vector>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <mutex>

using namespace std;

mutex myMutex;

//the function that will capture the chair for player
void player(int ID, struct tm *ptm, IntQueueHW6 & chairs, int& loserID, vector<int>& winners) 
{	
	//for equal opportunity to capture chair sleep the treads for 2 seconds
	this_thread::sleep_until(chrono::system_clock::from_time_t(mktime(ptm)));

	//for avoid chaos in the output myMutex
	myMutex.lock();
	if(!chairs.isFull()){
		chairs.enqueue(ID);
		winners.push_back(ID);//adding the players who captures into list in order to display in main
		cout<<"Player "<<ID<<" captured a chair at "<<ptm->tm_hour<<":"<<ptm->tm_min<<":"<<ptm->tm_sec<<endl;
		
	}
	else{
		cout<<"Player "<<ID<<" couldn't capture a chair."<<endl; 
		loserID = ID;//too know who is the loser in main
	}
	myMutex.unlock();//end of myMutex
}



int main(){

	//greeting and initilazing part
	cout<<"Welcome to Musical Chairs game!"<<endl;
	int numberOfPlayers;
	cout<<"Enter the number of players in the game: "<<endl;
	cin>>numberOfPlayers;
	cout<<"Game Start!"<<endl;

	//defining the start time
	time_t tt = chrono::system_clock::to_time_t (chrono::system_clock::now()); 
	struct tm *ptm = new struct tm;
	cout<<endl;
	localtime_s(ptm, &tt); 

	//forming vector of IDs to track the players who continue to game
	vector<int> IDs;
	for(int i=0; i<numberOfPlayers;i++){
		IDs.push_back(i);
	}

	//main loop of game that will continue until the end
	vector<int> winners;
	vector<thread> threads;
	while(IDs.size()!=1){
		
		cout << "Time is now " << put_time(ptm,"%X") << endl;

		//Queue of chairs
		IntQueueHW6 chairs(numberOfPlayers-1);

		//set time to 2 second ahead and check if pass minute
		ptm->tm_sec+=2;


		if(ptm->tm_sec>60){
			ptm->tm_sec = ptm->tm_sec%60;
			ptm->tm_min++;
		}

		//forming vector of threads to call them in loop
		int loserID = 0;
		for(int k=0; k<IDs.size();k++){
			threads.push_back(thread(&player,IDs[k],ptm,ref(chairs),ref(loserID),ref(winners)));
		}

		//calling threads in loop
		for (int i=0; i<threads.size(); i++){
			 threads[i].join();
		}

		//emptying the cahirs
		int deq;
		while(!chairs.isEmpty()){
			chairs.dequeue(deq);
		}

		//displaying remanining player from winners list
		cout<<"Remaining players are as follows: ";
		for(int i=0;i<winners.size();i++){
			cout<<winners[i]<<" ";
		}
		cout<<endl;

		//clearing the winner list for next round
		winners.clear();

		//clearing threads for next round
		threads.clear();
		
		//delete losers Id from the IDs list
		for(int i=0;i<IDs.size();i++){
			if(IDs[i]==loserID){
				IDs.erase(IDs.begin()+i);
			}
		}
		cout<<endl;
		numberOfPlayers--;
		
	}

	//End of game
	cout<<endl<<"Game over!"<<endl;
	cout<<"Winner is Player "<<IDs[0]<<"!";
	
	
	return 0;
}