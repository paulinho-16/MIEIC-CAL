#ifndef CAL_FP05_ALGORITMOS_H
#define CAL_FP05_ALGORITMOS_H

#include "Conetividade.h"

extern EatExpress<int> eatExpress;
extern Graph<int> graph;

Estafeta<int>* estafeta_ativo;

void Menu_Principal();
char Sair_Programa();


template <class T>       // Algoritmo usado na fase 1 - Um único pedido para um único estafeta
vector<Vertex<T>*> algFase1(Pedido<T>* pedido) {
    graph.dijkstraShortestPath(pedido->getEstafeta()->getPos());
    vector<Vertex<T>*> estafeta_restaurante = graph.getPath(pedido->getEstafeta()->getPos(), pedido->getRestaurante()->getMorada());    // Contém o caminho mais curto entre a posição do estafeta e o restaurante
    graph.dijkstraShortestPath(pedido->getRestaurante()->getMorada());
    vector<Vertex<T>*> restaurante_cliente = graph.getPath(pedido->getRestaurante()->getMorada(), pedido->getCliente()->getMorada());   // Contém o caminho mais curto entre o restaurante e o cliente

    restaurante_cliente.erase(restaurante_cliente.begin());     // Remove um vertex repetido (o restaurante)
    estafeta_restaurante.insert(estafeta_restaurante.end(), restaurante_cliente.begin(), restaurante_cliente.end());    // Une os dois vetores, pelo que estafeta_restaurante conterá o percurso mais curto

    cout << "\n Percurso Completo: " << endl << endl;
    for (Vertex<T>* vertex : estafeta_restaurante) {
        cout << "Vertex " << vertex->getInfo() << " com POS (" << vertex->getLatitude() << ", " << vertex->getLongitude() << ")"<<endl;
    }
    return estafeta_restaurante;
}

