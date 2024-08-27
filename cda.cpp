#include <iostream>
using namespace std;

template <typename T>
class DynamicArray {
private:
    T* data; // Pointer to first element
    size_t size; // number of element stored in array
    size_t capacity; // if size > capacity, resize

public:
    DynamicArray();
    ~DynamicArray();

    void push_back(const T& value);
    void pop_back();
    size_t getSize() const;
    size_t getCapacity() const;
    T& operator[](size_t index);
};

template <typename T>
DynamicArray<T>::DynamicArray() : size(0), capacity(1) {
    data = new T[capacity];
}

template <typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] data;
}

template <typename T>
void DynamicArray<T>::push_back(const T& value) {
    if (size == capacity) {
        capacity *= 2;
        T* newData = new T[capacity];

        for (size_t i = 0; i < size; ++i) {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
    }
    data[size++] = value;
}

template <typename T>
void DynamicArray<T>::pop_back() {
    if (size > 0) {
        --size;
    }
}

template <typename T>
T& DynamicArray<T>::operator[](size_t index) {
    if (index >= size) {
        throw out_of_range("Index out of range");
    }
    return data[index];
}

template <typename T>
size_t DynamicArray<T>::getSize() const {
    return size;
}

template <typename T>
size_t DynamicArray<T>::getCapacity() const {
    return capacity;
}

int main() {
    DynamicArray<int> arr;

    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    arr.push_back(4);

    cout << "Array size: " << arr.getSize() << endl;
    cout << "Array capacity: " << arr.getCapacity() << endl;

    arr.pop_back();

    cout << "Array size after pop: " << arr.getSize() << endl;

    for (size_t i = 0; i < arr.getSize(); ++i) {
        cout << arr[i] << " ";
    }

    return 0;
}