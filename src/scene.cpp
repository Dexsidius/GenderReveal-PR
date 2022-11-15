#include "scene.h"

LevelScene::LevelScene(SDL_Renderer * r, Framebuffer * framebuffer, SpriteCache * sprite_cache, TextCache * text_cache){
    this->framebuffer = framebuffer;
    starting = true;
    running = false;
    finished = false;
    paused = false;
    renderer = r;
    text_renderer = text_cache;
    
}

void LevelScene::AddPlayer(Player * pl){
    player = pl;

}

void LevelScene::Process(Clock * clock, KeyboardManager * keyboard, MouseManager * mouse, string * state, int width, int height, string * gender){
    
}


LevelScene::~LevelScene(){}


void LevelScene::RenderScene(){}

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
                *path = "resources/level/gr-1.mx";
                return 1;
                

            }else if (gender_options["girl"]->MouseClicking(mouse)){
                its_girl = true;
                its_boy = false;
                *gender = "girl";
                *state = "GAME";
                *path = "resources/level/gr-1.mx";
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

