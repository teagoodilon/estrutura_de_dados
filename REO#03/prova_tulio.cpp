#include <iostream>
using namespace std;

typedef int VarType;

class Node{
friend class DoubleList;
private:
    VarType data;
    Node *next, *previous;
public:
    Node();
    Node(VarType value = 0);
};

Node::Node(){}

Node::Node(VarType value /* = 0*/) : data(value){
    next = previous = NULL;
}

class DoubleList{
private:
    //the very first node is called head 
    //and the last node is called the tail. 
    Node *head, *tail;
    int size;
    void deleteAll(); //delete all elements in the Doublelist
public:
    //defeaut constructer
    DoubleList();
    //copy constructer
    DoubleList(const DoubleList& other);
    //destructor
    ~DoubleList();
    bool isEmpty();
    void insert(VarType value);
    void insertAtStart(VarType value);
    void insertAtEnd(VarType value);
    void insertAtPosition(int pos, VarType value);
    void deleteFisrt();
    void deleteLast();
    void deletePosition(int pos);
    void deleteValue(VarType value);
    int find(VarType value); //return pos of the node
    void display();
    void funcA();
    void funcB(DoubleList &l);
};

DoubleList::DoubleList(){
    //the constructer will make them NULL to avoid garbage value
    head = NULL;
    tail = NULL;
    size = 0;
}

DoubleList::DoubleList(const DoubleList& other){
    head = NULL;
    tail = NULL;
    size = 0;

    //percorre a Doublelista recebida como parametro, copiando os dados;
    Node *temp = other.head;
    while(temp != NULL){
        insertAtEnd(temp->data);
        temp = temp->next;
    }
}

DoubleList::~DoubleList(){
    deleteAll();
}

void DoubleList::deleteAll(){
    Node *aux = head;
    Node *temp;
    //percorrendo Doublelista e deletando os nós
    while (aux != NULL){
        temp = aux;
        aux = aux->next;
        delete temp;
    }
    //redirecionando os ponteiros
    size = 0;
    head = NULL;
    tail = NULL;
}

bool DoubleList::isEmpty(){
    return (size == 0);
}

void DoubleList::insert(VarType value){
    insertAtEnd(value);
}

void DoubleList::insertAtStart(VarType value){
    Node *temp = new Node(value);
    if(isEmpty()){
         head = tail = temp;
    } else{
        temp->next = head;
        head->previous = temp;
        head = temp;
    }
    size++;
}

void DoubleList::insertAtEnd(VarType value){
    Node *temp = new Node(value);
    if(isEmpty()){
        head = tail = temp;
    } else{
        tail->next = temp;
        temp->previous = tail;
        tail = temp;
    }
    size++;
}

void DoubleList::insertAtPosition(int pos, VarType value){
    if(pos <= size and pos >= 0){
        if(isEmpty()){
            Node *temp = new Node(value);
            head = tail = temp;
        } else if(pos == 0){
            insertAtStart(value);
        } else if(pos == size){
            insertAtEnd(value);
        } else{
            Node *temp = new Node(value);
            Node *aux = head;
            int i = 0;
            while(i < pos-1){
                aux = aux->next;
                i++;
            }
            temp->next = aux->next;
            aux->next->previous = temp;
            aux->next = temp;
            temp->previous = aux;
        }
        size++;
    } else{
        cerr << "Posicao invalida\n";
        //exit(EXIT_FAILURE);
    }
}

int DoubleList::find(VarType value){
    Node *temp = head;
    int i = 0;
    while(temp != NULL and temp->data != value){
        i++;
        temp = temp->next;
    }
    if(temp == NULL){
        i = -1;
    }
    return i;
}

void DoubleList::deleteFisrt(){
    if(isEmpty()){
        cerr << "Remocao em Doublelista vazia\n";
        //exit(EXIT_FAILURE);
    }
    Node *aux = head;
    head = head->next;
    if(head != NULL){
        head->previous = NULL;
    }
    delete aux;
    size--;
    if(isEmpty()){
        tail = NULL;
    }
}

void DoubleList::deleteLast(){
    if(isEmpty()){
        cerr << "Remocao em Doublelista vazia\n";
       // exit(EXIT_FAILURE);
    }
    Node *aux = tail;
    tail = tail->previous;
    if(tail != NULL){
        tail->next = NULL;
    }
    delete aux;

    size--;
    if(isEmpty()){
        tail = head = NULL;
    }
}

void DoubleList::deletePosition(int pos){
    if(isEmpty()){
        cerr << "Remocao em Doublelista vazia\n";
        //exit(EXIT_FAILURE);
    }
    if(pos < 0  or pos > size){
        cerr << "Posicao invalida\n";
        //exit(NULL);
    }
    if(pos == 0){
        deleteFisrt();
    } else if(pos == size-1){
        deleteLast();
    } else{
        Node *aux = head;
        Node *anterior;
        int i = 0;
        while(i < pos){
            anterior = aux;
            aux = aux->next;
            i++;
        }
        aux->next->previous = anterior;
        anterior->next = aux->next;
        size--;
        delete aux;
    }
}

