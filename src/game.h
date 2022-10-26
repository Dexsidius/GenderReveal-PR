#pragma once
#include "headers.h"

class PacManGR {
private:
    //Private SDL Variables
    SDL_Window * window;
    SDL_Renderer * renderer;
    SDL_Event event;

    //Private general variables

    int WIDTH = 1280, HEIGHT = 720
    int GAME_WIDTH = 800, GAME_HEIGHT = 600
    string_state = "MENU";
    string scene_path = "";

    //Private Objects
    KeyboardManager * keyboard;
    Clock clock;
    //Jukebox * jukebox;
    SpriteCache * cache;
    MenuScene * menu;
    LevelScene * game_scene;
    Player * pl;
    MouseManager * mouse;
    Framebuffer * framebuffer;
    TextCache * text;

    //Private Functions
    void Process();

public:
    //Variables
    bool running;
    int current_width = WIDTH, current_height = HEIGHT;
    PacManGR();

    int Start(int argc, char ** argv);
    void Loop();
    void End();
    void Render();

    ~PacManGR();
}

