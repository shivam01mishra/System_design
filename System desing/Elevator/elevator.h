#pragma once

#include "status.h"
#include "request.h"

#include <queue>
#include <vector>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <thread>

class Elevator {

private:

    int m_elevator_id;

    int m_current_floor;

    Status m_status;

    std::priority_queue<
        int,
        std::vector<int>,
        std::greater<>
    > up_queue;

    std::priority_queue<int> down_queue;

    mutable std::mutex m_mutex;

    std::condition_variable m_cv;

    std::thread m_worker_thread;

    bool m_stop;

private:

    void process_requests();

    void move_up_to_floor(
        int target_floor
    );

    void move_down_to_floor(
        int target_floor
    );

public:

    Elevator(
        int id,
        int initial_floor
    );

    ~Elevator();

    void add_request(
        const Request& request
    );

    int get_current_floor() const;

    Status get_status() const;

    int get_id() const;
};