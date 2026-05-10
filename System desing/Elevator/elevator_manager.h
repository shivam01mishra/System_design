#pragma once

#include "elevator.h"
#include "request.h"

#include <memory>
#include <vector>

class ElevatorManager {

private:

    std::vector<
        std::shared_ptr<Elevator>
    > m_elevators;

private:

    std::shared_ptr<Elevator>
    find_best_elevator(
        const Request& request
    );

public:

    void add_elevator(
        std::shared_ptr<Elevator>
            elevator
    );

    void handle_request(
        const Request& request
    );
};