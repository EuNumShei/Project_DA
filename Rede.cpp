//
// Created by Guilherme Teixeira on 05/03/2024.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "Rede.h"
#include "City.h"
#include "Reservoir.h"
#include "Station.h"
#include <math.h>

using namespace std;

void Rede::ler_ficheiro_cidades() {
    ifstream in("../Cities.csv");
    if (!in) {
        cerr << "Erro ao abrir o arquivo." << endl;
    } else {
        string linha;
        getline(in, linha);
        while (getline(in, linha)) {
            istringstream iss(linha);
            string palavra;
            string name;
            int id;
            string code;
            double demand;
            int population;
            int count = 0;

            while (std::getline(iss, palavra, ',')) {
                switch (count) {
                    case 0:
                        name = palavra;
                        break;
                    case 1:
                        id = stoi(palavra);
                        break;
                    case 2:
                        code = palavra;
                        break;
                    case 3:
                        demand = stod(palavra);
                        break;
                    default:
                        population = stoi(palavra.substr(1, palavra.size() - 2));
                }
                count++;
            }
            City new_city = City(name, id, code, demand, population);
            pair<string, City> pair = {code, new_city};
            cities.insert(pair);
            g.addVertex(code);
        }
    }
}

/** Funcao que le o ficheiro com as informacoes relativas aos aeroportos e guarda essa informacao
 *  no grafo
 *  Time complexity: O(l*w), being l the number of lines and w the number of words
 */
void Rede::ler_ficheiro_reservatorios() {
    ifstream in("../Reservoir.csv");
    if (!in) {
        cerr << "Erro ao abrir o arquivo." << endl;
    } else {
        //string palavra;
        string linha;
        getline(in, linha);
        while (getline(in, linha)) {
            istringstream iss(linha);
            string palavra;
            string name;
            string municipality;
            int id;
            string code;
            int max_delivery;
            int count = 0;
            while (std::getline(iss, palavra, ',')) {
                switch (count) {
                    case 0:
                        name = palavra;
                        break;
                    case 1:
                        municipality = palavra;
                        break;
                    case 2:
                        id = stoi(palavra);
                        break;
                    case 3:
                        code = palavra;
                        break;
                    default:
                        max_delivery = stoi(palavra);
                }
                count++;
            }
            Reservoir reservoir = Reservoir(name, municipality, id, code, max_delivery);
            pair<string, Reservoir> pair = {code, reservoir};
            reservoirs.insert(pair);
            g.addVertex(code);
        }
    }
}

/** Funcao que le o ficheiro com as informacoes acerca dos voos existentes e coloca essa informacao
 *  no grafo
 *  Time complexity: O(l*w), being l the number of lines and w the number of words
 */
void Rede::ler_ficheiro_estacoes() {
    ifstream in("../Stations.csv");
    if (!in) {
        cerr << "Erro ao abrir o arquivo." << endl;
    } else {
        string linha;
        getline(in, linha);
        while (getline(in, linha)) {
            istringstream iss(linha);
            string palavra;
            int id;
            string code;
            int count = 0;
            while (std::getline(iss, palavra, ',')) {
                switch (count) {
                    case 0:
                        id = stoi(palavra);
                        break;
                    default:
                        code = palavra;
                }
                count++;
            }
            const Station &station = Station(id, code);
            pair<string, Station> pair = {code, station};
            stations.insert(pair);
            g.addVertex(code);
        }
    }
}

void Rede::ler_ficheiro_pipes() {
    ifstream in("../Pipes.csv");
    if (!in) {
        cerr << "Erro ao abrir o arquivo." << endl;
    } else {
        //string palavra;
        string linha;
        getline(in, linha);
        while (getline(in, linha)) {
            istringstream iss(linha);
            string palavra;
            int capacidade;
            int bidirecional;
            string partida;
            string chegada;
            int count = 0;
            while (std::getline(iss, palavra, ',')) {
                switch (count) {
                    case 0:
                        partida = palavra;
                        break;
                    case 1:
                        chegada = palavra;
                        break;
                    case 2:
                        capacidade = stoi(palavra);
                        break;
                    default:
                        bidirecional = stoi(palavra);
                }
                count++;
            }

            if(!bidirecional) g.addEdge(partida, chegada, capacidade);
            else g.addBidirectionalEdge(partida, chegada, capacidade);
        }
    }
}

void Rede::numero_de_estacoes() {
    cout << "Numero atual de estacoes intermedias: " << stations.size() << "\n";
}

/*
* Function that returns the total number of airports
* Time complexity: O(1)
*/

void Rede::numero_de_cidades() {
    cout << "Numero atual de cidades: " << cities.size() << "\n";
}

/*
* Function that returns the total number of flights
* Time complexity: O(1)
*/

void Rede::numero_de_reservatorios() {
    cout << "Numero atual de reservatorios: " << reservoirs.size() << "\n";
}

bool Rede::verificar_edge(const string& source, const string& dest) {
    auto v1 = g.findVertex(source);
    auto v2 = g.findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    for(auto edge : v1->getAdj()){
        if(edge->getDest() == v2) {
            return true;
        }
    }
    return false;
}

