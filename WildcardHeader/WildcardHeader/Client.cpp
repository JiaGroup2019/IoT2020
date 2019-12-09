//
//  main.cpp
//  FuzzyQuery
//
//  Created by 王明月 on 2019/11/17.
//  Copyright © 2019年 王明月. All rights reserved.
//

#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <cstdlib>
#include <time.h>
#include "gen_rule.hpp"
#include "ClientCPP.hpp"


////build plain trapdoor
//vector<double> buildTrap(vector<int> ipAddr){
//    vector<double> plain_trap;
//    for(int k = 0; k < L; k++){
//        plain_trap.push_back(1);
//    }
//    for(int i = 0; i < 4; i++){
//        int index = (ipAddr[i] + mapKey[i]) % L;
//        plain_trap[index] /= mapKey[i];
//    }
//    return plain_trap;
//}

////generate nonce
//size_t genNonce(){
//    size_t non;
//    srand((unsigned)time(NULL));
//    non = rand();
//    return non;
//}

////generate token for each ip
//size_t genToken(vector<int> rule_ip){
//    string str = to_string(rule_ip[0]);
//    hash<string> t_h;
//    size_t token = t_h(str);
//    return token;
//}

////encrypt index
//vector<size_t> encInd(vector<int> rule_ip, vector<int> plain_ind){
//    vector<size_t> enc_ind;
//    hash<string> enc_h;
//    string str = to_string(rule_ip[0]);
//    hash<string> t_h;
//    size_t token = t_h(str);
//    srand((unsigned)time(NULL));
//    size_t nonce = rand();
//    for (int i = 0; i < L; i++) {
//        enc_ind.push_back(plain_ind[i]);
//    }
//    for (int j = 0; j < L; j++) {
//        string t_temp;
//        t_temp = to_string(token) + to_string(j) + to_string(nonce);
//        enc_ind[j] ^= enc_h(t_temp);
//    }
//    return enc_ind;
//}

//encrypt trapdoor
//match index and trapdoor



int main(int argc, const char * argv[]) {
    /* vector<int> res_test = getIp("192.168.50.120.");
     for(int i = 0; i < 4; i++)
     cout << res_test[i]<< endl;

     vector<int> test_ind = buildInd(res_test);
     for(int i = 0; i < L; i++)
     cout << test_ind[i]<< endl;
     cout << endl;

     vector<double> test_trap = buildTrap(res_test);
     for(int i = 0; i < L; i++)
     cout << test_trap[i]<< endl;

     cout << endl;

     size_t test_non = genNonce();
     cout << test_non << endl << endl;

     vector<size_t> test_encInd = encInd(res_test, test_ind, test_non);
     for (int i = 0; i < L; i++) {
     cout << test_encInd[i] << endl;
     }*/
    GenRule test_genrule;
    string ruleFileName("/Users/wangmingyue/Desktop/WildcardHeader/firewall.txt");
    string outputRule("/Users/wangmingyue/Desktop/WildcardHeader/plainrule.txt");
    string outputHeader("/Users/wangmingyue/Desktop/WildcardHeader/plainheader.txt");
    test_genrule.genRule(outputRule, ruleFileName);
    test_genrule.genHeader(outputHeader, 10001);
    return 0;
}
