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
    sprites["VULNERABLE"] = new AnimatedSprite(cache, {0, 0, 16, 16}, {x, y, 32, 32}, "resources/vulnerable_ghost.bmp", 16, 4, .2);


    hitboxes["left"] = {d_rect.x, d_rect.y, 1,  h};
    hitboxes["right"] = {d_rect.x, d_rect.y, 1,  h};
    hitboxes["up"] = {d_rect.x, d_rect.y, w, 1};
    hitboxes["down"] = {d_rect.x, d_rect.y, w, 1};

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

    HitboxPositionUpdate();
    sprites[state]->Animate(clock);

    if (player->powered_up){
        state = "VULNERABLE";
    }else{
        state = "DEFAULT";
    }
}

void Ghost::PathFinding(Player * pl){}


void Ghost::HitboxPositionUpdate(){
    hitboxes["left"].x = d_rect.x;
    hitboxes["left"].y = d_rect.y;
    hitboxes["right"].x = d_rect.x + 24;
    hitboxes["right"].y = d_rect.y;
    hitboxes["up"].x = d_rect.x;
    hitboxes["up"].y = d_rect.y;
    hitboxes["down"].x = d_rect.x;
    hitboxes["down"].y = d_rect.y+24;

}

void Ghost::Move(string d){
    if ((d == "none") || (state == "DYING")){
        this->moving = false;
    }
    else {
        moving = true;
        direction = d;
    }

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
    HitboxPositionUpdate();
}

bool Ghost::TouchingPlayer(SDL_Rect * rect){
    SDL_HasIntersection(rect, &d_rect);
}

void Ghost::Render(){
    d_rect.x = (x_pos - int(d_rect.w / 2));
    d_rect.y = (y_pos - int(d_rect.h / 2));
    d_rect.w = sprites[state]->d_rect.w;
    d_rect.h = sprites[state]->d_rect.h;

    sprites[state]->SetPos(x_pos, y_pos);
    sprites[state]->Render();
}

void Ghost::Attack(){}

bool Ghost::CheckMove(string direction, SDL_Rect * walls){
    SDL_Rect * predicted_move = {};
    if (direction == "left"){
        for (auto const &hitbox : hitboxes){
            predicted_move->x = hitbox.second.x - speed;
            predicted_move->y = hitbox.second.y;
            predicted_move->w = hitbox.second.w;
            predicted_move->h = hitbox.second.h;

            if (SDL_HasIntersection(walls, predicted_move)){
                return false;
            }
            return true;
        }
    }
    if (direction == "right"){
        for (auto const &hitbox: hitboxes){
            predicted_move->x = hitbox.second.x + speed;
            predicted_move->y = hitbox.second.y;
            predicted_move->w = hitbox.second.w;
            predicted_move->h = hitbox.second.h;

            if (SDL_HasIntersection(walls, predicted_move)){
                return false;
            }
            return true;
        }
    }
    if (direction == "up"){
        for (auto const &hitbox: hitboxes){
            predicted_move->x = hitbox.second.x;
            predicted_move->y = hitbox.second.y - speed;
            predicted_move->w = hitbox.second.w;
            predicted_move->h = hitbox.second.h;

            if (SDL_HasIntersection(walls, predicted_move)){
                return false;
            }
            return true;
        }
    }
    if (direction == "down"){
        for (auto const &hitbox: hitboxes){
            predicted_move->x = hitbox.second.x;
            predicted_move->y = hitbox.second.y + speed;
            predicted_move->w = hitbox.second.w;
            predicted_move->h = hitbox.second.h;

            if (SDL_HasIntersection(walls, predicted_move)){
                return false;
            }
            return true;
        }
    }
}

Ghost::~Ghost(){}

Blinky::Blinky(SpriteCache * cache, int x, int y, int w, int h, string src, string t, Player * player) 
: Ghost(cache, x, y, w, h, src, t, player){
    sprites["DEFAULT"] = new AnimatedSprite(cache, {0, 0, 16, 16}, {x, y, 32, 32}, src, 16, 8, .2);
    state = "DEFAULT";

}

Pinky::Pinky(SpriteCache * cache, int x, int y, int w, int h, string src, string t, Player * player) 
: Ghost(cache, x, y, w, h, src, t, player){
    sprites["DEFAULT"] = new AnimatedSprite(cache, {0, 0, 16, 16}, {x, y, 32, 32}, src, 16, 8, .2);
    state = "DEFAULT";
}

Inky::Inky(SpriteCache * cache, int x, int y, int w, int h, string src, string t, Player * player) 
: Ghost(cache, x, y, w, h, src, t, player){
    sprites["DEFAULT"] = new AnimatedSprite(cache, {0, 0, 16, 16}, {x, y, 32, 32}, src, 16, 8, .2);
    state = "DEFAULT";
}

Clyde::Clyde(SpriteCache * cache, int x, int y, int w, int h, string src, string t, Player * player) 
: Ghost(cache, x, y, w, h, src, t, player){
    sprites["DEFAULT"] = new AnimatedSprite(cache, {0, 0, 16, 16}, {x, y, 32, 32}, src, 16, 8, .2);
    state = "DEFAULT";
}