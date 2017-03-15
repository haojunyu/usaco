/*
ID: haojuny2
LANG: C++
TASK: test
*/
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

int main(){
    ifstream fin("test.in");
    ofstream fout("test.out");

    int a,b;
    fin >> a >> b;
    fout << a+b << endl;

    return(0);
}

