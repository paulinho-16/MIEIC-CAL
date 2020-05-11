#ifndef CAL_FP05_ALGORITMOS_H
#define CAL_FP05_ALGORITMOS_H

extern EatExpress<int> eatExpress;

template <class T>
void Um_Estafeta_Um_Pedido() {
    system("CLS");
    Logotipo();
    cout << "\n\n\t\t     Atendimento de um unico Pedido por um unico Estafeta \n\n";
    int nc = 1, nr = 1, ne = 1, n_cliente, n_restaurante, n_estafeta;
    for (Cliente<T>* cliente : eatExpress.getClientes()) {
        cout << " [" << nc << "]" << cliente->getNome() << " - " << cliente->getNif() << endl;
        nc++;
    }
    do {
        cout << "\nCliente que deseja efetuar o pedido: ";
        cin.clear();
        cin >> n_cliente;
        cin.ignore(1000, '\n');
    } while(n_cliente < 1 || n_cliente > eatExpress.getNumClientes());
    Cliente<T>* cliente = eatExpress.getClientes().at(n_cliente-1);
    cout << endl;
    for (Restaurante<T>* restaurante : eatExpress.getRestaurantes()) {
        cout << " [" << nr << "]" << restaurante->getNome() << " - " << restaurante->getDescricao() << endl;
        nr++;
    }
    do {
        cout << "\nRestaurante desejado: ";
        cin.clear();
        cin >> n_restaurante;
        cin.ignore(1000, '\n');
    } while(n_restaurante < 1 || n_restaurante > eatExpress.getNumRestaurantes());
    Restaurante<T>* restaurante = eatExpress.getRestaurantes().at(n_restaurante-1);
    cout << endl;
    for (Estafeta<T>* estafeta : eatExpress.getEstafetas()) {
        cout << " [" << ne << "]" << estafeta->getNome() << " - " << estafeta->getNif() << endl;
        ne++;
    }
    do {
        cout << "\nEstafeta que vai atender o pedido: ";
        cin.clear();
        cin >> n_estafeta;
        cin.ignore(1000, '\n');
    } while(n_estafeta < 1 || n_estafeta > eatExpress.getNumEstafetas());
    Estafeta<T>* estafeta = eatExpress.getEstafetas().at(n_estafeta-1);

    // JA TEMOS O CLIENTE, RESTAURANTE E ESTAFETA, AGORA É IMPLEMENTAR O ALGORITMO - CHAMAR AQUI E FAZER EM FUNÇÃO DIFERENTE
}

template <class T>
void Um_Estafeta_Varios_Pedidos() {
    system("CLS");
    Logotipo();
    cout << "\n\n\t\t     Atendimento de varios Pedidos por um unico Estafeta \n\n";
    int nc = 1, nr = 1, ne = 1;
    cout << "Clientes:" << endl;
    for (Cliente<T> *cliente : eatExpress.getClientes()) {
        cout << " [" << nc << "]" << cliente->getNome() << " - " << cliente->getNif() << endl;
        nc++;
    }
    cout << endl << "Restaurantes:" << endl;
    for (Restaurante<T> *restaurante : eatExpress.getRestaurantes()) {
        cout << " [" << nr << "]" << restaurante->getNome() << " - " << restaurante->getDescricao() << endl;
        nr++;
    }

    vector<Pedido<T>*> pedidos;
    Cliente<T>* cliente;
    Restaurante<T>* restaurante;
    int n_cliente, n_restaurante;
    do {
        do {
            cout << "\nCliente que deseja efetuar o pedido: ";
            cin.clear();
            cin >> n_cliente;
            cin.ignore(1000, '\n');
        } while (n_cliente < 0 || n_cliente > eatExpress.getNumClientes());
        if (n_cliente != 0)
            cliente = eatExpress.getClientes().at(n_cliente - 1);
        do {
            cout << "\nRestaurante desejado: ";
            cin.clear();
            cin >> n_restaurante;
            cin.ignore(1000, '\n');
        } while (n_restaurante < 0 || n_restaurante > eatExpress.getNumRestaurantes());
        if (n_restaurante != 0)
            restaurante = eatExpress.getRestaurantes().at(n_restaurante - 1);
        if (n_cliente != 0 && n_restaurante != 0) {
            Pedido<T>* pedido = new Pedido<T>(cliente, restaurante);
            pedidos.push_back(pedido);
        }
    } while (n_cliente != 0 && n_restaurante != 0);


    cout << endl;
    for (Estafeta<T>* estafeta : eatExpress.getEstafetas()) {
        cout << " [" << ne << "]" << estafeta->getNome() << " - " << estafeta->getNif() << endl;
        ne++;
    }
    int n_estafeta;
    do {
        cout << "\nEstafeta que vai atender o pedido: ";
        cin.clear();
        cin >> n_estafeta;
        cin.ignore(1000, '\n');
    } while(n_estafeta < 1 || n_estafeta > eatExpress.getNumEstafetas());
    Estafeta<T>* estafeta = eatExpress.getEstafetas().at(n_estafeta-1);

    // JA TEMOS A LISTA DE PEDIDOS E O ESTAFETA, AGORA É IMPLEMENTAR O ALGORITMO - CHAMAR AQUI E FAZER EM FUNÇÃO DIFERENTE
}

