//
//  ClientCPP.cpp
//  WildcardHeader
//
//  Created by 王明月 on 2019/11/29.
//  Copyright © 2019年 王明月. All rights reserved.
//

#include "ClientCPP.hpp"
#include <time.h>
#include <vector>
#include <string>
#define L 13
//vector<int> mapKey = {1039, 1279, 1471, 1511};

using namespace std;

uint32_t ClientCPP::DiffTimeInMicroSecond(){
    static timeval t_start, t_end;
    gettimeofday(&t_end, NULL);
    uint32_t uiTimeInterval = 10000000 * (t_end.tv_sec - t_start.tv_sec) + t_end.tv_usec - t_start.tv_usec;
    gettimeofday(&t_start, NULL);
    
    return uiTimeInterval;
}

uint32_t ClientCPP::DiffTimeInSecond(){
    static time_t t_cur;
    uint32_t ui_time = time(NULL) - t_cur;
    t_cur = time(NULL);
    
    return ui_time;
}

vector<int> ClientCPP::getIp(string ip_addr){
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

//build plain trapdoor
vector<double> ClientCPP::buildTrap(vector<int> ipAddr){
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

//generate token for each ip
size_t ClientCPP::genToken(vector<int> rule_ip){
    string str = to_string(rule_ip[0]);
    hash<string> t_h;
    size_t token = t_h(str);
    return token;
}
