//
// Created by Guilherme Teixeira on 05/03/2024.
//

#ifndef PROJECT1DATASETSMALL_REDE_H
#define PROJECT1DATASETSMALL_REDE_H
#include "Graph.h"
#include "Station.h"
#include "City.h"
#include <string>
#include <unordered_map>


class Rede {
public:
    Rede(){
        ler_ficheiro_estacoes();
        ler_ficheiro_reservatorios();
        ler_ficheiro_cidades();
        ler_ficheiro_pipes();
    }
    void ler_ficheiro_cidades();
    void ler_ficheiro_pipes();
    void ler_ficheiro_reservatorios();
    void ler_ficheiro_estacoes();
    void numero_de_cidades();
    void numero_de_reservatorios();
    void numero_de_estacoes();
    bool verificar_edge(const string& source, const string& dest);
    void edmonds_karp(const string& source, const string& dest);
    void testAndVisit(std::queue< Vertex<string>*> &q, Edge<string> *e, Vertex<string> *w, double residual);
    bool findAugmentingPath(Vertex<string> *s, Vertex<string> *t);
    void augmentFlowAlongPath(Vertex<string> *s, Vertex<string> *t, double f);
    double findMinResidualAlongPath(Vertex<string> *s, Vertex<string> *t);
    std::unordered_map<string, Station> getStations() { return stations; }
    std::unordered_map<string, Reservoir> getReservoirs() {return reservoirs; }
    std::unordered_map<string, City> getCities() { return cities; }
    void initialize_flow();
    double max_flow(const string& cidade);
    double average_flow_capacity();
    double maximum_flow_capacity();
    double variance_flow_capacity();
    void BalancedLoad();

private:
    Graph<string> g;
    std::unordered_map<string, Station> stations;
    std::unordered_map<string, Reservoir> reservoirs;
    std::unordered_map<string, City> cities;
};


#endif //PROJECT1DATASETSMALL_REDE_H
