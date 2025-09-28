#include<thread>
#include<iostream>
#include<queue>
#include<mutex>
#include<condition_variable>
using namespace std;


class Buffer {
	condition_variable cv;
	queue<int>q;
	mutex m;
	int max_size;
public:
	Buffer(int buffer_limit):max_size{buffer_limit}{}
	void push(int x) {
		{
			unique_lock<mutex>lc(m);
			cv.wait(lc, [this] {return this->q.size() < max_size; });
			q.push(x);
		}
		cv.notify_all();	
	}

	int pop() {
		int x;
		{
			unique_lock<mutex>lc(m);
			cv.wait(lc, [this] {return this->q.size(); });
			x = q.front();
			q.pop();
		}
		cv.notify_all();
		return x;
	}

};

void produser(Buffer& buffer,int max_rate){
	auto allow_time = std::chrono::steady_clock::now();
	auto interval = 1000 / max_rate;
	for (int i = 0; i < 100; i++) {
		buffer.push(i);
		allow_time += chrono::milliseconds(interval);
		this_thread::sleep_until(allow_time);
	}

}

void consumer(Buffer& buffer, int max_rate) {
	auto allow_time = std::chrono::steady_clock::now();
	auto interval = 1000 / max_rate;
	for (int i = 0; i < 100; i++) {
		int x=buffer.pop();
		cout << i << " ";
		allow_time += chrono::milliseconds(interval);
		this_thread::sleep_until(allow_time);
	}

}

int main()
{
	Buffer buffer(10);
	thread p(produser, ref(buffer), 20);
	thread c(consumer, ref(buffer), 10);
	p.join();
	c.join();
	return 0;
}