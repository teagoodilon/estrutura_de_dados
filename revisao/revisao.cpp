
#include <iostream>

using namespace std;

int main(){
    int vetorA[8]={1,4,5,9,12,3,0,99};
    int vetorB[8], j = 0;
    
    for (int i = 7; i >= 0; i--){
        vetorB[j]=vetorA[i];
        j++;
    }
    for (int i = 0; i < 7; i++){
        cout<<vetorB[i]<<" ";
    }
    return 0;	
}
