#include "buttons.h"

Button::Button(int x, int y, int w, int h){
    x_pos = x;
    y_pos = y;
    area.x = x;
    area.y = y;
    area.w = w;
    area.h = h;
}

Button::~Button(){}

bool Button::MouseTouching(MouseManager * mouse){
    return mouse->IsTouching(&area);
}

bool Button::MouseClicking(MouseManager * mouse){
    return MouseTouching(mouse) && mouse->IsClicking(&area);
}

void Button::Process(Clock * clock, MouseManager * mouse){
    if (MouseTouching(mouse)){
        this->highlight = true;
    }
}

void Button::Render(){}

