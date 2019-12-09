//
//  ClientCPP.hpp
//  WildcardHeader
//
//  Created by 王明月 on 2019/11/29.
//  Copyright © 2019年 王明月. All rights reserved.
//

#ifndef ClientCPP_hpp
#define ClientCPP_hpp

#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>
#include <vector>
#define L 13

using namespace std;
class ClientCPP {
    
public:
    ClientCPP();
    ~ClientCPP();
    static uint32_t DiffTimeInMicroSecond();
    static uint32_t DiffTimeInSecond();
    vector<int> getIp(string ip_addr);
    vector<double> buildTrap(vector<int> ipAddr);
    size_t genToken(vector<int> rule_ip);
private:
    vector<int> mapKey = {1039, 1279, 1471, 1511};
};
#endif /* ClientCPP_hpp */
