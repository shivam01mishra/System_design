#include<iostream>
#include<string>
#include<mutex>
#include<thread>

using namespace std;

void fun1(int& n , mutex &m) {
	for (int i = 0; i < 10000; i++) {
		m.lock();
		n++;
		m.unlock();
	}
}

void fun2(int& n, mutex& m) {
	for (int i = 0; i < 10000; i++) {
		m.lock();
		n++;
		m.unlock();
	}
}

int main() {
	mutex m;
	int n = 0;
	thread t1(fun1, ref(n), ref(m));
	thread t2(fun2, ref(n), ref(m));
	t1.join();
	t2.join();

	cout << " final velue of n is :" << n;
	return 0;
}

