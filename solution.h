//
// Created by najib on 24/02/16.
//

#ifndef CONTROL_FLOW_OPTIMIZATION_SOLUTION_H
#define CONTROL_FLOW_OPTIMIZATION_SOLUTION_H

#include <vector>
#include "tid.h"

class Solution {
public :
    Solution() { };

    ~Solution() { };

    bool isExist(Tid tid);
    int getDistance(Tid tid1,Tid tid2);
    void setPosition();

    std::vector<Tid> tids;
};


#endif //CONTROL_FLOW_OPTIMIZATION_SOLUTION_H
