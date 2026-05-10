#include "elevator.h"

#include <iostream>
#include <chrono>
#include <thread>

std::mutex cout_mutex;

Elevator::Elevator(
        int id,
        int initial_floor)

    : m_elevator_id{id},
      m_current_floor{initial_floor},
      m_status{Status::IDLE},
      m_stop{false}
{
    {
        std::lock_guard<std::mutex>
            cout_lock(cout_mutex);

        std::cout
            << "[Elevator "
            << m_elevator_id
            << "] Started at floor "
            << m_current_floor
            << '\n';
    }

    m_worker_thread =
        std::thread(
            &Elevator::process_requests,
            this
        );
}

Elevator::~Elevator(){

    {
        std::lock_guard<std::mutex>
            lock(m_mutex);

        m_stop = true;
    }

    m_cv.notify_one();

    if(m_worker_thread.joinable()){
        m_worker_thread.join();
    }

    {
        std::lock_guard<std::mutex>
            cout_lock(cout_mutex);

        std::cout
            << "[Elevator "
            << m_elevator_id
            << "] Shutting down\n";
    }
}

int Elevator::get_current_floor() const{

    std::lock_guard<std::mutex>
        lock(m_mutex);

    return m_current_floor;
}

Status Elevator::get_status() const{

    std::lock_guard<std::mutex>
        lock(m_mutex);

    return m_status;
}

int Elevator::get_id() const{

    return m_elevator_id;
}

void Elevator::add_request(
        const Request& request){

    {
        std::lock_guard<std::mutex>
            lock(m_mutex);

        if(request.floor >
           m_current_floor){

            up_queue.push(
                request.floor
            );
        }
        else if(request.floor <
                m_current_floor){

            down_queue.push(
                request.floor
            );
        }
        else{
            return;
        }
    }

    {
        std::lock_guard<std::mutex>
            cout_lock(cout_mutex);

        std::cout
            << "[Elevator "
            << m_elevator_id
            << "] Request added for floor "
            << request.floor
            << '\n';
    }

    m_cv.notify_one();
}

void Elevator::process_requests(){

    while(true){

        std::unique_lock<std::mutex>
            lock(m_mutex);

        m_cv.wait(
            lock,
            [this]{
                return m_stop ||
                       !up_queue.empty() ||
                       !down_queue.empty();
            }
        );

        if(m_stop){
            break;
        }

        while(!up_queue.empty()){

            int target =
                up_queue.top();

            up_queue.pop();

            lock.unlock();

            move_up_to_floor(
                target
            );

            lock.lock();
        }

        while(!down_queue.empty()){

            int target =
                down_queue.top();

            down_queue.pop();

            lock.unlock();

            move_down_to_floor(
                target
            );

            lock.lock();
        }

        m_status = Status::IDLE;
    }
}

void Elevator::move_up_to_floor(
        int target_floor){

    {
        std::lock_guard<std::mutex>
            lock(m_mutex);

        m_status =
            Status::MOVING_UP;
    }

    while(true){

        {
            std::lock_guard<std::mutex>
                lock(m_mutex);

            if(m_current_floor >=
               target_floor){

                break;
            }

            ++m_current_floor;

            {
                std::lock_guard<std::mutex>
                    cout_lock(cout_mutex);

                std::cout
                    << "[Elevator "
                    << m_elevator_id
                    << "] Moving UP -> Floor "
                    << m_current_floor
                    << '\n';
            }
        }

        std::this_thread::sleep_for(
            std::chrono::milliseconds(500)
        );
    }

    {
        std::lock_guard<std::mutex>
            cout_lock(cout_mutex);

        std::cout
            << "[Elevator "
            << m_elevator_id
            << "] Door OPEN at floor "
            << m_current_floor
            << '\n';
    }

    std::this_thread::sleep_for(
        std::chrono::seconds(1)
    );
}

void Elevator::move_down_to_floor(
        int target_floor){

    {
        std::lock_guard<std::mutex>
            lock(m_mutex);

        m_status =
            Status::MOVING_DOWN;
    }

    while(true){

        {
            std::lock_guard<std::mutex>
                lock(m_mutex);

            if(m_current_floor <=
               target_floor){

                break;
            }

            --m_current_floor;

            {
                std::lock_guard<std::mutex>
                    cout_lock(cout_mutex);

                std::cout
                    << "[Elevator "
                    << m_elevator_id
                    << "] Moving DOWN -> Floor "
                    << m_current_floor
                    << '\n';
            }
        }

        std::this_thread::sleep_for(
            std::chrono::milliseconds(500)
        );
    }

    {
        std::lock_guard<std::mutex>
            cout_lock(cout_mutex);

        std::cout
            << "[Elevator "
            << m_elevator_id
            << "] Door OPEN at floor "
            << m_current_floor
            << '\n';
    }

    std::this_thread::sleep_for(
        std::chrono::seconds(1)
    );
}