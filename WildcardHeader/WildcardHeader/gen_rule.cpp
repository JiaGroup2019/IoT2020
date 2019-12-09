//
//  gen_rule.cpp
//  FuzzyQuery
//
//  Created by 王明月 on 2019/11/27.
//  Copyright © 2019年 王明月. All rights reserved.
//

#include "gen_rule.hpp"
#include <fstream>
#include <iostream>
#include <ctime>
using namespace std;

GenRule::GenRule(){
    
}

GenRule::~GenRule(){
    
}

void GenRule::genRule(string outputPath, string rulePath){
    //const int maxLineSize = 128;
    //char buffer[maxLineSize];
    ifstream fin(rulePath);
    ofstream fout(outputPath);
    
    if(fin.good() && fout.good()){
        cout << "good!" << endl;
        string strLine;
        int i = 0;
        while (getline(fin, strLine)) {
            //cout << strLine << endl;
            fout << strLine << endl;
            i++;
        }
        fin.close();
        fout.close();
    }
    else {
        cout << "error open file!" << endl;
    }
}

void GenRule::genHeader(string outputHeader, int packageCount){
    srand((unsigned)time(NULL));
    const int packageSize = 60;
    int ip_addr[4];
    ofstream fout(outputHeader);
    
    if (fout.good()) {
        for (int i = 0; i < packageCount; i++) {
            for (int j = 0; j < 4; j++) {
                int temp = rand() % 256;
                ip_addr[j] = temp;
            }
            fout << ip_addr[0] << "." << ip_addr[1] << "." << ip_addr[2] << "."<< ip_addr[3] << "." << " " << packageSize << endl;
        }
        fout.close();
    } else {
        cout << "error on open file" << outputHeader << endl;
    }
}
