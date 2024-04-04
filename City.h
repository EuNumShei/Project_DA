//
// Created by Guilherme Teixeira on 05/03/2024.
//

#ifndef PROJECT1DATASETSMALL_CITY_H
#define PROJECT1DATASETSMALL_CITY_H
#include <string>
#include "Station.h"
using namespace std;

class City : public Station{
public:
    City(string name, int id, string code, double demand, int population) : Station(id, code), name(name), demand(demand), population(population) {}

    string get_name() {return name;}
    double get_demand() {return demand;}
    int get_population() {return population;}
private:
    string name;
    double demand;
    int population;
};


#endif //PROJECT1DATASETSMALL_CITY_H
