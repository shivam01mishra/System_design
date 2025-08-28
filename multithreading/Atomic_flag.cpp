#include<iostream>
#include<thread>
//#include<mutex>
#include<string>
#include<queue>
//#include<condition_variable>
#include<atomic>
using namespace std;

class Buffer {
	queue<int>q;
	/*mutex m;*/
	int cap;
	/*condition_variable cv;*/
	atomic_flag  af= ATOMIC_FLAG_INIT;
	void lock() {
		while (af.test_and_set())
		{
		}
	}
	void unlock() {
		af.clear();
	}
public:
	Buffer(int cp) : cap(cp)
	{
	}
	void push_data(int x) {
		while (true)
		{
			lock();
			if (q.size() < cap)
			{
				q.push(x);
				unlock();
				break;
			}
			
			unlock();
		}
	 
		 
	}
	int pop_data() {
		int x;
		while (true) {
			lock();
			if (!q.empty())
			{
				x= q.front(); q.pop();
				unlock();
				break;

			}
			
			unlock();
		}
		
		
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