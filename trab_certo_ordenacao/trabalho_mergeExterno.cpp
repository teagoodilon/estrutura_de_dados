#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

struct pacote {
  unsigned indice;
  float tempo;
  char origem[40];
  char destino[40];
  char protocolo[18];
  unsigned tamanho;
  char informacao[100]; 
  int i;
};

void swap(pacote* x, pacote* y);

class minHeap{
    pacote* mPtr;
    int tamHeap;
  public:
    minHeap(pacote a[], int tamanho); //construtor
    void minHeapFy(int);
    int esquerda(int i) {return 2*i+1;}
    int direita(int i) {return 2*i+2;}
    pacote getRaiz() {return mPtr[0];}
    void novaRaiz(pacote x) {
      mPtr[0] = x;
      minHeapFy(0);
    }
};

minHeap::minHeap(pacote a[], int tamanho){
  tamHeap = tamanho;
  mPtr = a;
  int i = (tamHeap - 1)/2;
  while (i >= 0){
    minHeapFy(i);
    i--;
  }
}

void minHeap::minHeapFy(int i){
  int esq = esquerda(i);
  int dir = direita(i);
  int menor = i;
  if(esq < tamHeap and mPtr[esq].indice < mPtr[i].indice){
    menor = esq;
  }
  if(dir < tamHeap and mPtr[dir].indice < mPtr[menor].indice){
    menor = dir;
  }
  if(menor != i){
    swap(&mPtr[i], &mPtr[menor]);
    minHeapFy(menor);
  }
}

FILE* abrirArquivo(char* nomeArquivo, char* mode){
  FILE* arq = fopen(nomeArquivo, mode);
  return arq;
}

void swap(pacote* x, pacote* y){
  pacote temp = *x;
  *x = *y;
  *y = temp;
}

void intercala(int vetor[], int inicio, int meio, int fim){
  int n1 = meio - inicio + 1;
  int n2 = fim - meio;
  int esq[n1], dir[n2];

  for(int i = 0; i < n1; i++){
    esq[i] = vetor[inicio+i];
  }
  for (int j = 0; j < n2; j++){
    dir[j] = vetor[meio+1+j];
  }
  int i = 0, j = 0, k = inicio;
  while(i < n1 and j < n2){
    if(esq[i] <= dir[j]){
      vetor[k++] = esq[i++];
    } else {
      vetor[k++] = dir[j++];
    }
  }
  while(i < n1){
    vetor[k++] = esq[i++];
  }
  while(j < n2){
    vetor[k++] = dir[j++];
  }
}

void mergeSort(int vetor[], int inicio, int fim){
  if(inicio < fim){
    int meio = (fim + inicio)/2;
    mergeSort(vetor, inicio, meio);
    mergeSort(vetor, meio+1, fim);
    intercala(vetor, inicio, meio, fim);
  }
}

void mergeArquivos(char* arqSaida, int n, int tam){
  FILE* entrada[tam];
  for(int i = 0; i < tam; i++){
    char nomeArquivo[2];
    snprintf(nomeArquivo, sizeof(nomeArquivo), "%d", i);
    entrada[i] = abrirArquivo(nomeArquivo, "r");
  }
  FILE* saida = abrirArquivo(arqSaida, "w");
  pacote* vetor = new pacote[tam];
  int i;
  for(i = 0; i < tam and not(fscanf(entrada[i], "%d ", &vetor[i].indice) != 1); i++){
    vetor[i].i = i;
  }
  minHeap mHeap(vetor, i);
  int cont = 0;
  while(cont != i){
    pacote raiz = mHeap.getRaiz();
    fprintf(saida, "%d\n", raiz.indice);
    if(fscanf(entrada[raiz.i], "%d", &raiz.indice) != 1){
      raiz.indice = 4294967295;
      cont++;
    }
    mHeap.novaRaiz(raiz);
  }
  for(int i = 0; i < tam; i++){
    fclose(entrada[i]);
  }
  fclose(saida);
}

void criaArquivoSaida(char* arqEntrada, int tam, int numCaminhos){
  FILE* entrada = abrirArquivo(arqEntrada, "r");
  FILE* saida [numCaminhos];
  char nomeArquivo[2];
  for(int i = 0; i < numCaminhos; i++){
    snprintf(nomeArquivo, sizeof(nomeArquivo), "%d", i);
    saida[i] = abrirArquivo(nomeArquivo, "w");
  }
  int* vetor = (int*)malloc(tam * sizeof(int));
  bool adicionar = true;
  int proxArquivo = 0, i;
  while(adicionar){
    for(i = 0; i < tam; i++){
      if(fscanf(entrada, "%d ", &vetor[i]) != 1){
        adicionar = false;
      }
    }
    if(adicionar){
      mergeSort(vetor, 0, i - 1);
      for(int j = 0; j < i; j++){
        fprintf(saida[proxArquivo], "%d\n", vetor[j]);
      }
      proxArquivo++;
    }
  }
  for(int i = 0; i < numCaminhos; i++){
    fclose(saida[i]);
  }
  fclose(entrada);
}

void mergeExterno(char* arqEntrada, char* arqSaida, int numCaminhos, int tam){
  criaArquivoSaida(arqEntrada, tam, numCaminhos);
  mergeArquivos(arqSaida, tam, numCaminhos);
}

void le_arquivo_bin(ifstream& arquivo, ofstream& saida) {
    pacote umPacote;
    while(arquivo.read((char*) &umPacote, sizeof(umPacote))) {
      saida << umPacote.indice << " "
      << umPacote.tempo << " "
      << umPacote.origem << " "
      << umPacote.destino << " "
      << umPacote.protocolo << " "
      << umPacote.tamanho << " "
      << umPacote.informacao << endl;
    }
}

int main(){
  ifstream arquivo_bin_read("captura_pacotes.bin",ios::binary);
  ofstream saida_bin("saida.txt");
  le_arquivo_bin(arquivo_bin_read, saida_bin);
  return 0;
}