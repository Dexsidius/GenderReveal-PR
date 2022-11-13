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

void LevelScene::Process(Clock * clock, KeyboardManager * keyboard, MouseManager * mouse, string * state, int width, int height){
    
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

    buttons["play"] = new SpriteButton(cache, "resources/play_quit.bmp", 640, 360, 64, 24, {0, 0, 64, 24}, 7, 0, .06);
    buttons["quit"] = new SpriteButton(cache, "resources/play_quit.bmp", 640, 460, 64, 24, {0, 48, 64, 24}, 7, 0, .06);
}

MenuScene::~MenuScene(){}

bool MenuScene::Process(Clock * clock, MouseManager * mouse, string * state, string * path){

    for (auto const &button : buttons){
        button.second->Process(clock);
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

    

    framebuffer->UnsetBuffers();
}

