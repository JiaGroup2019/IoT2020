//
//  HeaderRule.cpp
//  MiddleBox
//
//  Created by 王明月 on 2019/11/28.
//  Copyright © 2019年 王明月. All rights reserved.
//

#include <iostream>
#include "HeaderRule.hpp"
#include <vector>
#include <string>
#include <time.h>
#include <fstream>
#include <sstream>
#include "math.h"

#define L 5
#define JUDGE_FLAG 0.000001
#define PACKET_NUMBER 365

using namespace std;

HeaderRule::HeaderRule(){
    
}
HeaderRule::~HeaderRule(){
    
}

uint32_t HeaderRule::DiffTimeInMicroSecond(){
    static timeval t_start, t_end;
    gettimeofday(&t_end, NULL);
    uint32_t uiTimeInterval = 10000000 * (t_end.tv_sec - t_start.tv_sec) + t_end.tv_usec - t_start.tv_usec;
    gettimeofday(&t_start, NULL);
    
    return uiTimeInterval;
}

uint32_t HeaderRule::DiffTimeInSecond(){
    static time_t t_cur;
    uint32_t ui_time = time(NULL) - t_cur;
    t_cur = time(NULL);
    
    return ui_time;
}

vector<int> HeaderRule::getIp(string ip_addr){
    vector<int> ruleIp;
    string splitIp[4];
    int counter = 0;
    for(int i = 0; i < ip_addr.length(); i++){
        if (ip_addr[i] != '.') {
            splitIp[counter] += ip_addr[i];
        }else
            counter ++;
    }
    for(int j = 0; j < counter; j++){//string to int
        if(splitIp[j] != "*"){
            int temp = stoi(splitIp[j]);
            ruleIp.push_back(temp);
        }else{
            int temp = 1000;
            ruleIp.push_back(temp);
        }
    }
    return ruleIp;
}

//build plain index
vector<int> HeaderRule::buildInd(vector<int> ruleIp){
    vector<int> plain_ind;
    for(int k = 0; k < L; k++){
        plain_ind.push_back(1);
    }
    for(int i = 0; i < 4; i++){
        if(ruleIp[i] == 1000){
            for (int j = 0; j < L; j++) {
                plain_ind[j] *= mapKey[i];
            }
        }else{
            int index = (ruleIp[i] + mapKey[i]) % L;
            plain_ind[index] *= mapKey[i];
        }
    }
    return plain_ind;
}

//encrypt index
vector<size_t> HeaderRule::encInd(vector<int> rule_ip, vector<int> plain_ind){
    vector<size_t> enc_ind;
    hash<string> enc_h;
    string str = to_string(rule_ip[0]);
    hash<string> t_h;
    size_t token = t_h(str);
    srand((unsigned)time(NULL));
    size_t nonce = rand();
    for (int i = 0; i < L; i++) {
        enc_ind.push_back(plain_ind[i]);
    }
    for (int j = 0; j < L; j++) {
        string t_temp;
        t_temp = to_string(token) + to_string(j) + to_string(nonce);
        enc_ind[j] ^= enc_h(t_temp);
    }
    enc_ind[L] = nonce;
    return enc_ind;
}

void HeaderRule::loadRule(string plainRulePath, int size){
    const int maxLineSize = 64;
    char buffer[maxLineSize];
    ifstream fin(plainRulePath);
    vector<int> ruleIp;
    vector<int> plainIndex;
    vector<size_t> encIndex;
    
    if (fin.good())
    {
        vecHeaderRules.clear();
        for (int i = 0; fin.good() && i < size; i++)
        {
            fin.getline(buffer, maxLineSize);
            HeaderRule head;
            ruleIp = head.getIp(buffer);
            plainIndex = head.buildInd(ruleIp);
            encIndex = head.encInd(ruleIp, plainIndex);
            //head.init(&engine);
            vecHeaderRules.push_back(encIndex);
        }
        fin.close();
        cout << "Load "<<vecHeaderRules.size()<< " rules." << endl;
    }
    else
    {
        cout << "Open file "<< plainRulePath <<" Failed." << endl;
    }
}


