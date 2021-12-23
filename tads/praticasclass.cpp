#include <iostream>
#include <cstdlib>
using namespace std;

class vectorx {
  private:
    int* vetor;
    int tam;

  public:
    //construtores e destrutores
    vectorx();
    vectorx(int n);
    vectorx(const vectorx& vec);
    ~vectorx();

    // methods
    vectorx& operator+(const vectorx& vec);
    vectorx& operator=(const vectorx& vec);

    void preenche();
    void imprime();
    int getTam();

    int operator*(const vectorx& vec);
    vectorx operator*(const int& n);

    friend vectorx operator*(const int& n, vectorx& vec);

    int& operator[](int pos);
    friend ostream& operator<<( ostream& output, const vectorx& vec);
};

vectorx::vectorx(){
  vetor = new int[10];
  tam = 10;
}

vectorx::vectorx(int n){
  vetor = new int[n];
  tam = n;
}

vectorx::vectorx(const vectorx& vec){
  cout << "construtor de cópia" << endl;
  tam = vec.tam;
  vetor = new int[tam];
  for (int i = 0; i < tam; i++){
    vetor[i] = vec.vetor[i];
  }
}

vectorx::~vectorx() {
  cout << "morri" << endl;
  delete[] vetor;
  tam = 0;
}

vectorx& vectorx::operator=(const vectorx& vec){
  cout << "atribuição" << endl;
  delete[] vetor;
  tam = vec.tam;
  vetor = new int[tam];
  for (int i = 0; i < tam; i++){
    vetor[i] = vec.vetor[i];
  }
  return *this;
}

vectorx& vectorx::operator+(const vectorx& vec){
  vectorx* result;
  int tam1 = tam;
  int tam2 = vec.tam;

  result = new vectorx(tam1+tam2);

  for (int i = 0; i < tam1; i++){
    result->vetor[i] = vetor[i];
  }

  for (int i = 0; i < tam1; i++){
    result->vetor[i+tam1] = vec.vetor[i];
  }
  return *result;
}

int vectorx::operator*(const vectorx& vec){
  int result = 0;

  if(tam != vec.tam) {
    cerr << "tamanhos diferentes de vetores" << endl;
    exit(EXIT_FAILURE);
  } else {
    for (int i = 0; i < tam; i++){
      result += vetor[i]*vec.vetor[i];
    }
  }
  return result;
}

vectorx vectorx::operator*(const int& n){
  vectorx v = *this;

  for (int i = 0; i < tam; i++){
    v.vetor[i] = n * v.vetor[i];
  }
  return v;
}

vectorx operator*(const int& n, vectorx& vec){
  return vec*n;
}


void vectorx::preenche() {
  for (int i = 0; i < tam; i++){
    vetor[i]= rand() % 100;
  }
}

ostream& operator<<( ostream& output, const vectorx& vec){
  for (int i = 0; i < vec.tam; i++){
    output << vec.vetor[i] << " ";
  }
  output << endl;
  return output;
}

int vectorx::getTam(){
  return tam;
}

int& vectorx::operator[](int pos){
  if((pos < 0) or (pos >= tam)){
    cerr << "posicao invalida" << endl;
    exit(EXIT_FAILURE);
  } else {
    return vetor[pos];
  }
}


int main(){
  int tam1, tam2;

  cin >> tam1 >> tam2;

  srand(time(NULL));

  vectorx teste1;
  vectorx vec1(tam1);
  vectorx vec2(tam2);

  vectorx vec3;

  vectorx *ptrVecx;
  ptrVecx = new vectorx(13);

  vec1.preenche();
  vec2.preenche();

  vec2[5] = 10;

  cout<< vec1*vec2 << endl;

  teste1.preenche();
  ptrVecx->preenche();
  cout << "ok" << endl;

  vec3 = vec1 + vec2;

  vectorx teste2 = teste1;

  vectorx teste3;
  teste3 = teste1;

  cout << vec1 << vec2 << vec3;
  cout << "teste1" << endl;
  cout << teste1;
  teste1 = teste1 * 2;
  cout << teste1;
  teste1 = 3 * teste1;
  cout << teste1 << teste2 << *ptrVecx;
 
  delete ptrVecx;

  return 0;
}

