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

/**@brief Parser de cidades
 * Lê o ficheiro Cities.csv e guarda as cidades num unordered_map
 * Time complexity: O(c) sendo c o número de cidadesn
 */

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

/**@brief Parser de reservatórios
 * Lê o ficheiro Reservoir.csv e guarda os reservatórios num unordered_map
 * Time complexity: O(r) sendo r o número de reservatórios
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

/**@brief Parser de estações
 * Lê o ficheiro Stations.csv e guarda as estações num unordered_map
 * Time complexity: O(e) sendo e o número de estações
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

/**@brief Parser de pipes
 * Lê o ficheiro Pipes.csv e guarda as pipes no grafo
 * Time complexity: O(a) sendo a o número de arestas
 */

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

/**
 * Retorna o número de estações intermédias
 * Time complexity: O(1)
 */

void Rede::numero_de_estacoes() {

    cout << "|      Número atual de estações intermédias: " << stations.size()<< "\t\t\t\t\t\t\t|" << "\n";
}

/**
 * Retorna o número de cidades
 * Time complexity: O(1)
 */

void Rede::numero_de_cidades() {

    cout << "|      Número atual de cidades: " << cities.size() << "\t\t\t\t\t\t\t\t\t\t|"<< "\n";
}

/**
 * Retorna o número de reservatórios
 * Time complexity: O(1)
 */

void Rede::numero_de_reservatorios() {

    cout << "|      Número atual de reservatórios: "<< reservoirs.size() << "\t\t\t\t\t\t\t\t|" << "\n";
}

/**
 * Verifica se existe uma aresta entre dois vértices
 * Time complexity: O(n) sendo n o número de arestas adjacentes ao vértice source
 * @param source - vértice de origem
 * @param dest - vértice de destino
 * @return true se a aresta existir, falso caso contrário
 */

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

/**
 * Testa o vértice 'w' dado e visitá-lo se as condições forem cumpridas
 * Time complexity: O(1)
 * @param q - queue de vértices
 * @param e - pipe
 * @param w - vértice
 * @param residual - capacidade residual
 */

