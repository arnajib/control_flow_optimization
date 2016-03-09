#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <ctime>
#include <list>
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

void Vorace(vector<PairTid> &data, Solution &solution) {

    for (auto item : data) {
        if (!solution.isExist(item.getEntry().first))
            solution.tids.push_back(item.getEntry().first);
        if (!solution.isExist(item.getEntry().second))
            solution.tids.push_back(item.getEntry().second);
    }
    solution.setPosition();
}

void VoraceCenter(vector<PairTid> &data, Solution &solution) {
    bool toggle = false;
    list<Tid> temp;
    for (auto item : data) {
        if (!toggle) {
            if (!solution.isExist(item.getEntry().first)) {
                solution.tids.push_back(item.getEntry().first);
                temp.push_back(item.getEntry().first);
            }
            if (!solution.isExist(item.getEntry().second)) {
                solution.tids.push_back(item.getEntry().second);
                temp.push_back(item.getEntry().second);
            }
            toggle = !toggle;
        } else {
            if (!solution.isExist(item.getEntry().first)) {
                solution.tids.push_back(item.getEntry().first);
                temp.push_front(item.getEntry().first);
            }
            if (!solution.isExist(item.getEntry().second)) {
                solution.tids.push_back(item.getEntry().second);
                temp.push_front(item.getEntry().second);
            }
            toggle = !toggle;

        }
    }
    for(int i=0;i<solution.tids.size();++i){
        solution.tids[i] = temp.front();
        temp.pop_front();
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

/**
 *  Ecriture des resultats dans un fichier .csv
 */

void WriteSolution(Solution solution, string file_name, vector<PairTid> data) {
    int i_1, i_2;
    std::ofstream myfile;
    std::string file_path_out = "result/vorace_center/" + file_name + "_solution.txt";
    myfile.open(file_path_out, std::fstream::app);
    myfile << "Distance max : " << getDistanceMax(solution, data, i_1, i_2) << std::endl;
    for (auto item : solution.tids) {
        myfile << item.getId_() << "\n";
    }

    myfile.close();
}


int main() {
/**
 *  lecture des informations a partir d un fichier texte
 */
    int distance_max = 0;
    int i_1 = 0, i_2 = 0;
    vector<PairTid> data;
    Solution solution;
    std::string file_in = "trace_1000_sec_cpu1";
    ReadFile("data/" + file_in + ".txt", data);
//    Vorace(data, solution);
    VoraceCenter(data, solution);

    Solution solution_temp = solution;
    distance_max = getDistanceMax(solution, data, i_1, i_2);

    std::cout << "__________________________ " << std::endl;
    std::cout << "Distance max : " << getDistanceMax(solution, data, i_1, i_2) << std::endl;

    std::clock_t start;
    double duration;
    start = std::clock();

//    while (duration < 1.0) {
//        swapTid(solution_temp, i_1, i_2);
//        if (distance_max > getDistanceMax(solution_temp, data, i_1, i_2)) {
//            solution = solution_temp;
//            distance_max = getDistanceMax(solution, data, i_1, i_2);
//            std::cout << "__________________________ " << std::endl;
//            std::cout << "Distance max : " << getDistanceMax(solution, data, i_1, i_2) << std::endl;
//        }
//        duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
//
//    }
    //   Afficher les distances
//
//    std::cout << "__________________________ " << std::endl;
//    std::cout << "Distance max : " << getDistanceMax(solution, data, i_1, i_2) << std::endl;
//    for (auto item : data) {
//        std::cout << "distance entre :" << item.getEntry().first.getId_() << " et " <<
//        item.getEntry().second.getId_() << ":" << solution.getDistance(item.getEntry().first, item.getEntry().second) <<
//        std::endl;
//    }
    WriteSolution(solution, file_in, data);
    return 0;
}

