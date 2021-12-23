/*
  Nome: Thiago Odilon de Almeida 10A
  Método de ordenação: Shell Sort
  Para implementar o que foi proposto no enunciado da questão, criei 2 variáveis
  "totalBenfeitor" e "totalAnimal" para definir o tamanho máximo do vetor.
  Logo no início do programa já peço para o usuário cadastrar uma quantidade de 
  animais e benfeitores, para amenizar a quantidade de vezes que é chamado o Shell Sort.
  Junto a isso, no maior desafio que estava tendo na questão de somar o montante
  quando o nome for igual, criei uma variável "posBenfeitor" para armazenar a
  posicão onde o vetor tem o mesmo nome e tipo, conseguindo assim no ato de
  digitar o valor doado ele já soma na pessoa/empresa cadastrada e reduzindo
  uma posição no totalBenfeitor indicando o tamanho certo do vetor.
  Para ordenação utilizei o Shell Sort que no momento de inserção de mais um cadastro
  de benfeitor ele já ordena o vetor novamente.
*/

#include <iostream>
#include <string>
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
    void listarBenfeitores();
    void listarAnimais();
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
  if(totalAnimal < 100){
    cout << "Nome do " << totalAnimal + 1 <<"º animal: ";
    getline(cin, myanimal[totalAnimal].nomeAnimal);
    cout << "Especie: ";
    getline(cin, myanimal[totalAnimal].especieAnimal);
    cout << "Local do resgate: ";
    getline(cin, myanimal[totalAnimal].localResgate);
    cout << "Data do resgate: ";
    getline(cin, myanimal[totalAnimal].dataResgate);
    totalAnimal++;
    cout << endl;
  } else {
    cout << "Capacidade máxima atingida, não foi possivel cadastrar" <<endl;
  }
}

void ong::cadastrarBenfeitor(){
  int posBenfeitor = -1;
  if(totalBenfeitor < 100){
    cout << "Nome do benfeitor: ";
    getline(cin, mybenfeitor[totalBenfeitor].nomeBenfeitor);
    cout << "Digite o tipo desse Benfeitor:" <<
    endl << " [1] - CPF" <<
    endl << " [2] - CNPJ" << endl;
    int escolha;
    cin >> escolha;
    cin.ignore();
    while(escolha < 1 or escolha > 2){
      cout << "Selecione uma opção válida: " <<
      endl << " [1] - CPF" <<
      endl << " [2] - CNPJ" << endl;
      cin >> escolha;
      cin.ignore();
    }
    if(escolha==1){
      mybenfeitor[totalBenfeitor].tipoBenfeitor = "CPF";
    } else {
      mybenfeitor[totalBenfeitor].tipoBenfeitor = "CNPJ";
    }
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
      cin.ignore();
    } 
    totalBenfeitor++;
    cout << endl;
  } else {
    cout << "Capacidade máxima atingida, não foi possivel cadastrar" <<endl;
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

void ong::listarBenfeitores(){
  if(totalBenfeitor > 0){
    cout << endl <<"Lista de Benfeitores:" << endl;
    for (int i = 0; i < totalBenfeitor; i++){
      cout << i + 1 << "º: " << mybenfeitor[i].nomeBenfeitor << " - "
      << mybenfeitor[i].tipoBenfeitor
      << ", Montante Doado: R$ " << mybenfeitor[i].valorDoacao;
      cout << endl;
    }
  cout << endl;
  } else {
    cout << "Nenhum benfeitor foi cadastrado!" << endl << endl;
  }
}

void ong::listarAnimais(){
  if(totalAnimal > 0){
    cout << endl << "Lista de Animais:" << endl;
    for (int i = 0; i < totalAnimal; i++){
    cout << "Nome: " << myanimal[i].nomeAnimal << " - "
    << "Espécie: "<< myanimal[i].especieAnimal << " - "
    << "Local do Resgate: "<< myanimal[i].localResgate << " - " 
    << "Data do resgate: "<< myanimal[i].dataResgate << endl;
    }
  cout << endl;
  } else {
    cout << "Nenhum animal foi cadastrado!" << endl << endl;
  }
}

void ong::procurarBenfeitor(string procuraBenfeitor){
  bool achou = false;
  for (int i = 0; i < totalBenfeitor; i++){
    if(mybenfeitor[i].nomeBenfeitor == procuraBenfeitor){
      cout << "Resultado da pesquisa: ";
      cout << mybenfeitor[i].nomeBenfeitor << " - "
      << mybenfeitor[i].tipoBenfeitor <<
      ", Montante Doado: R$ " << mybenfeitor[i].valorDoacao << endl;
      achou = true;
    }
  }
  if (achou){
    cout << endl;
  } else {
    cout << "Benfeitor não cadastrado!" << endl << endl;
  }
}

int main(){
  int qtdAnimais = 0, qtdBenfeitores = 0;
  ong *organizacao = new ong;
  cout << "Quantos Animais serão cadastrados: ";
  cin >> qtdAnimais;
  while (qtdAnimais > 100){
    cout << "A capacidade máxima de animais é 100" << endl
    << "Digite novamente quantos animais deseja cadastrar:";
    cin >> qtdAnimais;
  }
  cin.ignore();
  for (int i = 0; i < qtdAnimais; i++) {
    organizacao->cadastrarAnimal();
  }
  if(qtdAnimais > 0){
    cout << "Todos animais foram cadastrados!" << endl << endl;
  }
  cout << "Quantos Benfeitores serão cadastrados: ";
  cin >> qtdBenfeitores;
  while (qtdBenfeitores > 100){
    cout << "A capacidade máxima de benfeitores é 100" << endl
    << "Digite novamente quantos benfeitores deseja cadastrar:";
    cin >> qtdBenfeitores;
  }
  cin.ignore();
  for (int i = 0; i < qtdBenfeitores; i++) {
    organizacao->cadastrarBenfeitor();
  }
  if(qtdBenfeitores > 0){
    cout << "Todos Benfeitores foram cadastrados!" << endl << endl;
  }
  organizacao->shellSort();
  bool menu = true;
  while (menu){
    cout << "Controle admnistrativo da ONG Amigo Quatro Patas" << endl
    << "O que deseja fazer?" << endl << endl
    << " [1] - Adicionar novo animal" << endl
    << " [2] - Adicionar novo benfeitor" << endl
    << " [3] - Listar todos animais" << endl
    << " [4] - Listar todos benfeitores" << endl
    << " [5] - Procurar um único befeitor" << endl
    << " [6] - Encerrar sessão" << endl << endl;
    int escolha;
    string benf;
    cout << "Escolha uma opção: ";
    cin >> escolha;
    switch (escolha){
    case 1:
      cin.ignore();
      organizacao->cadastrarAnimal();
      break;
    case 2:
      cin.ignore();
      organizacao->cadastrarBenfeitor();
      organizacao->shellSort();
      break;
    case 3:
      organizacao->listarAnimais();
      break;
    case 4:
      organizacao->listarBenfeitores();
      break;
    case 5:
      cin.ignore();
      cout << "Digite o benfeitor que deseja procurar: " << endl;
      getline(cin, benf);
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
}