// Function to test the given vertex 'w' and visit it if conditions are met
void Rede::testAndVisit(std::queue< Vertex<string>*> &q, Edge<string> *e, Vertex<string> *w, double residual) {
// Check if the vertex 'w' is not visited and there is residual capacity
    if (! w->isVisited() && residual > 0) {
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

/**
 * Encontra um caminho aumentativo usando Breadth-First Search
 * Time complexity: O(V + E) sendo V o número de vértices e E o número de arestas
 * @param s - vértice de origem
 * @param t - vértice de destino
 * @return true se um caminho para o destino for encontrado, falso caso contrário
 */

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

/**
 * Encontra a capacidade residual mínima ao longo do caminho aumentativo
 * Time complexity: O(V) sendo V o número de vértices
 * @param s - vértice de origem
 * @param t - vértice de destino
 * @return capacidade residual mínima - double
 */

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

/**
 * Função para aumentar o fluxo ao longo do caminho aumentativo com o valor de fluxo dado
 * Time complexity: O(V) sendo V o número de vértices
 * @param s - vértice de origem
 * @param t - vértice de destino
 * @param f - valor de fluxo
 */

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

/**
* Algoritmo de Edmonds-Karp para encontrar o fluxo máximo
* Time complexity: O(V*E²) sendo V o número de vértices e E o número de arestas
*/

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

/**
 * Inicializa o fluxo em todas as arestas para 0
 * Time complexity: O(V+A) sendo V o número de vértices e A o número de arestas
 */

void Rede::initialize_flow(){
    for (auto v : g.getVertexSet()) {
        for (auto e: v->getAdj()) {
            e->setFlow(0);
        }
    }
}

/**
 * Retorna o fluxo máximo de uma cidade
 * Time complexity: O(1)
 * @param cidade - nome da cidade
 * @return fluxo máximo - double
 */

double Rede::max_flow(const std::string &cidade) {
    double res = -1;
    auto v1 = g.findVertex(cidade);
    if(v1 != nullptr) {
        res = v1->getAdj()[0]->getFlow();
    }
    return res;
}

/**
 * Retorna o fluxo máximo de todas as cidades
 * Time complexity: O(V) sendo V o número de vértices
 */

void Rede::max_flow() {
    double total = 0;
    double temp = 0;
    cout << endl << "--------------------- MAX FLOW DE TODAS AS CIDADES ----------------------" << std::endl;
    std::cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|" << endl;
    for(auto vertex : g.getVertexSet()){
        if(vertex->getInfo()[0] == 'C') {
            temp = vertex->getAdj()[0]->getFlow();
            string adjusted;
            if((temp > 1000) && vertex->getInfo().length() == 3) adjusted = " m³/sec\t\t\t\t\t\t\t\t\t\t|";
            else if (temp > 1000) adjusted = " m³/sec\t\t\t\t\t\t\t\t\t|";
            else adjusted = " m³/sec\t\t\t\t\t\t\t\t\t\t|";
            cout << "|      " <<vertex->getInfo() << " -> Max Flow: " << temp << adjusted << endl;
            total += temp;
            temp = 0;
        }
    }
    std::cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|";
    cout << endl << "|      O max flow total e " << total << " m³/sec \t\t\t\t\t\t\t\t\t|" << endl;

    cout  << "-------------------------------------------------------------------------" << std::endl;
}

/**
 * Escreve o ficheiro 2_2.csv
 * Time complexity: O(V) sendo V o número de vértices
 */

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

/**
 * Escreve o ficheiro 3_1.csv
 * Time complexity: O(V) sendo V o número de vértices
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

            if (demand > flow){ //não sei se é para deixar assim ou por >=
                cout << "|      " <<code << " -> Deficit: " << demand - flow << " m³/sec\t\t\t\t\t\t\t\t\t\t|" << endl;
            }

        }

    }
    cout << "-------------------------------------------------------------------------" << endl;
}

/**
 * @brief Remove um reservatório da rede
 * Esta função é responsável por remover temporariamente um reservatório da rede, recalcular o fluxo máximo na rede usando o algoritmo de Edmonds-Karp e, em seguida, restaurar o reservatório ao seu estado original.
 *
 * @param reservoir Uma string que representa o reservatório a ser removido.
 * @return Retorna verdadeiro se o reservatório não existir na rede ou se o código do reservatório não começar com 'R'. Caso contrário, retorna falso indicando que o reservatório foi removido com sucesso.
 *
 * Time complexity: O(V*E²), onde V é o número de vértices e E é o número de arestas no grafo
 */

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

/**
 * @brief Remove uma estação da rede
 *
 * Esta função é responsável por remover temporariamente uma estação da rede, recalcular o fluxo máximo na rede usando o algoritmo de Edmonds-Karp e, em seguida, restaurar a estação ao seu estado original.
 *
 * @param station Uma string que representa a estação a ser removida.
 * @return Retorna verdadeiro se a estação não existir na rede ou se o código da estação não começar com 'PS'. Caso contrário, retorna falso indicando que a estação foi removida com sucesso.
 *
 * Time Complexity: O(V*E² + E), onde V é o número de vértices e E é o número de arestas no grafo. Isso é dominado pela chamada para o algoritmo de Edmonds-Karp e pela iteração sobre as arestas de entrada da estação.
 */

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

/**
 * @brief Remove uma ou mais pipes da rede
 *
 * Esta função é responsável por remover temporariamente uma ou mais pipes da rede, recalcular o fluxo máximo na rede usando o algoritmo de Edmonds-Karp e, em seguida, restaurar as pipes ao seu estado original.
 *
 * @param pipes Um vetor de strings que representa as pipes a serem removidas.
 *
 * Time Complexity: O(V*E² + E), onde V é o número de vértices e E é o número de arestas no grafo.
 */

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

/**
 * @brief Analisa os dados após a remoção de um reservatório
 *
 * Esta função lê o arquivo `2_2.csv`, que contém informações sobre o fluxo máximo de cada cidade. Para cada cidade, a função compara o fluxo máximo antigo (lido do arquivo) com o novo fluxo máximo (calculado após a remoção de um reservatório). Se o novo fluxo máximo for menor que o antigo, a função imprime essas informações.
 *
 * @note Esta função assume que o arquivo `2_2.csv` está no formato correto e que a primeira linha é um cabeçalho que deve ser ignorado.
 *
 * Complexidade de tempo: O(n), onde n é o número de linhas no arquivo `2_2.csv` (ou seja, o número de cidades).
 */


void Rede::dados_3_1() {
    ifstream in("../2_2.csv");
    if (!in) {
        cerr << "Erro ao abrir o arquivo." << endl;
    } else {
        string linha;
        getline(in, linha);
        cout << "------------------------ REMOÇÃO DO RESERVATÓRIO ------------------------" << endl;

        std::cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|" << endl;
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
                cout << "|      "<< code << " -> Old Flow: " << flow << " m³/sec || New Flow: " << max_flow_2 << " m³/sec\t\t\t\t|" << endl;
            }
        }
    }
}

