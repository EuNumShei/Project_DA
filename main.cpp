#include <iostream>
#include <stack>
#include <vector>
#include "Rede.h"

using namespace std;

/** Apresenta uma mensagem inicial informando que, por alguns instantes o sistema esta a processar
 *  a informacao que necessita
 */
void indicacao_de_processo(){
    cout << "Por favor, aguarde enquanto o sistema esta em processamento..." << endl;
}

/** Define e apresenta uma mensagem inicial
 */
void bem_vindo(){
    cout << "-------------------------------------------------" << endl;
    cout << "-          Bem vindo ao sistema AUGUINHA          -" << endl;
    cout << "-------------------------------------------------" << endl << endl;
}

/** Define uma mensagem inicial para o menu com os comandos disponíveis
* @param vetor de strings com os comandos disponíveis
* Time complexity: O(n)
*/
void print_inicio(const vector<string>& vetor) {
    cout << endl <<"Aqui se encontram todos os comandos disponiveis:" << endl;
    for (const string &metodo: vetor) {
        cout << "      " << metodo << endl;
    }
}


/** Define o resultado de um comando mal introduzido
* Time complexity: O(1)
*/
void print_incorreto(){
    cout << "Escrito incorretamente. Tente novamente: " << endl;
}

/** Apresenta o menu inicial com os comandos existentes
* Time complexity: O(1)
*/
void apresentacao_do_menu_inicial(){
    vector<string> vetor = {"1. Consultar o numero de cidades, reservatorios e estacoes",
                            "2. Verificar o max flow possivel de uma cidade",
                            "3. Verificar a distribuicao por cidade",
                            "4. Verificar o efeito da remocao de um reservatorio",
                            "5. Verificar o efeito da remocao de uma estacao",
                            "6. Verificar o efeito da remocao de uma/varias pipes",
                            "7. Terminar programa",
                            "Escolha uma opção."};

    cout << "---------Menu inicial---------" << endl;
    print_inicio(vetor);
}

void menu_intermedio(){

}

