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
    vector<int> erased;
    string type;
    string state;
    SDL_Rect d_rect = {};
    double x_pos, y_pos;
    int default_speed = 0;
    bool stunned_cooldown;
    double cooldown_timer = 0.0;
    double cooldown_time = 0.0;
    bool dead = false;
    Player * player;

    Ghost(SpriteCache * cache, int x, int y, int w, int h, string src, string t, Player * player);

    virtual void Process(Clock * clock, int height);
    virtual void Move(string d);
    void SetPos(int x, int y);
    void Reset();
    bool TouchingPlayer(SDL_Rect * rect);
    
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

