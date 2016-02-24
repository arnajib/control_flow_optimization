#include <iostream>
#include <fstream>
#include <vector>
#include "pair_tid.h"

using namespace std;

void ReadFile(std::string filename, vector<PairTid> &data){

    std::fstream file(filename);
    int id1=0;
    int id2=0;
    Tid tid1;
    Tid tid2;
    std::pair<Tid, Tid> entry;
    int nbr_transition =0;
    if (file.is_open()) {
        while (!file.eof()) {
            file >>id1;
            file >>id2;
            file >>nbr_transition;
            tid1 = Tid(id1);
            tid2 = Tid(id2);
            entry = std::make_pair(tid1,tid2);
            data.push_back(PairTid(entry,nbr_transition));
        }
    } else {
        std::cout << "Error open file :" << filename << std::endl;
        return;
    }

}

int main() {
/**
 *  lecture des informations a partir d un fichier texte
 */

    vector<PairTid> data;
    ReadFile("data/trace_10_micro_sec_cpu0.txt", data);
    return 0;
}

