#pragma once
#include "headers.h"
#include "sprites.h"

class Player{
    private:
        map<string, Sprite *> sprites;
        int width, height;
        bool moving;
        string direction;
        SDL_Renderer * renderer;
        SpriteCache * cache;
        double starting_xpos = 0, starting_ypos = 0;
        

    public:
        string state;
        int points = 0;
        SDL_Rect d_rect = {};
        map<string, SDL_Rect> hitboxes = {};
        double x_pos = 0, y_pos = 0;
        int starting_life = 3;
        int lives = starting_life;
        double respawn_timer = 2;
        double power_timer = 5;
        int speed = 8;
        bool powered_up = false;
        bool dead;
        

        Player(SpriteCache * cache, int x, int y, int w, int h, string src);

        void Process(Clock * clock);
        void Move(string d);
        void Render();
        void SetPos(int x, int y);
        void Reset();
        void Died();
        void AddPoints(int points_added);
        bool CollisionCheck(SDL_Rect * rect, SDL_Rect * rectB);
        bool EatingPellet(SDL_Rect * rect);
        bool TouchingEnemy(SDL_Rect * rect);
        
        
        ~Player();

};