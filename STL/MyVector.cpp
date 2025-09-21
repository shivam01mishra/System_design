#include <iostream>
#include <stdexcept>
using namespace std;

template<typename T>
class MyVector {
    int cap;
    int my_size;
    T* arr;

public:
    MyVector() : cap(0), my_size(0), arr(nullptr) {}

    MyVector(size_t i) : cap(i), my_size(i), arr(new T[i]()) {}

    MyVector(size_t i, T value) : cap(i), my_size(i), arr(new T[i]()) {
        for (int j = 0; j < i; j++) {
            arr[j] = value;
        }
    }

    MyVector(const MyVector& temp)
        : cap(temp.cap), my_size(temp.my_size), arr(new T[temp.cap]()) {
        for (int j = 0; j < my_size; j++) {
            arr[j] = temp.arr[j];
        }
    }

    ~MyVector() {
        delete[] arr;
    }

    T& operator[](int i) {
        return arr[i];
    }

    const T& operator[](int i) const {
        return arr[i];
    }

    void push_back(const T& value) {
        if (arr == nullptr) {                // first element
            arr = new T[1];
            cap = 1;
        }
        else if (my_size == cap) {         // grow
            int new_cap = (cap == 0) ? 1 : 2 * cap;
            T* temp = new T[new_cap];
            for (int j = 0; j < my_size; j++) {
                temp[j] = arr[j];
            }
            delete[] arr;
            arr = temp;
            cap = new_cap;
        }
        arr[my_size] = value;
        my_size++;
    }

    T& back() {
        if (my_size == 0) {
            throw out_of_range("back() called on empty vector");
        }
        return arr[my_size - 1];
    }

    T pop_back() {
        if (my_size == 0) {
            throw out_of_range("pop_back() called on empty vector");
        }
        my_size--;
        return arr[my_size];
    }

    size_t size() const { return my_size; }
    size_t capacity() const { return cap; }
};

int main() {
    MyVector<int> v(10, 5);  // initialize with 5
    v[5] = 12;
    cout << v[5] << endl;

    MyVector<int> v2 = v;    // copy constructor
    cout << v2[5] << endl;

    MyVector<int> v3;        // empty vector
    v3.push_back(42);
    v3.push_back(100);
    cout << "v3: ";
    for (int i = 0; i < v3.size(); i++) {
        cout << v3[i] << " ";
    }
    cout << "\nLast element = " << v3.back() << endl;

    cout << "Popped: " << v3.pop_back() << endl;
    cout << "Now size = " << v3.size() << endl;

    return 0;
}
