#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


int main(){

    ifstream readFile;
    string fileName;
    cout<<"Please enter the file name:"<<endl;
	cin>>fileName;
    readFile.open(fileName.c_str());
    while(readFile.fail()){
        cout<<"Could not open the file. Please enter a valid file name:"<<endl;
        cin>>fileName;
        readFile.open(fileName.c_str());
    }

    bool flag = true;
    char temp;
    string tempLine;

    getline(readFile,tempLine);
    int lineLength= tempLine.length();
    readFile.seekg(0);

    while(getline(readFile,tempLine)){
        if (tempLine.length()!=lineLength) {
            flag = false;
            break;
        }
        for(int i=0;i<tempLine.length();i++){
            if(tempLine.substr(i,1) != "-" && tempLine.substr(i,1) != "#"){
                flag = false;
                break;
            }
        }
    }
	readFile.close();

	if(flag == false){
		cout<<"Erroneous file content. Program terminates."<<endl;
	}
	else{
		vector<vector<char>> mat;
		string tLine;
		char tChar;
		readFile.open(fileName.c_str());
		cout<<"The matrix file contains:"<<endl;
		while(getline(readFile,tLine)){
			vector<char> tVec;
			for(int i=0;i<tLine.length();i++){
				tChar = tLine.at(i);
				cout<<tChar;
				tVec.push_back(tChar);
			}
			cout<<endl;
			mat.push_back(tVec);
		}
		bool f2= true;
		while(f2==true){
			string query;
			cout<<"Enter the string query for a shape, or "<<"\"Quit\""<<" to terminate the program: "<<endl;
			cin>>query;
			if(query=="Quit"){
				break;
			}
			else{
				query = query+"/";
				vector<vector<char>> stars;
				vector<char> star;
				string tstar = "";
				for(int i=0;i<query.length();i++){
					if(query.at(i)!='/'){
						tstar = tstar + query.at(i);
					}
					else if (query.at(i)='/'){
						if(tstar==""){
							tstar = "1 ";
						}
						vector<char> star;
						for(int k=0;k<tstar.length();k=k+2){
							int number = tstar.at(k) - '0';
							for(int j=0;j<number;j++){
								star.push_back(tstar.at(k+1));
							}
						
						}
						tstar = "";
						stars.push_back(star);
					}
				}
				int size = 0;
				for (int i=0;i<stars.size();i++){
					if (stars[i].size()>size)
					{
						size = stars[i].size();
					}
				}
				for(int k=0; k<stars.size();k++){
					if(stars[k].size()<size){
						int rsize = stars[k].size();
						for(int l=0;l<size-rsize;l++){
							stars[k].push_back('b');
						}
					}
				}
				if(size > mat[0].size() || stars.size() > mat.size()){
					cout<<"No placements found."<<endl;
				}
				else{
					int count = 1;
					for(int j=0;j<=mat.size()-stars.size();j++){	
						for(int i = 0; i<=mat[j].size()-stars[0].size();i++){
							bool f = true;
							vector<vector<int>> indexes;
							for(int k = 0; k<stars.size();k++){
								for(int l = 0;l<stars[k].size();l++){
									vector<int> index;
										if(mat[k+j][l+i]=='-'&&stars[k][l]=='s'){
											index.push_back(k+j);
											index.push_back(l+i);
											indexes.push_back(index);
										}
										else if(mat[k+j][l+i]=='#'&&stars[k][l]=='s'){
											f = false;
										}
								}	
							}
							if(f==false){
								indexes.clear();
							}
							if(indexes.size()!=0){
								cout<<"Placement number "<<count<<":"<<endl;
								for(int i=0; i<indexes.size();i++){
									cout<<"("<<indexes[i][0]<<","<<indexes[i][1]<<") ";
								}
								cout<<endl;
								count++;
							}
						}
						
					}
					if(count==1){
						cout<<"No placements found."<<endl;
					}
				}
			}
		}
	}
	return 0;
}

