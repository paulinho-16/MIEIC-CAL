#include <iostream>

#include "Graph.h"
#include "utils.h"
#include "EatExpress.h"
#include "Algoritmos.h"

using namespace std;

Graph<int> graph;
EatExpress<int> eatExpress;
bool bidirectional_edges;

void Menu_Principal();

/*void Logotipo() {
    cout << "        ______      _   ______" << endl;
    cout << "       |  ____|    | | |  ____|" << endl;
    cout << "       | |__   __ _| |_| |__  __  ___ __  _ __ ___  ___ ___" << endl;
    cout << "       |  __| / _` | __|  __| \\ \\/ / '_ \\| '__/ _ \\/ __/ __|" << endl;
    cout << "       | |___| (_| | |_| |____ >  <| |_) | | |  __/\\__ \\__ \\ " << endl;
    cout << "       |______\\__,_|\\__|______/_/\\_\\ .__/|_|  \\___||___/___/" << endl;
    cout << "                                   | |" << endl;
    cout << "                                   |_|" << endl;
}*/

char Sair_Programa()
{
    char sair;
    cout << "\nSair do Programa? (S/N)\n\n";
    do{
        cout << "R: ";
        cin >> sair;
    } while(sair != 'N' && sair != 'n' && sair != 'S' && sair != 's');
    return sair;
}

void Menu_Visualizacao() {
    system("CLS");
    Logotipo();
    cout << "\n\n\t\t     Menu de Visualizacao do Mapa \n\n";
    cout << "Abrindo Mapa..." << endl;
    Visualizar_Mapa();
    char sair = Sair_Programa();
    if (sair == 'N' || sair == 'n')
        Menu_Principal();
}

void Menu_Gestao_Restaurantes() {
    system("CLS");
    Logotipo();
    cout << "\n\n\t\t     Menu de Gestao de Restaurantes \n\n";
    char sair = Sair_Programa();
    if (sair == 'N' || sair == 'n')
        Menu_Principal();
}

void Menu_Gestao_Estafetas() {
    system("CLS");
    Logotipo();
    cout << "\n\n\t\t     Menu de Gestao de Estafetas \n\n";
    char sair = Sair_Programa();
    if (sair == 'N' || sair == 'n')
        Menu_Principal();
}

void Menu_Gestao_Clientes() {
    system("CLS");
    Logotipo();
    cout << "\n\n\t\t     Menu de Gestao de Clientes \n\n";
    char sair = Sair_Programa();
    if (sair == 'N' || sair == 'n')
        Menu_Principal();
}

void Menu_Efetuar_Pedidos() {
    system("CLS");
    Logotipo();
    cout << "\n\n\t\t     Menu de Atendimento de Pedidos \n\n";
    cout << "[1] Um estafeta a realizar um unico pedido \n";
    cout << "[2] Um estafeta a realizar multiplos pedidos em simultaneo (carga ilimitada)\n";
    cout << "[3] Multiplos estafetas a atender multiplos pedidos (carga ilimitada) \n";
    cout << "[4] Multiplos estafetas a atender multiplos pedidos (carga limitada) \n";
    cout << "[5] Voltar ao Menu Principal \n";
    cout << "\nOpcao: ";

    string name;
    cin >> name;
    char opcao;
    if(name.size() == 1) opcao = name[0];
    else opcao = '9';

    switch(opcao)
    {
        case '1':
            Um_Estafeta_Um_Pedido<int>();
            break;
        case '2':
            Um_Estafeta_Varios_Pedidos<int>();
            break;
        case '3':
            Varios_Estafetas_Sem_Carga<int>();
            break;
        case '4':
            Varios_Estafetas_Com_Carga<int>();
            break;
        case '5':
            Menu_Principal();
            break;
        default:
            Menu_Efetuar_Pedidos(); break;
    }
}

void Menu_Principal()
{
    system("CLS");
   Logotipo();
    cout << "\n\n\t\t     Menu Principal \n\n";
    cout << "[1] Visualizar o mapa recorrendo ao GraphViewer \n";
    cout << "[2] Gestao de Restaurantes \n";
    cout << "[3] Gestao de Estafetas \n";
    cout << "[4] Gestao de Clientes \n";
    cout << "[5] Atendimento de Pedidos \n";
    cout << "[0] Sair do Programa \n";
    cout << "\nOpcao: ";

    string name;
    cin >> name;
    char opcao;
    if(name.size() == 1) opcao = name[0];
    else opcao = '9';

    switch(opcao)
    {
        case '1':
            Menu_Visualizacao(); break;
        case '2':
            Menu_Gestao_Restaurantes(); break;
        case '3':
            Menu_Gestao_Estafetas(); break;
        case '4':
            Menu_Gestao_Clientes(); break;
        case '5':
            Menu_Efetuar_Pedidos(); break;
        case '0':
            break;
        default:
            Menu_Principal(); break;
    }
}

template <class T>
int Menu_Mapas() {
    system("CLS");
    Logotipo();
    cout << "\n\n\t\t     Menu de Escolha do Mapa \n\n";
    cout << "\t GraphGrid \n";
    cout << "[1] 4x4 \n";
    cout << "[2] 8x8 \n";
    cout << "[3] 16x16 \n";
    cout << "\t PortugalMaps \n";
    cout << "[4] Aveiro \n";
    cout << "[5] Braga \n";
    // METER AS OUTRAS OPÇÕES
    cout << "\n[0] Sair do Programa \n";
    cout << "\nOpcao: ";

    string name;
    cin >> name;
    char opcao;
    if(name.size() == 1) opcao = name[0];
    else opcao = '9';

    switch(opcao)
    {
        case '1':
            bidirectional_edges = true;
            readMap("../maps/GridGraphs/4x4");
            break;
        case '2':
            bidirectional_edges = true;
            readMap("../maps/GridGraphs/8x8");
            break;
        case '3':
            bidirectional_edges = true;
            readMap("../maps/GridGraphs/16x16");
            break;
        case '4':
            bidirectional_edges = false;
            break;
        case '5':
            bidirectional_edges = false;
            break;
        case '0':
            return 1;
        default:
            Menu_Mapas<int>(); break;
    }
    return 0;
}

int main(int argc, char* argv[]) {
    if (Menu_Mapas<int>() == 1)
        return 0;
    Recolher_Info();
    Menu_Principal();
    system("pause");
    return 0;
}