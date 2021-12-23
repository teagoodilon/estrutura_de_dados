/*
    MaxHeap, para alteração de prioridade
    by joukim & bruno, 2019
*/

#include <iostream>
#include <utility> // para usar swap
#include <stdexcept> // para usar exceção com runtime_error
#include <cstring>

using namespace std;

struct dado {
    int prioridade;
    int valor;
};

bool operator>(dado d1, dado d2) {
    return d1.prioridade > d2.prioridade;
}

bool operator<(dado d1, dado d2) {
    return d1.prioridade < d2.prioridade;
}

ostream& operator<<(ostream& output,const dado& d) {
    output << "[" << d.valor << "/" << d.prioridade << "]"; 
    return output;
}

class MaxHeap {
private:
    dado* heap;
    int capacidade;
    int tamanho;
    inline int pai(int i);
    inline int esquerdo(int i);
    inline int direito(int i); 
    void arruma();
    void corrigeDescendo(int i); 
    void corrigeSubindo(int i);
public:
    MaxHeap(int cap);
    MaxHeap(dado vet[], int tam);
    ~MaxHeap();
    void imprime();
    dado retiraRaiz();
    void insere(dado d);
    void alteraPrioridade(int umValor, int novaPrioridade);
};

MaxHeap::MaxHeap(int cap) {
  capacidade = cap;
  heap = new dado [cap];
  tamanho = 0;
}

MaxHeap::MaxHeap(dado vet[], int tam) {
  capacidade = tam;
  heap = new dado[capacidade];
  memcpy(heap, vet, tam * sizeof(dado));
  tamanho = tam;
  arruma();
}

MaxHeap::~MaxHeap() {
  delete[] heap;
}

void MaxHeap::arruma(){
  for(int i=(tamanho/2-1); i >= 0; i--){
    corrigeDescendo(i);
  }
}

int MaxHeap::pai(int i) {
  return (i-1)/2;
}
    
int MaxHeap::esquerdo(int i) {
  return 2*i+1;
}
    
int MaxHeap::direito(int i) {
  return 2*i+2;
}
    
void MaxHeap::corrigeDescendo(int i) {
  int esq = esquerdo (i);
  int dir = direito (i);
  int maior = i;

  if((esq < tamanho) and (heap[esq] > heap[maior])){
    maior = esq;
  }
  if((dir < tamanho) and (heap[dir] > heap[maior])){
    maior = dir;
  }
  if(maior != i){
    swap(heap[i], heap[maior]);
    corrigeDescendo(maior);
  }
}

void MaxHeap::corrigeSubindo(int i) {
  int p = pai(i);
  if(heap[i] > heap[p]){
    swap(heap[i], heap[p]);
    corrigeSubindo(p);
  }
}
        
void MaxHeap::imprime() {
  for (int i = 0; i < tamanho; i++) {
    cout << heap[i] << " ";
  } 
  cout << endl;
}

dado MaxHeap::retiraRaiz() {
  if(tamanho == 0){
    cerr << "Erro ao retirar raiz" << endl;
    exit(EXIT_FAILURE);
  }
  dado aux = heap[0];
  swap(heap[0], heap[tamanho-1]);
  tamanho--;
  corrigeDescendo(0);
  return aux;
}


void MaxHeap::insere(dado d){
  if(tamanho == capacidade){
    cerr << "Erro ao inserir" << endl;
    exit(EXIT_FAILURE);
  }
  heap[tamanho] = d;
  corrigeSubindo(tamanho);
  tamanho++;
}

void MaxHeap::alteraPrioridade(int umValor, int novaPrioridade) {
  dado valor = retiraRaiz();
  dado* vetor;
  int i = 0;
  vetor = new dado[capacidade];
  while (valor.valor != umValor){
    vetor[i] = valor; 
    i++;
    valor = retiraRaiz();
  }
  valor.prioridade = novaPrioridade;
  insere(valor);
  for(int j = 0; j < i; j++){
    insere(vetor[j]);
  }
}

int main () {
  int capacidade;
  cin >> capacidade;
  MaxHeap meuHeap(capacidade);
  
  char opcao;
  cin >> opcao;
  
  dado umDado;
  int valor, novaPrioridade;

  while (opcao != 'Q') {
    switch(opcao) {
      case 'I':
        cin >> umDado.valor;
        cin >> umDado.prioridade;
        meuHeap.insere(umDado);
        break;
      case 'R':
        cout << meuHeap.retiraRaiz().valor << endl;
        break;
      case 'A':
        cin >> valor >> novaPrioridade;
        meuHeap.alteraPrioridade(valor,novaPrioridade); 
        break;               
      case 'P':
        meuHeap.imprime();
        break;
      default:
        cout << "Opção inválida!" << endl;
    }
    cin >> opcao;
  }
  return 0;
}