#include <iostream>
#include <string>
using namespace std;

struct passagem {
  int identificador = 0;
  string cpf = " ";
  string nome = " ";
  string telefone = " ";
};

class noh {
  friend class lista;
  private:
    passagem mPassagem;
    noh* proximo;
  public:
    noh(passagem p);
};

noh::noh(passagem p) : mPassagem(p){
  proximo = NULL;
}

class lista {
  private:
    noh* primeiro;
    noh* ultimo;
    int tamanho;
    void removeTodos();
  public:
    lista();
    ~lista();
    inline void insere(passagem p);
    void insereNoFim(passagem p);
    void insereNoInicio(passagem p);
    void insereNaPosicao(int posicao, passagem p);
    void removeNoFim();
    void removeNoInicio();
    void removeValor(passagem p);
    int procura(passagem p);
    int contaEspera(passagem p);
    void imprime();
    inline bool vazia();
};

lista::lista() {
  primeiro = NULL;
  ultimo = NULL;
  tamanho = 0;
}

lista::~lista() {
  removeTodos();
}

void lista::removeTodos() {
  noh* aux = primeiro;
  noh* temp;
  while (aux != NULL) {
    temp = aux;
    aux = aux->proximo;
    delete temp;
  }
  primeiro = NULL;
  ultimo = NULL;
  tamanho = 0;
}

void lista::insere(passagem p) {
  insereNoFim(p);
}

void lista::insereNoFim(passagem p) {
  noh* novo = new noh(p);
  if(vazia()){
    primeiro = novo;
    ultimo = novo;
  } else {
    ultimo->proximo = novo;
    ultimo = novo;
  }
  tamanho++;
}

void lista::insereNoInicio(passagem p) {
  noh* novo = new noh(p);
  if(vazia()){
    primeiro = novo;
    ultimo = novo;
  } else {
    novo->proximo = primeiro;
    primeiro = novo;
  }
  tamanho++;
}

int lista::procura(passagem p){
  noh* aux = primeiro;
  int posAux = 0;
  while((aux != NULL) and (aux->mPassagem.cpf != p.cpf)){
    posAux++;
    aux = aux->proximo;
  }
  if(aux == NULL){
    posAux = -1;
  }
  return posAux;
}

inline bool lista::vazia(){
  return (primeiro == NULL);
}

void lista::removeValor(passagem p){
  noh* aux = primeiro;
  noh* anterior;
  while ((aux != NULL) and (aux->mPassagem.cpf != p.cpf)){
    anterior = aux;
    aux = aux->proximo;
  }
  if(aux != NULL){
    if(aux == primeiro){
      removeNoInicio();
    } else if (aux == ultimo){
      removeNoFim();
    } else {
      anterior->proximo = aux->proximo;
      tamanho--;
      delete aux;
    } 
  }
}

void lista::removeNoFim(){
  noh* aux = primeiro;
  noh* anterior;
  while (aux->proximo != NULL){
    anterior = aux;
    aux = aux->proximo;
  }
  delete ultimo;
  anterior->proximo = NULL;
  ultimo = anterior;
  if (vazia()){
    primeiro = NULL;
  }
  tamanho--;
}

void lista::removeNoInicio(){
  noh* removido = primeiro;
  primeiro = primeiro->proximo;
  delete removido;
  tamanho--;
  if (vazia()){
    ultimo = NULL;
  }
}

int lista::contaEspera(passagem p){
  int cont = -1;
  noh* aux = primeiro;
  while (aux != NULL){
    if(aux->mPassagem.identificador == p.identificador){
      cont ++;
    }
    aux = aux->proximo;
  }
  return cont;
}

int main(){
  lista minhaLista;
  passagem mPassagem;
  long unsigned int iterador = 0, i = 0;
  bool menu = true;
  while(menu){
    int operacao;
    cin >> operacao;
    switch(operacao){
    case 1:
      iterador = 0;
      i = 0;
      cin >> mPassagem.identificador >> mPassagem.cpf;
      cin.ignore();
      getline(cin, mPassagem.nome);
      while ((iterador < mPassagem.nome.length()) and (mPassagem.nome[iterador] <= '9') and (mPassagem.nome[iterador] >= '0')){
        iterador++;
      } 
      if (iterador == mPassagem.nome.length()){
        cin >> mPassagem.telefone;
      } else {
        while (iterador < mPassagem.nome.length()){
          mPassagem.telefone[i] = mPassagem.nome[iterador];
          i++;
          iterador++;
        }
      }
      if(minhaLista.procura(mPassagem) == -1){
        minhaLista.insere(mPassagem);
      }
      break;
    case 2:
      cin >> mPassagem.cpf;
      minhaLista.removeValor(mPassagem);
      break;
    case 3:
      cin >> mPassagem.identificador;
      if(minhaLista.contaEspera(mPassagem)>=0){
        cout << "Ocupado - Espera: " << minhaLista.contaEspera(mPassagem) << endl;
      } else {
        cout << "Disponível" << endl;
      }
      break;
    default:
      menu = false;
      break;
    }
  }
  return 0;
}