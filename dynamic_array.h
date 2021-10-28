#include <iostream>
using namespace std;

class DynamicArray{
    int capacity;
    int size;
    int *data;
public:
    DynamicArray(){
        capacity = 10;
        size = 0;
        data = new int[capacity];
    };
    DynamicArray(int newCapacity){
        capacity = newCapacity;
        size = 0;
        data = new int[capacity];
    };
    ~DynamicArray(){
        delete[] data;
    };
    void setCapacity(int);
    void ensureCapacity(int);
    void pack();
    void trim();
    void rangeCheck(int);
    void setData(int, int);
    int getData(int);
    void removeAt(int);
    void insertAt(int, int);
    void printArray();
};

void DynamicArray::setCapacity(int newCapacity){
    int *newData = new int[newCapacity];
    memcpy(newData, data, sizeof(int)*size);
    capacity = newCapacity;
    delete [] data;
    data = newData;
}

void DynamicArray::ensureCapacity(int minCapacity){
    if(capacity < minCapacity){
        int newCapacity = (capacity*3)/2 + 1;
        if(newCapacity < minCapacity) newCapacity = minCapacity;
        setCapacity(newCapacity);
    }
}

void DynamicArray::pack(){
    if(capacity/2 >= size){
        int newCapacity = (size*3)/2 +1;
        setCapacity(newCapacity);
    }
}

void DynamicArray::trim(){
    int newCapacity = size;
    setCapacity(newCapacity);
}

void DynamicArray::rangeCheck(int index){
    if(index >= size || index < 0)  throw "Over-bounded index !";
}

void DynamicArray::setData(int index, int value){
    rangeCheck(index);
    data[index] = value;
}

int DynamicArray::getData(int index){
    rangeCheck(index);
    return data[index];
}

void DynamicArray::removeAt(int index){
    rangeCheck(index);
    int pivot = size - index - 1;
    if(pivot > 0) memmove(data+index, data +index+1, sizeof(int)*pivot);
    size--;
    pack();
}

void DynamicArray::insertAt(int index, int value){
    if(index > size) throw "Over-bounded index !";
    ensureCapacity(index+1);
    int pivot = size - index;
    if(pivot !=0){
        memmove(data+index+1, data+index, sizeof(int)*pivot);
    }
    *(data+index)= value;
    size++;
}

void DynamicArray::printArray(){
    for(int i=0; i<size; i++){
        cout << *(data+i)<<" ";
    }
}
