#include <iostream>
#include <utility>

class A {
    int first;
    int second;
public:
    A(int x, int y) : first(x), second(y) {}
    A() : first(0), second(0) {}

    void set_data(int x, int y) {
        first = x;
        second = y;
    }

    void show_data() {
        std::cout << first << " " << second << "\n";
    }
};

class memory_manager {
    char* base;
    int cap;
    int used;
public:
    memory_manager(int max_size)
        : base(new char[max_size]), cap(max_size), used(0) {
    }

    ~memory_manager() {
        delete[] base;
    }

    template<class T, class... Args>
    T* make_object(Args&&... args) {
        if (used + sizeof(T) > cap) return nullptr;
        char* place = base + used;
        T* temp = new(place) T(std::forward<Args>(args)...);
        used += sizeof(T);
        return temp;
    }
};

int main() {
    memory_manager my_memory(100);

    A* a = my_memory.make_object<A>();
    a->set_data(10, 20);
    a->show_data();  // prints: 10 20

    A* a1 = my_memory.make_object<A>(40, 50);
    a1->show_data(); // prints: 40 50

    // must call destructors manually (since we used placement new)
    a->~A();
    a1->~A();

    return 0;
}




































