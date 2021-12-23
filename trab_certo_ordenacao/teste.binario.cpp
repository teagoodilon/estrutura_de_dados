#include <iostream>
#include <cstring>
#include <fstream>

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


void le_arquivo_bin(ifstream& arquivo, ofstream& saida) {
  pacote umPacote;
  while(arquivo.read((char*) &umPacote, sizeof(umPacote))) {
    saida << umPacote.indice << " "
    << umPacote.tempo << " "
    << umPacote.origem << " "
    << umPacote.destino << " "
    << umPacote.protocolo << " "
    << umPacote.tamanho << " "
    << umPacote.informacao << endl;
  }
}

int main(){
  ifstream arquivo_bin_read("captura_pacotes.bin",ios::binary);
  ofstream saida_bin("saida.txt");
  le_arquivo_bin(arquivo_bin_read, saida_bin);
  return 0;
}