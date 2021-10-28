#include <iostream>

using namespace std;

template <class T>
class SLinkedList {
public:
    class Node;
protected:
    Node* head;
    Node* tail;
    int count;
public:
    SLinkedList(){};
    ~SLinkedList(){
        this->clear();
    };

    class Node 
    {
        private:
            T data;
            Node* next;
            friend class SLinkedList<T>;
        public:
            Node() {
                next = 0;
            }
            Node(Node* next) {
                this->next = next;
            }
            Node(T data, Node* next) {
                this->data = data;
                this->next = next;
            };
    };

    void print_list();
    void clear();
    void add(const T&);
    void add(int, const T&);
    int size();
    void reverse_list();
    void delete_node(int);
};

template <class T>
void SLinkedList<T>::clear(){
    Node* dlt = nullptr;
    while(this->head != nullptr){
        dlt = this->head;
        this->head = this->head->next;
        delete dlt;
    }
};

template <class T>
void SLinkedList<T>::print_list(){
    Node* walker = nullptr;
    walker = this->head;
    while(walker != nullptr){
        cout << walker->data << " ";
        walker = walker->next;
    }
};

template <class T>
int SLinkedList<T>::size(){
     return this->count;
} ;

template <class T>
void SLinkedList<T>::reverse_list(){
    Node* current = nullptr;
        Node* pre = nullptr;
        Node* next = nullptr;
        current = this->head;
        while(current != nullptr){
            next = current->next;
            current->next = pre;
            pre = current;
            current = next;
        }
        this->head = pre;
};

template <class T>
void SLinkedList<T>::add(const T& e){
    Node* node = new Node;
    Node* walker = nullptr;
    node->data = e;
    node->next = nullptr;
    if(this->count == 0){
        this->head = node;
        this->count++;
    }
    else{
       walker = this->head;
       while(walker->next != nullptr){
           walker = walker->next;
       }
       walker->next = node;
       this->count++;
    }
};

template <class T>
void SLinkedList<T>::add(int index, const T& e){
        if(index < 0 || index > this->count) return;
        if(index == this->count){
            this->add(e);
            return;
        }
        if(index == 0){
            Node* new_node = new Node();           
            new_node->data = e;
            if(this->head == nullptr){
                this->head = new_node;
                this->count++;
            }
            else{
                new_node->next = this->head;
                this->head = new_node;
                this->count++;
            }
        }
        else{
            if(this->head == nullptr) return;
            else{
                Node* new_node = new Node();
                Node* walker = nullptr;
                walker = this->head;
                new_node->data = e;
                int count = 0;
                while(count < index - 1){
                    walker = walker->next;
                    count ++;
                }
                new_node->next = walker->next;
                walker->next = new_node;
                this->count++;
            }
        }   
};

template <class T>
void SLinkedList<T>::delete_node(int index){
    if(this->head == nullptr || index < 0 || index >= this->count) return;
    Node* current = nullptr;
    current = this->head;
    
    if(index == 0){
        this->head = this->head->next;
        delete current;
        return;
    }
    
    for(int i=0; i < index-1; i++){
        current = current->next;
    }
    Node* holder = nullptr;
    holder = current->next;
    current->next = current->next->next;
    delete holder;
};