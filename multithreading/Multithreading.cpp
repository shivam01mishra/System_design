#include <iostream>
#include <thread>
using namespace std;

void fun1() {
    for (int i = 0; i < 5; i++) {
        cout << "Fun1: " << i << endl;
    }
}

void fun2() {
    for (int i = 0; i < 5; i++) {
        cout << "Fun2: " << i << endl;
    }
}

int main() {
    thread t1(fun1);
    thread t2(fun2);

    t1.join();
    t2.join();

    return 0;
}
