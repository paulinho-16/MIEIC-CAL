#include <iostream>

#include "Graph.h"
#include "utils.h"
#include "EatExpress.h"
#include "Algoritmos.h"
#include "Conetividade.h"
#include "AnaliseTempo.h"

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

template <class T>
void Menu_Conetividade() {
    system("CLS");
    Logotipo();
    cout << "\n\n\t\t     Menu da Conetividade do Grafo \n\n";
    cout<<"\nTesting Connectivity..."<<endl;
    vector<Vertex<T>*> vec = Avaliar_Conetividade<int>(graph.getVertexSet()[0]); //devolve parte fortemente conexa do grafo a partir da casa dos estafetas
    if(vec.size()==graph.getVertexSet().size()){
        cout<<"Grafo fortemente conexo!"<<endl;
    }
    else{
        cout<<"Grafo nao e fortemente conexo!"<<endl;
    }
    vector<T> vec_aux;
    for(Vertex<T>* v: vec){
        vec_aux.push_back(v->getInfo());
    }
    showConnection<T>(vec_aux);
    char sair = Sair_Programa();
    if (sair == 'N' || sair == 'n')
        Menu_Principal();
}

void Menu_Visualizacao() {
    system("CLS");
    Logotipo();
    cout << "\n\n\t\t     Menu de Visualizacao do Mapa \n\n";
    cout << "Abrindo Mapa..." << endl;
    cout << "\n Cores: " << endl << endl;
    cout << "Laranja - Casa dos Estafetas" << endl;
    cout << "Amarelo - Estafetas" << endl;
    cout << "Verde - Clientes" << endl;
    cout << "Vermelho - Restaurantes" << endl;
    Visualizar_Mapa();
    char sair = Sair_Programa();
    if (sair == 'N' || sair == 'n')
        Menu_Principal();
}

template <class T>
void Visualizar_Clientes() {
    system("CLS");
    Logotipo();
    cout << "\n\n\t\t     Menu de Visualizacao de Clientes \n\n";
    int i = 0;
    for (Cliente<T>* cliente : eatExpress.getClientes()) {
        cout << "Nome: " << cliente->getNome() << endl;
        cout << "Nif: " << cliente->getNif() << endl;
        cout << "Morada: " << cliente->getMorada() << endl;
        if (i != eatExpress.getNumClientes() - 1)
            cout << "----------" << endl;
        i++;
    }
    char sair = Sair_Programa();
    if (sair == 'N' || sair == 'n')
        Menu_Principal();
}

template <class T>
void Visualizar_Restaurantes() {
    system("CLS");
    Logotipo();
    cout << "\n\n\t\t     Menu de Visualizacao de Restaurantes \n\n";
    int i = 0;
    for (Restaurante<T>* restaurante : eatExpress.getRestaurantes()) {
        cout << "Nome: " << restaurante->getNome() << endl;
        cout << "Descricao: " << restaurante->getDescricao() << endl;
        cout << "Morada: " << restaurante->getMorada() << endl;
        if (i != eatExpress.getNumRestaurantes() - 1)
            cout << "----------" << endl;
        i++;
    }
    char sair = Sair_Programa();
    if (sair == 'N' || sair == 'n')
        Menu_Principal();
}

template <class T>
void Visualizar_Estafetas() {
    system("CLS");
    Logotipo();
    cout << "\n\n\t\t     Menu de Visualizacao de Estafetas \n\n";
    int i = 0;
    for (Estafeta<T>* estafeta : eatExpress.getEstafetas()) {
        cout << "Nome: " << estafeta->getNome() << endl;
        cout << "Nif: " << estafeta->getNif() << endl;
        cout << "Morada: " << estafeta->getPos() << endl;
        cout << "Transporte: " << estafeta->getTransporte().getNome() << endl;
        if (i != eatExpress.getNumEstafetas() - 1)
            cout << "----------" << endl;
        i++;
    }
    char sair = Sair_Programa();
    if (sair == 'N' || sair == 'n')
        Menu_Principal();
}

