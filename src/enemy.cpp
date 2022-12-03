#include "enemy.h"

Ghost::Ghost(SpriteCache * cache, int x, int y, int w, int h, string src, string t, Player * player){
    renderer = cache->renderer;
    this->player = player;
    this->cache = cache;

    x_pos = x;
    y_pos = y;
    starting_xpos = x_pos;
    starting_ypos = y_pos;
    width = w;
    height = h;

    d_rect.x = x;
    d_rect.y = y;
    d_rect.w = w;
    d_rect.h = h;

    sprites["DEFAULT"] = nullptr;
    sprites["VULNERABLE"] = new AnimatedSprite(cache, {0, 0, 16, 16}, {x, y, w, h}, "resources/vulnerable_ghost.bmp", 16, 4, .2);
    state = "";
    default_speed = 9;
    speed = default_speed;
}

void Ghost::Process(Clock * clock){

    if (direction == "left"){
        x_pos -= ((speed * 10) * clock->delta_time_s);
    }
    if (direction == "right"){
        x_pos += ((speed * 10) * clock->delta_time_s);
    }
    if (direction == "up"){
        y_pos -= ((speed * 10) * clock->delta_time_s);
    }
    if (direction == "down"){
        y_pos += ((speed * 10) * clock->delta_time_s);
    }

    sprites[state]->Animate(clock);

    if (player->powered_up){
        state = "VULNERABLE";
    }else{
        state = "DEFAULT";
    }
}

void Ghost::PathFinding(Player * pl){}

void Ghost::Move(string d){

}

void Ghost::Reset(){
    for (auto sprite : sprites){
        sprite.second->Reset();
    }
    eaten = false;
    state = "DEFAULT";
    SetPos(starting_xpos, starting_ypos);
}

void Ghost::SetPos(int x, int y){
    x_pos = x;
    y_pos = y;
}

bool Ghost::TouchingPlayer(SDL_Rect * rect){}

void Ghost::Render(){
    d_rect.x = (x_pos - int(d_rect.w / 2));
    d_rect.y = (y_pos - int(d_rect.h / 2));
    d_rect.w = sprites[state]->d_rect.w;
    d_rect.h = sprites[state]->d_rect.h;

    sprites[state]->SetPos(x_pos, y_pos);
    sprites[state]->Render();
}

void Ghost::Attack(){}

Ghost::~Ghost(){}

Blinky::Blinky(SpriteCache * cache, int x, int y, int w, int h, string src, string t, Player * player) 
: Ghost(cache, x, y, w, h, src, t, player){
    sprites["DEFAULT"] = new AnimatedSprite(cache, {0, 0, 16, 16}, {x, y, w, h}, src, 16, 8, .2);
    state = "DEFAULT";

}

Pinky::Pinky(SpriteCache * cache, int x, int y, int w, int h, string src, string t, Player * player) 
: Ghost(cache, x, y, w, h, src, t, player){
    sprites["DEFAULT"] = new AnimatedSprite(cache, {0, 0, 16, 16}, {x, y, w, h}, src, 16, 8, .2);
    state = "DEFAULT";
}

Inky::Inky(SpriteCache * cache, int x, int y, int w, int h, string src, string t, Player * player) 
: Ghost(cache, x, y, w, h, src, t, player){
    sprites["DEFAULT"] = new AnimatedSprite(cache, {0, 0, 16, 16}, {x, y, w, h}, src, 16, 8, .2);
    state = "DEFAULT";
}

Clyde::Clyde(SpriteCache * cache, int x, int y, int w, int h, string src, string t, Player * player) 
: Ghost(cache, x, y, w, h, src, t, player){
    sprites["DEFAULT"] = new AnimatedSprite(cache, {0, 0, 16, 16}, {x, y, w, h}, src, 16, 8, .2);
    state = "DEFAULT";
}