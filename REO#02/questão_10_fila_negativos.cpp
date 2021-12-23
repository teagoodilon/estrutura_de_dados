#include <iostream>
#include <cstring>
using namespace std;

class noh {
  friend class fila;
  private:
    int mDado;
    noh* mProximo;  
  public:
    noh(int dado);
};

noh::noh(int dado){
  mDado = dado;
  mProximo = NULL; 
}

class fila {
  private:
    noh* mInicio;
    noh* mFim;
    unsigned mTamanho;
  public:
    fila();
    ~fila();
    unsigned tamanho();
    void enfileira(int dado);
    int desenfileira();
    bool vazia();
    void limpaFila();
};

fila::fila(){
  mInicio = NULL;
  mFim = NULL;
  mTamanho = 0;
}

fila::~fila(){
  limpaFila();
}

void fila::limpaFila(){
  while(mTamanho > 0){
    desenfileira();
  };
}

unsigned fila::tamanho(){
  return mTamanho;
}

bool fila::vazia(){
  return (mTamanho == 0);
}

void fila::enfileira(int dado){
  noh* novo = new noh(dado);
  if(mTamanho == 0){
    mInicio = novo;
  } else {
    mFim->mProximo = novo;
  }
  mFim = novo;
  mTamanho++;
}

int fila::desenfileira(){
  int dado = mInicio->mDado;
  noh* temp = mInicio;
  mInicio = mInicio->mProximo;
  delete temp;
  mTamanho--;
  if(mTamanho == 0){
    mFim = NULL;
  }
  return dado;
}

int main (){
  fila f1, f2;
  int tamanho, elemento, elemento2;
  cin >> tamanho;
  for (int i = 0; i < tamanho; i++){
    cin >> elemento;
    f1.enfileira(elemento);
  }
  int subfila, contador = 0;
  cin >> subfila;
  for (int i = 0; i < tamanho; i++){   
    elemento = f1.desenfileira();
    f2.enfileira(elemento);
    while(int(f2.tamanho()) == subfila){
      elemento2 = f2.desenfileira();  
      if(elemento2 > 0){
        if(f2.vazia()){
          cout << "inexistente" << " ";
        } else {
          contador++;
          if(contador == subfila){
            cout << "inexistente" << " ";
            contador--;
          }
        }
      } else {
        cout << elemento2 << " ";
        while (contador > 0){
          cout << elemento2 << " ";
          contador--;
        }
      }
    }
  }
  return 0;
}