template <class T>
void Varios_Estafetas_Sem_Carga() {
    system("CLS");
    Logotipo();
    cout << "\n\n\t\t     Atendimento de varios Pedidos por varios Estafetas, com carga ilimitada \n\n";
    int nc = 1, nr = 1, ne = 1;
    cout << "Clientes:" << endl;
    for (Cliente<T> *cliente : eatExpress.getClientes()) {
        cout << " [" << nc << "]" << cliente->getNome() << " - " << cliente->getNif() << endl;
        nc++;
    }
    cout << endl << "Restaurantes:" << endl;
    for (Restaurante<T> *restaurante : eatExpress.getRestaurantes()) {
        cout << " [" << nr << "]" << restaurante->getNome() << " - " << restaurante->getDescricao() << endl;
        nr++;
    }

    vector<Pedido<T>*> pedidos;
    Cliente<T>* cliente;
    Restaurante<T>* restaurante;
    int n_cliente, n_restaurante;
    do {
        do {
            cout << "\nCliente que deseja efetuar o pedido: ";
            cin.clear();
            cin >> n_cliente;
            cin.ignore(1000, '\n');
        } while (n_cliente < 0 || n_cliente > eatExpress.getNumClientes());
        if (n_cliente != 0)
            cliente = eatExpress.getClientes().at(n_cliente - 1);
        do {
            cout << "\nRestaurante desejado: ";
            cin.clear();
            cin >> n_restaurante;
            cin.ignore(1000, '\n');
        } while (n_restaurante < 0 || n_restaurante > eatExpress.getNumRestaurantes());
        if (n_restaurante != 0)
            restaurante = eatExpress.getRestaurantes().at(n_restaurante - 1);
        if (n_cliente != 0 && n_restaurante != 0) {
            Pedido<T>* pedido = new Pedido<T>(cliente, restaurante);
            pedidos.push_back(pedido);
        }
    } while (n_cliente != 0 && n_restaurante != 0);

    // JA TEMOS A LISTA DE PEDIDOS, AGORA É IMPLEMENTAR O ALGORITMO, OS ESTAFETAS SÃO ESCOLHIDOS POR UM CRITERIO - CHAMAR AQUI E FAZER EM FUNÇÃO DIFERENTE
}

template <class T>
void Varios_Estafetas_Com_Carga() {
    system("CLS");
    Logotipo();
    cout << "\n\n\t\t     Atendimento de varios Pedidos por varios Estafetas, com carga limitada \n\n";
    int nc = 1, nr = 1, ne = 1;
    cout << "Clientes:" << endl;
    for (Cliente<T> *cliente : eatExpress.getClientes()) {
        cout << " [" << nc << "]" << cliente->getNome() << " - " << cliente->getNif() << endl;
        nc++;
    }
    cout << endl << "Restaurantes:" << endl;
    for (Restaurante<T> *restaurante : eatExpress.getRestaurantes()) {
        cout << " [" << nr << "]" << restaurante->getNome() << " - " << restaurante->getDescricao() << endl;
        nr++;
    }

    vector<Pedido<T>*> pedidos;
    Cliente<T>* cliente;
    Restaurante<T>* restaurante;
    int n_cliente, n_restaurante;
    do {
        do {
            cout << "\nCliente que deseja efetuar o pedido: ";
            cin.clear();
            cin >> n_cliente;
            cin.ignore(1000, '\n');
        } while (n_cliente < 0 || n_cliente > eatExpress.getNumClientes());
        if (n_cliente != 0)
            cliente = eatExpress.getClientes().at(n_cliente - 1);
        do {
            cout << "\nRestaurante desejado: ";
            cin.clear();
            cin >> n_restaurante;
            cin.ignore(1000, '\n');
        } while (n_restaurante < 0 || n_restaurante > eatExpress.getNumRestaurantes());
        if (n_restaurante != 0)
            restaurante = eatExpress.getRestaurantes().at(n_restaurante - 1);
        if (n_cliente != 0 && n_restaurante != 0) {
            Pedido<T>* pedido = new Pedido<T>(cliente, restaurante);
            pedidos.push_back(pedido);
        }
    } while (n_cliente != 0 && n_restaurante != 0);

    // JA TEMOS A LISTA DE PEDIDOS, AGORA É IMPLEMENTAR O ALGORITMO, OS ESTAFETAS SÃO ESCOLHIDOS POR UM CRITERIO - CHAMAR AQUI E FAZER EM FUNÇÃO DIFERENTE
}

#endif //CAL_FP05_ALGORITMOS_H
