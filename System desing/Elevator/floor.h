#pragma once

#include "elevator_manager.h"

class FloorButton {

private:

    int m_floor_number;

    ElevatorManager&
        m_elevator_manager;

public:

    FloorButton(
        int floor_number,
        ElevatorManager&
            elevator_manager
    );

    void up();

    void down();
};