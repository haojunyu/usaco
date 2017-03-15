/*
ID: haojuny2
LANG: C++
PROG: ride
*/
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

int strHash(string s){
    int res = 1, i;
    for(i=0; i<s.length(); i++){
      res = (res * (s[i]-'A'+1)) % 47;
    }
    return res;
}

int main(){
    ifstream fin("ride.in");
    ofstream fout("ride.out");

    string comet, group;
    fin >> comet >> group;

    if(strHash(comet) == strHash(group)){
      fout << "GO" << endl;
    }else{
      fout << "STAY" << endl;
    }

    return(0);
}

