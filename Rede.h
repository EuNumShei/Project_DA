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
        ler_ficheiro_cidades();
        ler_ficheiro_estacoes();
        ler_ficheiro_reservatorios();
        ler_ficheiro_pipes();
        g.addVertex("R_0");
        g.addVertex("PS_0");
        Reservoir new_source = Reservoir("Source", "Cena", 0, "R_0", INF);
        Station new_target = Station(0, "PS_0");
        reservoirs.insert({"R_0", new_source});
        stations.insert({"PS_0", new_target});
        for(auto vertex : g.getVertexSet()){
            if(vertex->getInfo()[0] == 'R'){
                g.addEdge("R_0", vertex->getInfo(), reservoirs.at(vertex->getInfo()).get_max_delivery());
            }
            if(vertex->getInfo()[0] == 'C'){
                g.addEdge(vertex->getInfo(), "PS_0", cities.at(vertex->getInfo()).get_demand());
            }
        }
    }
    void ler_ficheiro_cidades();
    void ler_ficheiro_pipes();
    void ler_ficheiro_reservatorios();
    void ler_ficheiro_estacoes();
    void numero_de_cidades();
    void numero_de_reservatorios();
    void numero_de_estacoes();
    bool verificar_edge(const string& source, const string& dest);
    void edmonds_karp();
    void testAndVisit(std::queue< Vertex<string>*> &q, Edge<string> *e, Vertex<string> *w, double residual);
    bool findAugmentingPath(Vertex<string> *s, Vertex<string> *t);
    void augmentFlowAlongPath(Vertex<string> *s, Vertex<string> *t, double f);
    double findMinResidualAlongPath(Vertex<string> *s, Vertex<string> *t);
    std::unordered_map<string, Station> getStations() { return stations; }
    std::unordered_map<string, Reservoir> getReservoirs() {return reservoirs; }
    std::unordered_map<string, City> getCities() { return cities; }
    void initialize_flow();
    double max_flow(const string& cidade);
    void max_flow();
    void escrever_ficheiro_2_2();
    void escrever_ficheiro_3_1();
    void dados_2_2();
    void dados_3_1();
    bool remover_reservatorio(string reservoir);
    void dados_3_2();
    void escrever_ficheiro_3_2();
    bool remover_station(string station);
    void remover_pipes();
    void dados_3_3();
private:
    Graph<string> g;
    std::unordered_map<string, Station> stations;
    std::unordered_map<string, Reservoir> reservoirs;
    std::unordered_map<string, City> cities;
    vector<Edge<string> *> edges;
};


#endif //PROJECT1DATASETSMALL_REDE_H
