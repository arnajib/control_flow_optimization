//
// Created by najib on 24/02/16.
//

#ifndef CONTROL_FLOW_OPTIMIZATION_PAIRE_TID_H
#define CONTROL_FLOW_OPTIMIZATION_PAIRE_TID_H

#include <bits/stl_pair.h>
#include "tid.h"

class PairTid {

public :
    PairTid();

    PairTid(std::pair<Tid, Tid> &entry,int number_transition);

    ~PairTid();

    int getNumber_transition_();

    void setNumber_transition_(int number_transition);

    std::pair<Tid, Tid> getEntry(){
        return entry_;
    };

    void setEntry( std::pair<Tid, Tid> &entry_);

private:
    int number_transition_;
    std::pair<Tid, Tid> entry_;


};


#endif //CONTROL_FLOW_OPTIMIZATION_PAIRE_TID_H
