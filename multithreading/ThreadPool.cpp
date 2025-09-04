#include <thread>
#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <vector>

using namespace std;

class ThreadPool {
    queue<function<void()>> task_q;
    vector<thread> workers;
    mutex m;
    condition_variable cv;
    bool stop;

public:
    ThreadPool(int n) : stop(false) {
        for (int i = 0; i < n; i++) {
            workers.emplace_back([this]() {
                while (true) {
                    function<void()> task;
                    {
                        unique_lock<mutex> loc(m);
                        cv.wait(loc, [this]() { return stop || !task_q.empty(); });
                        if (stop && task_q.empty())
                            return; // exit worker thread
                        task = move(task_q.front());
                        task_q.pop();
                    }
                    task();
                }
                });
        }
    }

    template <class F>
    void push_task(F&& f) {
        {
            unique_lock<mutex> loc(m);
            task_q.push(std::forward<F>(f));
        }
        cv.notify_one(); // wake one worker
    }

    ~ThreadPool() {
        {
            unique_lock<mutex> lc(m);
            stop = true;
        }
        cv.notify_all();
        for (auto& t : workers) {
            t.join();
        }
    }
};

void fun() {
    cout << "function has been executed\n";
}

int main() {
    ThreadPool MythreadPool(5);
    for (int i = 0; i < 10; i++) {
        MythreadPool.push_task(fun);
    }
    return 0;
}
