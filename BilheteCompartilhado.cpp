/**
 * Prevenção de deadlocks usando Grafos em situação simulada.
 * 
*/
#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
int mapaVetoresEmpresaX[4][4];
int mapaVetoresEmpresaY[4][4];
int mapaVetoresEmpresaZ[4][4];

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
        //linha em branco
        getline(arquivo, result);
        for(int i=0; i<4; i++){
            getline(arquivo, result);
            for(int j=0; j<4; j++){
                mapaVetoresEmpresaZ[i][j]=result[j]-'0';
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
        if ( vetores[partida][i] == 1 && i != destino){// se existe uma passagem para essa cidade
            reservar(vetores, i, destino, possibilidades);//testa se é possivel chegar ao destino
        }
    }
}

void compraBilhete( int partida, int destino, vector<int> &possibilidadesX, vector<int>&possibilidadesY, vector<int>&possibilidadesZ){

    cout << "\npossibilidades de trajeto na empresa X" << endl;
    buscaEmLargura(mapaVetoresEmpresaX, partida, destino, possibilidadesX );
    for (size_t i = 0; i < possibilidadesX.size(); i++){
        if ( possibilidadesX[i] == partida){
            printf("bilhete direto para a cidade %d\n", destino);
        }
        else {
            printf("bilhete com parada na cidade %d\n", possibilidadesX[i]);
        }
    }
    if( possibilidadesX.size() == 0){
        cout << "nenhuma passagem disponivel\n";
    }
    cout << "\npossibilidades de trajeto na empresa Y" << endl;
    buscaEmLargura(mapaVetoresEmpresaY, partida, destino, possibilidadesY );
    for (size_t i = 0; i < possibilidadesY.size(); i++){
        if ( possibilidadesY[i] == partida){
            printf("bilhete direto para a cidade %d\n", destino);
        }
        else {
            printf("bilhete com parada na cidade %d\n", possibilidadesY[i]);
        }
    }
    if( possibilidadesY.size() == 0){
        cout << "nenhuma passagem disponivel\n";
    }
    cout << "\npossibilidades de trajeto na empresa Z" << endl;
    buscaEmLargura(mapaVetoresEmpresaZ, partida, destino, possibilidadesZ );
    for (size_t i = 0; i < possibilidadesZ.size(); i++){
        if ( possibilidadesZ[i] == partida){
            printf("bilhete direto para a cidade %d\n", destino);
        }
        else {
            printf("bilhete com parada na cidade %d\n", possibilidadesZ[i]);
        }
    }
    if( possibilidadesZ.size() == 0){
        cout << "nenhuma passagem disponivel\n";
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
    int partidaEsther = 1;
    int destinoMariana = 3;
    int destinoAnderson = 3;
    int destinoEsther = 3;
    vector<int> ApossibilidadesX;
    vector<int> MpossibilidadesX;
    vector<int> EpossibilidadesX;
    vector<int> ApossibilidadesY;
    vector<int> MpossibilidadesY;
    vector<int> EpossibilidadesY;
    vector<int> ApossibilidadesZ;
    vector<int> MpossibilidadesZ;
    vector<int> EpossibilidadesZ;
    cout << "Mariana desejar comprar uma passagem da cidade 0 para a cidade 3\n";
    compraBilhete(partidaMariana , destinoMariana, MpossibilidadesX, MpossibilidadesY, MpossibilidadesZ);
    cout << "\nAnderson desejar comprar uma passagem da cidade 1 para a cidade 3\n";
    compraBilhete(partidaAnderson , destinoAnderson, ApossibilidadesX, ApossibilidadesY, ApossibilidadesZ);

    cout << "\nMariana escolhe a primeira possibilidade de trajeto na empresa X\n";
    
    cout << "\nAnderson escolhe a primeira possibilidade de trajeto na empresa Y\n";
    
    //restaurando possibilidade de compra dos bilhetes não escolhidos
    mapaVetoresEmpresaX[ApossibilidadesX[1]][destinoAnderson]++;
    mapaVetoresEmpresaX[MpossibilidadesX[1]][destinoMariana]++;
    mapaVetoresEmpresaY[MpossibilidadesY[0]][destinoMariana]++;

    cout << "\nEsther desejar comprar uma passagem da cidade 1 para a cidade 3\n";
    compraBilhete(partidaEsther , destinoEsther, EpossibilidadesX, EpossibilidadesY, EpossibilidadesZ);

    cout << "\nEsther escolhe a primeira possibilidade de trajeto na empresa Y\n";
    
    return 0;
}