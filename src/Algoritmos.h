#ifndef CAL_FP05_ALGORITMOS_H
#define CAL_FP05_ALGORITMOS_H


extern EatExpress<int> eatExpress;
extern Graph<int> graph;

Estafeta<int>* estafeta_ativo;

void Menu_Principal();
char Sair_Programa();

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

    // JA TEMOS O CLIENTE, RESTAURANTE E ESTAFETA, AGORA É IMPLEMENTAR O ALGORITMO - CHAMAR AQUI E FAZER EM FUNÇÃO DIFERENTE:
    Pedido<T> *pedido = new Pedido<T>(cliente, restaurante);
    pedido->setEstafeta(estafeta);
    vector<Pedido<T>*> pedidos = {pedido};
    eatExpress.setPedidos(pedidos);

    graph.dijkstraShortestPath(estafeta->getPos());
    vector<Vertex<T>*> estafeta_restaurante = graph.getPath(estafeta->getPos(), restaurante->getMorada());
    graph.dijkstraShortestPath(restaurante->getMorada());
    vector<Vertex<T>*> restaurante_cliente = graph.getPath(restaurante->getMorada(), cliente->getMorada());

    //int restauranteIndex = estafeta_restaurante.size() - 1;  // Para evitar pintar o vértice do Restaurante no showPathGV

    restaurante_cliente.erase(restaurante_cliente.begin());
    estafeta_restaurante.insert(estafeta_restaurante.end(), restaurante_cliente.begin(), restaurante_cliente.end());

    cout << endl;
    for (Vertex<T>* vertex : estafeta_restaurante) {
        cout << "Vertex " << vertex->getInfo() << " com POS (" << vertex->getLatitude() << ", " << vertex->getLongitude() << ")"<<endl;
    }

    showPathGV(estafeta_restaurante);

    char sair = Sair_Programa();
    if (sair == 'N' || sair == 'n')
        Menu_Principal();
}

