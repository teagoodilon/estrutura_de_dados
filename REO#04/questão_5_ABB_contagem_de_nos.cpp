#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
using namespace std;

class noh{
  friend class arvore;
  private:
    int mValor;
    noh* ptEsq;
    noh* ptDir;
    noh* pai;
  public:
    noh(int d);
};

noh::noh(int d){
  mValor = d;
  ptEsq = NULL;
  ptDir = NULL;
  pai = NULL;
}

class arvore{
  private:
    noh* raiz;
  public:
    arvore();
    ~arvore();
    void inserir(int d);
    void EscreverNivelANivel(std::ostream& saida);
    void contador();
    int contaDiferenca(noh* tree);
};

arvore::arvore(){
  raiz = NULL;
}

arvore::~arvore(){
  delete raiz;
}

int arvore::contaDiferenca(noh* tree){
  if(tree == NULL){
    return 0;
  }
  int dir = 0 , esq = 0;
  esq = contaDiferenca(tree->ptEsq);
  dir = contaDiferenca(tree->ptDir);
  cout << "round: " << dir+esq << endl;
  return dir+esq+1;
}

void arvore::contador(){
  int dir = 0 , esq = 0;
  if(raiz != NULL){
    esq = contaDiferenca(raiz->ptEsq);
    dir = contaDiferenca(raiz->ptDir);   
    cout << dir+esq+1 << endl << esq - dir << endl;
  }  else {
    cout << 0 << endl << 0 << endl;
  }
}

void arvore::inserir(int d){
  noh* novoNoh = new noh(d);
  if (raiz == NULL){
    raiz = novoNoh;
  } else {
    noh* atual = raiz;
    noh* anterior = NULL;
    while (atual != NULL){
      anterior = atual;
      if(atual->mValor > d){
        atual = atual -> ptEsq;
      } else {
        atual = atual -> ptDir;
      }
    }
    novoNoh->pai = anterior;
    if(anterior->mValor > novoNoh->mValor){
      anterior->ptEsq = novoNoh;
    } else {
      anterior->ptDir = novoNoh;
    }
  }
}

int main(){
  arvore* abb = new arvore();
  int valor = 0;
  cin >> valor;
  while(valor != -1){
    abb->inserir(valor);
    cin >> valor;
  }
  abb->contador();
  delete abb;
  return 0;
}