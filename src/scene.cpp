#include "scene.h"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>

LevelScene::LevelScene(SDL_Renderer * r, Framebuffer * framebuffer, SpriteCache * sprite_cache, TextCache * text_cache){
    this->framebuffer = framebuffer;
    starting = true;
    running = false;  //dont forget to turn this back off.  True only for Testing purposes
    finished = false;
    paused = false;
    renderer = r;
    text_renderer = text_cache;
    
}


void LevelScene::AddPlayer(Player * pl){
    player = pl;
}

void LevelScene::Reset(){
    player->Reset();
    for (auto const &ghost : ghosts){
        ghost->Reset();
    }
    starting = true;
    running = false;
}

void LevelScene::Process(Clock * clock, KeyboardManager * keyboard, MouseManager * mouse, string * state, int width, int height, string * gender){
    if (starting){
        total_pellets = pellets.size() + big_pellets.size();
        pellets_collected = pellets_collected;
        
        running = true;
    }

    if (running){
        
        if (keyboard->KeyWasPressed(SDL_SCANCODE_P)){
            if (paused){
                paused = false;
            }else {
                paused = true;
            }
        }

        if (!paused){
            if (keyboard->KeyIsPressed(SDL_SCANCODE_A)){
                player->Move("left");
            }
            else if (keyboard->KeyIsPressed(SDL_SCANCODE_D)){
                player->Move("right");
            }
            else if (keyboard->KeyIsPressed(SDL_SCANCODE_W)){
                player->Move("up");
            }
            else if (keyboard->KeyIsPressed(SDL_SCANCODE_S)){
                player->Move("down");
            }
            else if (keyboard->KeyIsPressed(SDL_SCANCODE_R)){
                Reset();
            }

            // Wall Collision Correction
            for(auto const &wall : walls){
                player->offset_x = 0;
                player->offset_y = 0;

                if (player->CollisionCheck(&player->hitboxes["right"], &wall->d_rect)){
                    player->offset_x = -1;
                    player->Move("none");
                }
                if (player->CollisionCheck( &player->hitboxes["left"], &wall->d_rect)){
                    player->offset_x = 1;
                    player->Move("none");
                }
                if (player->CollisionCheck( &player->hitboxes["up"], &wall->d_rect)){
                    player->offset_y = 1;
                    player->Move("none");
                }
                if (player->CollisionCheck( &player->hitboxes["down"], &wall->d_rect)){
                    player->offset_y = -1;
                    player->Move("none");
                }
                player->SetPos(player->x_pos + player->offset_x, player->y_pos + player->offset_y);
            }

            // Player goes through tunnel and appears on the other end
            if (player->hitboxes["right"].x < -32 ){
                player->SetPos(760, player->y_pos);
            }
            if (player->hitboxes["left"].x > 770){
                player->SetPos(-1, player->y_pos);
            }

            // Pellet relocation instead of deleting
            for (auto const &pellet : pellets){
                if (player->EatingPellet(&pellet->d_rect)){
                    pellet->SetPos(-5, -5);
                    player->AddPoints(25);
                    pellets_collected += 1;
                }
            }
            
            for (auto const &big_pellet : big_pellets){
                if (player->EatingPellet(&big_pellet->d_rect)){
                    big_pellet->SetPos(-5, -5);
                    player->AddPoints(50);
                    pellets_collected += 1;
                    player->powered_up = true;
                    
                }
            }
            
            // Win Condition
            if (pellets_collected == total_pellets){
                win = true;
                *state = "CUTSCENE";
            }
            
            // Ghost Loop Conditions
            ManageEnemies(clock, player, keyboard, mouse);

            player->Process(clock);

        }
        
    }
    
}

void LevelScene::AddEnemy(Ghost * ghost){
    ghosts.push_back(ghost);
}

void LevelScene::ManageEnemies(Clock * clock, Player * player, KeyboardManager * keyboard, MouseManager * mouse){
    if (!paused){
        for (auto const &ghost : ghosts){
            ghost->Process(clock);

            if (keyboard->KeyIsPressed(SDL_SCANCODE_LEFT)){
                ghost->Move("left");
            }
            else if (keyboard->KeyIsPressed(SDL_SCANCODE_RIGHT)){
                ghost->Move("right");
            }
            else if (keyboard->KeyIsPressed(SDL_SCANCODE_UP)){
                ghost->Move("up");
            }
            else if (keyboard->KeyIsPressed(SDL_SCANCODE_DOWN)){
                ghost->Move("down");
            }


            for(auto const &wall : walls){
                ghost->offset_x = 0;
                ghost->offset_y = 0;

                if (ghost->CollisionCheck(&ghost->hitboxes["right"], &wall->d_rect)){
                    ghost->offset_x = -1;
                    ghost->Move("none");
                }
                if (ghost->CollisionCheck(&ghost->hitboxes["left"], &wall->d_rect)){
                    ghost->offset_x = 1;
                    ghost->Move("none");
                }
                if (ghost->CollisionCheck(&ghost->hitboxes["up"], &wall->d_rect)){
                    ghost->offset_y = 1;
                    ghost->Move("none");
                }
                if (ghost->CollisionCheck(&ghost->hitboxes["down"], &wall->d_rect)){
                    ghost->offset_y = -1;
                    ghost->Move("none");
                }
                ghost->SetPos(ghost->x_pos + ghost->offset_x, ghost->y_pos + ghost->offset_y);
            }




            if (player->TouchingEnemy(&ghost->d_rect)){
                if (player->powered_up){
                    ghost->eaten = true;
                }else{
                    player->Died();
                }
            }
        }
    }
}

