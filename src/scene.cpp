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
                    player->offset_y = + 1;
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
            }
            
            // Ghost Loop Conditions
            ManageEnemies(clock, player);

            player->Process(clock);
        }
        
    }
    
}

void LevelScene::AddEnemy(Ghost * ghost){
    ghosts.push_back(ghost);
}

void LevelScene::ManageEnemies(Clock * clock, Player * player){
    for (auto const &ghost : ghosts){
        ghost->Process(clock);

        if (player->TouchingEnemy(&ghost->d_rect)){
            if (player->powered_up){
                ghost->eaten = true;
            }else{
                player->Died();
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
    gender_options["boy"] = new SpriteButton(cache, "resources/boy.bmp", 400, 300, 96, 48, {0, 0, 64, 24}, 2, 64, .08);
    gender_options["girl"] = new SpriteButton(cache, "resources/girl.bmp", 900, 300, 96, 48, {0, 0, 64, 24}, 2, 64, .08);
    

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
            for (auto const &options : gender_options){
                if (select_newgame){
                    options.second->Process(clock);
            }
        }
            if (gender_options["boy"]->MouseClicking(mouse)){
                its_boy = true;
                its_girl = false;
                *gender = "boy";
                *state = "GAME";
                *path = "resources/level/pacman_level.mx";
                select_newgame = false;
                seconds_passed = 0;
                return 1;
                

            }else if (gender_options["girl"]->MouseClicking(mouse)){
                its_girl = true;
                its_boy = false;
                *gender = "girl";
                *state = "GAME";
                *path = "resources/level/pacman_level.mx";
                select_newgame = false;
                seconds_passed = 0;
                return 1;
                
            }

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

