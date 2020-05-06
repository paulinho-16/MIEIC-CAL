#include <iostream>

#include "Menus.h"

using namespace std;

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
    Menu_Principal();
    system("pause");
    return 0;
}