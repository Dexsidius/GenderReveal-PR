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

    buttons["play"] = new SpriteButton(cache, "resources/play_quit.bmp", 640, 360, 32, 48, {0, 0, 32, 24}, 7, 24, .06);
    buttons["quit"] = new SpriteButton(cache, "resources/play_quit.bmp", 640, 560, 32, 48, {0, 48, 32, 24}, 7, 24, .06);
}

MenuScene::~MenuScene(){}

bool MenuScene::Process(Clock * clock, MouseManager * mouse, string * state, string * path){

    for (auto const &button : buttons){
        
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

