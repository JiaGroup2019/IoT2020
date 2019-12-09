//
//  HeaderRule.hpp
//  MiddleBox
//
//  Created by 王明月 on 2019/11/28.
//  Copyright © 2019年 王明月. All rights reserved.
//

#ifndef HeaderRule_hpp
#define HeaderRule_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>
using namespace std;

class HeaderRule {
    
public:
    HeaderRule();
    ~HeaderRule();
    static uint32_t DiffTimeInMicroSecond();
    static uint32_t DiffTimeInSecond();
    vector<int> getIp(string ip_addr);
    vector<int> buildInd(vector<int> ruleIp);
    vector<size_t> encInd(vector<int> rule_ip, vector<int> plain_ind);
    void loadRule(string plainRulePath, int size);
    
    size_t genToken(vector<int> rule_ip);
    vector<double> buildTrap(vector<int> ipAddr);
    
    int CheckHeader(vector<double> trap, size_t token, vector<size_t> encInd);
    void loadHeader(string plainHeaderPath);
    
    void getTableReport(string filename);
    
    vector<vector<double>>* getHeaders();
    vector<vector<size_t>>* getHeaderRules();
    vector<size_t>* getTokens();
    //int sendHeaderQuickly(int seed);
    
    vector<vector<size_t>> vecHeaderRules;
    vector<vector<double>> vecHeader;
    vector<int> mapKey = {1039, 1279, 1471, 1511};
    vector<size_t> tokenHeader;
    vector<int> hitRule;
    vector<int> vecLatency;
    vector<int> vecPacketSize;
};

#endif /* HeaderRule_hpp */
