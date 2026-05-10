#include "elevator_manager.h"

#include <limits>
#include <cmath>

void ElevatorManager::add_elevator(
        std::shared_ptr<Elevator>
            elevator){

    m_elevators.push_back(
        elevator
    );
}

void ElevatorManager::handle_request(
        const Request& request){

    auto elevator =
        find_best_elevator(request);

    if(elevator){

        elevator->add_request(
            request
        );
    }
}

std::shared_ptr<Elevator>
ElevatorManager::find_best_elevator(
        const Request& request){

    if(m_elevators.empty()){
        return nullptr;
    }

    int best_distance =
        std::numeric_limits<int>::max();

    std::shared_ptr<Elevator>
        best_elevator = nullptr;

    for(auto& elevator :
        m_elevators){

        int current_floor =
            elevator->get_current_floor();

        int distance =
            std::abs(
                current_floor -
                request.floor
            );

        if(distance <
           best_distance){

            best_distance =
                distance;

            best_elevator =
                elevator;
        }
    }

    return best_elevator;
}