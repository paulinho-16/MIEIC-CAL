#include <iostream>

#include "Menus.h"
#include "utils.h"

using namespace std;

//#include "Restaurante.h"
//#include "Cliente.h"
//#include "Pedido.h"

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
            readMap("../maps/GridGraphs/4x4"); break;
        case '2':
            break;
        case '3':
            break;
        case '4':
            break;
        case '5':
            break;
        case '0':
            return 1;
        default:
            Menu_Mapas(); break;
    }
    return 0;
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

int main(int argc, char* argv[]) {
    if (Menu_Mapas() == 1)
        return 0;
    //Menu_Principal();
    system("pause");
    return 0;
}