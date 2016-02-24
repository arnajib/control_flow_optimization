//
// Created by najib on 24/02/16.
//

#include "pair_tid.h"

PairTid::PairTid(){

}
PairTid::PairTid(std::pair<Tid, Tid> &entry, int number_transition){
entry_ = entry;
    number_transition_ = number_transition;
}
PairTid::~PairTid(){

}

int PairTid::getNumber_transition_() const {
    return number_transition_;
}

void PairTid::setNumber_transition_(int number_transition) {
    number_transition_ = number_transition;
}

void PairTid::setEntry(const std::pair<Tid, Tid> &entry) {
    entry_ = entry;
}