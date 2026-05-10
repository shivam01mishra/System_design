#pragma once

#include "status.h"

class Request {

public:

    int floor;

    Direction direction;

    Request(
        int floor_number,
        Direction dir
    )
        : floor{floor_number},
          direction{dir}
    {
    }
};