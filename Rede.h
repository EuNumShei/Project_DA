//
// Created by Guilherme Teixeira on 05/03/2024.
//

#ifndef PROJECT1DATASETSMALL_REDE_H
#define PROJECT1DATASETSMALL_REDE_H
#include "Graph.h"
#include "Station.h"
#include <string>


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

private:
    Graph<Station> g;
};


#endif //PROJECT1DATASETSMALL_REDE_H