template <class T>
struct Compare {
    bool operator()(Vertex<T>* const& p1, Vertex<T>* const& p2) {
        // return "true" if "p1" is ordered
        // before "p2", for example:
        cout << "COMPARANDO VERTEX P2 - (" << p2->getLatitude() << ", " << p2->getLongitude() << ") com VERTEX P1 - (" <<p1->getLatitude() << ", " << p1->getLongitude() << ") :  ";

        if (p1->getType() == 2 && p2->getType() == 2) {     //2 restaurantes
            if (graph.getDist(estafeta_ativo->getPos(), p1->getInfo()) > graph.getDist(estafeta_ativo->getPos(), p2->getInfo())) {
                cout << "TRUE" << endl;
                return true;
            } else {
                cout << "FALSE" << endl;
                return false;
            }
        }
        else if (p1->getType() == 1 && p2->getType() == 1) {    //2 clientes
            if (eatExpress.findPedido(p1->getInfo())->isRequisitado() && eatExpress.findPedido(p2->getInfo())->isRequisitado()) {   // ambos requisitados
                if (graph.getDist(estafeta_ativo->getPos(), p1->getInfo()) > graph.getDist(estafeta_ativo->getPos(), p2->getInfo())) {
                    cout << "TRUE" << endl;
                    return true;
                }
                else {
                    cout << "FALSE" << endl;
                    return false;
                }
            }
            else if (eatExpress.findPedido(p1->getInfo())->isRequisitado() && !eatExpress.findPedido(p2->getInfo())->isRequisitado()) {
                cout << "FALSE" << endl;
                return false;
            }
            else if (!eatExpress.findPedido(p1->getInfo())->isRequisitado() && eatExpress.findPedido(p2->getInfo())->isRequisitado()) {
                cout << "TRUE" << endl;
                return true;
            }
            else {
                if (graph.getDist(estafeta_ativo->getPos(), p1->getInfo()) > graph.getDist(estafeta_ativo->getPos(), p2->getInfo())) {
                    cout << "TRUE" << endl;
                    return true;
                }
                else {
                    cout << "FALSE" << endl;
                    return false;
                }
            }
        }
        else if (p1->getType() == 2 && p2->getType() == 1) {    //1 restaurante - 1 cliente
            if (eatExpress.findPedido(p1->getInfo()) == eatExpress.findPedido(p2->getInfo())) {
                cout << "FALSE" << endl;
                //eatExpress.findPedido(p1->getInfo())->setRequisitado(true);
                return false;
            }
            else {
                if (graph.getDist(estafeta_ativo->getPos(), p1->getInfo()) > graph.getDist(estafeta_ativo->getPos(), p2->getInfo())) {
                    cout << "TRUE" << endl;
                    return true;
                }
                else {
                    cout << "FALSE" << endl;
                    return false;
                }
            }
        }
        else if (p1->getType() == 1 && p2->getType() == 2) {    //1 cliente - 1 restaurante
            if (eatExpress.findPedido(p1->getInfo()) == eatExpress.findPedido(p2->getInfo())) {
                cout << "TRUE" << endl;
                return true;
            }
            else {
                if (graph.getDist(estafeta_ativo->getPos(), p1->getInfo()) > graph.getDist(estafeta_ativo->getPos(), p2->getInfo())) {
                    cout << "TRUE" << endl;
                    return true;
                }
                else {
                    cout << "FALSE" << endl;            // MUDAR ESTE TALVEZ
                    return false;
                }
            }
        }
        cout << "FALSE" << endl;
        return false;
    }
};

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
        cout << "\nEstafeta que vai atender os pedidos: ";
        cin.clear();
        cin >> n_estafeta;
        cin.ignore(1000, '\n');
    } while(n_estafeta < 1 || n_estafeta > eatExpress.getNumEstafetas());
    Estafeta<T>* estafeta = eatExpress.getEstafetas().at(n_estafeta-1);

    // JA TEMOS A LISTA DE PEDIDOS E O ESTAFETA, AGORA É IMPLEMENTAR O ALGORITMO - CHAMAR AQUI E FAZER EM FUNÇÃO DIFERENTE

    /*eatExpress.setPedidos(pedidos); //USING NEARESTNEIGHBOR
    for (Pedido<T>* pedido : eatExpress.getPedidos()) {
        pedido->setEstafeta(estafeta);
        pedido->setRequisitado(false);
        cout<<pedido->getCliente()->getNome()<<" - "<<pedido->getRestaurante()->getNome()<<endl;
    }
    vector<Vertex<T>*> percurso = graph.NearestNeighborFloyd(estafeta->getPos());
    showPathGV(percurso);*/

    estafeta_ativo = estafeta;
    for (Pedido<T>* pedido : eatExpress.getPedidos()) {
        pedido->setEstafeta(estafeta);
        pedido->setRequisitado(false);
    }
    eatExpress.setPedidos(pedidos);

    //graph.floydWarshallShortestPath();

    // DE OUTRA MANEIRA
    vector<T> restaurantes;
    vector<T> clientes;
    vector<Vertex<T>*> result;

    for (Pedido<T>* pedido : pedidos) {
        restaurantes.push_back(pedido->getRestaurante()->getMorada());
    }

    T restaurante_mais_proximo, menor;

    while (!restaurantes.empty() || !clientes.empty()) {
        if (!restaurantes.empty()) {
            restaurante_mais_proximo = getRestauranteProximo<T>(restaurantes);
        }
        if (result.empty()) {
            result.push_back(graph.findVertex(restaurante_mais_proximo));
            apagar(restaurante_mais_proximo, restaurantes);
            T cliente_do_restaurante = eatExpress.findPedido(restaurante_mais_proximo)->getCliente()->getMorada();
            clientes.push_back(cliente_do_restaurante);
        }
        else {
            if (!restaurantes.empty())
                menor = restaurante_mais_proximo;
            else
                menor = clientes[0];
            for (T client : clientes) {
                if (graph.getDist(estafeta_ativo->getPos(), client) < graph.getDist(estafeta_ativo->getPos(), menor)) {
                    menor = client;
                }
            }
            if (menor == restaurante_mais_proximo) {
                apagar(menor, restaurantes);
                T cliente_do_restaurante = eatExpress.findPedido(restaurante_mais_proximo)->getCliente()->getMorada();
                clientes.push_back(cliente_do_restaurante);
            }
            else {
                apagar(menor, clientes);
            }
            result.push_back(graph.findVertex(menor));
        }
    }

    vector<Vertex<T>*> percurso;

    T init = result[0]->getInfo();
    T final;
    graph.dijkstraShortestPath(estafeta->getPos());
    vector<Vertex<T>*> vetor = graph.getPath(estafeta->getPos(), init);
    percurso.insert(percurso.end(), vetor.begin(), vetor.end() - 1);
    cout << "\nVERTEX: " << result[0]->getLatitude() << ", " << result[0]->getLongitude() << endl;
    bool inicio = true;
    for (Vertex<T>* vertex : result) {
        if (inicio) {
            inicio = false;
            continue;
        }
        cout << "VERTEX: " << vertex->getLatitude() << ", " << vertex->getLongitude() << endl;
        final = vertex->getInfo();
        graph.dijkstraShortestPath(init);
        vetor = graph.getPath(init, final);
        percurso.insert(percurso.end(), vetor.begin(), vetor.end() - 1);
        init = final;
    }

    percurso.push_back(graph.findVertex(final));

    //system("pause");

    // ----------------

    // COM FILA DE PRIORIDADE
    /*priority_queue<Vertex<T>*, vector<Vertex<T>*>, Compare<T>> Q;

    for (Pedido<T>* pedido : eatExpress.getPedidos()) {
        if (!pedido->getRestaurante()->RestauranteJaPedido()) {
            Q.push(graph.findVertex(pedido->getRestaurante()->getMorada()));
            pedido->getRestaurante()->setJaPedido(true);
        }
    }
    for (Pedido<T>* pedido : eatExpress.getPedidos()) {
        Q.push(graph.findVertex(pedido->getCliente()->getMorada()));
        pedido->getRestaurante()->setJaPedido(false);
    }*/

    //MOSTRAR Q
    //while (!Q.empty()) {
        //Vertex<T>* vert = Q.top();
        //cout << "VERTEX: " << vert->getLatitude() << ", " << vert->getLongitude() << endl;
        //Q.pop();
    //}
    //system("pause");

    /*vector<Vertex<T>*> percurso;
    Vertex<T>* vert = Q.top();
    Q.pop();
    cout << "VERTEX: " << vert->getLatitude() << ", " << vert->getLongitude() << endl;
    T init = vert->getInfo();
    T final;
    graph.dijkstraShortestPath(estafeta->getPos());
    vector<Vertex<T>*> vetor = graph.getPath(estafeta->getPos(), init);
    percurso.insert(percurso.end(), vetor.begin(), vetor.end() - 1);
    while (!Q.empty()) {
        //estafeta->setPos(init);
        vert = Q.top();
        cout << "VERTEX: " << vert->getLatitude() << ", " << vert->getLongitude() << endl;
        Q.pop();
        final = vert->getInfo();
        graph.dijkstraShortestPath(init);
        vetor = graph.getPath(init, final);
        percurso.insert(percurso.end(), vetor.begin(), vetor.end() - 1);
        init = final;
    }*/

    //percurso.push_back(graph.findVertex(final));    // Coloca o vertex final

    /*for (Vertex<T>* vertex : percurso) {
        cout << "VERTEX: " << vertex->getLatitude() << ", " << vertex->getLongitude() << endl;
    }*/

    //vector<Vertex<T>*> caminho= graph.NearestNeighborFloyd(estafeta->getPos());

    for (Pedido<T>* pedido : eatExpress.getPedidos()) {
        pedido->setEstafeta(estafeta);
    }

    showPathGV(percurso);

    char sair = Sair_Programa();
    if (sair == 'N' || sair == 'n')
        Menu_Principal();
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

    //atribuirEstafeta(pedidos);
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
