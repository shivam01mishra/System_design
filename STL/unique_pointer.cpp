#include<iostream>

using namespace std;
template<typename T>
class unique_pointer {
	T* ptr;
	unique_pointer(const unique_pointer& temp) = delete;
	void operator=(const unique_pointer& temp) = delete;
public:
	unique_pointer(unique_pointer&& temp) {
		ptr = temp.ptr;
		temp.ptr = nullptr;
	}
	explicit	unique_pointer(T* input) : ptr(input) {}
	unique_pointer() : ptr(nullptr) {}
	T& operator*() {
		return *ptr;
	}
	/*T operator[](size_t i) {
		return ptr[i];
	}*/
	const	T& operator*() const {
		return *ptr;
	}
	T* get() {
		return ptr;
	}
	T* release() {
		T* temp = ptr;
		ptr = nullptr;
		return temp;
	}

	~unique_pointer() {
		delete ptr;
	}

};
int main() {
	unique_pointer<int>my_ptr1(new int(10));
	int* ptr1 = my_ptr1.release();
	cout << (*ptr1);
	return 0;

}