/**
 * @brief Analisa os dados após a remoção de uma estação
 * Esta função lê o arquivo `2_2.csv`, que contém informações sobre o fluxo máximo de cada cidade. Para cada cidade, a função compara o fluxo máximo antigo (lido do arquivo) com o novo fluxo máximo (calculado após a remoção de uma estação). Se o novo fluxo máximo for menor que o antigo, a função imprime essas informações.
 * @note Esta função assume que o arquivo `2_2.csv` está no formato correto e que a primeira linha é um cabeçalho que deve ser ignorado.
 * Complexidade de tempo: O(n), onde n é o número de linhas no arquivo `2_2.csv` (ou seja, o número de cidades).

 */

void Rede::dados_3_2() {
    ifstream in("../2_2.csv");
    if (!in) {
        cerr << "Erro ao abrir o arquivo." << endl;
    } else {

        string linha;
        getline(in, linha);
        cout << "-------------------------- REMOÇÃO DA ESTAÇÃO ---------------------------" << endl;

        std::cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|";
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
                cout << endl << "|      "<< code << " -> Old Flow: " << flow << " m³/sec || New Flow: " << max_flow_2 << " m³/sec\t\t\t\t|" << endl;
            }
        }
    }
}

/**
 * @brief Analisa os dados após a remoção de uma ou mais pipes
 * Esta função lê o arquivo `2_2.csv`, que contém informações sobre o fluxo máximo de cada cidade. Para cada cidade, a função compara o fluxo máximo antigo (lido do arquivo) com o novo fluxo máximo (calculado após a remoção de uma ou mais pipes). Se o novo fluxo máximo for menor que o antigo, a função imprime essas informações.
 * @note Esta função assume que o arquivo `2_2.csv` está no formato correto e que a primeira linha é um cabeçalho que deve ser ignorado.
 * Complexidade de tempo: O(n), onde n é o número de linhas no arquivo `2_2.csv` (ou seja, o número de cidades).
 */

void Rede::dados_3_3(){
    ifstream in("../2_2.csv");
    if (!in) {
        cerr << "Erro ao abrir o arquivo." << endl;
    } else {
        string linha;
        getline(in, linha);
        cout << "--------------------------- REMOÇÃO DA PIPE -----------------------------" << endl;

        std::cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|";
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
                cout << endl << "|      "<< code << " -> Old Flow: " << flow << " m³/sec || New Flow: " << max_flow_2 << " m³/sec\t\t\t\t|" << endl;
            }
        }
    }
}