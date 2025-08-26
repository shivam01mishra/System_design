#include<iostream>
#include<thread>
#include<mutex>
#include<string>
#include<queue>
#include<condition_variable>
using namespace std;

class Buffer {
	queue<int>q;
	mutex m;
	int cap;
	condition_variable cv;
public:
	Buffer(int cp): cap(cp)
	{ }
	void push_data(int x) {
		unique_lock<mutex>lc(m);
		cv.wait(lc, [this] { return q.size() < cap; });
		q.push(x);
		lc.unlock();
		cv.notify_one();
	}
	int pop_data() {
		unique_lock<mutex>lc(m);
		cv.wait(lc, [this] { return !q.empty(); });
		int x = q.front(); q.pop();
		lc.unlock();
		cv.notify_one();
		return x;
	}
};


void producer(Buffer& buff) {
	for (int i = 0; i < 100; i++) {
		buff.push_data(i);
	}

}
void consumer(Buffer& buff) {
	
	for (int i = 0; i < 100; i++) {
		cout << buff.pop_data() << " ";
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