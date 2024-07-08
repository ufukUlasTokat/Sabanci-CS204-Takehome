#include <iostream>

#include <string>
using namespace std;


// a function check whether if input is valid or not and returns true if it is valid 

bool validty_check(string board_config){
	bool checking = true;	int dash_loc = 0;	for(int i=0;i<board_config.length();i = i+dash_loc){		dash_loc = board_config.find("/",i) ;		int dash_loc2 = board_config.find("/",dash_loc+1);		if(dash_loc2- dash_loc == 2){			int number = board_config.at(dash_loc+1) - '0';			if(number<4 && number>0){				string player =  board_config.substr(dash_loc+2,1);				if(player != "x" && player != "o"){					checking = false;					break;				}				else{					checking = true;				}			}			else{				checking = false;				break;			}		}		else{			checking = false;			break;		}	}	return checking;
}



int main(){


	//displaying the name of game
	cout<<"    ___________      ___   ____  __ __ "<<endl;
	cout<<"   / ____/ ___/     |__ \\ / __ \\/ // /"<<endl;
	cout<<"  / /    \\__ \\________/ // / / / // /_"<<endl;
	cout<<" / /___ ___/ /_____/ __// /_/ /__  __/"<<endl;
	cout<<" \\____//____/     /____/\\____/  /_/"<<endl;
	cout<<endl;
	cout<<"   _____ __             __ "<<endl;
	cout<<"  / ___// /_____ ______/ /______ _____ _____ ___  ____ ___  ____  ____"<<endl;
	cout<<"  \\__ \\/ __/ __ `/ ___/ //_/ __ `/ __ `/ __ `__ \\/ __ `__ \\/ __ \\/ __ \\ "<<endl;
	cout<<" ___/ / /_/ /_/ / /__/ ,< / /_/ / /_/ / / / / / / / / / / / /_/ / / / /"<<endl;
	cout<<"/____/\\__/\\__,_/\\___/_/|_|\\__, /\\__,_/_/ /_/ /_/_/ /_/ /_/\\____/_/ /_/ "<<endl;
	cout<<"                         /____/ "<<endl;
	cout<<endl;


	cout<<"[*] Enter a board configuration:"<<endl;	cout<<"[*] Welcome to the Stackgammon Game!"<<endl;	string board_config;	cin>>board_config;	cout<<board_config;		while(validty_check(board_config)==false){		cout<<"Invalid board configuration."<<endl;		cout<<"Enter a board configuration:"<<endl;		cin>>board_config;	}	



	return 0;
}