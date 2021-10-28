#include <iostream>
#include <string>
#include <sstream>

using namespace std;

template<class T>
class BinarySearchTree
{
public:
    class Node;
private:
    Node* root;
public:
    BinarySearchTree() : root(nullptr) {}

    ~BinarySearchTree(){
        this->clear(this->root);
    };

    void add(T value){
        if(this->root == nullptr) {Node* newNode = new Node(value); this->root = newNode; return;}
        Node* walker = nullptr;
        Node* holder = nullptr;
        walker = this->root;
        while(walker != nullptr){
            holder = walker;
            if(value <= walker->value)     walker = walker->pLeft;
            else if(value > walker->value) walker = walker->pRight;
        }
        Node* newNode = new Node(value);
        if(value <= holder->value){
            holder->pLeft = newNode;
        }
        else holder->pRight = newNode;
        return;
    };

    T getMin(){
        Node* walker = nullptr;
        walker = this->root;
        while(walker->pLeft != nullptr){
            walker = walker->pLeft;
        }
        return walker->value;
    };

    T getMax(){
        Node* walker = nullptr;
        walker = this->root;
        while(walker->pRight != nullptr){
            walker = walker->pRight;
        }
        return walker->value;
    };

    string inOrderRec(Node* root) {
        stringstream ss;
        if (root != nullptr) {
            ss << inOrderRec(root->pLeft);
            ss << root->value << " ";
            ss << inOrderRec(root->pRight);
        }
        return ss.str();
    }
    
    string inOrder(){
        return inOrderRec(this->root);
    };
    
    void run_count(Node* root, int& count){
        if(root->pLeft!=nullptr && root->pRight!=nullptr) count ++;
        if(root->pLeft != nullptr) run_count(root->pLeft, count);
        if(root->pRight != nullptr) run_count(root->pRight, count);
        return;
    };

    int countTwoChildrenNode()
    {
        int count = 0;
        run_count(this->root, count);
        return count;
    };

    bool find(T i) {
        if(this->root == nullptr) return false;
        Node* walk = nullptr;
        walk = this->root;
        while(walk != nullptr){
            if(i < walk->value) walk = walk->pLeft;
            else if(i > walk->value) walk = walk->pRight;
            else return true;
        }
        return false;
    };

    void run_sum(Node* root, T& sum, T l, T r){
        if(root == nullptr) return;
        if(root->value >= l && root->value <= r) sum = sum + root->value;
        run_sum(root->pLeft, sum, l, r);
        run_sum(root->pRight, sum, l, r);
        return;
    };

    T sum(T l, T r) {
        T sum = 0;
        run_sum(this->root, sum, l, r);
        return sum;
    };

    string preOrderRec(Node* root){
        stringstream ss;
        if (root != nullptr) {
            ss << root->value << " ";
            ss << preOrderRec(root->pLeft);
            ss << preOrderRec(root->pRight);
        }
        return ss.str();
    };
    
    string preOrder() {
        return preOrderRec(this->root);
    };

    string postOrderRec(Node* root){
        stringstream ss;
        if (root != nullptr) {
            ss << postOrderRec(root->pLeft);
            ss << postOrderRec(root->pRight);
            ss << root->value << " ";
        }
        return ss.str();
    };

    string postOrder() {
        return postOrderRec(this->root);
    };

    int getHeight() {
        return run_getHeight(this->root); 
    };

    int run_getHeight(Node* root){
        if(root==nullptr) return 0;
        else{
            int lh = run_getHeight(root->pLeft);
            int rh = run_getHeight(root->pRight);
            if(lh > rh) return lh+1;
            else return rh+1;
        }
    };

    void run_sumOfLeafs(Node* root, T& sum){
        if(root == nullptr) return;
        if(root->pLeft==nullptr && root->pRight==nullptr) sum = sum + root->value;
        if(root->pLeft!=nullptr) run_sumOfLeafs(root->pLeft, sum);
        if(root->pRight!=nullptr) run_sumOfLeafs(root->pRight, sum);
        return;
    };
    
    T sumOfLeafs(){
        T sum = 0;
        run_sumOfLeafs(this->root, sum);
        return sum;
    };

    int run_getDiameter(Node* root){
        if(root == nullptr) return 0;
        int v1 = run_getHeight(root->pLeft) + run_getHeight(root->pRight) + 1;
        int a = run_getDiameter(root->pLeft), b = run_getDiameter(root->pRight);
        int v2 = ((a>b)?a:b);
        return ((v1>v2)?v1:v2);
    };