/*
#include <iostream>
using namespace std;

struct animal{
  string nomeAnimal, especieAnimal, localResgate, dataResgate;
};

struct benfeitor{
  string nomeBenfeitor, tipoBenfeitor;
  float valorDoacao;
};

class ong {
  private:
    benfeitor* mybenfeitor;
    animal* myanimal;
    int totalBenfeitor;
    int totalAnimal;
  public:
    ong();
    ~ong();
    void cadastrarAnimal();
    void cadastrarBenfeitor();
    void listaBenfeitor();
    void listaAnimal();
    void shellSort();
    void procurarBenfeitor(string);
};

ong::ong(){
  myanimal = new animal[100];
  mybenfeitor = new benfeitor[100];
  totalBenfeitor = 0;
  totalAnimal = 0;
}

ong::~ong(){
  delete [] myanimal;
  delete [] mybenfeitor;
  totalBenfeitor = 0;
  totalAnimal = 0;
}

void ong::cadastrarAnimal(){
  if(totalAnimal < 99){
    cout << "Nome do " << totalAnimal + 1 <<"º animal: ";
    cin >> myanimal[totalAnimal].nomeAnimal;
    cout << "Especie: ";
    cin >> myanimal[totalAnimal].especieAnimal;
    cout << "Local de resgate: ";
    cin >> myanimal[totalAnimal].localResgate;
    cout << "Data do resgate: ";
    cin >> myanimal[totalAnimal].dataResgate;
    totalAnimal++;
    cout << endl;
  } else {
    cout << "Capacidade Máxima, não foi possivel cadastrar" <<endl;
  }
}

void ong::cadastrarBenfeitor(){
  int posBenfeitor = -1;
  if(totalBenfeitor < 99){
    cout << "Nome do benfeitor: ";
    cin >> mybenfeitor[totalBenfeitor].nomeBenfeitor;
    cout << "Tipo do benfeitor: ";
    cin >> mybenfeitor[totalBenfeitor].tipoBenfeitor;
    for(int i = 0; i < totalBenfeitor; i++){
      if(mybenfeitor[totalBenfeitor].nomeBenfeitor == mybenfeitor[i].nomeBenfeitor and
      mybenfeitor[totalBenfeitor].tipoBenfeitor == mybenfeitor[i].tipoBenfeitor){
        posBenfeitor = i;
        i = totalBenfeitor;
        cout << "Valor da doação: R$";
        cin >> mybenfeitor[i].valorDoacao;
      }
      if(posBenfeitor != -1){
        mybenfeitor[posBenfeitor].valorDoacao += mybenfeitor[i].valorDoacao;
        i += totalBenfeitor;
        totalBenfeitor--;
      }
    }
    if(posBenfeitor == -1){
      cout << "Valor da doação: R$";
      cin >> mybenfeitor[totalBenfeitor].valorDoacao;
    } 
    totalBenfeitor++;
    cout << endl;
  } else {
    cout << "Capacidade Máxima, não foi possivel cadastrar" <<endl;
  }
}

void ong::shellSort(){
  int gaps[5] = {1,4,10,23,57}; //ordenação shell sort
  int pos_gaps = 4;
  while(gaps[pos_gaps] > totalBenfeitor){
    pos_gaps --;
  }
  benfeitor valor;
  int j;
  while (pos_gaps >= 0){  
    int gap = gaps[pos_gaps]; 
    for (int i = gap; i < totalBenfeitor; i++){ 
      valor = mybenfeitor[i]; 
      j = i;         
      while ((j >= gap) and (valor.valorDoacao > mybenfeitor[j - gap].valorDoacao)){
        mybenfeitor[j] = mybenfeitor[j - gap];
        j = j - gap;
      }
      mybenfeitor[j] = valor;
    }
    pos_gaps--;    
  }
}

void ong::listaBenfeitor(){
  for (int i = 0; i < totalBenfeitor; i++){
    cout << i + 1 << "º: " << mybenfeitor[i].nomeBenfeitor << "  "
    << mybenfeitor[i].tipoBenfeitor
    << ", Montante Doado: R$ " << mybenfeitor[i].valorDoacao;
    cout << endl;
  }
}

void ong::listaAnimal(){
  for (int i = 0; i < totalAnimal; i++){
    cout << myanimal[i].nomeAnimal << " - "
    << myanimal[i].especieAnimal << " - "
    << myanimal[i].localResgate << " - " 
    << myanimal[i].dataResgate << endl;
  }
}

void ong::procurarBenfeitor(string procuraBenfeitor){
  for (int i = 0; i < totalBenfeitor; i++){
    if(mybenfeitor[i].nomeBenfeitor == procuraBenfeitor){
      cout << mybenfeitor[i].nomeBenfeitor << "  "
      << mybenfeitor[i].tipoBenfeitor <<
      ", Montante Doado: R$ " << mybenfeitor[i].valorDoacao << endl;
      i = totalBenfeitor;
    }
  }
}

int main(){
  int qtdAnimais, qtdBenfeitores;
  cout << "Quantos Animais serão cadastrados: ";
  cin >> qtdAnimais;

  cout << "Quantos Benfeitores serão cadastrados: ";
  cin >> qtdBenfeitores;

  ong *organizacao = new ong;

  for (int i = 0; i < qtdAnimais; i++) {
    organizacao->cadastrarAnimal();
  }
  cout << "Todos animais foram cadastrados!" << endl << endl;
  
  /*for (int i = 0; i < qtdBenfeitores; i++) {
    organizacao->cadastrarBenfeitor();
  }
  cout << "Todos Benfeitores foram cadastrados!" << endl << endl;
  
  organizacao->shellSort();

  bool menu = true;
  while (menu){
    cout << "Controle admnistrativo da ONG Amigo Quatro Patas" << endl
    << "O que deseja fazer?" << endl << endl
    << " [1] - Adicionar novo animal" << endl
    << " [2] - Adicionar novo benfeitor" << endl
    << " [3] - Listar todos animais" << endl
    << " [4] - Listar todos benfeitores" << endl
    << " [5] - Listar um único befeitor" << endl
    << " [6] - Encerrar sessão" << endl;
    int escolha;
    string benf;
    cout << "Escolha uma opção: ";
    cin >> escolha;
    switch (escolha){
    case 1:
      organizacao->cadastrarAnimal();
      break;
    case 2:
      organizacao->cadastrarBenfeitor();
      organizacao->shellSort();
      break;
    case 3:
      organizacao->listaAnimal();
      break;
    case 4:
      organizacao->listaBenfeitor();
      break;
    case 5:
      cout << "Digite o benfeitor que deseja procurar: " << endl;
      cin >> benf;
      organizacao->procurarBenfeitor(benf);
      break;
    case 6:
      cout << "Sessão encerrada." << endl;
      menu = false;
      break;
    default:
      cout << "Selecione uma opção válida." << endl;
      break;
    }
  } 
  delete organizacao;
  return 0;
}  */
