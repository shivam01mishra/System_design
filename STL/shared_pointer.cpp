#include<iostream>

using namespace std;
template<typename T>
class shared_pointer {
    T* ptr;
    int* reference_cnt;
    void decrease_cnt() {
        if (reference_cnt) {
            --(*reference_cnt);
            if (*reference_cnt == 0) {
                delete ptr;
                delete reference_cnt;
                ptr = nullptr;
                reference_cnt = nullptr;
            }
        }
    }
public:
    shared_pointer(shared_pointer&& temp) {
        ptr = temp.ptr;
        reference_cnt = temp.reference_cnt;
        temp.ptr = nullptr;
        temp.reference_cnt = nullptr;
    }
    explicit shared_pointer(T* input) : ptr(input), reference_cnt(new int(1)) {}
    shared_pointer() : ptr(nullptr), reference_cnt(nullptr) {}
    shared_pointer(const shared_pointer& temp) {
        ptr = temp.ptr;
        reference_cnt = temp.reference_cnt;
        if (reference_cnt) (*reference_cnt)++;
    }
    shared_pointer& operator=(const shared_pointer& temp) {
        if (this != &temp) {  // avoid self-assignment
            if (reference_cnt != nullptr) {
                decrease_cnt();
            }
            ptr = temp.ptr;
            reference_cnt = temp.reference_cnt;
            if (reference_cnt) (*reference_cnt)++;
        }
        return *this;
    }
    shared_pointer& operator=(shared_pointer&& temp) noexcept {
        if (this != &temp) {
            decrease_cnt(); // release current resource if any

            ptr = temp.ptr;
            reference_cnt = temp.reference_cnt;

            temp.ptr = nullptr;             // leave moved-from object safe
            temp.reference_cnt = nullptr;
        }
        return *this;
    }
    int use_count() {
        return (reference_cnt == nullptr) ? 0 : (*reference_cnt);
    }

    T& operator*() {
        return *ptr;
    }

    const	T& operator*() const {
        return *ptr;
    }

    ~shared_pointer() {
        decrease_cnt();

    }
};
int main() {
    shared_pointer<int>my_ptr1(new int(10));
    cout << (*my_ptr1);
    {
        shared_pointer<int>my_ptr2 = my_ptr1;
        cout << " " << (*my_ptr2);
        cout << " " << (my_ptr1.use_count());
    }

    cout << " " << (my_ptr1.use_count());

    return 0;

}