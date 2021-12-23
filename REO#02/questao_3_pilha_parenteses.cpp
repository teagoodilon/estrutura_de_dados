#include <iostream>
#include <cstring>
using namespace std;

class noh {
  friend class pilha;
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

class pilha {
  private:
    noh* mTopo;
    unsigned mTamanho;
  public:
    pilha();
    ~pilha();
    unsigned tamanho();
    void empilha(int dado);
    int desempilha();
    bool vazia();
    void limpaPilha();
};

pilha::pilha(){
  mTopo = NULL;
  mTamanho = 0;
}

pilha::~pilha(){
  limpaPilha();
}

void pilha::limpaPilha(){
  while(mTamanho > 0){
    desempilha();
  };
}

unsigned pilha::tamanho(){
  return mTamanho;
}

bool pilha::vazia(){
  return (mTamanho == 0);
}

void pilha::empilha(int dado){
  noh* novo = new noh(dado);
  novo->mProximo = mTopo;
  mTopo = novo;
  mTamanho++;
}

int pilha::desempilha(){
  int dado = mTopo->mDado;
  noh* temp = mTopo;
  mTopo = mTopo->mProximo;
  delete temp;
  mTamanho--;
  return dado;
}

int main (){
  pilha p1;
  string linhaTexto;
  int tamanhoTexto;
  getline(cin, linhaTexto);
  tamanhoTexto = int (linhaTexto.length());
  for (int i = 0; i < tamanhoTexto; i++){
    if (linhaTexto[i] == ')'){
      if(p1.vazia()){
        cout << i << endl;
        return 0;
      } else {
        p1.desempilha();
      }
    }
    if (linhaTexto[i] == '('){
      if(i == tamanhoTexto - 1){
        cout << i << endl;
        return 0;
      } else {
        p1.empilha(i);
      }
    }
  }
  if(not p1.vazia()){
    cout << p1.desempilha() << endl;
    return 0;
  }
  cout << "correto" << endl;
  return 0;
}