    int getDiameter(){
        return run_getDiameter(this->root);
    };

    class Node
    {
    private:
        T value;
        Node* pLeft, * pRight;
        friend class BinarySearchTree<T>;
    public:
        Node(T value) : value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };

    void run_isBST(Node* root, int& check){
        if(root == nullptr) return;
        if(root->pLeft != nullptr){
            if(root->value <= root->pLeft->value) check++;
        }
        if(root->pRight != nullptr){
            if(root->value >= root->pRight->value) check++;
        }
        run_isBST(root->pLeft, check);
        run_isBST(root->pRight, check);
    };
    
    bool isBST() {
        int check = 0;
        run_isBST(this->root, check);
        return ((check>0)? false : true);
    };

    void clear(Node* node){
        if(node == nullptr) return;
        clear(node->pLeft);
        clear(node->pRight);
        delete node;
    };

    void delete_node(T value){
        if(this->root == nullptr) return;
        if(value == this->root->value){
            if(this->root->pLeft == nullptr && this->root->pRight == nullptr){
                Node*temp = nullptr;
                temp = this->root;
                this->root = nullptr;
                delete temp;
            }
            else if(this->root->pLeft == nullptr || this->root->pRight == nullptr){
                if(this->root->pLeft != nullptr){
                    Node*temp = nullptr;
                    temp = this->root;
                    this->root = this->root->pLeft;
                    delete temp;
                }
                else{
                    Node*temp = nullptr;
                    temp = this->root;
                    this->root = this->root->pRight;
                    delete temp;
                }
            }
        }
        Node *walk = nullptr, *holder = nullptr, *parent = nullptr;
        walk = this->root;
        while(walk != nullptr){
            if(value < walk->value){
                parent = walk;
                walk = walk->pLeft;
            }
            else if(value > walk->value){
                parent = walk;
                walk = walk->pRight;
            }
            else {
                holder = walk;
                break;
            }
        }
        if(holder == nullptr) return;
        else{
            if(holder->pLeft == nullptr && holder->pRight==nullptr){
                if(parent->pLeft == holder){
                    parent->pLeft = nullptr; delete holder;
                }
                else{parent->pRight = nullptr; delete holder;}
            }
            else if(holder->pLeft == nullptr || holder->pRight==nullptr){
                if(holder->pLeft != nullptr){
                    if(parent->pLeft == holder){
                        parent->pLeft = holder->pLeft; delete holder;
                    }
                    else{parent->pRight = holder->pLeft; delete holder;}
                }
                else {
                    if(parent->pLeft == holder){
                        parent->pLeft = holder->pRight; delete holder;
                    }
                    else{parent->pRight = holder->pRight; delete holder;}
                }
            }
            else{
                parent = holder;
                walk = holder->pRight;
                while(walk->pLeft != nullptr){
                    parent = walk;
                    walk = walk->pLeft;
                }
                holder->value = walk->value;
                if(parent == holder){
                    holder->pRight = holder->pRight->pRight;
                    delete walk;
                }
                else{
                    if(walk->pRight == nullptr){
                        parent->pLeft = nullptr;
                        delete walk;
                    }
                    else{
                        parent->pLeft = walk->pRight;
                        delete walk;
                    }
                }
            }
        }
    };

    struct node{
        Node* data;
        node* next; 
        node(Node* a) : data(a), next(nullptr) {};
    };
    
    struct queue{
        node* front;
        node* rear;
        int count;
        queue() : front(nullptr) , rear(nullptr), count(0) {};
    };
    
    void enQueue(queue& a, Node*x){
            node* new_node = new node(x);
            if(a.count == 0) a.front = new_node;
            else a.rear->next = new_node;
            a.rear = new_node;
            a.count++; 
    };

    Node* deQueue(queue& a){
            node* dlt = nullptr;
            Node* out_value = a.front->data;
            dlt = a.front;
            if(a.count == 1){
                a.rear = nullptr;
            }
            a.front = a.front->next;
            delete dlt;
            a.count--;
            return out_value;
    };

    void BFS(){
        Node* current = nullptr;
        current = this->root;
        queue a;
        while(current != nullptr){
            cout << current->value << " ";
            if(current->pLeft  != nullptr) enQueue(a, current->pLeft);
            if(current->pRight != nullptr) enQueue(a, current->pRight);
            if(a.count != 0) current = deQueue(a);
            else current = nullptr;
        }
    };
};