/*void menu_de_paises(Sistema & sistema){
    vector<string> vetor2 = {"aeroporto                      Para consultar a partir de um aeroporto",
                             "cidade                         Para consultar a partir de uma cidade",
                             "sair"};
    while(true){
        cout << "---------Ponto de partida---------" << endl;
        print_inicio(vetor2);
        string partida;
        cin >> partida;
        if(partida == "aeroporto") {
            string codigo;
            cout << "Indique o codigo do aeroporto de partida (Ex.:OPO): ";
            Vertex<Aeroporto> *aeroporto_inicial = nullptr;
            while (aeroporto_inicial == nullptr) {
                cout << "Escreva aqui:";
                cin >> codigo;
                aeroporto_inicial = sistema.procura_aeroporto(codigo);
            }
            sistema.numero_de_paises_aeroporto(codigo);
        }else if(partida == "cidade"){
            string cidade;
            cout << "Indique o nome da cidade de partida (Ex.:New_York): ";
            cin >> cidade;
            sistema.numero_de_paises_cidade(cidade);
        }else if(partida == "sair"){
            apresentacao_do_menu_inicial();
            break;
        }
        else{
            print_incorreto();
        }
    }
}
void menu_de_destinos(Sistema & sistema){
    vector<string> vetor = {"aeroportos                     Para consultar todos os aeroportos de destino",
                            "cidades                        Para consultar todos as cidades de destino",
                            "pais                           Para consultar todos os paises de destino",
                            "sair"};
    vector<string> vetor2 = {"aeroporto                      Para consultar a partir de um aeroporto",
                             "cidade                         Para consultar a partir de uma cidade",
                             "sair"};
    while (true){
        cout << "---------Ponto de partida---------" << endl;
        print_inicio(vetor2);
        string partida;
        cin >> partida;
        if(partida == "aeroporto") {
            while(true) {
                cout << "-------Consulta de destinos-------" << endl;
                print_inicio(vetor);
                string comando;
                cin >> comando;
                if (comando == "aeroportos") {
                    string codigo;
                    cout
                            << "Indique o aeroporto de onde deseja verificar os seus aeroportos de destino, usando o codigo correspondente (Ex.:OPO):";
                    Vertex<Aeroporto> *aeroporto_inicial = nullptr;
                    while (aeroporto_inicial == nullptr) {
                        cout << "Escreva aqui:";
                        cin >> codigo;
                        aeroporto_inicial = sistema.procura_aeroporto(codigo);
                    }
                    sistema.n_destinos_aeroportos_aero(codigo);
                } else if (comando == "cidades") {
                    string codigo;
                    cout
                            << "Indique o aeroporto de onde deseja verificar as suas cidades de destino, usando o codigo correspondente (Ex.:OPO):";
                    Vertex<Aeroporto> *aeroporto_inicial = nullptr;
                    while (aeroporto_inicial == nullptr) {
                        cout << "Escreva aqui:";
                        cin >> codigo;
                        aeroporto_inicial = sistema.procura_aeroporto(codigo);
                    }
                    sistema.n_destinos_cidades_aero(codigo);
                } else if (comando == "pais") {
                    string codigo;
                    cout
                            << "Indique o aeroporto de onde deseja verificar os seus paises de destino, usando o codigo correspondente (Ex.:OPO):";
                    Vertex<Aeroporto> *aeroporto_inicial = nullptr;
                    while (aeroporto_inicial == nullptr) {
                        cout << "Escreva aqui:";
                        cin >> codigo;
                        aeroporto_inicial = sistema.procura_aeroporto(codigo);
                    }
                    sistema.n_destinos_paises_aero(codigo);
                } else if (comando == "sair") {
                    break;
                } else {
                    print_incorreto();
                }
            }
        }else if(partida == "cidade"){
            while(true) {
                cout << "-------Consulta de destinos-------" << endl;
                print_inicio(vetor);
                string comando;
                cin >> comando;
                if (comando == "aeroportos") {
                    string cidade;
                    cout << "Indique a cidade de onde deseja verificar os seus aeroportos de destino (Ex.:New_York):";
                    cin >> cidade;
                    sistema.n_destinos_aeroportos_cid(cidade);
                } else if (comando == "cidades") {
                    string cidade;
                    cout << "Indique a cidade de onde deseja verificar as suas cidades de destino (Ex.:New_York):";
                    cin >> cidade;
                    sistema.n_destinos_cidades_cid(cidade);
                } else if (comando == "pais") {
                    string cidade;
                    cout << "Indique a cidade de onde deseja verificar os seus paises de destino (Ex.:New_York):";
                    cin >> cidade;
                    sistema.n_destinos_paises_cid(cidade);
                } else if (comando == "sair") {
                    break;
                } else {
                    print_incorreto();
                }
            }
        }else if(partida == "sair"){
            apresentacao_do_menu_inicial();
            break;
        }
        else{
            print_incorreto();
        }
    }
}


void menu_melhor_viagem(Sistema & sistema){
    vector<string> vetor = {"aeroporto                      Para procurar o melhor voo recorrendo ao codigo ou nome do aeroporto",
                            "cidade                         Para procurar o melhor voo recorrendo a todos os aeroportos de uma dada cidade",
                            "coordenadas                    Para procurar o melhor voo recorrendo a coordenadas geograficas",};
    string resposta;
    bool continuar = true;
    while (continuar){
        cout << "-------Consulta de viagens-------" << endl;
        print_inicio(vetor);

        cout << "\nEscolha qual metodo prefere para encontrar o(s) aeroporto(s) que deseja como partida.";

        string comando;
        vector<Vertex<Aeroporto>*> aeroportos_iniciais;

        while(comando != "aeroporto" and comando != "cidade" and comando != "coordenadas") {
            cout << "Escreva aqui:";
            cin >> comando;
            cout << endl;
            if (comando == "aeroporto") {
                string aeroporto;
                cout << "Indique o aeroporto de onde deseja iniciar a sua partida, usando o codigo ou nome correspondente (Ex.:OPO)";
                Vertex<Aeroporto> *aeroporto_inicial = nullptr;
                while (aeroporto_inicial == nullptr) {
                    cout << "Escreva aqui:";
                    cin >> aeroporto;
                    aeroporto_inicial = sistema.procura_aeroporto(aeroporto);
                }
                aeroportos_iniciais.push_back(aeroporto_inicial);
            } else if (comando == "cidade") {
                string cidade;
                cout << "Indique o nome da cidade de onde deseja inicializar a sua viagem (Ex.:New_York)";

                while (aeroportos_iniciais.empty()) {
                    cout << "Escreva aqui:";
                    cin >> cidade;
                    aeroportos_iniciais = sistema.procura_aeroporto_cidade(cidade);
                }
            } else if (comando == "coordenadas") {
                double latitude;
                double longitude;
                cout << "Indique a latitude das coordenadas de onde deseja inicializar a sua viagem (Ex.:49.012779):";
                cin >> latitude;
                cout << "Indique a longitude das coordenadas de onde deseja inicializar a sua viagem (Ex.:2.550000):";
                cin >> longitude;
                Distancia dist = Distancia(latitude, longitude);
                aeroportos_iniciais = sistema.procura_aeroporto_coord(dist);
                cout << "Aeroportos mais proximos das coordenadas:" << '\n';
                for(auto aero : aeroportos_iniciais) aero->getInfo().print();


            } else {
                print_incorreto();
            }
        }
        print_inicio(vetor);
        cout << "\nEscolha qual metodo prefere para encontrar o(s) aeroporto(s) que deseja como destino.";
        comando = "";

        vector<Vertex<Aeroporto>*> aeroportos_finais;
        while(comando != "aeroporto" and comando != "cidade" and comando != "coordenadas") {
            cout << "Escreva aqui:";
            cin >> comando;
            cout << endl;
            if (comando == "aeroporto") {
                string aeroporto;
                cout<< "Indique o aeroporto de onde deseja finalizar a sua viagem, usando o codigo ou nome correspondente (Ex.:OPO)";
                Vertex<Aeroporto> *aeroporto_final = nullptr;
                while (aeroporto_final == nullptr) {
                    cout << "Escreva aqui:";
                    cin >> aeroporto;
                    aeroporto_final = sistema.procura_aeroporto(aeroporto);
                }
                aeroportos_finais.push_back(aeroporto_final);
            } else if (comando == "cidade") {
                string cidade;
                cout << "Indique o nome da cidade de onde deseja finalizar a sua viagem (Ex.:New_York)";
                while (aeroportos_finais.empty()) {
                    cout << "Escreva aqui:";
                    cin >> cidade;
                    aeroportos_finais = sistema.procura_aeroporto_cidade(cidade);
                }
            } else if (comando == "coordenadas") {
                double latitude;
                double longitude;
                cout << "Indique a latitude das coordenadas de onde deseja finalizar a sua viagem (Ex.:49.012779):";
                cin >> latitude;
                cout << "Indique a longitude das coordenadas de onde deseja finalizar a sua viagem (Ex.:2.550000):";
                cin >> longitude;
                Distancia dist = Distancia(latitude, longitude);
                aeroportos_finais = sistema.procura_aeroporto_coord(dist);
                cout << "Aeroporto mais proximo das coordenadas:" << '\n';
                for(auto aero : aeroportos_finais) aero->getInfo().print();

            } else {
                print_incorreto();
            }
        }
        cout << "\nAeroportos pedidos encontrados.\n";
        sistema.melhorViagem(aeroportos_iniciais, aeroportos_finais);
        cout << "Continuar procura? Digite 'nao' para voltar ao menu principal.\n";
        cin >> resposta;
        if(resposta == "nao"){
            continuar = false;
        }
    }
    apresentacao_do_menu_inicial();
}


void menu_melhor_viagem_filtros(Sistema & sistema){
    vector<string> vetor1 = {"companhias_desejadas          Para introduzir uma ou varias companhias aerias com as quais se pretende viajar",
                             "companhias_indesejadas        Para introduzir uma uo varias companhias aerias com as quais o cliente nao quer viajar"};




    vector<string> vetor = {"aeroporto                      Para procurar o melhor voo recorrendo ao codigo ou nome do aeroporto",
                            "cidade                         Para procurar o melhor voo recorrendo a todos os aeroportos de uma dada cidade",
                            "coordenadas                    Para procurar o melhor voo recorrendo a coordenadas geograficas",};
    string resposta;
    bool continuar = true;
    while (continuar){
        cout << "-------Consulta de viagens-------" << endl;

        print_inicio(vetor1);

        cout << "\nEscolha qual filtro pretende colocar, para encontrar a melhor viagem para si.";

        string comando1;

        bool comp_desejadas = false;

        bool comp_indesejadas = false;
        vector<Companhia> companhias;

        while(comando1 != "companhias_desejadas" and comando1 != "companhias_indesejadas") {
            cout << "Escreva aqui:";
            cin >> comando1;
            cout << endl;
            if (comando1 == "companhias_desejadas") {
                string comp;
                cout << "Indique o codigo das companhias aerias com que pretende viajar (Ex.:TAP)";

                while (comp != "nao") {
                    cout << "Escreva aqui:";
                    cin >> comp;
                    if(sistema.procura_existe_companhia(comp)) companhias.push_back(sistema.procura_companhia(comp));
                    cout << "\nQuer adicionar mais companhias? Digite 'nao' para terminar. ";
                    cin >> comp;
                    if(comp == "nao") break;
                }
                comp_desejadas = true;
            }
            if (comando1 == "companhias_indesejadas") {
                string comp;
                cout << "Indique o codigo das companhias aerias com que nao pretende viajar (Ex.:TAP)";

                while (comp != "nao") {
                    cout << "Escreva aqui:";
                    cin >> comp;
                    if(sistema.procura_existe_companhia(comp)) companhias.push_back(sistema.procura_companhia(comp));
                    cout << "\nQuer adicionar mais companhias? Digite 'nao' para terminar. ";
                    cin >> comp;
                    if(comp == "nao") break;
                }
                comp_indesejadas = true;
            }
        }


        print_inicio(vetor);

        cout << "\nEscolha qual metodo prefere para encontrar o(s) aeroporto(s) que deseja como partida.";

        string comando;
        vector<Vertex<Aeroporto>*> aeroportos_iniciais;

        while(comando != "aeroporto" and comando != "cidade" and comando != "coordenadas") {
            cout << "Escreva aqui:";
            cin >> comando;
            cout << endl;
            if (comando == "aeroporto") {
                string aeroporto;
                cout << "Indique o aeroporto de onde deseja iniciar a sua partida, usando o codigo ou nome correspondente (Ex.:OPO)";
                Vertex<Aeroporto> *aeroporto_inicial = nullptr;
                while (aeroporto_inicial == nullptr) {
                    cout << "Escreva aqui:";
                    cin >> aeroporto;
                    aeroporto_inicial = sistema.procura_aeroporto(aeroporto);
                }
                aeroportos_iniciais.push_back(aeroporto_inicial);
            } else if (comando == "cidade") {
                string cidade;
                cout << "Indique o nome da cidade de onde deseja inicializar a sua viagem (Ex.:New_York)";

                while (aeroportos_iniciais.empty()) {
                    cout << "Escreva aqui:";
                    cin >> cidade;
                    aeroportos_iniciais = sistema.procura_aeroporto_cidade(cidade);
                }
            } else if (comando == "coordenadas") {
                double latitude;
                double longitude;
                cout << "Indique a latitude das coordenadas de onde deseja inicializar a sua viagem (Ex.:49.012779):";
                cin >> latitude;
                cout << "Indique a longitude das coordenadas de onde deseja inicializar a sua viagem (Ex.:2.550000):";
                cin >> longitude;
                Distancia dist = Distancia(latitude, longitude);
                aeroportos_iniciais = sistema.procura_aeroporto_coord(dist);
                cout << "Aeroportos mais proximos das coordenadas:" << '\n';
                for(auto aero : aeroportos_iniciais) aero->getInfo().print();


            } else {
                print_incorreto();
            }
        }
        print_inicio(vetor);
        cout << "\nEscolha qual metodo prefere para encontrar o(s) aeroporto(s) que deseja como destino.";
        comando = "";

        vector<Vertex<Aeroporto>*> aeroportos_finais;
        while(comando != "aeroporto" and comando != "cidade" and comando != "coordenadas") {
            cout << "Escreva aqui:";
            cin >> comando;
            cout << endl;
            if (comando == "aeroporto") {
                string aeroporto;
                cout<< "Indique o aeroporto de onde deseja finalizar a sua viagem, usando o codigo ou nome correspondente (Ex.:OPO)";
                Vertex<Aeroporto> *aeroporto_final = nullptr;
                while (aeroporto_final == nullptr) {
                    cout << "Escreva aqui:";
                    cin >> aeroporto;
                    aeroporto_final = sistema.procura_aeroporto(aeroporto);
                }
                aeroportos_finais.push_back(aeroporto_final);
            } else if (comando == "cidade") {
                string cidade;
                cout << "Indique o nome da cidade de onde deseja finalizar a sua viagem (Ex.:New_York)";
                while (aeroportos_finais.empty()) {
                    cout << "Escreva aqui:";
                    cin >> cidade;
                    aeroportos_finais = sistema.procura_aeroporto_cidade(cidade);
                }
            } else if (comando == "coordenadas") {
                double latitude;
                double longitude;
                cout << "Indique a latitude das coordenadas de onde deseja finalizar a sua viagem (Ex.:49.012779):";
                cin >> latitude;
                cout << "Indique a longitude das coordenadas de onde deseja finalizar a sua viagem (Ex.:2.550000):";
                cin >> longitude;
                Distancia dist = Distancia(latitude, longitude);
                aeroportos_finais = sistema.procura_aeroporto_coord(dist);
                cout << "Aeroporto mais proximo das coordenadas:" << '\n';
                for(auto aero : aeroportos_finais) aero->getInfo().print();

            } else {
                print_incorreto();
            }
        }
        cout << "\nAeroportos pedidos encontrados.\n";
        if(comp_desejadas) sistema.melhorViagem_filtros_comp_desejadas(aeroportos_iniciais,
                                                                       aeroportos_finais,
                                                                       companhias);
        if(comp_indesejadas) sistema.melhorViagem_filtros_comp_indesejadas(aeroportos_iniciais,
                                                                           aeroportos_finais,
                                                                           companhias);
        cout << "Continuar procura? Digite 'nao' para voltar ao menu principal.\n";
        cin >> resposta;
        if(resposta == "nao"){
            continuar = false;
        }
    }
    apresentacao_do_menu_inicial();
}



void menu_de_destinos_alcansaveis(Sistema & sistema){
    vector<string> vetor = {"aeroportos                     Para consultar o numero de aeroportos acessiveis usando escalas",
                            "cidades                        Para consultar o numero das cidades acessiveis usando escalas",
                            "pais                           Para consultar o numero dos paises acessiveis usando escalas",
                            "sair"};

    while (true){
        cout << "-------Consulta de destinos alcancaveis-------" << endl;
        print_inicio(vetor);
        string comando;
        cin >> comando;
        if(comando == "aeroportos"){
            string codigo;
            cout << "Indique o aeroporto que deseja verificar os seus aeroportos de destino, usando o codigo correspondente (Ex.:OPO):";
            cin >> codigo;
            string escalas;
            cout<<"\nEscreva o numero de escalas (Ex.:1):";
            cin >> escalas;
            try{
                int escalas_int = stoi(escalas);
                sistema.n_destinos_aeroportos_alcansaveis(codigo,escalas_int);
            }catch(exception e){
                cout << "\nNumero errado. Tente novamente" << endl;
            }
        }
        else if(comando == "cidades"){
            string codigo;
            cout << "Indique o aeroporto que deseja verificar as suas cidades de destino, usando o codigo correspondente (Ex.:OPO):";
            cin >> codigo;
            string escalas;
            cout<<"\nEscreva o numero de escalas (Ex.:1):";
            cin >> escalas;
            try{
                int escalas_int = stoi(escalas);
                sistema.n_destinos_cidades_alcansaveis(codigo,escalas_int);
            }catch(exception e){
                cout << "\nNumero errado. Tente novamente" << endl;
            }
        }
        else if(comando == "pais"){
            string codigo;
            cout << "Indique o aeroporto que deseja verificar os seus paises de destino, usando o codigo correspondente (Ex.:OPO):";
            cin >> codigo;
            string escalas;
            cout<<"\nEscreva o numero de escalas (Ex.:1):";
            cin >> escalas;
            try{
                int escalas_int = stoi(escalas);
                sistema.n_destinos_paises_alcansaveis(codigo,escalas_int);
            }catch(exception e){
                cout << "\nNumero errado. Tente novamente" << endl;
            }
        }
        else if(comando == "sair"){
            apresentacao_do_menu_inicial();
            break;
        }
        else{
            print_incorreto();
        }
    }
}*/



