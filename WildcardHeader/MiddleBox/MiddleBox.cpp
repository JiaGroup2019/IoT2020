//
//  main.cpp
//  MiddleBox
//
//  Created by 王明月 on 2019/11/27.
//  Copyright © 2019年 王明月. All rights reserved.
//

#include <iostream>
#include "HeaderRule.hpp"
#include <vector>
#include <string>

using namespace std;

int sendHeaderQuickly(HeaderRule client, int seed){
    
    vector<vector<double>>* headers = client.getHeaders();
    vector<vector<size_t>>* headerRules = client.getHeaderRules();
    vector<size_t>* tokens = client.getTokens();
    
    vector<double> trapdoor = headers->at(seed % headers -> size());
    vector<size_t> index = headerRules -> at(seed % headerRules -> size());
    size_t token = tokens -> at(seed % tokens -> size());
    
    client.CheckHeader(trapdoor, token, index);
    
    return 0;
}

int main(int argc, const char * argv[]) {
    HeaderRule testRule;
    //HeaderRule::DiffTimeInMicroSecond();
    testRule.loadRule("/Users/wangmingyue/Desktop/WildcardHeader/plainrule.txt", 365);
    //uint32_t buildTime = HeaderRule::DiffTimeInMicroSecond();
    //cout << "Finish read rules, use "<< buildTime <<" us." << endl;
    testRule.vecLatency.clear();
    testRule.hitRule.clear();
    testRule.loadHeader("/Users/wangmingyue/Desktop/WildcardHeader/plainheader.txt");
    
    srand(82349530);
    
    int testTime = 30;
    uint32_t uiCurTime;
    uint32_t uiBegTime = 1575100750;
    uint32_t uiEndTime = uiBegTime + testTime;
    
    uint32_t times=0;
    
    while (true){
        uiCurTime = time(NULL);
        if (uiCurTime < uiBegTime) {
            continue;
        }
        if (uiCurTime >= uiEndTime){
            break;
        }
        sendHeaderQuickly(testRule, rand());
        times++;
        
    }
    cout << times << endl;
        
//    for (int i = 0; i < testRule.vecPacketSize.size(); i++) {
//        cout << testRule.vecPacketSize.at(i) << endl;
//    }
    
//    for(int i = 0; i < testRule.vecHeader.size(); i++){
//        //HeaderRule::DiffTimeInMicroSecond();
//
//        for(int j = 0; j < testRule.vecHeaderRules.size(); j++){
//
//            int temp = testRule.CheckHeader(testRule.vecHeader.at(i), testRule.tokenHeader.at(i), testRule.vecHeaderRules.at(j));
//
//            if (temp == 1) {
//                testRule.hitRule.push_back(j);
//            }else{
//                testRule.hitRule.push_back(0);
//            }
//        }
//        int latency = HeaderRule::DiffTimeInMicroSecond();
//        testRule.vecLatency.push_back(latency);
//    }
//
//    testRule.getTableReport("/Users/wangmingyue/Desktop/WildcardHeader/testResult.csv");
//
    return 0;
}