// Function to test the given vertex 'w' and visit it if conditions are met
void Rede::testAndVisit(std::queue< Vertex<string>*> &q, Edge<string> *e, Vertex<string> *w, double residual) {
// Check if the vertex 'w' is not visited and there is residual capacity
    if (! w->isVisited() && residual > 0) {
// Mark 'w' as visited, set the path through which it was reached, and enqueue it
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

// Function to find an augmenting path using Breadth-First Search
bool Rede::findAugmentingPath(Vertex<string> *s, Vertex<string> *t) {
// Mark all vertices as not visited
    for(auto v : g.getVertexSet()) {
        v->setVisited(false);
    }
// Mark the source vertex as visited and enqueue it
    s->setVisited(true);
    std::queue<Vertex<string> *> q;
    q.push(s);
// BFS to find an augmenting path
    while( ! q.empty() && ! t->isVisited()) {
        auto v = q.front();
        q.pop();
// Process outgoing edges
        for(auto e: v->getAdj()) {
            testAndVisit(q, e, e->getDest(), e->getWeight() - e->getFlow());
        }
// Process incoming edges
        for(auto e: v->getIncoming()) {
            testAndVisit(q, e, e->getOrig(), e->getFlow());
        }
    }
// Return true if a path to the target is found, false otherwise
    return t->isVisited();
}

// Function to find the minimum residual capacity along the augmenting path
double Rede::findMinResidualAlongPath(Vertex<string> *s, Vertex<string> *t) {
    double f = INF;
// Traverse the augmenting path to find the minimum residual capacity
    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        if (e->getDest() == v) {
            f = std::min(f, e->getWeight() - e->getFlow());
            v = e->getOrig();
        }
        else {
            f = std::min(f, e->getFlow());
            v = e->getDest();
        }
    }
// Return the minimum residual capacity
    return f;
}

// Function to augment flow along the augmenting path with the given flow value
void Rede::augmentFlowAlongPath(Vertex<string> *s, Vertex<string> *t, double f) {
    double f_c;
// Traverse the augmenting path and update the flow values accordingly
    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        double flow = e->getFlow();
        if (e->getDest() == v) {
            e->setFlow(flow + f);
            f_c = e->getWeight() - (flow + f);
            e->setFlowCapacity(f_c);
            v = e->getOrig();
        }
        else {
            e->setFlow(flow - f);
            f_c = e->getWeight() - (flow - f);
            e->setFlowCapacity(f_c);
            v = e->getDest();
        }
    }
}

void Rede::edmonds_karp(const string &source, const string &dest) {
// Main function implementing the Edmonds-Karp algorithm
// Find source and target vertices in the graph
    Vertex<string>* s = g.findVertex(source);
    Vertex<string>* t = g.findVertex(dest);
// Validate source and target vertices
    if (s == nullptr || t == nullptr || s == t)
        throw std::logic_error("Invalid source and/or target vertex");
// Initialize flow on all edges to 0
// While there is an augmenting path, augment the flow along the path
    while( findAugmentingPath(s, t) ) {
        double f = findMinResidualAlongPath(s, t);
        augmentFlowAlongPath(s, t, f);
    }
}

void Rede::initialize_flow(){
    for (auto v : g.getVertexSet()) {
        for (auto e: v->getAdj()) {
            e->setFlow(0);
            e->setFlowCapacity(e->getWeight());
        }
    }
}

double Rede::max_flow(const string& cidade) {
    double res = 0;
    auto v1 = g.findVertex(cidade);
    for(auto vertex : g.getVertexSet()){
        for(auto edge : vertex->getAdj()){
            if(edge->getDest() == v1){
                res += edge->getFlow();
            }
        }
    }
    return res;
}


double Rede::average_flow_capacity() {
    double soma = 0;
    double count = 0;
    double res;
    for (Vertex<string>* v : g.getVertexSet()) {;
        for(Edge<string>* e : v->getAdj()) {
            //cout << e->getFlowCapacity() << endl;
            soma += e->getFlowCapacity();
            count++;
        }
    }
    res = soma / count;
    return res;
}

double Rede::variance_flow_capacity() {
    double count = 0;
    double soma = 0;
    double mod_desvio;
    double desvio;
    double variance;
    for (Vertex<string>* v : g.getVertexSet()) {;
        for(Edge<string>* e : v->getAdj()) {
            desvio = average_flow_capacity() - e->getFlowCapacity();
            if (desvio < 0) {
                mod_desvio = desvio * -1;
            } else if(desvio >= 0) {
                mod_desvio = desvio;
            }
            soma += mod_desvio;
            count++;
        }
    }
    variance = pow(soma / count, 2);
    return variance;
}

double Rede::maximum_flow_capacity() {
    double max_fc = 0;
    for (Vertex<string>* v : g.getVertexSet()) {;
        for(Edge<string>* e : v->getAdj()) {
            if (max_fc < e->getFlowCapacity()) {
                max_fc = e->getFlowCapacity();
            }
        }
    }
    return max_fc;
}