//
// Created by Guilherme Teixeira on 05/03/2024.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include "Rede.h"
#include "City.h"
#include "Reservoir.h"
#include "Station.h"

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
                        population = stoi(palavra);
                        break;
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
                        break;
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
                    case 1:
                        code = palavra;
                        break;
                    default:
                        break;
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
                    case 3:
                        bidirecional = stoi(palavra);
                        break;
                    default:
                        break;
                }
                count++;
            }

            if(bidirecional) g.addEdge(partida, chegada, capacidade);
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
    for(auto &edge : v1->getAdj()){
        if(edge->getDest() == v2) {
            edges.push_back(edge);
            return true;
        }
    }
    return false;
}

// Function to test the given vertex 'w' and visit it if conditions are met
void Rede::testAndVisit(std::queue< Vertex<string>*> &q, Edge<string> *e, Vertex<string> *w, double residual) {
// Check if the vertex 'w' is not visited and there is residual capacity
    if (! w->isVisited() && residual > 0) {
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
    while( !q.empty() && !t->isVisited()) {
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
// Traverse the augmenting path and update the flow values accordingly
    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        double flow = e->getFlow();
        if (e->getDest() == v) {
            e->setFlow(flow + f);
            v = e->getOrig();
        }
        else {
            e->setFlow(flow - f);
            v = e->getDest();
        }
    }
}

void Rede::edmonds_karp() {
    unordered_map<string, Reservoir> copia = reservoirs;
    unordered_map<string, Station> copia2 = stations;
    Vertex<string>* s = g.findVertex("R_0");
    Vertex<string>* t = g.findVertex("PS_0");
// Validate source and target vertices
    if (s == nullptr || t == nullptr || s == t)
        throw std::logic_error("Invalid source and/or target vertex");
// Initialize flow on all edges to 0
// While there is an augmenting path, augment the flow along the path
    while( findAugmentingPath(s, t) ) {
        double f = findMinResidualAlongPath(s, t);
        augmentFlowAlongPath(s, t, f);
    }
    reservoirs = copia;
    stations = copia2;
}

void Rede::initialize_flow(){
    for (auto v : g.getVertexSet()) {
        for (auto e: v->getAdj()) {
            e->setFlow(0);
        }
    }
}

double Rede::max_flow(const std::string &cidade) {
    double res = -1;
    auto v1 = g.findVertex(cidade);
    if(v1 != nullptr) {
        res = v1->getAdj()[0]->getFlow();
    }
    return res;
}

void Rede::max_flow() {
    double total = 0;
    double temp = 0;
    for(auto vertex : g.getVertexSet()){
        if(vertex->getInfo()[0] == 'C') {
            temp = vertex->getAdj()[0]->getFlow();
            cout << vertex->getInfo() << " -> Max Flow: " << temp << " m³/sec" << endl;
            total += temp;
            temp = 0;
        }
    }
    cout << "O max flow total e " << total << " m³/sec" << endl;
}

void Rede::escrever_ficheiro_2_2() {
    ofstream outputFile("../2_2.csv");

    if (!outputFile.is_open()) {
        cerr << "Error opening file!" << endl;
    }
    string cabecalho = "City_Code,Max_Flow,Demand";

    outputFile << cabecalho << endl;

    for(auto v : g.getVertexSet()){
        if(v->getInfo()[0] == 'C'){
            outputFile << v->getInfo() << "," << to_string(max_flow(v->getInfo())) << "," << to_string(cities.at(v->getInfo()).get_demand()) << endl;
        }
    }

    outputFile.close();
}

/** Funcao que le o ficheiro com as informacoes acerca dos voos existentes e coloca essa informacao
 *  no grafo
 *  Time complexity: O(l*w), being l the number of lines and w the number of words
 */
void Rede::dados_2_2() {
    ifstream in("../2_2.csv");
    if (!in) {
        cerr << "Erro ao abrir o arquivo." << endl;
    } else {
        string linha;
        getline(in, linha);
        while (getline(in, linha)) {
            istringstream iss(linha);
            string palavra;
            string code;
            int flow;
            int demand;
            int count = 0;
            while (std::getline(iss, palavra, ',')) {
                switch (count) {
                    case 0:
                        code = palavra;
                        break;
                    case 1:
                        flow = stoi(palavra);
                        break;
                    default:
                        demand = stoi(palavra);
                }
                count++;
            }
            if (demand > flow){
                cout << code << " -> Deficit: " << demand - flow << " m³/sec" << endl;
            }
        }
    }
}

bool Rede::remover_reservatorio(string reservoir) {
    auto source = g.findVertex(reservoir);
    if(reservoir[0] != 'R' || source == nullptr) return true;
    double capacity = source->getIncoming()[0]->getWeight();
    source->getIncoming()[0]->setCapacity(0);
    edmonds_karp();
    dados_3_1();
    source->getIncoming()[0]->setCapacity(capacity);
    return false;
}

bool Rede::remover_station(string station){
    auto source = g.findVertex(station);
    if(source == nullptr || station[0] != 'P' || station[1] != 'S') return true;
    stack<double> capacities;
    for(auto &edge : source->getIncoming()) {
        capacities.push(edge->getWeight());
        edge->setCapacity(0);
    }
    edmonds_karp();
    dados_3_2();
    for(auto &edge : source->getIncoming()){
        edge->setCapacity(capacities.top());
        capacities.pop();
    }
    return false;
}

void Rede::remover_pipes(){
    stack<double> capacities;
    for (auto &edge : edges) {
        capacities.push(edge->getWeight());
        edge->setCapacity(0);
        if(edge->getReverse() != nullptr){
            capacities.push(edge->getReverse()->getWeight());
            edge->getReverse()->setCapacity(0);
        }
    }
    edmonds_karp();
    dados_3_3();
    for (auto &edge: edges) {
        edge->setCapacity(capacities.top());
        capacities.pop();
        if(edge->getReverse() != nullptr){
            edge->getReverse()->setCapacity(capacities.top());
            capacities.pop();
        }
    }
    edges.clear();
}

void Rede::dados_3_1() {
    ifstream in("../2_2.csv");
    if (!in) {
        cerr << "Erro ao abrir o arquivo." << endl;
    } else {
        string linha;
        getline(in, linha);
        while (getline(in, linha)) {
            istringstream iss(linha);
            string palavra;
            string code;
            int flow;
            int count = 0;
            while (std::getline(iss, palavra, ',')) {
                switch (count) {
                    case 0:
                        code = palavra;
                        break;
                    case 1:
                        flow = stoi(palavra);
                        break;
                    default:
                        break;
                }
                count++;
            }
            double max_flow_2 = max_flow(code);
            if (max_flow_2 < flow){
                cout << code << " -> Old Flow: " << flow << " m³/sec || New Flow: " << max_flow_2 << " m³/sec" << endl;
            }
        }
    }
}

void Rede::dados_3_2() {
    ifstream in("../2_2.csv");
    if (!in) {
        cerr << "Erro ao abrir o arquivo." << endl;
    } else {
        string linha;
        getline(in, linha);
        while (getline(in, linha)) {
            istringstream iss(linha);
            string palavra;
            string code;
            int flow;
            int count = 0;
            while (std::getline(iss, palavra, ',')) {
                switch (count) {
                    case 0:
                        code = palavra;
                        break;
                    case 1:
                        flow = stoi(palavra);
                        break;
                    default:
                        break;
                }
                count++;
            }
            double max_flow_2 = max_flow(code);
            if (max_flow_2 < flow){
                cout << code << " -> Old Flow: " << flow << " m³/sec || New Flow: " << max_flow_2 << " m³/sec" << endl;
            }
        }
    }
}

void Rede::dados_3_3(){
    ifstream in("../2_2.csv");
    if (!in) {
        cerr << "Erro ao abrir o arquivo." << endl;
    } else {
        string linha;
        getline(in, linha);
        while (getline(in, linha)) {
            istringstream iss(linha);
            string palavra;
            string code;
            int flow;
            int count = 0;
            while (std::getline(iss, palavra, ',')) {
                switch (count) {
                    case 0:
                        code = palavra;
                        break;
                    case 1:
                        flow = stoi(palavra);
                        break;
                    default:
                        break;
                }
                count++;
            }
            double max_flow_2 = max_flow(code);
            if (max_flow_2 < flow){
                cout << code << " -> Old Flow: " << flow << " m³/sec || New Flow: " << max_flow_2 << " m³/sec" << endl;
            }
        }
    }
}