#include <iostream>
using namespace std;

template <class T>
class Stack{
public:
    class Node;
private:
    Node* top;
    int size;
public:
    class Node{
    private:
        Node* next;
        T data;
        friend class Stack<T>;
    public:
        Node(T index_data){
        data = index_data;
        next = nullptr;
        };
    };
    Stack();
    ~Stack();
    void push(T index);
    int pop(T& out_value);
    int get_top(T& out_value);
    void clear();
    int is_empty();
    int get_size();
    void print_stack();
};

template <class T> Stack<T>::Stack(){
    this->top = nullptr;
    this->size = 0;
};

template <class T> Stack<T>::~Stack(){
    this->clear();
};

template <class T> void Stack<T>::push(T index){
    Node* new_node = new Node(index);
    new_node->next = this->top;
    this->top = new_node;
    this->size++;
};

template <class T> void Stack<T>::print_stack(){
    Node* walker = nullptr;
    walker = this->top;
    while(walker != nullptr){
        cout << walker->data << " ";
        walker = walker->next;
    }
};

template <class T> void Stack<T>::clear(){
    if(this->size == 0) return;
    Node* dlt_ptr = nullptr;
    while(this->top != nullptr){
        dlt_ptr = this->top;
        this->top = this->top->next;
        delete dlt_ptr; 
    }
};

template <class T> int Stack<T>::pop(T &out_value){
    if(this->size == 0) return 0;
    Node* dlt_ptr = nullptr;
    dlt_ptr = this->top;
    out_value = this->top->data;
    this->top = this->top->next;
    delete dlt_ptr;
    this->size --;
    return 1;
};

template <class T> int Stack<T>::get_top(T& out_value){
    if(this->size == 0) return 0;
    out_value = this->top->data;
    return 1;
}

template <class T> int Stack<T>::is_empty(){
    return (this->size == 0);
}

template <class T> int Stack<T>::get_size(){
    return this->size;
}