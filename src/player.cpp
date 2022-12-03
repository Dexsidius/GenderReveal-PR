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
    sprites["DYING"] = new AnimatedSprite(cache, {0, 0, 16, 16}, {x_pos, y_pos, d_rect.w, d_rect.h}, "resources/dying_pacman.bmp", 16, 10, .06);

    hitboxes["left"] = {d_rect.x, d_rect.y, 1,  h};
    hitboxes["right"] = {d_rect.x, d_rect.y, 1,  h};
    hitboxes["up"] = {d_rect.x, d_rect.y, w, 1};
    hitboxes["down"] = {d_rect.x, d_rect.y, w, 1};

    state = "right";
    
}

void Player::Process(Clock * clock){
    if (moving){
        if (direction == "left"){
            x_pos -= ((speed * 10) * clock->delta_time_s);
            HitboxPositionUpdate();
        }
        
        if (direction == "right"){
            x_pos += ((speed * 10) * clock->delta_time_s);
            HitboxPositionUpdate();
        }
        if (direction == "up"){
            y_pos -= ((speed * 10) * clock ->delta_time_s);
            HitboxPositionUpdate();
        }
        if (direction == "down"){
            y_pos += ((speed * 10) * clock ->delta_time_s);
            HitboxPositionUpdate();
        }

        // TODO: Update Hitboxes x,y with every movement to track PacMan Collision
        if (powered_up){
            power_time += clock->delta_time_s;
            if (power_time >= power_timer){
                power_time = 0;
                powered_up = false;
            }
        }

        state = direction;
        sprites[state]->Animate(clock);

        cout << x_pos << ", " << y_pos << endl;
        cout << hitboxes[state].x << ", " << hitboxes[state].y << endl;
    }
}

void Player::Died(){
    lives -= 1;
    state = "DYING";
    dead = true;
}

void Player::Reset(){
    for (auto sprite : sprites){
        sprite.second->Reset();
    }
    state = "right";
    SetPos(starting_xpos, starting_ypos);
    lives = starting_life;
    respawn_timer = 3.0;
    dead = false;
}

bool Player::CollisionCheck(SDL_Rect * rect, SDL_Rect * rectB){
    return SDL_HasIntersection(rect, rectB); 

}

bool Player::TouchingEnemy(SDL_Rect * rect){
    return SDL_HasIntersection(&d_rect, rect);
}

bool Player::EatingPellet(SDL_Rect * rect){
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
    HitboxPositionUpdate();
    
    
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

    for (auto const &hitbox : hitboxes){
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &hitbox.second);
    }
}

void Player::AddPoints(int points_added){
    points += points_added;
}

void Player::HitboxPositionUpdate(){
    hitboxes["left"].x = d_rect.x;
    hitboxes["left"].y = d_rect.y;
    hitboxes["right"].x = d_rect.x + 24;
    hitboxes["right"].y = d_rect.y;
    hitboxes["up"].x = d_rect.x;
    hitboxes["up"].y = d_rect.y;
    hitboxes["down"].x = d_rect.x;
    hitboxes["down"].y = d_rect.y+24;

}

Player::~Player(){};