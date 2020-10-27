/**
 * Detecção e tratamento de deadlocks usando Grafos.
*/
#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
vector<vi> AdjList;  // Lista de adjacencia para o grafo
#define N 20 // Quantidade de trechos/recursos
vi color;
#define BLACK 1
#define GRAY 0
#define WHITE -1

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

int main() {
    srand (time(NULL));

    int M = rand() % 10 + 2; // M processos - solicitações

    AdjList.assign(M, vi());
    selectResources(M);
    cout << detectCycle(M) << endl;
    return 0;
}