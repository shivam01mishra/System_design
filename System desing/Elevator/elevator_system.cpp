#include "elevator_manager.h"
#include "floor.h"

#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include <chrono>

void simulate_user_request(
        FloorButton& button,
        bool go_up){

    if(go_up){
        button.up();
    }
    else{
        button.down();
    }
}

int main(){

    ElevatorManager manager;

    // Create elevators

auto elevator1 =
    std::make_shared<Elevator>(
        1,
        0
    );

auto elevator2 =
    std::make_shared<Elevator>(
        2,
        5
    );

auto elevator3 =
    std::make_shared<Elevator>(
        3,
        10
    );

    manager.add_elevator(
        elevator1
    );

    manager.add_elevator(
        elevator2
    );

    manager.add_elevator(
        elevator3
    );

    // Create floor buttons

    FloorButton floor1(
        1,
        manager
    );

    FloorButton floor3(
        3,
        manager
    );

    FloorButton floor7(
        7,
        manager
    );

    FloorButton floor10(
        10,
        manager
    );

    // Simulate concurrent users

    std::thread t1(
        simulate_user_request,
        std::ref(floor1),
        true
    );

    std::thread t2(
        simulate_user_request,
        std::ref(floor7),
        false
    );

    std::thread t3(
        simulate_user_request,
        std::ref(floor3),
        true
    );

    std::thread t4(
        simulate_user_request,
        std::ref(floor10),
        false
    );

    // Wait for request threads

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    // Allow elevators time to process

    std::this_thread::sleep_for(
        std::chrono::seconds(15)
    );

    std::cout
        << "Simulation completed\n";

    return 0;
}