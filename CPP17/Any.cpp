#include<iostream>
#include<any>
#include<vector>
using namespace std;

class A {
	int value;
public:
	explicit A(int x) :value(x) {}
	void show_data() {
		cout << value << " ";
	}
};
class AnyVector {
	vector<std::any>data;
public:
	void push_back(std::any x) {
		data.push_back(x);
	}
	void print_idx(int i) {
		if (data[i].type() == typeid(int)) {
			cout << any_cast<int>(data[i])<<" ";
		}
		else if(data[i].type() == typeid(char)) {
			cout << any_cast<char>(data[i])<<" ";
		}
		else if (data[i].type() == typeid(A)) {
			any_cast<A&>(data[i]).show_data();
		}
	}
};

void fun(std::any x) {
	cout << std::any_cast<int>(x);
}
int main() {
	AnyVector v;
	A a(15);
	v.push_back(10);
	v.push_back('c');
	v.push_back(a);
	v.print_idx(0);
	v.print_idx(1);
	v.print_idx(2);
	return 0;
}