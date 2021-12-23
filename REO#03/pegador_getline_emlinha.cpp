#include <iostream>

using namespace std;

int main(){
  string entrada, telefone;
  getline(cin,entrada);
  unsigned int iterador = 0, i = 0;
  while ((iterador < entrada.length()) and (entrada[iterador] != '9')){
    iterador++;
  } 
  if (iterador == entrada.length()){
    cin >> telefone;
  } else {
    while (iterador < entrada.length()){
      telefone[i] = entrada[iterador];
      i++;
      iterador++;
    }
  }
  cout << entrada << endl << telefone;
  return 0;
}