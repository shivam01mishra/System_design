#include <iostream>
#include <variant>
#include <vector>
#include <type_traits>
using namespace std;

class A {
    int value;
public:
    explicit A(int x) : value(x) {}
    void show_data() const {
        cout << value << " ";
    }
};

class AnyVector {
    vector<variant<int, char, A>> data;
public:
    void push_back(variant<int, char, A> x) {
        data.push_back(x);
    }

    void print_idx(int i) {
        visit([](auto&& args) {
            using T = decay_t<decltype(args)>; // remove & and const
            if constexpr (is_same_v<T, int>) {
                cout << args << " ";
            }
            else if constexpr (is_same_v<T, char>) {
                cout << args << " ";
            }
            else if constexpr (is_same_v<T, A>) {
                args.show_data();
            }
            }, data[i]);
    }
};

int main() {
    AnyVector v;
    A a(15);
    v.push_back(10);
    v.push_back('c');
    v.push_back(a);

    v.print_idx(0); // prints: 10
    v.print_idx(1); // prints: c
    v.print_idx(2); // prints: 15
}
