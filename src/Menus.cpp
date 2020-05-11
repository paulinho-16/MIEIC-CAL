#include "Menus.h"

/*
void Logotipo() {
  cout << "        ______      _   ______" << endl;
  cout << "       |  ____|    | | |  ____|" << endl;
  cout << "       | |__   __ _| |_| |__  __  ___ __  _ __ ___  ___ ___" << endl;
  cout << "       |  __| / _` | __|  __| \\ \\/ / '_ \\| '__/ _ \\/ __/ __|" << endl;
  cout << "       | |___| (_| | |_| |____ >  <| |_) | | |  __/\\__ \\__ \\ " << endl;
  cout << "       |______\\__,_|\\__|______/_/\\_\\ .__/|_|  \\___||___/___/" << endl;
  cout << "                                   | |" << endl;
  cout << "                                   |_|" << endl;
}

void Menu_Visualizacao() {
    system("CLS");
    Logotipo();
    cout << "\n\n\t\t     Menu de Visualizacao do Mapa \n\n";
    cout << "Abrindo Mapa..." << endl;
    Visualizar_Mapa();
}

void Menu_Gestao_Restaurantes() {
    system("CLS");
    Logotipo();
    cout << "\n\n\t\t     Menu de Gestao de Restaurantes \n\n";
}

void Menu_Gestao_Estafetas() {
    system("CLS");
    Logotipo();
    cout << "\n\n\t\t     Menu de Gestao de Estafetas \n\n";
}

void Menu_Gestao_Clientes() {
    system("CLS");
    Logotipo();
    cout << "\n\n\t\t     Menu de Gestao de Clientes \n\n";
}

void Menu_Efetuar_Pedidos() {
    system("CLS");
    Logotipo();
    cout << "\n\n\t\t     Menu de Atendimento de Pedidos \n\n";
    cout << "[1] Um estafeta a realizar um unico pedido \n";
    cout << "[2] Um estafeta a realizar multiplos pedidos em simultaneo (carga ilimitada)\n";
    cout << "[3] Multiplos estafetas a atender multiplos pedidos (carga ilimitada) \n";
    cout << "[4] Multiplos estafetas a atender multiplos pedidos (carga limitada) \n";

    string name;
    cin >> name;
    char opcao;
    if(name.size() == 1) opcao = name[0];
    else opcao = '9';

    switch(opcao)
    {
        case '1':
            break;
        case '2':
            break;
        case '3':
            break;
        case '4':
            break;
        case '5':
            break;
        default:
            Menu_Efetuar_Pedidos(); break;
    }
    //recolher_info_clientes<int>();
}*/