void DoubleList::deleteValue(VarType value){
    Node *aux = head;
    while(aux != NULL and aux->data != value){
        aux = aux->next;
    }
    if(aux == NULL){
        cerr << "Remocao de valor nao encontrado" << endl;
        //exit(EXIT_FAILURE);
    } else{
        Node *anterior = aux->previous;
        Node *proximo = aux->next;
        if(anterior != NULL)
            anterior->next = proximo;
        else
            head = aux->next;
        if(proximo != NULL)
            proximo->previous = anterior;
        else
            tail = aux->previous;
        delete aux;
    }
    size--;
    if(isEmpty()){
        head = tail = NULL;
    }
}

void DoubleList::display(){
    if(isEmpty()){
         cerr << "lista vazia" << endl;
         //exit(EXIT_FAILURE);
    }
    Node *temp = head;
    cout << "impressao direta: ";
    while(temp != NULL){
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
    cout << "impressao reversa: ";
    temp = tail;
    while(temp != NULL){
        cout << temp->data << " ";
        temp = temp->previous;
    }
    cout << endl;
}

void DoubleList::funcA(){
    Node *noh1 = head;
    Node *noh2;
    Node *noh3;

    while (noh1 != NULL){
        noh2 = noh1->previous;
        noh3 = noh1->next;

        if (noh1->data % 2 == 0){
            if (noh2 != NULL)
                noh2->next = noh3;
            else
                head = noh1->next;
            if (noh3 != NULL)
                noh3->previous = noh2;
            else
                tail = noh1->previous;
            delete noh1;
        }
        noh1 = noh3;
    }
}

void DoubleList::funcB(DoubleList &l){
    Node *noh1 = head;

    while (noh1 != NULL){
		
		if(noh1 -> data % 2 == 0){
			Node *noh2 = new Node(noh1->data);
			
			if(l.head == NULL){
				l.head = noh2;
				l.tail = noh2;
			}else{
				l.tail->next = noh2;
				noh2->previous = l.tail;
				l.tail = noh2;
			}
		}
        noh1 = noh1->next;
    }
}

int main(){

    DoubleList lista1, lista2;
    int m, n;
    cout << "m: ";
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        cin >> n;
        lista1.insertAtStart(n);
    }
    cout << "\nm: ";
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        cin >> n;
        lista2.insertAtEnd(n);
    }
    lista1.funcB(lista2);
    lista2.funcA();
    lista2.display();    
    // cout << "\t\tDoubleListas Dinamicas\t\t\n";
    // cout << "\nquant de valores a serem inseridos: ";
    // int quant;
    // cin >> quant;
    // VarType num;
    // DoubleList myDoubleList;
    // for (int i = 0; i < quant; i++){
    //     cin >> num;
    //     myDoubleList.insert(num);
    // }
    // cout << "\ndisplay:\n";
    // myDoubleList.display();
    // cout << "insertAtStart(18)\n";
    // myDoubleList.insertAtStart(18);
    // myDoubleList.display();
    // cout << "insertAtPosition(4, 25)\n";
    // myDoubleList.insertAtPosition(4, 25);
    // //cout << "display:\n";
    // myDoubleList.display();
    // cout << "inserir 12 e inserir o 50 no comeco\n";
    // myDoubleList.insert(12);
    // myDoubleList.insertAtStart(50);
    // myDoubleList.display();
    // cout << "find 0, 50, 12\n";
    // cout << "0 esta na posicao: " << myDoubleList.find(0) << endl;
    // cout << "50 esta na posicao: " << myDoubleList.find(50) << endl;
    // cout << "12 esta na posicao: " << myDoubleList.find(12) << endl;
    // cout <<"construtor de copia\n";
    // DoubleList myDoubleList2;
    // myDoubleList2 = myDoubleList;
    // cout << "display myDoubleList2:\n";
    // myDoubleList2.display();
    // cout << "delete last and display\n";
    // myDoubleList2.deleteLast();
    // myDoubleList2.display();
    // cout << "delete first and display\n";
    // myDoubleList2.deleteFisrt();
    // myDoubleList2.display();
    //cout << "delete at invalid position(50) and display\n";
    //myDoubleList2.deletePosition(50);
    //myDoubleList2.display();
    // cout << "delete at position 0 and display\n";
    // myDoubleList2.deletePosition(0);
    // myDoubleList2.display();
    // cout << "delete value 3 and display\n";
    // myDoubleList2.deleteValue(3);
    // myDoubleList2.display();
    return 0;
}