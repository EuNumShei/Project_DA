//
// Created by Guilherme Teixeira on 05/03/2024.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include "Rede.h"
#include "City.h"
#include "Reservoir.h"
#include "Station.h"

using namespace std;

void Rede::ler_ficheiro_cidades() {
    ifstream in("../Code/Cities.csv");
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
            const City new_city = City(name, id, code, demand, population, 'C');
            g.addVertex(new_city);
        }
    }
}

/** Funcao que le o ficheiro com as informacoes relativas aos aeroportos e guarda essa informacao
 *  no grafo
 *  Time complexity: O(l*w), being l the number of lines and w the number of words
 */
void Rede::ler_ficheiro_reservatorios() {
    ifstream in("../Code/Reservoir.csv");
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
            Reservoir reservoir = Reservoir(name, municipality, id, code, max_delivery, 'R');
            g.addVertex(reservoir);
        }
    }
}

/** Funcao que le o ficheiro com as informacoes acerca dos voos existentes e coloca essa informacao
 *  no grafo
 *  Time complexity: O(l*w), being l the number of lines and w the number of words
 */
void Rede::ler_ficheiro_estacoes() {
    ifstream in("../Code/Stations.csv");
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
            Station station = Station(id, code, 'S');
            g.addVertex(station);
        }
    }
}

void Rede::ler_ficheiro_pipes() {
    ifstream in("../Code/Pipes.csv");
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
    int res = 0;
    for(auto vertex : g.getVertexSet()){
        if(vertex->getInfo().get_code()[0] == 'P') res++;
    }
    cout << "Numero atual de estacoes intermedias: " << res << "\n";
    for(auto vertex: g.getVertexSet()){
        cout << vertex->getInfo().get_code() << ' ';
    }
}

/*
* Function that returns the total number of airports
* Time complexity: O(1)
*/
void Rede::numero_de_cidades() {
    int res = 0;
    for(auto vertex : g.getVertexSet()){
        if(vertex->getInfo().get_code()[0] == 'C') res++;
    }
    cout << "Numero atual de cidades: " << res << "\n";
}

/*
* Function that returns the total number of flights
* Time complexity: O(1)
*/
void Rede::numero_de_reservatorios() {
    int res = 0;
    for(auto vertex : g.getVertexSet()){
        if(vertex->getInfo().get_code()[0] == 'R') res++;
    }
    cout << "Numero atual de reservatorios: " << res << "\n";
}
