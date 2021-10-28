#include <iostream>

using namespace std;

template <class T>
class Queue{
public:
    class Node;
private:
    Node* front;
    Node* rear;
    int count;
public:
    class Node{
        private:
            T data;
            Node* next;
            friend class Queue<T>;
        public:
            Node(T value){
                data = value;
                next = nullptr;
        };
    };

    Queue(){
        this->front = nullptr;
        this->rear = nullptr;
        this->count = 0;
    };

    ~Queue(){
        this->clear();
    };

    void enQueue(T);
    int deQueue(T&);
    int get_front(T&);
    int get_rear(T&);
    void clear();
    int is_empty();
    int get_size();
    void print_queue();
};

template <class T>
void Queue<T>::enQueue(T index){
    Node* node = new Node(index);
    if(this->count == 0) this->front = node;
    else this->rear->next = node;
    this->rear = node;
    this->count++; 
};

template <class T>
int Queue<T>::deQueue(T& out_value){
    if(this->count == 0) return 0;
    Node* dlt = nullptr;
    out_value = this->front->data;
    dlt = this->front;
    if(this->count == 1){
        this->rear = nullptr;
    }
    this->front = this->front->next;
    delete dlt;
    this->count--;
    return 1;
};

template <class T>
int Queue<T>::get_front(T& out_value){
    if(this->count == 0) return 0;
    out_value = this->front->next;
    return 1;
};

template <class T>
int Queue<T>::get_rear(T& out_value){
    if(this->count == 0) return 0;
    out_value = this->rear->data;
    return 1;
};

template <class T>
void Queue<T>::clear(){
    Node* current = nullptr;
    while(this->front != nullptr){
        current = this->front;
        this->front = this->front->next;
        delete current;
    }
    this->rear = nullptr;
};

template <class T>
int Queue<T>::is_empty(){
    return (this->count == 0);
};

template <class T>
int Queue<T>::get_size(){
    return this->count;
};

template <class T>
void Queue<T>::print_queue(){
    Node* walker = nullptr;
    walker = this->front;
    while(walker != nullptr){
        cout << walker->data << " ";
        walker = walker->next;
    }
};