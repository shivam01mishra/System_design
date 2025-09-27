#include<iostream>
using namespace std;
template<typename T>
class base {
protected:
	base() = default;
public:
	void fun() {
		static_cast<T*>(this)->fun();
	}
};
class chiled1:public base<chiled1>{
public:
	void fun() {
		cout << "this is chiled class1\n";
}
};
class chiled2:public base<chiled2>{
public:
	void fun() {
		cout << "this is chiled class2\n";
}
};

int main() {
	chiled1 c1;
	c1.fun();
	chiled2 c2;
	c2.fun();
	return 0;
}