void Visualizar_Transportes() {
    system("CLS");
    Logotipo();
    cout << "\n\n\t\t     Menu de Visualizacao de Transportes \n\n";
    int i = 0;
    for (MeioTransporte transporte : eatExpress.getTransportes()) {
        cout << "Nome: " << transporte.getNome() << endl;
        cout << "Velocidade: " << transporte.getVelocidade() << endl;
        cout << "Capacidade: " << transporte.getCapacidade() << endl;
        if (i != eatExpress.getNumTransportes() - 1)
            cout << "----------" << endl;
        i++;
    }
    char sair = Sair_Programa();
    if (sair == 'N' || sair == 'n')
        Menu_Principal();
}

void Menu_Visualizar_Dados() {
    system("CLS");
    Logotipo();
    cout << "\n\n\t\t     Menu de Visualizacao de Dados \n\n";
    cout << "[1] Visualizar Clientes\n";
    cout << "[2] Visualizar Restaurantes\n";
    cout << "[3] Visualizar Estafetas\n";
    cout << "[4] Visualizar Meios de Transporte\n";
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
            Visualizar_Clientes<int>(); break;
        case '2':
            Visualizar_Restaurantes<int>(); break;
        case '3':
            Visualizar_Estafetas<int>(); break;
        case '4':
            Visualizar_Transportes(); break;
        case '5':
            Menu_Principal(); break;
        default:
            Menu_Visualizar_Dados(); break;
    }
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
    cout << "[1] Avaliar Conetividade do grafo \n";
    cout << "\n\t Visualizacao: \n\n";
    cout << "[2] Visualizar o mapa recorrendo ao GraphViewer \n";
    cout << "[3] Visualizar Dados \n";
    cout << "\n\t Pedidos: \n\n";
    cout << "[4] Atendimento de Pedidos \n";
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
            Menu_Conetividade<int>(); break;
        case '2':
            Menu_Visualizacao(); break;
        case '3':
            Menu_Visualizar_Dados(); break;
        case '4':
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
    cout << "[4] Personalizado \n";
    cout << "\n\t Mapas de Portugal \n";
    cout << "\n Mapas Fortemente Conexos \n\n";
    cout << "[5] Penafiel \n";
    cout << "[6] Espinho \n";
    cout << "[7] Porto \n";
    cout << "\n Mapas Nao Conexos \n\n";
    cout << "[8] Penafiel \n";
    cout << "[9] Espinho \n";
    cout << "[10] Porto \n";

    cout << "\n\n[11] Analise Temporal\n";
    cout << "\n[0] Sair do Programa \n";
    cout << "\nOpcao: ";

    string name;
    cin >> name;
    char opcao;
    if(name.size() == 1) opcao = name[0];
    else {
        if (name == "10") opcao = 'p';
        else if (name == "11") opcao = 'a';
        else opcao = 'r';
    }

    switch(opcao)
    {
        case '1':
            bidirectional_edges = true;
            readMap<T>("../maps/GridGraphs/4x4");
            break;
        case '2':
            bidirectional_edges = true;
            readMap<T>("../maps/GridGraphs/8x8");
            break;
        case '3':
            bidirectional_edges = true;
            readMap<T>("../maps/GridGraphs/16x16");
            break;
        case '4':
            bidirectional_edges = false;
            readMap<T>("../maps/Personalizado");
            break;
        case '5':
            bidirectional_edges = false;
            readMap<T>("../maps/MapasConexos/Penafiel");
            break;
        case '6':
            bidirectional_edges = false;
            readMap<T>("../maps/MapasConexos/Espinho");
            break;
        case '7':
            bidirectional_edges = false;
            readMap<T>("../maps/MapasConexos/Porto");
            break;
        case '8':
            bidirectional_edges = false;
            readMap<T>("../maps/MapasNaoConexos/Penafiel");
            break;
        case '9':
            bidirectional_edges = false;
            readMap<T>("../maps/MapasNaoConexos/Espinho");
            break;
        case 'p':
            bidirectional_edges = false;
            readMap<T>("../maps/MapasNaoConexos/Porto");
            break;
        case 'a':
            Analise_Temporal();
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