#include "game.h"

PacManGR::PacManGR(){};

int PacManGR::Start(int argc, char ** argv){
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);

    atexit(SDL_Quit);
    
    // Creating Window..
    window = SDL_CreateWindow("PacMan Gender Reveal - Dexsidius", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, WINDOW_FLAGS);
    
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
    //clock = Clock();

    //mouse = new MouseManager();
    //keyboard = new KeyboardManager();
    //framebuffer = new Framebuffer(window, renderer);
    //text = new TextCache(renderer);
    //cache = new SpriteCache(renderer);
    //p1 = new Player(cache, 0, 0, 32, 32, "resources/pacman_sprites.png");

    //text->SetFont("joystix.tff");

    //menu = new MenuScene(cache, framebuffer, text, p1);
    //game_scene = nullptr;

    running = true;
    return 1;
}

void PacManGR::Loop(){

    Process();
    Render();
    SDL_Delay(5);
}

void PacManGR::Process(){
    //TODO: Clock tick


    //TODO: Keyboard and Mouse

    //Event Loop
    while (SDL_PollEvent(&event)){
        //mouse->GetPositionEvent(&event);
        if(event.type == SDL_QUIT){
            running = false;
            break;
        }
    }

}

void PacManGR::Render(){
    if (running){
        //Render Scale
        SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        
    }
}

PacManGR::~PacManGR(){
    //delete p1;
    //delete cache;
    //delete framebuffer;
    //delete mouse;
    //delete keyboard;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

}
