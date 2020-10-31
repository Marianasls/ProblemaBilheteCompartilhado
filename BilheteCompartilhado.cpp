/**
 * Prevenção de deadlocks usando Grafos em situação simulada.
 * 
*/
#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
int mapaVetoresEmpresaX[4][4];
int mapaVetoresEmpresaY[4][4];

void leitura(char *name) {
    ifstream arquivo;
    arquivo.open(name);
    string result;
    while(arquivo.is_open()){
        for(int i=0; i<4; i++){
            getline(arquivo, result);
            for(int j=0; j<4; j++){
                mapaVetoresEmpresaX[i][j]=result[j]-'0';
            }
        }
        //linha em branco
        getline(arquivo, result);
        for(int i=0; i<4; i++){
            getline(arquivo, result);
            for(int j=0; j<4; j++){
                mapaVetoresEmpresaY[i][j]=result[j]-'0';
            }
        }
        arquivo.close();
    }
}

void reservar(int vetores[4][4], int partida, int destino, vector<int>&possibilidades){

    if( vetores[partida][destino] == 1){
        vetores[partida][destino]--;//bloqueando o trajeto
        possibilidades.push_back(partida);
        return;
    }
}

void buscaEmLargura(int vetores[4][4] , int partida, int destino, vector<int>&possibilidades){
    
    reservar(vetores, partida, destino, possibilidades); //testa se ja é possivel ir diretamente
    for (size_t i = 0; i < 4; i++){
        if ( vetores[partida][i] == 1){// se existe uma passagem para essa cidade
            reservar(vetores, i, destino, possibilidades);//testa se é possivel chegar ao destino
        }
    }
}

void compraBilhete( int partida, int destino, vector<int> &possibilidadesX, vector<int>&possibilidadesY){

    cout << "possibilidades de trajeto na empresa X" << endl;
    buscaEmLargura(mapaVetoresEmpresaX, partida, destino, possibilidadesX );
    for (size_t i = 0; i < possibilidadesX.size(); i++){
        //cout << "bilhete com parada na cidade " << &possibilidadesX[i] << endl;
        printf("bilhete com parada na cidade %d\n", possibilidadesX[i]);
    }
    cout << "possibilidades de trajeto na empresa Y" << endl;
    buscaEmLargura(mapaVetoresEmpresaY, partida, destino, possibilidadesY );
    for (size_t i = 0; i < possibilidadesY.size(); i++){
        //cout << "bilhete com parada na cidade " << &possibilidadesY[i] << endl;
        printf("bilhete com parada na cidade %d\n", possibilidadesX[i]);
    }
}

int main() {
    srand (time(NULL));
    char arq[]="input.txt";
    leitura(arq);
    vector<int> TrajetoMariana;
    vector<int> TrajetoAnderson;
    int partidaMariana = 0;
    int partidaAnderson = 1;
    int destinoMariana = 0;
    int destinoAnderson = 0;
    vector<int> ApossibilidadesX;
    vector<int> MpossibilidadesX;
    vector<int> ApossibilidadesY;
    vector<int> MpossibilidadesY;
    cout << "Mariana desejar comprar uma passagem da cidade 0 para a cidade 3\n";
    compraBilhete(partidaMariana , destinoMariana, MpossibilidadesX, MpossibilidadesY);
    cout << "Anderson desejar comprar uma passagem da cidade 0 para a cidade 3\n";
    compraBilhete(partidaAnderson , destinoAnderson, ApossibilidadesX, ApossibilidadesY);

    cout << "Mariana escolhe a primeira possibilidade de trajeto na empresa X\n";
    if(MpossibilidadesX.size() )TrajetoMariana.push_back(MpossibilidadesX[0]);
    
    cout << "Anderson escolhe a primeira possibilidade de trajeto na empresa Y\n";
    if(ApossibilidadesY.size() ) TrajetoAnderson.push_back(ApossibilidadesY[0]);

    //restaurando possibilidade de compra dos bilhetes não escolhidos
    mapaVetoresEmpresaX[partidaAnderson][MpossibilidadesX[0]]++;
    mapaVetoresEmpresaY[partidaMariana][MpossibilidadesX[1]]++;
    mapaVetoresEmpresaY[partidaMariana][MpossibilidadesY[0]]++;

    return 0;
}