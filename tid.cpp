//
// Created by najib on 24/02/16.
//

#include "tid.h"

Tid::Tid() {

}

Tid::~Tid() {

}

int Tid::getId_() const {
    return id_;
}

void Tid::setId_(int id) {
    Tid::id_ = id;
}

int Tid::getPosition() const {
    return position_;
}

void Tid::setPosition(int position) {
    position_ = position;
}