template<class T>       // Algoritmo utilizado na Fase 2 - Um único estafeta atende vários pedidos
vector<Vertex<T>*> algFase2(Estafeta<T> *estafeta, vector<Pedido<T>*> pedidos) {
    vector<T> restaurantes;     // Este vetor vai conter os restaurantes para os quais o estafeta se pode dirigir (é inicializado com todos os restaurantes que estão nos pedidos)
    vector<T> clientes;         // Este vetor vai conter os clientes para os quais o estafeta se pode dirigir, isto é, aqueles que o estafeta já requisitou o pedido no restaurante que eles pediram (é vazio inicialmente)
    vector<Vertex<T>*> result;  // Este vetor vai conter os pontos de interesse pela ordem em que o estafeta os vai percorrer (restaurantes e clientes)

    // -------------------------------------------- Algoritmo de cálculo do vetor ordenado dos pontos de interesse percorridos pelo estafeta --------------------------------------------

    // Inicializa o vetor restaurantes com todos os restaurantes que estão presentes nos pedidos
    for (Pedido<T>* pedido : pedidos) {
        restaurantes.push_back(pedido->getRestaurante()->getMorada());
    }

    T restaurante_mais_proximo, menor;      // restaurante_mais_proximo contém o restaurante mais próximo do estafeta a cada momento, e menor contém o ponto mais próximo do estafeta a qualquer momento, podendo ser um restaurante ou um cliente

    // Organiza um vetor, de modo a tornar-se o percurso mais curto, e a garantir que o estafeta passa primeiro pelo restaurante X antes de entregar o pedido ao Cliente X
    while (!restaurantes.empty() || !clientes.empty()) {
        if (!restaurantes.empty()) {    // Enquanto o vetor restaurantes não estiver vazio, vamos buscar o restaurante mais próximo do estafeta
            restaurante_mais_proximo = getRestauranteProximo<T>(restaurantes);
        }
        if (result.empty()) {       // Na primeira iteração (result não tem nenhum vertex ainda), adicionamos ao result o restaurante mais próximo do estafeta - é o primeiro ponto por onde vai passar
            result.push_back(graph.findVertex(restaurante_mais_proximo));
            apagar(restaurante_mais_proximo, restaurantes);     // Após adicioná-lo ao result, podemos removê-lo do vetor restaurantes
            T cliente_do_restaurante = eatExpress.findPedido(restaurante_mais_proximo)->getCliente()->getMorada();
            clientes.push_back(cliente_do_restaurante);     // Uma vez que já requisitamos o pedido desse restaurante, podemos adicionar ao vetor clientes o cliente que efetuou esse pedido (o estafeta já pode passar por ele, pois já requisitou o seu pedido)
        }
        else {      // Nas restantes iterações
            if (!restaurantes.empty())      // Enquanto houver restaurantes no vetor, menor ficará com o valor inicial do restaurante que se encontra mais próximo do estafeta
                menor = restaurante_mais_proximo;
            else
                menor = clientes[0];        // Se o estafeta já tiver passado por todos os restaurantes, menor fica com o valor inicial do primeiro elemento da lista dos clientes
            for (T client : clientes) {
                if (graph.getDist(/*estafeta_ativo->getPos()*/result.back()->getInfo(), client) < graph.getDist(/*estafeta_ativo->getPos()*/result.back()->getInfo(), menor)) {
                    menor = client;                 // O valor de menor é alterado sempre que é encontrado um cliente mais próximo do estafeta
                }
            }
            // Neste ponto, menor tem o ponto de interesse mais próximo do estafeta, pode corresponder a um restaurante ou cliente
            if (menor == restaurante_mais_proximo) {    // No caso de menor corresponder a um restaurante, eliminamos o restaurante da lista de restaurantes, e adicionamos o cliente que pediu esse restaurante à lista de clientes
                apagar(menor, restaurantes);
                T cliente_do_restaurante = eatExpress.findPedido(restaurante_mais_proximo)->getCliente()->getMorada();
                clientes.push_back(cliente_do_restaurante);
            }
            else {      // No caso de menor corresponder a um cliente, retiramos esse cliente da lista de clientes
                apagar(menor, clientes);
            }
            result.push_back(graph.findVertex(menor));      // Por fim, adicionamos ao result o valor de menor
        }
    }

    // -------------------------------------------- Fim do Algoritmo --------------------------------------------

    vector<Vertex<T>*> percurso;        // Vai conter o percurso completo do estafeta

    // Após termos o vetor ordenado de pontos de interesse por onde o estafeta vai ter de passar (result), resta encontrar os menores percursos entre cada par desses pontos
    T init = result[0]->getInfo();
    T final;
    graph.dijkstraShortestPath(estafeta->getPos());
    vector<Vertex<T>*> vetor = graph.getPath(estafeta->getPos(), init);
    percurso.insert(percurso.end(), vetor.begin(), vetor.end() - 1);
    bool inicio = true;
    for (Vertex<T>* vertex : result) {
        if (inicio) {
            inicio = false;
            continue;
        }
        final = vertex->getInfo();
        graph.dijkstraShortestPath(init);
        vetor = graph.getPath(init, final);
        percurso.insert(percurso.end(), vetor.begin(), vetor.end() - 1);
        init = final;
    }

    percurso.push_back(graph.findVertex(final));

    // Apresenta na consola o percurso efetuado
    /*cout << "\n Percurso Completo: \n\n";
    for (Vertex<T>* vertex : percurso) {
        cout << "Vertex " << vertex->getInfo() << " com POS (" << vertex->getLatitude() << ", " << vertex->getLongitude() << ")"<<endl;
    }*/

    return percurso;
}

