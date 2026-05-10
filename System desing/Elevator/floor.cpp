#include "floor.h"

#include "request.h"

FloorButton::FloorButton(
        int floor_number,
        ElevatorManager&
            elevator_manager)

    : m_floor_number{
        floor_number
      },

      m_elevator_manager{
        elevator_manager
      }
{
}

void FloorButton::up(){

    Request request(
        m_floor_number,
        Direction::UP
    );

    m_elevator_manager
        .handle_request(
            request
        );
}

void FloorButton::down(){

    Request request(
        m_floor_number,
        Direction::DOWN
    );

    m_elevator_manager
        .handle_request(
            request
        );
}

