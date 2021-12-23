#include <iostream>
#include <cstring>
#include <fstream>

#define tamanhoVet 999
using namespace std;

struct pacote {
  unsigned indice;
  float tempo;
  char origem[40];
  char destino[40];
  char protocolo[18];
  unsigned tamanho;
  char informacao[100]; 
};

struct arquivo{
  FILE *mArq;
  int pos, max;
  int *buffer;
};

void intercala(int a[],int inicio, int meio, int fim){
	 int i = inicio, j = meio +1;
	 int tamanho = fim - inicio + 1;
	 int aux[tamanho];
	 for(int k=0; k < tamanho; k++){
		 if((i<=meio) and (j<= fim)){
			 if(a[i] <= a[j]){
				 aux[k] = a[i];
				 i++;
			 }else{
				 aux[k] = a[j];
				 j++;
			 }
		 }else if(i > meio){
		 	aux[k] = a[j];
			j++;			 
		 }else{
			 aux[k] = a[i];
			 i++;
		 }
	 }
	 for(int k=0; k < tamanho; k++){
		 a[inicio + k]= aux[k];
	 }
}

void mergeSortVet(int a[], int inicio,int fim){
	int meio;
	if(inicio < fim){
		meio = (inicio + fim)/2;
		mergeSortVet(a, inicio, meio);
		mergeSortVet(a, meio+1, fim);
		intercala(a,inicio,meio, fim);
	}
}

void salvaArquivo(char* nome, int* v, int tam, int mudaLinha){
  FILE *f = fopen(nome, "a");
  for (int i = 0; i < tam-1; i++){
    fprintf(f, "%d\n", v[i]);
  }
  if(mudaLinha == 0){
    fprintf(f, "%d", v[tam-1]);
  } else {
    fprintf(f, "%d\n", v[tam-1]);
  }
  fclose(f);
}

int criaArquivoOrdenado(char* nome){
  int vet[tamanhoVet];
  char novo[20];
  int cont = 0, total = 0;
  FILE *f = fopen(nome, "r");
  while(!feof(f)){
    fscanf(f, "%d", &vet[total]);
    total++;
    if(total == tamanhoVet){
      cont++;
      sprintf(novo, "Temp%d.txt", cont);
      mergeSortVet(vet, 0, tamanhoVet-1);
      salvaArquivo(novo, vet, total, 0);
      total = 0;
    }
  }
  if(total > 0){
    cont++;
    sprintf(novo, "Temp%d.txt", cont);
    mergeSortVet(vet, 0, tamanhoVet-1);
    salvaArquivo(novo, vet, total, 0);
  }
  fclose(f);
  return cont;
}

void preencheBuffer(struct arquivo* arq, int t){
  int i;
  if (arq->mArq == NULL){
    return;
  }
  arq->pos = 0;
  arq->max = 0;
  for(i=0; i<t; i++){
    if(!feof(arq->mArq)){
      fscanf(arq->mArq, "%d", &arq->buffer[arq->max]);
      arq->max++;
    } else {
      fclose(arq->mArq);
      arq->mArq = NULL;
      i = t;
    }
  }
}

int procuraMenor(struct arquivo* arq, int k, int t, int* menor){
  int i, idx = -1;
  for (i = 0; i < k; i++){
    if(arq[i].pos < arq[i].max){
      if(idx == -1){
        idx = i;
      } else {
        if(arq[i].buffer[arq[i].pos] < arq[idx].buffer[arq[idx].pos]){
          idx = 1;
        }
      }
    }
  }
  if(idx != -1){
    *menor = arq[idx].buffer[arq[idx].pos];
    arq[idx].pos++;
    if(arq[idx].pos == arq[idx].max){
      preencheBuffer(&arq[idx], t);
    }
    return 1;
  } else {
    return 0;
  }
}

void merge(char *nome, int k, int t){
  char novo[20];
  int *buffer = (int*)malloc(t*sizeof(int));
  struct arquivo* arq;
  arq = (struct arquivo*)malloc(k*sizeof(struct arquivo));
  for(int i=0; i < k; i++){
      sprintf(novo,"Temp%d.txt",i+1);
      arq[i].mArq = fopen(novo,"r");
      arq[i].max = 0;
      arq[i].pos = 0;
      arq[i].buffer = (int*)malloc(t*sizeof(int));
      preencheBuffer(&arq[i],t);
  }
  int menor, qtdBuffer = 0;
  while(procuraMenor(arq,k,t,&menor) == 1){
      buffer[qtdBuffer] = menor;
      qtdBuffer++;
      if(qtdBuffer == t){
          salvaArquivo(nome, buffer, t, 1);
          qtdBuffer = 0;
      }
  }
  if(qtdBuffer != 0){
    salvaArquivo(nome, buffer, qtdBuffer, 1);
  }
  for(int i = 0; i < k; i++){
    free(arq[i].buffer);
  }
  free(arq);
  free(buffer);
}

void mergeExterno(char* nome){
  char novo[20];
  int k = criaArquivoOrdenado(nome);
  int t = tamanhoVet/(k+1);
  remove(nome);
  merge(nome, k, t);
  for(int i = 0; i < k; i++){
    sprintf(novo, "Temp%d.txt", i+1);
    remove(novo);
  }
}

void verificaArquivoOrdenado(char *nome){
  int v1,v2, erro = 0;
  FILE *f = fopen(nome,"r");
  fscanf(f,"%d",&v1);
  while(!feof(f)){
    fscanf(f,"%d",&v2);
    if (v2 < v1){
      erro = 1;
      break;
    }
  }
  fclose(f);
  if(erro)
    printf("Valores fora de ordem!\n");
  else
    printf("Arquivo corretamente ordenado!\n");
}

void le_arquivo_bin(ifstream& arquivo) {
  pacote umPacote;
  while(arquivo.read((char*) &umPacote, sizeof(umPacote))) {
    cout << umPacote.indice << "; ";
    //cout << umPacote.tempo << "; ";
    //cout << umPacote.origem << "; ";
    //cout << umPacote.destino << "; ";
    cout << umPacote.protocolo << "; " << endl;
    //cout << umPacote.tamanho << "; ";
    //cout << umPacote.informacao << endl << endl << endl;
  }
}

int main(){
  mergeExterno("dados.txt");
  verificaArquivoOrdenado("dados.txt");
  return 0;
}