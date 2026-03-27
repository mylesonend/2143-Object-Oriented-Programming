#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Args.h"

using namespace std;

vector<string> valid= {"--grayscale","--brightness","--rotate","--blur"};

Args::Args(int argc, char* argv[]) {
    
}

void Args::print() const {
   
}

bool argTester(string arg){
    for(auto &item : valid){
        if(arg==item){
            return true;
        }
    }
    return false;
}


    





    ////////////////////////////////////////////////////////////////////////////////////
    // if(argc < 2){
    //     cout<<"Error: need filename\n";
    //     cout<<"Usage: ./deux <filename>\n";
    //     exit(1);
    // }

    // ifstream fin;
    // fin.open(argv[1]);
    // int x;

    // while(!fin.eof()){
    //     fin>>x;
    //     cout<<x<<" ";
    // }

    ////////////////////////////////////////////////////////////////////////////////////
    // cout<<argc<<endl;
    // cout<<argv[0]<<endl;
