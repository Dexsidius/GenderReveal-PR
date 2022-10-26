#pragma once
#include "headers.h"

class Clock {
    private:
        uint32_t last_time;
        uint32_t current_time;
    
    public:
        double delta_time s;
        double delta_time;
        Clock();
        void Tick();
        ~Clock();
}