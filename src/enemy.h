#pragma once
#include "headers.h"
#include "sprites.h"
#include "player.h"


class Ghost{
    protected:
        map<string, Sprite *> sprites;
        int width, height;
        bool moving;
        string direction;
        int starting_xpos, starting_ypos;
        SDL_Renderer * renderer;
        SpriteCache * cache;

    public:
        string type;
        string state;
        SDL_Rect d_rect = {};
        map<string, SDL_Rect> hitboxes = {};
        map<string, tuple<int, int>> possible_moves = {};

        double x_pos, y_pos;
        int default_speed = 0;
        bool stunned_cooldown;
        double cooldown_timer = 0.0;
        double cooldown_time = 5.0;
        bool eaten = false;
        int speed = 8;
        int offset_x;
        int offset_y;
        Player * player;

        Ghost(SpriteCache * cache, int x, int y, int w, int h, string src, string t, Player * player);

        virtual void Process(Clock * clock);
        virtual void Move(string d);
        void SetPos(int x, int y);
        void Reset();
        bool TouchingPlayer(SDL_Rect * rect);
        void Attack();
        void PathFinding(Player * pl);
        void HitboxPositionUpdate();
        bool CheckMove(string direction, SDL_Rect * walls);
        bool CollisionCheck(SDL_Rect * rect, SDL_Rect * rectB);

        virtual void Render();
        virtual ~Ghost();
};

class Pinky : public Ghost {
    public:
        Pinky(SpriteCache * cache, int x, int y, int w, int h, string src, string t, Player * player);
};
    

class Blinky : public Ghost {
    public:
        Blinky(SpriteCache * cache, int x, int y, int w, int h, string src, string t, Player * player);
};

class Inky : public Ghost {
    public:
        Inky(SpriteCache * cache, int x, int y, int w, int h, string src, string t, Player * player);
};

class Clyde : public Ghost {
    public:
        Clyde(SpriteCache * cache, int x, int y, int w, int h, string src, string t, Player * player);
};