/** Dependendo do comando introduzido pelo usuario chama a funcao correspondente
 *
 * @param sistema que contem toda a informacao sobre aeroportos e viagens
 */
/*void menu_inicial(Rede & rede) {
    apresentacao_do_menu_inicial();
    while (true) {
        string comando;
        cin >> comando;
        if (comando == "consultar_n_globais") {
            rede.numero_de_cidades();
            rede.numero_de_reservatorios();
            rede.numero_de_estacoes();
            apresentacao_do_menu_inicial();
        } else if (comando == "consultar_edges"){
            cout << "Qual o codigo da source: ";
            string source, dest;
            cin >> source;
            cout << "Qual o codigo do dest: ";
            cin >> dest;
            if(rede.verificar_edge(source, dest)){
                cout << "Existe uma edge entre os 2 vertices" << endl;
            }else{
                cout << "Nao existe uma edge entre os 2 vertices" << endl;
            }
            apresentacao_do_menu_inicial();
        } else if (comando == "consultar_max_flow_cidade"){
            cout << "Qual o codigo da cidade: ";
            string cidade;
            cin >> cidade;
            rede.initialize_flow();
            for(auto reservoir : rede.getReservoirs()){
                rede.edmonds_karp(reservoir.first, cidade);
            }
            cout << "A cidade " << cidade << " tem um max flow de " << rede.max_flow(cidade) << endl;
            rede.initialize_flow();
            apresentacao_do_menu_inicial();
        } else if (comando == "sair") {
            // guardar_dados();
            break;
        } else {
            print_incorreto();
        }
    }
}
 */

