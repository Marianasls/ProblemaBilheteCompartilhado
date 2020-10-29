/**
 * Detecção e tratamento de deadlocks usando Grafos.
*/
#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
vector<vi> AdjList;  // Lista de adjacencias para o grafo
#define N 20 // Quantidade de trechos/recursos
vi color;
#define BLACK 1
#define GRAY 0
#define WHITE -1

int mapaVetoresEmpresaX[4][4] = {
    {0, 0 , 1, 1},//cidade A empresa x
    {1, 0 , 1, 1},//cidade B empresa x
    {0, 1 , 0, 1},//cidade C empresa x
    {1, 1 , 1, 0},//cidade D empresa x
};
int mapaVetoresEmpresaY[4][4] = {
    {0, 0 , 0, 1},//cidade A empresa y
    {1, 0 , 1, 1},//cidade B empresa y
    {0, 1 , 0, 1},//cidade C empresa y
    {1, 1 , 1, 0},//cidade D empresa y
};
/**
 * Checa se um grafo direcionado possui ciclos.
 * 
 * @return booleano true se houver ciclo, false caso não.
*/
bool dfs(int u, int parent=-1){
    color[u] = GRAY;
    
    for (int j = 0; j < (int)AdjList[u].size(); j++){
        int v = AdjList[u][j];
    
        if(color[v] == GRAY) 
            return true;
        
        if(color[v] == WHITE && dfs(v, u)) 
            return true;
    }
    color[u] = BLACK;
    return false;
}

/**
 * Procura em todos os vertices do grafo ainda não visitados e chama a função dfs()
 * para detectar ciclos.
 * @return bool true se houver ciclo, false caso não.
*/
bool detectCycle(int n) {
    color.assign(n, WHITE);
    for(int i=0; i<n; i++){
        if(color[i] == WHITE && dfs(i)) 
            return true;
    }
    return false;
}

/**
 * Gera um grafo com numero de processos e recursos requeridos para cada processo de forma aleatoria
 * com um limite de M quantidade de processos e N quantidade de recursos/trechos.
 * 
 * @param M quantidade de processos.
*/
void selectResources(int M){

    for(int i=0; i<M; i++) {
        int s = rand() % N; 
        int t = rand() % N + 1; // n quantidade de recursos(trechos) requeridos pelo processo i
        for(int j=s; j<t; j++) {
            cout << "Pessoa " << i+1 << " solicitou o trecho " << j+1 << endl;
            AdjList[i].push_back(j);
        }
    }
}

void reservar(int vetores[4][4], int partida, int destino, vector<int>* possibilidades){

    if( vetores[partida][destino] == 1){
        vetores[partida][destino]--;//bloqueando o trajeto
        possibilidades->push_back(partida);
        return;
    }
}

vector<int> buscaEmLargura(int vetores[4][4] , int partida, int destino){

    vector<int> possibilidades;
    reservar(vetores, partida, destino, &possibilidades); //testa se ja é possivel ir diretamente
    for (size_t i = 0; i < 4; i++)
    {
        if ( vetores[partida][i] == 1){// se existe uma passagem para essa cidade
            reservar(vetores, i, destino, &possibilidades);//testa se é possivel chegar ao destino
        }
    }

    return possibilidades;
}

void comprarBilhete( int partida, int destino){

    cout << "possibilidades de trajeto na empresa X" << endl;
    vector<int> possibilidades = buscaEmLargura(mapaVetoresEmpresaX, partida, destino );
    for (size_t i = 0; i < possibilidades.size(); i++){
        cout << possibilidades[i] << endl;
    }
    
}

int main() {
    srand (time(NULL));
    comprarBilhete(0,3);
    return 0;
}