//generate token for each ip
size_t HeaderRule::genToken(vector<int> rule_ip){
    string str = to_string(rule_ip[0]);
    hash<string> t_h;
    size_t token = t_h(str);
    return token;
}

//build plain trapdoor
vector<double> HeaderRule::buildTrap(vector<int> ipAddr){
    vector<double> plain_trap;
    for(int k = 0; k < L; k++){
        plain_trap.push_back(1);
    }
    for(int i = 0; i < 4; i++){
        int index = (ipAddr[i] + mapKey[i]) % L;
        plain_trap[index] /= mapKey[i];
    }
    return plain_trap;
}

//match
int HeaderRule::CheckHeader(vector<double> trap, size_t token, vector<size_t> encInd){
    //int hitRule = 1;
    hash<string> enc_h;
    vector<size_t> decInd;
    vector<double> resMulti;
    vector<int> resFlag;
    for (int k = 0; k < L + 1; k++) {
        decInd.push_back(encInd[k]);
    }
    for (int i = 0; i < L; i++) {
        string t_temp;
        t_temp = to_string(token) + to_string(i) + to_string(decInd[L]);
        decInd[i] ^= enc_h(t_temp);
        resMulti.push_back(decInd[i] * trap[i]);
    }
    for (int j = 0; j < L; j++) {
        if ((resMulti[j] - (int)resMulti[j]) < JUDGE_FLAG && (resMulti[j] - (int)resMulti[j]) > (-JUDGE_FLAG)) {
            resFlag.push_back(1);
        }else{
            resFlag.push_back(0);
        }
    }
    
    if (resFlag[0] == 1 && resFlag[1] == 1 && resFlag[2] == 1 && resFlag[3] == 1 && resFlag[4] == 1 && resFlag[5] == 1 && resFlag[6] == 1 && resFlag[7] == 1 && resFlag[8] == 1 && resFlag[9] == 1 && resFlag[10] == 1 && resFlag[11] == 1 && resFlag[12] == 1) {
        return 1;
    }else{
        return 0;
    }
    //return hitRule;
}

//load headers
void HeaderRule::loadHeader(string plainHeaderPath){
    const int maxLineSize = 64;
    char buffer[maxLineSize];
    ifstream fin(plainHeaderPath);
    vector<int> ruleIp;
    vector<double> plainTrap;
    
    if (fin.good())
    {
        vecHeader.clear();
        vecPacketSize.clear();
        tokenHeader.clear();
        for (int i = 0; fin.good() && i < PACKET_NUMBER; i++)
        {
            fin.getline(buffer, maxLineSize);
            stringstream stringin(buffer);
            string ip;
            int packageSize;
            stringin >> ip >> packageSize;
            HeaderRule head;
            ruleIp = head.getIp(ip);
            tokenHeader.push_back(genToken(ruleIp));
            plainTrap = head.buildTrap(ruleIp);
            //head.init(&engine);
            vecHeader.push_back(plainTrap);
            vecPacketSize.push_back(packageSize);
        }
        fin.close();
        vecLatency.reserve(vecHeader.size());
        cout << "Load "<<vecHeader.size()<< " headers." << endl;
    }
    else
    {
        cout << "Open headers Failed." << endl;
    }
}

//generate table .csv
void HeaderRule::getTableReport(string filename){
    ofstream fout(filename);
    const int bufferSize = 128;
    char buffer[bufferSize];
    
    if (fout.good())
    {
        fout << "id,hit rule,package size,latency" << endl;
        for (int i = 0; i < PACKET_NUMBER; i++)
        {
            sprintf(buffer, "%d,%d,%d,%d\n", i, hitRule[i], vecPacketSize[i], vecLatency[i]);
            fout << buffer;
        }
        fout.close();
    }
    else
    {
        cout << "Open file " << filename << " error." << endl;
    }
    
}

vector<vector<double>>* HeaderRule::getHeaders(){
    return &vecHeader;
}

vector<vector<size_t>>* HeaderRule::getHeaderRules(){
    return &vecHeaderRules;
}
vector<size_t>* HeaderRule::getTokens(){
    return &tokenHeader;
}
