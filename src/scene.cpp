#include "scene.h"
#include <SDL2/SDL_rect.h>

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

            // Wall Collision Correction
            for(auto const &wall : walls){
                if (player->CollisionCheck(&wall->d_rect, &player->hitboxes["right"])){
                    player->SetPos(player->x_pos-1 , player->y_pos);
                    cout << "right touching" << endl;
                    player->Move("none");
                }
                if (player->CollisionCheck(&wall->d_rect, &player->hitboxes["left"])){
                    player->SetPos(player->x_pos+1 , player->y_pos);
                    cout << "left" << endl;
                    player->Move("none");
                }
                if (player->CollisionCheck(&wall->d_rect, &player->hitboxes["up"])){
                    player->SetPos(player->x_pos, player->y_pos +1 );
                    cout << "up" << endl;
                    player->Move("none");
                }
                if (player->CollisionCheck(&wall->d_rect, &player->hitboxes["down"])){
                    player->SetPos(player->x_pos , player->y_pos - 1);
                    cout << "down" << endl;
                    player->Move("none");
                }
            }

            // Player goes through tunnel and appears on the other end
            if (player->d_rect.x < -32 ){
                player->SetPos(width, player->y_pos);
            }
            else if (player->d_rect.x > 832){
                player->SetPos(-1, player->y_pos);
            }

            // Pellet relocation instead of deleting
            for (auto const &pellet : pellets){
                if (player->EatingPellet(&pellet->d_rect)){
                    pellet->SetPos(-5, -5);
                    player->AddPoints(25);
                    pellets_collected +=1;
                }
            }
            
            for (auto const &big_pellet : big_pellets){
                if (player->EatingPellet(&big_pellet->d_rect)){
                    big_pellet->SetPos(-5, -5);
                    player->AddPoints(50);
                    pellets_collected += 1;
                    
                }
            }
            
            // Win Condition
            if (pellets_collected == total_pellets){
                win = true;
            }
            
            // Ghost Loop Conditions
            for (auto const &ghost : ghosts){
                ghost->Process(clock);

                if (player->powered_up){
                    if (player->TouchingEnemy(&ghost->d_rect)){
                        ghost->eaten = true;
                    }
                }
                else if (player->TouchingEnemy(&ghost->d_rect)){
                    player->dead = true;
                }
            }

            player->Process(clock);
        }
        
    }
    
}

void LevelScene::AddEnemy(Ghost * ghost){
    ghosts.push_back(ghost);
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

