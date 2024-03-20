//
// Created by Guilherme Teixeira on 05/03/2024.
//

#ifndef PROJECT1DATASETSMALL_RESERVOIR_H
#define PROJECT1DATASETSMALL_RESERVOIR_H
#include <string>
#include "Station.h"
using namespace std;


class Reservoir : public Station{
public:
    Reservoir(string name, string municipality, int id, string code, int max_delivery) : Station(id, code), name(name), municipality(municipality), max_delivery(max_delivery){}

    string get_name() {return name;}
    string get_municipality() {return municipality;}
    int get_max_delivery() {return max_delivery;}
    void set_max_delivery(double delivery) {
        max_delivery = delivery;
    }
private:
    string name;
    string municipality;
    int max_delivery;
};


#endif //PROJECT1DATASETSMALL_RESERVOIR_H
