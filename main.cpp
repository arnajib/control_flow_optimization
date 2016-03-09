#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <ctime>
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

int getDistanceMax(Solution solution, vector<PairTid> data, int &i_1, int &i_2) {
    //   Afficher les distances
    int distance_max = 0;
    for (int i = 0; i < solution.tids.size() - 1; ++i) {
        for (int j = i + 1; j < solution.tids.size(); ++j) {
            int distance = 0;
            if (isAPair(solution.tids[i], solution.tids[j], data)) {
                distance = solution.getDistance(solution.tids[i], solution.tids[j]);
                if (distance_max < distance) {
                    distance_max = distance;
                    i_1 = i;
                    i_2 = j;
                }
//                std::cout << "distance entre :" << solution.tids[i].getId_() << " et " <<
//                solution.tids[j].getId_() << ":" << solution.getDistance(solution.tids[i], solution.tids[j]) <<
//                std::endl;
            }
        }

    }
    return distance_max;
}

void swapTid(Solution solution, int &i_1, int &i_2) {
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0.0, solution.tids.size() - 1);
    int i = distribution(generator);
    int j = distribution(generator);
    Tid temp;
    temp = solution.tids[i];
    solution.tids[i] = solution.tids[i_1];
    solution.tids[i_1] = temp;
    temp = solution.tids[j];
    solution.tids[j] = solution.tids[i_2];
    solution.tids[i_2] = temp;
    solution.setPosition();

}

int main() {
/**
 *  lecture des informations a partir d un fichier texte
 */
    int distance_max = 0;
    int i_1 = 0, i_2 = 0;
    vector<PairTid> data;
    Solution solution;
    std::string file_in = "data/trace_1000_sec_cpu0.txt";
    ReadFile(file_in, data);
    Vorace(data, solution);

    Solution solution_temp = solution;
    distance_max = getDistanceMax(solution, data, i_1, i_2);

    std::cout << "__________________________ " << std::endl;
    std::cout << "Distance max : " << getDistanceMax(solution, data, i_1, i_2) << std::endl;

    std::clock_t start;
    double duration;
    start = std::clock();

    while (duration < 100.0) {
        swapTid(solution_temp, i_1, i_2);
        if (distance_max > getDistanceMax(solution_temp, data, i_1, i_2)) {
            solution = solution_temp;
            distance_max = getDistanceMax(solution, data, i_1, i_2);
            std::cout << "__________________________ " << std::endl;
            std::cout << "Distance max : " << getDistanceMax(solution, data, i_1, i_2) << std::endl;
        }
        duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;

    }
    //   Afficher les distances

    std::cout << "__________________________ " << std::endl;
    std::cout << "Distance max : " << getDistanceMax(solution, data, i_1, i_2) << std::endl;
//    for (auto item : data) {
//        std::cout << "distance entre :" << item.getEntry().first.getId_() << " et " <<
//        item.getEntry().second.getId_() << ":" << solution.getDistance(item.getEntry().first, item.getEntry().second) <<
//        std::endl;
//    }
    return 0;
}

