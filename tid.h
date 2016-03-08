//
// Created by najib on 24/02/16.
//

#ifndef CONTROL_FLOW_OPTIMIZATION_TID_H
#define CONTROL_FLOW_OPTIMIZATION_TID_H


class Tid {
public :
    Tid();
    Tid(int id){
        id_=id;
    }
    ~Tid();

public:
    int getId_() const;

    void setId_(int id);

    int getPosition() const ;

    void setPosition(int position) ;
    bool operator==(const Tid& tid);
private:
    int id_;
    int position_;

};


#endif //CONTROL_FLOW_OPTIMIZATION_TID_H
