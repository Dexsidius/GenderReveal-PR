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

MenuScene::MenuScene(SpriteCache * cache, Framebuffer * framebuffer, TextCache * text, Player * player){}

MenuScene::~MenuScene(){}

bool MenuScene::Process(Clock * clock, MouseManager * mouse, string * state, string * path){}

void MenuScene::RenderScene(){
    //Rendering
    framebuffer->SetActiveBuffer("MENU");
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    framebuffer->UnsetBuffers();
}

