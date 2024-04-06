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
    cout << "-------------------------------------------------------------------------" << endl;
    cout << "-                     Bem vindo ao sistema AUGUINHA                     -" << endl;
    cout << "-------------------------------------------------------------------------" << endl << endl;
}

/** Define uma mensagem inicial para o menu com os comandos disponíveis
* @param vetor de strings com os comandos disponíveis
* Time complexity: O(n)
*/
void print_inicio(const vector<string>& vetor) {
    cout <<"|           Aqui se encontram todos os comandos disponiveis:            |" << endl;
    cout <<"|                                                                       |" << endl;
    for (const string &metodo: vetor) {
        cout << "|      " << metodo << endl;
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
    vector<string> vetor = {"1. Consultar o numero de cidades, reservatorios e estacoes       |",
                            "2. Verificar o max flow possível de uma cidade                   |",
                            "3. Verificar a distribuição por cidade                           |",
                            "4. Verificar o efeito da remoção de um reservatório              |",
                            "5. Verificar o efeito da remoção de uma estação                  |",
                            "6. Verificar o efeito da remoção de uma/várias pipes             |",
                            "7. Terminar programa                                             |",};

    std::cout << "----------------------------- MENU INICIAL ------------------------------" << std::endl;
    cout << "|                                                                       |" << endl;

    print_inicio(vetor);
    std::cout << "-------------------------------------------------------------------------" << std::endl;

    std::cout << "Escolha uma opção: ";
}

void menu_intermedio(){

}


void menu_inicial(Rede & rede) {
    bool done = false;

    while (true) {
        apresentacao_do_menu_inicial();
        char comando;
        string cidade, reservatorio, station, orig, dest, more_edges = "yes";
        double max_flow;
        cin >> comando;

        switch (comando) {
            case '1':

                std::cout << "----------------------------- INFORMAÇÕES -------------------------------" << std::endl;


                rede.numero_de_cidades();
                rede.numero_de_reservatorios();
                rede.numero_de_estacoes();

                std::cout << "-------------------------------------------------------------------------" << std::endl;
                //show the results before showing the menu again
                cout << "To go back to the menu, type anything and press enter: ";
                cin >> comando;
                break;
            case '2':
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
                            cout << "--------------------------- MAX FLOW DE " << cidade << " -----------------------------" << std::endl;
                            cout << "|                                                                       |" << endl;
                            cout << "|      " << cidade << " -> Max Flow: " << max_flow << " m³/sec\t\t\t\t\t\t\t\t\t\t|" << endl;
                            std::cout << "-------------------------------------------------------------------------" << std::endl;
                            break;
                        }
                    }
                }
                done = true;
                //show the results before showing the menu again
                cout << "To go back to the menu, type anything and press enter: ";
                cin >> comando;
                break;
            case '3':
                rede.initialize_flow();
                if(!done){
                    rede.edmonds_karp();
                    rede.escrever_ficheiro_2_2();
                }
                cout << "------------------------ DISTRIBUIÇÃO POR CIDADE ------------------------" <<endl;
                std::cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|" ;


                cout << endl;

                rede.dados_2_2();


                cout << "To go back to the menu, type anything and press enter: ";
                cin >> comando;
                break;
            case '4':
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


                std::cout << "-------------------------------------------------------------------------" << std::endl;
                cout << "To go back to the menu, type anything and press enter: ";
                cin >> comando;
                break;
            case '5':
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

                std::cout << "-------------------------------------------------------------------------" << std::endl;
                cout << "To go back to the menu, type anything and press enter: ";
                cin >> comando;
                break;
            case '6':
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
                std::cout << "-------------------------------------------------------------------------" << std::endl;
                cout << "To go back to the menu, type anything and press enter: ";
                cin >> comando;

                break;
            case '7':
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