template<class T>       // Algoritmo utilizado na Fase 4 - Vários estafetas atendem vários pedidos, considerando carga (limite de pedidos)
vector<Vertex<T>*> algFase4(Estafeta<T> *estafeta, vector<Pedido<T>*> pedidos) {
    vector<T> restaurantes;       // Este vetor vai conter os restaurantes para os quais o estafeta se pode dirigir (é inicializado com todos os restaurantes que estão nos pedidos)
    vector<T> clientes;           // Este vetor vai conter os clientes para os quais o estafeta se pode dirigir, isto é, aqueles que o estafeta já requisitou o pedido no restaurante que eles pediram (é vazio inicialmente)
    vector<Vertex<T> *> result;  // Este vetor vai conter os pontos de interesse pela ordem em que o estafeta os vai percorrer (restaurantes e clientes)

    // -------------------------------------------- Algoritmo de cálculo do vetor ordenado dos pontos de interesse percorridos pelo estafeta --------------------------------------------

    // Inicializa o vetor restaurantes com todos os restaurantes que estão presentes nos pedidos
    for (Pedido<T> *pedido : pedidos) {
        restaurantes.push_back(pedido->getRestaurante()->getMorada());
    }

    T restaurante_mais_proximo, menor;      // restaurante_mais_proximo contém o restaurante mais próximo do estafeta a cada momento, e menor contém o ponto mais próximo do estafeta a qualquer momento, podendo ser um restaurante ou um cliente

    // Organiza um vetor, de modo a tornar-se o percurso mais curto, e a garantir que o estafeta passa primeiro pelo restaurante X antes de entregar o pedido ao Cliente X
    int capacidade_atual_estafeta = estafeta->getTransporte().getCapacidade();      // Vai conter a capacidade restante do estafeta em cada momento
    while (!restaurantes.empty() || !clientes.empty()) {
        if (!restaurantes.empty()) {    // Enquanto o vetor restaurantes não estiver vazio, vamos buscar o restaurante mais próximo do estafeta
            restaurante_mais_proximo = getRestauranteProximo<T>(restaurantes);
        }
        if (result.empty()) {       // Na primeira iteração (result não tem nenhum vertex ainda), adicionamos ao result o restaurante mais próximo do estafeta - é o primeiro ponto por onde vai passar
            result.push_back(graph.findVertex(restaurante_mais_proximo));
            apagar(restaurante_mais_proximo, restaurantes);     // Após adicioná-lo ao result, podemos removê-lo do vetor restaurantes
            capacidade_atual_estafeta--;    // Como o estafeta possui agora um pedido requisitado mas não entregue, substraímos 1 à sua capacidade atual
            T cliente_do_restaurante = eatExpress.findPedido(restaurante_mais_proximo)->getCliente()->getMorada();
            clientes.push_back(cliente_do_restaurante);     // Uma vez que já requisitamos o pedido desse restaurante, podemos adicionar ao vetor clientes o cliente que efetuou esse pedido (o estafeta já pode passar por ele, pois já requisitou o seu pedido)
        } else {      // Nas restantes iterações
            if (!restaurantes.empty() && capacidade_atual_estafeta > 0)      // Enquanto houver restaurantes no vetor, menor ficará com o valor inicial do restaurante que se encontra mais próximo do estafeta
                menor = restaurante_mais_proximo;       // Só poderá ter o valor do seguinte restaurante mais próximo se ainda tiver capacidade para o pedido
            else
                menor = clientes[0];        // Se o estafeta já tiver passado por todos os restaurantes, ou se não tiver mais capacidade para se dirigir a outro restaurante, menor fica com o valor inicial do primeiro elemento da lista dos clientes
            for (T client : clientes) {
                if (graph.getDist(/*estafeta_ativo->getPos()*/result.back()->getInfo(), client) <
                    graph.getDist(/*estafeta_ativo->getPos()*/result.back()->getInfo(), menor)) {
                    menor = client;                 // O valor de menor é alterado sempre que é encontrado um cliente mais próximo do estafeta
                }
            }
            // Neste ponto, menor tem o ponto de interesse mais próximo do estafeta, pode corresponder a um restaurante ou cliente
            if (menor == restaurante_mais_proximo) {    // No caso de menor corresponder a um restaurante, eliminamos o restaurante da lista de restaurantes, e adicionamos o cliente que pediu esse restaurante à lista de clientes
                apagar(menor, restaurantes);
                capacidade_atual_estafeta--;
                T cliente_do_restaurante = eatExpress.findPedido(restaurante_mais_proximo)->getCliente()->getMorada();
                clientes.push_back(cliente_do_restaurante);
            } else {      // No caso de menor corresponder a um cliente, retiramos esse cliente da lista de clientes
                apagar(menor, clientes);
                capacidade_atual_estafeta++;
            }
            result.push_back(graph.findVertex(menor));      // Por fim, adicionamos ao result o valor de menor
        }
    }

    // -------------------------------------------- Fim do Algoritmo --------------------------------------------

    vector<Vertex<T> *> percurso;        // Vai conter o percurso completo do estafeta

    T init = result[0]->getInfo();
    T final;
    graph.dijkstraShortestPath(estafeta->getPos());
    vector<Vertex<T> *> vetor = graph.getPath(estafeta->getPos(), init);
    percurso.insert(percurso.end(), vetor.begin(), vetor.end() - 1);
    bool inicio = true;
    for (Vertex<T> *vertex : result) {
        if (inicio) {
            inicio = false;
            continue;
        }
        final = vertex->getInfo();
        graph.dijkstraShortestPath(init);
        vetor = graph.getPath(init, final);
        percurso.insert(percurso.end(), vetor.begin(), vetor.end() - 1);
        init = final;
    }

    percurso.push_back(graph.findVertex(final));

    // Apresenta na consola o percurso efetuado
    cout << "\n Percurso Completo: \n\n";
    for (Vertex<T> *vertex : percurso) {
        cout << "Vertex " << vertex->getInfo() << " com POS (" << vertex->getLatitude() << ", "
             << vertex->getLongitude() << ")" << endl;
    }

    return percurso;
}



