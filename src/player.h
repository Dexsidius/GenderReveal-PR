#pragma once
#include "headers.h"
#include "sprites.h"

class Player{
    private:
    map<string, Sprite *> sprites;
    int width, height;
    bool moving;
    string string_direction;
    SDL_Renderer * renderer;
    SpriteCache * cache;
    double starting_xpos = 0, starting_ypos = 0;

    public:
        int points;
        SDL_Rect d_rect = {};
        double x_pos = 0, y_pos = 0;
        int starting_life = 3;
        int lives = starting_life;
        int speed;
        bool powered_up = false;
        Player(SpriteCache * cache, int x, int y, int w, int h, string src);

        void Process(Clock * clock);
        void Move(string d);
        void Render();
        void SetPos(int x, int y);
        void Reset();
        
        
        ~Player();

};