LevelScene::~LevelScene(){}


void LevelScene::RenderScene(){
    framebuffer->SetActiveBuffer("GAME");
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    for (auto const &wall : walls){
        wall->Render();
    }
    
    level->Render();

    for (auto const &pellet : pellets){
        pellet->Render();
    }
    
    for (auto const &big_pellet : big_pellets){
        big_pellet->Render();
    }

    for (auto const &ghost: ghosts){
        ghost->Render();
    }

    player->Render();

    framebuffer->UnsetBuffers();
}

void LevelScene::SetBackground(SpriteCache * cache, int x, int y, int w, int h, string filepath){
    this->level = new Sprite(cache, {0, 0}, {x, y, w, h}, filepath);
}

MenuScene::MenuScene(SpriteCache * cache, Framebuffer * framebuffer, TextCache * text, Player * player){
    this->framebuffer = framebuffer;
    this->cache = cache;
    starting = true;
    running = false;
    finished = false;
    renderer = cache->renderer;
    text_cache = text;
    this->player = player;

    buttons["play"] = new SpriteButton(cache, "resources/play.bmp", 640, 360, 96, 64, {0, 0, 48, 32}, 2, 48, .06);
    buttons["quit"] = new SpriteButton(cache, "resources/quit.bmp", 640, 450, 96, 64, {0, 0, 48, 32}, 2, 48, .06);
    

    animate_interval = 1.2;
}

MenuScene::~MenuScene(){}

bool MenuScene::Process(Clock * clock, MouseManager * mouse, string * state, string * path, string * gender){
    if (starting){
        running = true;
    }
    if (running){
        seconds_passed += clock->delta_time_s;

        

        if (select_newgame){
            *state = "GAME";
            *path = "resources/level/pacman_level.mx";
            seconds_passed = 0;

            return 1;

        }
        
        if (!select_newgame){
            for (auto const &button : buttons){
                button.second->Process(clock);
                if (buttons["play"]->MouseClicking(mouse)){
                    select_newgame = true;
                }

                if (buttons["quit"]->MouseClicking(mouse)){
                    running = false;
                    starting = false;
                }
            }
        }


    }
    
    return 0;
}

void MenuScene::RenderScene(){
    //Rendering
    framebuffer->SetActiveBuffer("MENU");
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    

    for (auto const &button : buttons){
        
        button.second->Render();
    }

    for (auto const &options : gender_options){
        if (select_newgame){
            options.second->Render();
        }
    }

    framebuffer->UnsetBuffers();
}

CutScene::CutScene(SpriteCache * cache, Framebuffer * framebuffer, TextCache * text){
    this->cache = cache;
    this->framebuffer = framebuffer;
    this->text_renderer = text;

    starting = true;
    running = false;
    finished = false;

}

bool CutScene::Process(Clock * clock, KeyboardManager * keyboard, MouseManager * mouse, string * state, string * gender){
    if (starting){
        controlled_actors["pacman"] = new AnimatedSprite(cache, {0, 0, 16, 16}, {0, 360, 64, 64}, "resources/pacman_sprite.bmp", 16, 2, .06);
        controlled_actors["ms.pacman"] = new AnimatedSprite(cache, {0, 16, 18, 16}, {1344, 360, 64, 64}, "resources/mspacman_sprite.bmp", 16, 3, .06);
        
       running = true;
    }

    if (running){
        starting = false;
        

        if (!SDL_HasIntersection(&controlled_actors["pacman"]->d_rect, &controlled_actors["ms.pacman"]->d_rect)){
            controlled_actors["pacman"]->x += ((actor_speed * 10) * clock->delta_time_s);
            controlled_actors["ms.pacman"]->x -= ((actor_speed * 5) * clock->delta_time_s);
            for (auto const &actor: controlled_actors){
                    actor.second->Animate(clock);
                }
            }else {
                if (*gender == "boy"){
                    controlled_actors["boy"] = new AnimatedSprite(cache, {0, 16, 16, 16}, {controlled_actors["ms.pacman"]->x, controlled_actors["ms.pacman"]->y + 100, 24, 24}, "resources/pacman_sprite.bmp", 16, 2, .06);
                } 
                else if (*gender == "girl"){
                    controlled_actors["girl"] = new AnimatedSprite(cache, {0, 16, 18, 16}, {controlled_actors["ms.pacman"]->x, controlled_actors["ms.pacman"]->y + 100, 24, 24}, "resources/mspacman_sprite.bmp", 16, 3, .06);
                }
            }
    }
    
    
}

void CutScene::RenderScene(){

    framebuffer->SetActiveBuffer("CUTSCENE");
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (auto const &actor : controlled_actors){
       actor.second->Render();
    }


    framebuffer->UnsetBuffers();

}

