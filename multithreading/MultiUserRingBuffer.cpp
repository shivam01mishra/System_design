#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
using namespace std;

struct Node {
    int data;
    atomic<size_t> seq;
};

class Buffer {
    int cap;
    Node *q;
    atomic<size_t> head;
    atomic<size_t> tail;

public:
    Buffer(int cp) : cap(cp),q(new Node[cap]) , head(0), tail(0) {
        for (int i = 0; i < cap; i++) {
            q[i].seq.store(i, memory_order_relaxed);
        }
    }

    bool push_data(int x) {
        size_t pos = head.load(memory_order_relaxed);
        while (true) {
            Node& node = q[pos % cap];
            size_t seq_no = node.seq.load(memory_order_acquire);
            intptr_t dif = (intptr_t)seq_no - (intptr_t)pos;

            if (dif == 0) {
                if (head.compare_exchange_strong(pos, pos + 1,
                    memory_order_relaxed)) {
                    node.data = x;
                    node.seq.store(pos + 1, memory_order_release);
                    return true;
                }
            }
            else if (dif < 0) {
                return false; // full
            }
            else {
                pos = head.load(memory_order_relaxed);
            }
        }
    }

    bool pop_data(int& x) {
        size_t pos = tail.load(memory_order_relaxed);
        while (true) {
            Node& node = q[pos % cap];
            size_t seq_no = node.seq.load(memory_order_acquire);
            intptr_t dif = (intptr_t)seq_no - (intptr_t)(pos + 1);

            if (dif == 0) {
                if (tail.compare_exchange_strong(pos, pos + 1,
                    memory_order_relaxed)) {
                    x = node.data;
                    node.seq.store(pos + cap, memory_order_release);
                    return true;
                }
            }
            else if (dif < 0) {
                return false; // empty
            }
            else {
                pos = tail.load(memory_order_relaxed);
            }
        }
    }
};

void producer(Buffer& buff) {
    for (int i = 0; i < 100; i++) {
        while (!buff.push_data(i)) { /* spin */ }
    }
}

void consumer(Buffer& buff) {
    for (int i = 0; i < 100; i++) {
        int x;
        while (!buff.pop_data(x)) { /* spin */ }
        cout << x << " ";
    }
}

int main() {
    Buffer buf(10);
    thread t1(consumer, ref(buf));
    thread t2(producer, ref(buf));
    t1.join();
    t2.join();
    return 0;
}
