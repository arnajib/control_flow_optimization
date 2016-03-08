//
// Created by najib on 24/02/16.
//

#include "solution.h"
#include <algorithm>
#include <cmath>

bool Solution::isExist(Tid tid) {
    if (std::find(tids.begin(), tids.end(), tid) != tids.end())
        return true;
    else
        return false;
}

int Solution::getDistance(Tid tid1,Tid tid2){
return std::abs(tid1.getPosition() - tid2.getPosition());
}
void Solution::setPosition(){
    for(int i=0;i<tids.size();i++){
            tids[i].setPosition(i);
    }
}