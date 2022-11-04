#pragma once
#include "headers.h"

class Button {
    protected:
        SDL_Rect area;
        SDL_Renderer * renderer;
        string state;
        

    public:
        bool highlight= false;
        double x_pos;
        double y_pos;

        Button(int x, int y, int w, int h, SpriteCache * cache);
        virtual ~Button();

        virtual bool MouseTouching(MouseManager * mouse);
        virtual bool MouseClicking(MouseManager * mouse);
        virtual void Prcess(Clock * clock);
        virtual void Render();
};