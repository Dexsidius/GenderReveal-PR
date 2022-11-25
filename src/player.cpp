#include "player.h"

Player::Player(SpriteCache * cache, int x, int y, int w, int h, string src){
    renderer = cache ->renderer;
    this->cache = cache;
    x_pos = x;
    y_pos = y;
    starting_xpos = x;
    starting_ypos = y;
    width = w;
    height = h;

    d_rect.x = x;
    d_rect.y = y;
    d_rect.w = w;
    d_rect.h = h;

    dead = false;
    moving = false;

    sprites["right"] = new AnimatedSprite(cache, {0, 0, 16, 16}, {x_pos, y_pos, d_rect.w, d_rect.h}, src, 16, 2, .06);
    sprites["left"] = new AnimatedSprite(cache, {0, 16, 16, 16}, {x_pos, y_pos, d_rect.w, d_rect.h}, src, 16, 2, .06);
    sprites["up"] = new AnimatedSprite(cache, {0, 32, 16, 16}, {x_pos, y_pos, d_rect.w, d_rect.h}, src, 16, 2, .06);
    sprites["down"] = new AnimatedSprite(cache, {0, 48, 16, 16}, {x_pos, y_pos, d_rect.w, d_rect.h}, src, 16, 2, .06);

    state = "right";
    
}

void Player::Process(Clock * clock){
    if (moving){
        if (direction == "left"){
            x_pos -= ((speed * 10) * clock->delta_time_s);
        }
        
        if (direction == "right"){
            x_pos += ((speed * 10) * clock->delta_time_s);
        }
        if (direction == "up"){
            y_pos -= ((speed * 10) * clock ->delta_time_s);
        }
        if (direction == "down"){
            y_pos += ((speed * 10) * clock ->delta_time_s);
        }

        state = direction;
        sprites[state]->Animate(clock);
    }
}

void Player::Died(){
    lives -= 1;
    state = "DYING";
}

void Player::Reset(){
    for (auto sprite : sprites){
        sprite.second->Reset();
    }
    state = "right";
    SetPos(starting_xpos, starting_ypos);
    lives = starting_life;
    respawn_timer = 0.0;
    dead = false;
}

bool Player::CollisionCheck(SDL_Rect * rect){
    cout << "touched" << endl;
    return SDL_HasIntersection(&d_rect, rect);
}

void Player::Move(string d){
    if ((d == "none") || (state == "DYING") || (state =="DEAD")){
        this->moving = false;
    }
    else {
        moving = true;
        direction = d;
        
    }
}

void Player::SetPos(int x, int y){
    starting_xpos = x;
    starting_ypos = y;
    x_pos = x;
    y_pos = y;
    
}

void Player::Render(){
    d_rect.x = (x_pos - int(d_rect.w / 2));
    d_rect.y = (y_pos - int(d_rect.h / 2));
    d_rect.w = sprites[state]->d_rect.w;
    d_rect.h = sprites[state]->d_rect.h;

    // Set the position of the rendered sprite to be the same position as the player
    sprites[state]->SetPos(x_pos, y_pos);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    sprites[state]->Render();
}

Player::~Player(){};