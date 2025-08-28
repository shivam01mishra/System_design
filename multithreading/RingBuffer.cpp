#include<iostream>
#include<thread>
//#include<mutex>
#include<string>
//#include<queue>
#include<vector>
//#include<condition_variable>
#include<atomic>
using namespace std;

class Buffer {
	vector<int>q;
	/*mutex m;*/
	int cap;
	atomic<int> head;
	atomic<int>tail;
	 
public:
	Buffer(int cp) : cap(cp), head(0),tail(0)
	{
		q.resize(cp);
	}
	bool push_data(int x) {
		 
		int current_head = head.load(memory_order_acquire);
		int next_head = (current_head + 1) % cap;

		if (next_head == tail.load(memory_order_acquire)) {
			return 0;
		}

		q[current_head] = x;

		

		head.store(next_head,memory_order_release);
		return true;
	}
	bool pop_data(int& x) {
		int current_tail = tail.load(memory_order_acquire);

		if (current_tail == head.load(memory_order_acquire)) {
			return 0;
		}

		 x= q[current_tail];

		current_tail=(current_tail+1)%cap ;

		tail.store(current_tail,memory_order_release);
		return true;
	}
};


void producer(Buffer& buff) {
	for (int i = 0; i < 100; i++) {
		bool run = 1;
		while(run)
			run = !buff.push_data(i);
	}

}
void consumer(Buffer& buff) {

	for (int i = 0; i < 100; i++) {
		bool run = 1;
		int x;
		while (run) {
			if (buff.pop_data(x))
			{
				cout << x << " ";
				run = 0;
			}
		}
		
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