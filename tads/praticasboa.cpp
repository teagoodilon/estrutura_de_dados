#include <iostream>
#include <cstdlib>
using namespace std;

struct vectorx {
  int* vetor;
  int tam;

  void inicializa(int n) {
    vetor = new int[n];
    tam = n;
  }

  void finaliza(){
    delete[] vetor;
    tam = 0;
  }
  void preenche() {
    for (int i = 0; i < tam; i++){
      vetor[i] = rand() % 100;
    }
  }
  void concatena(vectorx& vec1, vectorx& vec2) {
    int tam1 = vec1.tam;
    int tam2 = vec2.tam;

    for (int i = 0; i < tam1; i++){
      vetor[i] = vec1.vetor[i];
    }
    for (int i = 0; i < tam2; i++){
      vetor[i+tam1] = vec2.vetor[i];
    }
  }
  void imprime() {
    for (int i = 0; i < tam; i++){
      cout << vetor[i] << " ";
    }
    cout << endl;
  } 
};

int main(){
  vectorx vec1, vec2, vec3;
  int tam1, tam2;

  cin >> tam1 >> tam2;
  
  srand(time(NULL));

  vec1.inicializa(tam1);
  vec2.inicializa(tam2);
  vec3.inicializa(tam1 + tam2);
  
  vec1.preenche();
  vec2.preenche();
  vec3.concatena(vec1, vec2);

  vec1.imprime();
  vec2.imprime();
  vec3.imprime();
  
  vec1.finaliza();
  vec2.finaliza();
  vec3.finaliza();
  return 0;
}