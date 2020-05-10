
#include "utils.h"


void readMap(string directory) {
    string nodes_path = directory + "/nodes.txt";
    string edges_path = directory + "/edges.txt";
    readNodes<int>(nodes_path);
    readEdges<int>(edges_path);
}

template <class T>
void readNodes(string file_directory) {
    ifstream ler;
    string number;
    string tuple;
    ler.open(file_directory);
    getline(ler, number);
    int n = stoi(number);
    for (unsigned int i = 0 ; i < n ; i++) {
        getline(ler, tuple);
        tuple = tuple.substr(1, tuple.size() - 2);

        stringstream ss(tuple);
        string id, latitude, longitude;
        getline(ss, id, ',');
        getline(ss, latitude, ',');
        getline(ss, longitude, ',');
        Vertex<T>* vertex = new Vertex<T>(stoi(id), stof(latitude), stof(longitude));
        graph.addVertex(vertex);
    }
    cout << "Vertex Lidos: " << graph.getNumVertex() << endl;
   // graph.printVertexs();
    ler.close();
}

template <class T>
Vertex<T>* readNode(string tuple) {
    tuple = tuple.substr(1, tuple.size() - 2);
    stringstream ss(tuple);
    string id, latitude, longitude;
    getline(ss, id, ',');
    getline(ss, latitude, ',');
    getline(ss, longitude, ',');
    auto* vertex = new Vertex<T>(stoi(id), stof(latitude), stof(longitude));
    return vertex;
}

template <class T>
void readEdges(string file_directory) {
    ifstream ler;
    string number;
    string tuple;
    ler.open(file_directory);
    getline(ler, number);
    int n = stoi(number);
    for (unsigned int i = 0 ; i < n ; i++) {
        getline(ler, tuple);
        tuple = tuple.substr(1, tuple.size() - 2);

        stringstream ss(tuple);
        string id1, id2;
        getline(ss, id1, ',');
        getline(ss, id2, ',');
        graph.addEdge(stoi(id1), stoi(id2));
    }
    cout << "Edge Lidos: " << graph.getNumEdges() << endl;
   // graph.printEdges();
    ler.close();
}

template <class T>
void readTags(string file_directory) {

}

void Visualizar_Mapa() {
    GraphViewer *gv = new GraphViewer(600, 600, false);
    gv->createWindow(600, 600);
    gv->defineVertexColor("blue");
    gv->defineEdgeColor("black");
    for (Vertex<int>* vertex : graph.getVertexSet()) {
        gv->addNode(vertex->getInfo(), vertex->getLatitude(), vertex->getLongitude());
    }
    int edgeID = 0;
    for (Vertex<int>* vertex : graph.getVertexSet()) {
        for (Edge<int> edge : vertex->getAdj()) {
            gv->addEdge(edgeID,vertex->getInfo(), edge.getDest()->getInfo(), EdgeType::DIRECTED);
            edgeID++;
        }
    }
    gv->rearrange();
}

template <class T>
vector<Cliente<T>*> recolher_info_clientes(){
    ifstream ler;
    ler.open("files/clientes.txt");
    vector<Cliente<T>*> clientes;
    while(!ler.eof()) {
        string clientenome,clientenif,clientemorada;
        char c;
        ler>>clientenome>>c>>clientenif>>c>>clientemorada;
        Cliente<T> cliente;
        cliente.setNome(clientenome);
        cliente.setNif(clientenif);
        Vertex<T>* morada = graph.findVertex(stoi(clientemorada));
        cliente.setMorada(morada);
        clientes.push_back(cliente);
    }
    return clientes;
}

template <class T>
vector<Restaurante<T>*> recolher_info_restaurantes(){
    ifstream ler;
    ler.open("files/restaurantes.txt");
    vector<Restaurante<T>*> restaurantes;
    while(!ler.eof()) {
        string restaurantenome,restaurantemorada;
        char c;
        ler>>restaurantenome>>c>>restaurantemorada;
        Restaurante<T> res;
        res.setNome(restaurantenome);
        Vertex<T>* morada = graph.findVertex(stoi(restaurantemorada));
        res.setMorada(morada);
        restaurantes.push_back(res);
    }
    return restaurantes;
}

template <class T>
vector<Estafeta<T>*> recolher_info_estafetas(){
    ifstream ler;
    ler.open("files/estafetas.txt");
    vector<Estafeta<T>*> estafetas;
    while(!ler.eof()) {
        string estafetanome,estafetanif,estafetamorada,estafetatransporte;
        char c;
        ler>>estafetanome>>c>>estafetanif>>c>>estafetamorada>>c>>estafetatransporte;
        Estafeta<T> est;
        est.setNome(estafetanome);
        est.setNif(estafetanif);
        Vertex<T>* morada = graph.findVertex(stoi(estafetamorada));
        est.setMorada(morada);
        estafetas.push_back(est);
    }
    return estafetas;
}

template <class T>
void buildApp(){
    eatExpress.setClientes(recolher_info_clientes<T>());
    eatExpress.setRestaurantes(recolher_info_restaurantes<T>());
    eatExpress.setEstafetas(recolher_info_estafetas<T>());
    Vertex<T>* casa=graph.getVertexSet()[0];
    eatExpress.setCasaDosEstafetas(casa);

    //mudar cor dos vertices

    //Visualizar_Mapa();
}