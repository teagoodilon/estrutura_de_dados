#include <iostream>
#include <cstdlib>
using namespace std;

struct vectorx {
  int* vetor;
  int tam;
};

void inicializa(vectorx* vec, int n) {
  vec->vetor = new int[n];
  vec->tam = n;
}

void finaliza(vectorx* vec) {
  delete[] vec->vetor;
  vec->tam = 0;
}

void preenche(vectorx* vec) {
  for (int i = 0; i < vec->tam; i++){
    vec->vetor[i] = rand() % 100;
  }
}

void concatena(vectorx* vec, vectorx* vec1, vectorx* vec2) {
  int tam1 = vec1->tam;
  int tam2 = vec2->tam;

  for (int i = 0; i < tam1; i++){
    vec->vetor[i] = vec1->vetor[i];
  }
  for (int i = 0; i < tam2; i++){
    vec->vetor[i+tam1] = vec2->vetor[i];
  }
}

void imprime(vectorx* vec) {
  for (int i = 0; i < vec->tam; i++){
    cout << vec->vetor[i] << " ";
  }
  cout << endl;
}
int main(){
  vectorx vec1, vec2, vec3;
  int tam1, tam2;

  cin >> tam1 >> tam2;
  
  srand(time(NULL));

  inicializa(&vec1, tam1);
  inicializa(&vec2, tam2);
  inicializa(&vec3, tam1+tam2);
  
  preenche(&vec1);
  preenche(&vec2);
  concatena(&vec3, &vec1, &vec2);

  imprime(&vec1);
  imprime(&vec2);
  imprime(&vec3);
  
  finaliza(&vec1);
  finaliza(&vec2);
  finaliza(&vec3);
  
  return 0;
}