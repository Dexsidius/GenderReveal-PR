#include "game.h"

PacManGR::PacManGR();

int PacManGR::Start(int argc, char ** argv){
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
    Mix_Init(MIX_INIT_MOD);
    TTF_Init();

    atexit(SDL_Quit);
    atexit(Mix_Quit);
    atexit(TTF_Quit);
    
    // Creating Window..
    window = SDL_CreateWindow("PacMan Gender Reveal - Dexsidius", SDL_WINDOWPOS_UNDEFINED,
                            WIDTH, HEIGHT, WINDOW_FLAGS);
    
    if (!window){
        ShowError("PacMan Gender Reveal Error", "Couldn't Create Window", "Window creation failed!: ", true);
        return 0;
    }

    //Create Renderer..
    renderer = SDL_CreateRenderer(window, -1, RENDERER_FLAGS);
    if (!renderer){
        ShowError("PacMan Gender Reveal Error!", "Couldn't create renderer!", "Renderer Failed!: ", true);
        return 0;
    }

    // Initialize random seed
    srand(time(NULL));

    // Start Clock
    clock = Clock();

    mouse = new MouseManager();
    keyboard = new KeyboardManager();
    framebuffer = new Framebuffer(window, renderer);
    text = TextCache(renderer);
    cache = new SpriteCache(renderer);
    p1 = new Player(cache, 0, 0, 32, 32, "resources/pacman_sprites.png");

    text->SetFont("joystix.tff");

    menu = new MenuScene(cache, framebuffer, text, &flip, p1);
    game_scene = nullptr;

}