template <class T>      // Fase 1 - Um único estafeta um único pedido
void Um_Estafeta_Um_Pedido() {      // Fase 1 - Um único pedido para um único estafeta
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

    //VERIFICAR SE HÁ CAMINHO:

    Vertex<T>* v_estafeta=graph.findVertex(estafeta->getPos());
    Vertex<T>* v_restaurante=graph.findVertex(restaurante->getMorada());
    Vertex<T>* v_cliente=graph.findVertex(cliente->getMorada());

    vector<Vertex<T>*> caminho_conexo = dfs(&graph,v_estafeta);

    if(!isIn(v_restaurante,caminho_conexo) || !isIn(v_cliente,caminho_conexo)){
        cout<<"Lamentamos, nao ha caminho para efetuar esse pedido."<<endl;
        return;
    }
    else{
        cout<<"Encontramos um caminho!"<<endl;
        vector<Vertex<T>*> percurso = algFase1(pedido);     // Obtém o percurso completo do estafeta
        showPathGV(percurso);       // Mostra o percurso do estafeta no grafo
    }

    char sair = Sair_Programa();
    if (sair == 'N' || sair == 'n')
        Menu_Principal();
}

template <class T>      // Fase 2 - Um único estafeta atende vários pedidos
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

    estafeta_ativo = estafeta;
    for (Pedido<T>* pedido : eatExpress.getPedidos()) {
        pedido->setEstafeta(estafeta);
        pedido->setRequisitado(false);

        Vertex<T>* v_estafeta=graph.findVertex(pedido->getEstafeta()->getPos());
        Vertex<T>* v_restaurante=graph.findVertex(pedido->getRestaurante()->getMorada());
        Vertex<T>* v_cliente=graph.findVertex(pedido->getCliente()->getMorada());

        vector<Vertex<T>*> caminho_conexo = dfs(&graph,v_estafeta);

        if(!isIn(v_restaurante,caminho_conexo) || !isIn(v_cliente,caminho_conexo)){
            cout<<"Lamentamos, nao há caminho para efetuar estes pedidos!"<<endl;
            return;
        }
    }
    eatExpress.setPedidos(pedidos);

    //graph.floydWarshallShortestPath();

    // DE OUTRA MANEIRA __________________________________________________________________________________________________

    vector<Vertex<T>*> percurso=algFase2(estafeta,pedidos);

    // ________________________________________________________________________________________________________________________

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

template <class T>      // Fase 3 - Vários estafetas atendem vários pedidos, sem considerar carga (limite de pedidos)
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

    int ee=1;
    cout<<endl<<"Estafetas a atender os pedidos:"<<endl;
    for(Estafeta<T>* estafeta: eatExpress.getEstafetas()){
        cout << ee << " -> " << estafeta->getNome() <<endl;
        ee++;
    }
    // JA TEMOS A LISTA DE PEDIDOS, AGORA É IMPLEMENTAR O ALGORITMO, OS ESTAFETAS SÃO ESCOLHIDOS POR UM CRITERIO - CHAMAR AQUI E FAZER EM FUNÇÃO DIFERENTE

    vector<Vertex<T>*> percurso;        // Armazena o percurso de cada estafeta
    vector<vector<Vertex<T>*>> percursos;       // Lista dos percursos dos vários estafetas
    vector<Pedido<T>*> pedidos_impossiveis;

    // Atribuição dos estafetas aos pedidos - Critério de Seleção: Estafeta que estiver mais perto do restaurante do pedido
    for(Pedido<T>* pedido : pedidos) {
        atribuirEstafeta(pedido);
        pedido->setRequisitado(false);

        //Verificar se existe caminho com uma pesquisa em profundidade:
        Vertex<T>* v_estafeta=graph.findVertex(pedido->getEstafeta()->getPos());
        Vertex<T>* v_restaurante=graph.findVertex(pedido->getRestaurante()->getMorada());
        Vertex<T>* v_cliente=graph.findVertex(pedido->getCliente()->getMorada());
        vector<Vertex<T>*> caminho_conexo = dfs(&graph,v_estafeta);
        if(!isIn(v_restaurante,caminho_conexo) || !isIn(v_cliente,caminho_conexo)){
            pedidos_impossiveis.push_back(pedido);
        }
    }

    if(pedidos_impossiveis.size()!=0)
        cout<<"\nLamentamos, existem "<<pedidos_impossiveis.size()<<" pedidos que nao podem ser efetuados"<<endl;
    for(Pedido<T>* ped : pedidos_impossiveis){
        apagarPedido(ped,pedidos);
    }

    eatExpress.setPedidos(pedidos);

    // Calcular o percurso de cada estafeta
    for(Estafeta<T>* estafeta: eatExpress.getEstafetas()) {
        int num_pedidos = 0;

        // Calcula o número de pedidos do estafeta
        for(Pedido<T>* pedido:eatExpress.getPedidos()){
            if(pedido->getEstafeta()==estafeta){
                num_pedidos+=1;
            }
        }

        cout<<endl<<estafeta->getNome()<<" tem "<<num_pedidos<<" pedidos"<<endl;    //para ver quantos pedidos vai atender cada estafeta

        // No caso de ter mais do que um só pedido
        if (num_pedidos > 1) {
            vector<Pedido<T>*> pedidos;
            for(Pedido<T>* ped : eatExpress.getPedidos()) {
                if(ped->getEstafeta()==estafeta){
                    pedidos.push_back(ped);
                }
            }
            estafeta_ativo = estafeta;
            percurso = algFase2(estafeta,pedidos);
            percursos.push_back(percurso);
        }
        // No caso de ter um único pedido
        else if(num_pedidos == 1) {
            Pedido<T>* pedido;
            for(Pedido<T>* ped:eatExpress.getPedidos()){
                if(ped->getEstafeta()==estafeta){
                    pedido=ped;
                }
            }
            estafeta_ativo = estafeta;
            percurso = algFase1(pedido);
            percursos.push_back(percurso);
        }
    }

    showMultiplePathsGV(percursos);

    char sair = Sair_Programa();
    if (sair == 'N' || sair == 'n')
        Menu_Principal();
}

