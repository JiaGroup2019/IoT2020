//
//  gen_rule.hpp
//  FuzzyQuery
//
//  Created by 王明月 on 2019/11/27.
//  Copyright © 2019年 王明月. All rights reserved.
//

#ifndef gen_rule_hpp
#define gen_rule_hpp

#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class GenRule{
public:
    GenRule();
    ~GenRule();
    void genRule(string outputPath, string rulePath);
    void genHeader(string outputHeader, int packageCount);
};
#endif /* gen_rule_hpp */
