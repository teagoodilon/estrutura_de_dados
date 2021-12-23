#include <iostream>
#include <cstdlib>
using namespace std;

typedef int Dado;

class noh{
	friend class lista;
	
	private:
		const Dado dado;
		noh* proximo;
	
	public:
		noh(Dado d = 0);
};

noh:: noh(Dado d) : dado(d){
	proximo = NULL;
}

class lista {
	private:
		noh* primeiro;
		noh* ultimo;
		int tamanho;
		void removeTodos();
		void imprimeReversoAux(noh* umNoh);
	
	public:
		lista();
		lista(const lista& umaLista);
		~lista();
		//sobrecarga do operador de atribuicao
		lista& operator=(const lista& umaLista);
		
		inline void insere(Dado dado);
		void insereNoFim(Dado);
		void insereNoInicio(Dado dado);
		void insereNaPosicao(int posicao, Dado dado);
		
		int procura(Dado valor);
		void imprime();
		void imprimeReverso();
		inline bool vazia();
		
		void removeNoFim();
		void removeNoInicio();
		
		void funcA(){
			noh* noh1 = primeiro;
			noh* noh2 = NULL;
			noh* noh3;

			int d = 0;
			while (noh1 != NULL){
				noh3 = noh1->proximo;
				if(d%2==0){
					if(noh2 != NULL){
						noh2 -> proximo = noh3;
					} else {
						primeiro = noh1 -> proximo;
					}
					if(noh3 == NULL){
						ultimo = noh2;
					}
					delete noh1;
				} else {
					noh2 = noh1;
				}
				noh1 = noh3;
				d++;
			}
		}
		
		void funcB(lista& l){
			noh* noh1 = primeiro;
			
			while(noh1 != NULL){
				if(noh1 -> dado % 2 == 0){
					noh* noh2 = new noh(noh1 -> dado);
					if(l.primeiro == NULL){
						l.primeiro = noh2;
						l.ultimo = noh2;
					} else {
						l.ultimo -> proximo = noh2;
						l.ultimo = noh2;
					}
				}
				noh1 = noh1 -> proximo;
			}
		}
		
		
};

lista::lista(){
	tamanho = 0;
	primeiro = NULL;
	ultimo = NULL;
}
lista::lista(const lista& umaLista){
	tamanho = 0;
	primeiro = NULL;
	ultimo = NULL;
	
	noh* aux = umaLista.primeiro;
	
	while(aux != NULL){
		insereNoFim(aux -> dado);
		aux = aux-> proximo;
	}
}

lista::~lista(){
	removeTodos();
}

void lista::removeTodos(){
	noh*aux = primeiro;
	noh* temp;
	
	while(aux != NULL){
		temp = aux;
		aux = aux->proximo;
		delete temp;
	}
	
	tamanho = 0;
	primeiro = NULL;
	ultimo = NULL;
}

lista& lista::operator = (const lista& umaLista){
	//limpa a lista existente
	removeTodos();
	
	noh* aux = umaLista.primeiro;
	
	while(aux != NULL){
		insereNoFim(aux->dado);
		aux = aux->proximo;
	}
	return *this;
}

void lista::insere(Dado dado){
	insereNoFim(dado);
}

void lista::insereNoFim(Dado dado){
	noh* novo = new noh(dado);
	
	if(vazia()){
		primeiro = novo;
		ultimo = novo;
	}else{
		ultimo->proximo = novo;
		ultimo = novo;
	}
	tamanho++;
}

void lista::insereNoInicio(Dado dado){
	noh* novo = new noh(dado);
	
	if(vazia()){
		primeiro = novo;
		ultimo = novo;
	}else{
		novo->proximo = primeiro;
		primeiro = novo;
	}
	tamanho++;
}

void lista::insereNaPosicao(int posicao, Dado dado){
	noh* novo = new noh(dado);
	
	if(posicao <= tamanho and posicao>=0){
		if(vazia()){
			primeiro = novo;
			ultimo = novo;
		}else if (posicao == 0){
			novo->proximo = primeiro;
			primeiro = novo;
		}
		else if(posicao == tamanho){
			ultimo->proximo = novo;
			ultimo=novo;
		}
		else{
			noh* aux = primeiro;
			int posAux = 0;
			
			while( posAux < (posicao-1)){
				aux = aux->proximo;
				posAux++;
			}
			novo->proximo = aux->proximo;
			aux->proximo = novo;
		}
		tamanho++;
	}else{
		cerr<<"POSICAO INVALIDA"<<endl;
		exit(EXIT_FAILURE);
	}	
}

int lista::procura(Dado valor){
	noh* aux = primeiro;
	int posAux = 0;
	
	while(aux != NULL and aux->dado != valor){
		posAux++;
		aux = aux->proximo;
	}
	
	if(aux == NULL){
		posAux = -1;
	}
	return posAux;
}

void lista:: imprime(){
	noh* aux = primeiro;
	
	while(aux != NULL){
		cout << aux->dado<<" ";
		aux = aux->proximo;
	}
	cout << endl;
}

void lista::imprimeReverso(){
	imprimeReversoAux(primeiro);
	cout << endl;

}

void lista::imprimeReversoAux(noh* umNoh){
	if(umNoh!=NULL){
		imprimeReversoAux(umNoh->proximo);
		cout << umNoh->dado<<" ";
	}
}

inline bool lista::vazia(){
	return (primeiro == NULL);
}

void lista::removeNoFim(){
	if(vazia()){
		cerr<<"Lista vazia"<<endl;
		exit(EXIT_FAILURE);
	}

	noh* aux = primeiro;
	noh* anterior;
	while(aux->proximo != NULL){
		anterior = aux;
		aux = aux->proximo;
	}
	
	delete ultimo;
	anterior->proximo = NULL;
	ultimo = anterior;
	
	if(vazia()) {
		primeiro = NULL;
	}
	tamanho--;
}


void lista::removeNoInicio(){
	if(vazia()){
		cerr<<"Lista vazia"<<endl;
		exit(EXIT_FAILURE);
	}
	
	noh* removido = primeiro;
	primeiro = primeiro->proximo;
	delete removido;
	
	tamanho--;

	if(tamanho == 0) {
		ultimo = NULL;
	}
	
}

int main(){
	lista lista1;
	lista lista2;
	
	int m, n;
	cin >> m;
	for (int i = 0; i < m; i++){
		cin >> n;
		lista1.insereNoInicio(n);
	}
	cin >> m;
	for (int i = 0; i < m; i++){
		cin >> n;
		lista2.insereNoFim(n);
	}
	
	lista1.funcA();
	lista2.funcB(lista1);
	lista1.imprime();
	return 0;
}