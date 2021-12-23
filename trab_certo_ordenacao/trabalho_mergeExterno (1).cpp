#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

struct pacote {
  unsigned element;
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
  if(esq < tamHeap and mPtr[esq].element < mPtr[i].element){
    menor = esq;
  }
  if(dir < tamHeap and mPtr[dir].element < mPtr[menor].element){
    menor = dir;
  }
  if(menor != i){
    swap(&mPtr[i], &mPtr[menor]);
    minHeapFy(menor);
  }
}

FILE* abrirArquivo(char* nomeArquivo, char* mode){
  FILE* arq = fopen(nomeArquivo, mode);
  if(arq == NULL){
    perror("Erro ao abrir arquivo.\n");
    exit(EXIT_FAILURE);
  }
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
    entrada[i] = abrirArquivo(nomeArquivo, "rb");
  }
  FILE* saida = abrirArquivo(arqSaida, "ab");
  pacote* vetor = new pacote[tam];
  int i;
  for(i = 0; i < tam and not(fscanf(entrada[i], "%d ", &vetor[i].element) != 1); i++){
    vetor[i].i = i;
  }
  minHeap mHeap(vetor, i);
  int cont = 0;
  while(cont != i){
    pacote raiz = mHeap.getRaiz();
    fprintf(saida, "%d\n", raiz.element);
    if(fscanf(entrada[raiz.i], "%d", &raiz.element) != 1){
      raiz.element = 4294967295;
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
  FILE* entrada = abrirArquivo(arqEntrada, "rb");
  FILE* saida [numCaminhos];
  char nomeArquivo[2];
  for(int i = 0; i < numCaminhos; i++){
    snprintf(nomeArquivo, sizeof(nomeArquivo), "%d", i);
    saida[i] = abrirArquivo(nomeArquivo, "ab");
  }
  int* vetor = (int*)malloc(tam * sizeof(int));
  bool adicionar = true;
  int proxArquivo = 0, i, t;
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
int main(){
  int numTemp = 10;
	int tamTemp = 10000;
	char arqEntrada[] = "input.bin";
	char arqSaida[] = "output.bin";
	FILE* arqPrincipal = abrirArquivo(arqEntrada, "ab");
	srand(time(NULL));
	for (int i = 0; i < numTemp * tamTemp; i++){
		fprintf(arqPrincipal, "%d ", rand());
  }
	fclose(arqPrincipal);
	mergeExterno(arqEntrada, arqSaida, numTemp, tamTemp);
  return 0;
}
