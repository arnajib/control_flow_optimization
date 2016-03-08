#include <iostream>
#include <fstream>
#include <vector>
#include "pair_tid.h"
#include "solution.h"

using namespace std;

void ReadFile(std::string filename, vector<PairTid> &data) {

    std::fstream file(filename);
    int id1 = 0;
    int id2 = 0;
    Tid tid1;
    Tid tid2;
    std::pair<Tid, Tid> entry;
    int nbr_transition = 0;
    if (file.is_open()) {
        while (!file.eof()) {
            file >> id1;
            file >> id2;
            file >> nbr_transition;
            tid1 = Tid(id1);
            tid2 = Tid(id2);
            entry = std::make_pair(tid1, tid2);
            data.push_back(PairTid(entry, nbr_transition));
        }
    } else {
        std::cout << "Error open file :" << filename << std::endl;
        return;
    }

}

/**
 * Verifier si les tids ont aumoins une liaison
 */
bool isAPair(Tid tid_1, Tid tid_2, vector<PairTid> data) {
    for (auto item :data) {
        if ((item.getEntry().first.getId_() == tid_1.getId_() && item.getEntry().second.getId_() == tid_2.getId_()) ||
            (item.getEntry().first.getId_() == tid_2.getId_() && item.getEntry().second.getId_() == tid_1.getId_())) {
            return true;
        }
    }
    return false;
}

bool Vorace(vector<PairTid> &data, Solution &solution) {

    for (auto item : data) {
        if (!solution.isExist(item.getEntry().first))
            solution.tids.push_back(item.getEntry().first);
        if (!solution.isExist(item.getEntry().second))
            solution.tids.push_back(item.getEntry().second);
    }
    solution.setPosition();
}

int main() {
/**
 *  lecture des informations a partir d un fichier texte
 */

    vector<PairTid> data;
    Solution solution;
    ReadFile("data/trace_10_micro_sec_cpu0.txt", data);
    Vorace(data, solution);
    //   Afficher les distances
    for (auto item : data) {
        std::cout << "distance entre :" << item.getEntry().first.getId_() << " et " <<
        item.getEntry().second.getId_() << ":" << solution.getDistance(item.getEntry().first, item.getEntry().second) <<
        std::endl;
    }
    return 0;
}

