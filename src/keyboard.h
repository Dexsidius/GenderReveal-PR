#pragma once
#include "headers.h"

class KeyboardManager {
    private:
        // Variables

        const Uint8 * instance_keystate;
        Uint8 previous_keystate[SDL_NUM_SCANCODES];
        Uint8 current_keystate[SDL_NUM_SCANCODES];

    public:
        // Functions
        KeyboardManager();
        void Process();
        bool KeyIsPressed(int scancode);
        bool KeyWasPressed(int scancode);
};