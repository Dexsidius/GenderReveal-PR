#pragma once
#include "headers.h"
#include "functions.h"
#include "scene.h"
#include "framebuffer.h"
#include "player.h"
#include "sprites.h"
#include <SDL2/SDL_video.h>

class PacManGR {
private:
    //Private SDL Variables
    SDL_Window * window;
    SDL_Renderer * renderer;
    SDL_Event event;

    //Private general variables

    int WIDTH = 1280, HEIGHT = 720;
    int GAME_WIDTH = 1280, GAME_HEIGHT = 720;
    Uint32 WINDOW_FLAGS = SDL_WINDOW_RESIZABLE;
    Uint32 RENDERER_FLAGS = SDL_RENDERER_PRESENTVSYNC;
    string state = "MENU";
    string scene_path = "";
    string gender = "";
    string gender_input;

    bool its_boy = false;
    bool its_girl = false;

    //Private Objects

    KeyboardManager * keyboard;
    Clock clock;
    //Jukebox * jukebox;
    SpriteCache * cache;
    MenuScene * menu;
    LevelScene * game_scene;
    CutScene * cutscene;
    Player * p1;
    MouseManager * mouse;
    Framebuffer * framebuffer;
    TextCache * text;
    

    //Private Functions
    void Process();

public:
    //Variables
    bool running = false;
    int current_width = WIDTH, current_height = HEIGHT;
    PacManGR();

    int Start(int argc, char ** argv);
    void Loop();
    void End();
    void Render();

    ~PacManGR();
};