void menu_inicial(Rede & rede) {
    bool done = false;
    apresentacao_do_menu_inicial();
    while (true) {
        int comando;
        string cidade, reservatorio, station, orig, dest, more_edges = "yes";
        double max_flow;
        vector<Edge<string>> edges;
        cin >> comando;

        //safeguarding if comando is not an integer
        if(cin.fail()){
            cin.clear();
            cin.ignore(10000, '\n');
            print_incorreto();
            apresentacao_do_menu_inicial();
            continue;
        }

        switch (comando) {
            case 1:
                rede.numero_de_cidades();
                rede.numero_de_reservatorios();
                rede.numero_de_estacoes();

                //show the results before showing the menu again
                cout << "To go back to the menu, type anything and press enter: ";
                cin >> comando;
                break;
            case 2:
                rede.initialize_flow();
                rede.edmonds_karp();
                rede.escrever_ficheiro_2_2();
                cout << "Qual o codigo da cidade (Caso pretender o max flow de todas as cidades, escreva a palavra todas): ";
                while(true) {
                    cin >> cidade;
                    if (cidade == "todas") {
                        rede.max_flow();
                        break;
                    } else {
                        max_flow = rede.max_flow(cidade);
                        if (max_flow == -1) {
                            print_incorreto();
                        }else{
                            cout << cidade << " -> Max Flow: " << max_flow << " m³/sec" << endl;
                            break;
                        }
                    }
                }
                done = true;
                //show the results before showing the menu again
                cout << "To go back to the menu, type anything and press enter: ";
                cin >> comando;
                break;
            case 3:
                rede.initialize_flow();
                if(!done){
                    rede.edmonds_karp();
                    rede.escrever_ficheiro_2_2();
                }
                rede.dados_2_2();
                cout << "To go back to the menu, type anything and press enter: ";
                cin >> comando;
                break;
            case 4:
                rede.initialize_flow();
                if(!done){
                    rede.edmonds_karp();
                    rede.escrever_ficheiro_2_2();
                    rede.initialize_flow();
                }
                cout << "Qual o codigo do reservatorio: ";
                cin >> reservatorio;
                while(rede.remover_reservatorio(reservatorio)){
                    print_incorreto();
                    cin >> reservatorio;
                }
                cout << "To go back to the menu, type anything and press enter: ";
                cin >> comando;
                break;
            case 5:
                rede.initialize_flow();
                if(!done){
                    rede.edmonds_karp();
                    rede.escrever_ficheiro_2_2();
                    rede.initialize_flow();
                }
                cout << "Qual o codigo da station: ";
                cin >> station;
                while(rede.remover_station(station)){
                    print_incorreto();
                    cin >> station;
                }
                cout << "To go back to the menu, type anything and press enter: ";
                cin >> comando;
                break;
            case 6:
                rede.initialize_flow();
                if(!done){
                    rede.edmonds_karp();
                    rede.escrever_ficheiro_2_2();
                    rede.initialize_flow();
                }
                while(more_edges == "yes"){
                    cout << "What is the code of the source: " << endl;
                    cin >> orig;
                    cout << "What is the code of the destination: " << endl;
                    cin >> dest;
                    while (!rede.verificar_edge(orig, dest)) {
                        print_incorreto();
                        cout << "What is the code of the source: " << endl;
                        cin >> orig;
                        cout << "What is the code of the destination: " << endl;
                        cin >> dest;
                    }
                    cout << "If you desire anymore edges, type yes, else type anything else: " << endl;
                    cin >> more_edges;
                }
                rede.remover_pipes();
                cout << "To go back to the menu, type anything and press enter: ";
                cin >> comando;
                break;
            case 7:
                // guardar_dados();
                return;
            default:
                print_incorreto();
        }
    }
}



int main(){
    Rede rede;
    bem_vindo();
    menu_inicial(rede);
    return 0;
}