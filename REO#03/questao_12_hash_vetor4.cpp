#include <iostream>
using namespace std;

struct dado{
    int chave;
    string palavra;
    dado(){
        chave = -1;
    }
};

class tabela{
    private:
        dado* mDado;
        int posicao;
    public:
    tabela();
    ~tabela();
    int busca(int chave);
    void insere(dado d);
    void recupera(int chave);
    void imprime();
};

tabela::tabela(){
    mDado = new dado[4];
    posicao = 0;
}

tabela::~tabela(){
    posicao = 0;
    delete[] mDado;
}

int tabela::busca(int buscaChave){
    int posOcupada = -1;
    for(int i=0; i < posicao; i++){
        if (buscaChave == mDado[i].chave){
            posOcupada = i;
            return posOcupada;
        }
    }
    return posOcupada;    
}

void tabela::insere(dado d){
    if(busca(d.chave) != -1){
        cout << "ITEM JÁ ESTÁ NA TABELA!" << endl;
    } else {
        if(posicao == 4){
            cout << "NÚMERO MÁXIMO DE COLISÕES PARA CHAVE!" << endl;
        } else {
            mDado[posicao] = d;
            posicao++;
        }
    }
}

void tabela::recupera(int buscaChave){
    int posOcupada = busca(buscaChave);
    if(posOcupada != -1){
        cout << mDado[posOcupada].palavra << endl;
    } else {
        cout << "NÃO ENCONTRADO!" << endl;
    }
}

void tabela::imprime(){
    for(int i=0; i < 4; i++){
        cout << "[" << mDado[i].chave << "/" << mDado[i].palavra << "]";
    }
}

class tabelaHash{
    private:
        tabela* mTabelaHash;
        int tamanho;
    public:
        tabelaHash(int np);
        ~tabelaHash();
        void insere(dado d);
        void recupera(int buscaChave);
        void imprime();
};

tabelaHash::tabelaHash(int np){
    mTabelaHash = new tabela[np];
    tamanho = np;
}

tabelaHash::~tabelaHash(){
    tamanho = 0;
    delete[] mTabelaHash; 
}

void tabelaHash::insere(dado d){
    int localCerto = d.chave%tamanho;
    mTabelaHash[localCerto].insere(d);
}

void tabelaHash::recupera(int buscaChave){
    int localBusca = buscaChave%tamanho;
    mTabelaHash[localBusca].recupera(buscaChave);
}

void tabelaHash::imprime(){
    for(int i=0; i < tamanho; i++){
        cout << i << ":";
        mTabelaHash[i].imprime();
        cout << endl;
    }
}

int main(){
    dado mDado;
    int tamanho = 0, quantidade = 0, recuperacao = 0;
    cin >> tamanho >> quantidade;
    tabelaHash tabela(tamanho);
    for(int i=0; i< quantidade; i++){
        cin >> mDado.chave >> mDado.palavra;
        tabela.insere(mDado);
    }
    for(int i=0; i < 4; i++){
        cin >> recuperacao;
        tabela.recupera(recuperacao);
    }
    tabela.imprime();
    return 0;
}