template <class T>      // Fase 4 - Vários estafetas atendem vários pedidos, agora considerando carga (limite de pedidos)
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

    vector<Vertex<T>*> percurso;        // Armazena o percurso de cada estafeta
    vector<vector<Vertex<T>*>> percursos;       // Lista dos percursos dos vários estafetas
    vector<Pedido<T>*> pedidos_impossiveis;

    // Atribuição dos estafetas aos pedidos - Critério de Seleção: Estafeta que estiver mais perto do restaurante do pedido

    for(Pedido<T>* pedido : pedidos) {
        atribuirEstafeta(pedido);
        pedido->setRequisitado(false);

        //Verificar se existe caminho com uma pesquisa em profundidade:
        Vertex<T>* v_estafeta=graph.findVertex(pedido->getEstafeta()->getPos());
        Vertex<T>* v_restaurante=graph.findVertex(pedido->getRestaurante()->getMorada());
        Vertex<T>* v_cliente=graph.findVertex(pedido->getCliente()->getMorada());
        vector<Vertex<T>*> caminho_conexo = dfs(&graph,v_estafeta);
        if(!isIn(v_restaurante,caminho_conexo) || !isIn(v_cliente,caminho_conexo)){
            pedidos_impossiveis.push_back(pedido);
        }
    }

    if(pedidos_impossiveis.size()!=0)
        cout<<"\nLamentamos, existem "<<pedidos_impossiveis.size()<<" pedidos que nao podem ser efetuados"<<endl;
    for(Pedido<T>* ped : pedidos_impossiveis){
        apagarPedido(ped,pedidos);
    }

    eatExpress.setPedidos(pedidos);

    // Calcular o percurso de cada estafeta
    for(Estafeta<T>* estafeta: eatExpress.getEstafetas()) {
        int num_pedidos = 0;

        // Calcula o número de pedidos do estafeta
        for(Pedido<T>* pedido:eatExpress.getPedidos()){
            if(pedido->getEstafeta()==estafeta){
                num_pedidos+=1;
            }
        }

        cout<<endl<<estafeta->getNome()<<" tem "<<num_pedidos<<" pedidos"<<endl;    //para ver quantos pedidos vai atender cada estafeta

        // No caso de ter mais do que um só pedido
        if (num_pedidos > 1) {
            vector<Pedido<T>*> pedidos;
            for(Pedido<T>* ped : eatExpress.getPedidos()) {
                if(ped->getEstafeta()==estafeta){
                    pedidos.push_back(ped);
                }
            }
            estafeta_ativo = estafeta;
            percurso = algFase4(estafeta,pedidos);
            percursos.push_back(percurso);
        }
            // No caso de ter um único pedido
        else if(num_pedidos == 1) {
            Pedido<T>* pedido;
            for(Pedido<T>* ped:eatExpress.getPedidos()){
                if(ped->getEstafeta()==estafeta){
                    pedido=ped;
                }
            }
            estafeta_ativo = estafeta;
            percurso = algFase1(pedido);
            percursos.push_back(percurso);
        }
    }

    showMultiplePathsGV(percursos);

    char sair = Sair_Programa();
    if (sair == 'N' || sair == 'n')
        Menu_Principal();
}



#endif //CAL_FP05_ALGORITMOS_H
