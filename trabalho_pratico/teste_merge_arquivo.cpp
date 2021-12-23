#include <iostream>
#include <fstream>
using namespace std;
struct reg{
    string nome;
    int chave;
};

void intercala(reg* a, int inicio, int meio, int fim) {
    int i = inicio, j = meio + 1;
    int tamanho = fim - inicio + 1;
    reg* aux = new reg[tamanho];
    for (int k=0; k < tamanho; k++) {
        if ((i <= meio) and (j <= fim)){ 
            if (a[i].chave <= a[j].chave){ 
                aux[k] = a[i];
                i++;           
            } else { 
                aux[k] = a[j];
                j++;
            }    
        } else if (i > meio) {    
            aux[k] = a[j];
            j++;
        } else {          
            aux[k] = a[i];
            i++;
        }        
    }    
    for (int k=0; k < tamanho; k++){ 
        a[inicio + k] = aux[k];
    }
}

void mergesort(reg* a, int inicio, int fim){
    int meio;
    if (inicio < fim) {
        meio = (inicio + fim)/2; 
        mergesort(a, inicio, meio);
        mergesort(a, meio+1, fim);
        intercala(a, inicio, meio, fim);
    }
}

int main(){
    int quantidade;
    cin >> quantidade;
    reg* registro = new reg[quantidade];
    for(int i = 0; i < quantidade; i++){
        cin >> registro[i].nome >> registro[i].chave;
    }
    mergesort(registro, 0, quantidade - 1);
    string nome_arquivo;
    cin >> nome_arquivo;
    ofstream arquivo(nome_arquivo.c_str());
    arquivo.write((const char*) (registro), quantidade*sizeof(reg));
    delete[] registro;
    arquivo.close();
    return 0;
}