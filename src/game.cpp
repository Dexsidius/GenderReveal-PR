#include "game.h"

PacManGR::PacManGR(){};

int PacManGR::Start(int argc, char ** argv){
    cout << "Input 1 for boy \nInput 2 for girl\nThen Press ENTER." << endl;
    cin >> gender_input;

    if (gender_input == "1"){
        gender = "boy";
        its_boy = true;
        its_girl = false;

    }else if (gender_input == "2"){
        gender = "girl";
        its_girl = true;
        its_boy = false;
    }

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    atexit(TTF_Quit);
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

    event = SDL_Event();

    // Start Clock
    clock = Clock();

    mouse = new MouseManager();
    keyboard = new KeyboardManager();
    framebuffer = new Framebuffer(window, renderer);
    text = new TextCache(renderer);
    cache = new SpriteCache(renderer);
    p1 = new Player(cache, 398, 456, 32, 32, "resources/pacman_sprite.bmp");

    text->SetFont("joystix.ttf");
    menu = new MenuScene(cache, framebuffer, text, p1);
    cutscene = new CutScene(cache, framebuffer, text);
    game_scene = nullptr;

    framebuffer->CreateBuffer("MENU", WIDTH, HEIGHT);
    framebuffer->CreateBuffer("GAME", GAME_WIDTH, GAME_HEIGHT);
    framebuffer->CreateBuffer("CUTSCENE", GAME_WIDTH, GAME_HEIGHT);

    running = true;
    return 1;
}

void PacManGR::Loop(){

    while(running){

        Process();
        Render();
        SDL_Delay(5);
    }
}

void PacManGR::Process(){
    //TODO: Clock tick
    clock.Tick();


    //TODO: Keyboard and Mouse
    keyboard->Process();
    mouse->Process();

    if (keyboard->KeyIsPressed(SDL_SCANCODE_ESCAPE)){
        running = false;
    }

    //Event Loop
    while (SDL_PollEvent(&event)){
        mouse->GetPositionEvent(&event);
        if(event.type == SDL_QUIT){
            running = false;
            break;
        }
        
    }

    if (state == "MENU"){
        if (menu->Process(&clock, mouse, &state, &scene_path, &gender)){
            delete game_scene;
            game_scene = CreateScene(cache, framebuffer, text, p1, scene_path);
        }
    }

    if (state == "GAME"){
        game_scene->Process(&clock, keyboard, mouse, &state, GAME_WIDTH, GAME_HEIGHT, &gender);
    }

    if (state == "CUTSCENE"){
        if (cutscene->Process(&clock, keyboard, mouse, &state, &gender)){

        }
    }

    

}

void PacManGR::Render(){
    if (running){
        //Render Scale
        SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT);

        if (state == "MENU"){
            menu->RenderScene();
        }

        if (state == "GAME"){
            game_scene->RenderScene();
        }
        if (state == "CUTSCENE"){
            cutscene->RenderScene();
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        if (state == "MENU"){
            framebuffer->RenderBuffer("MENU", WIDTH/2, HEIGHT/2, WIDTH, HEIGHT);
        }
        if (state == "GAME"){
            framebuffer->RenderBuffer("GAME", WIDTH/2, HEIGHT/2, WIDTH, HEIGHT);
        }
        if (state == "CUTSCENE"){
            framebuffer->RenderBuffer("CUTSCENE", WIDTH/2, HEIGHT/2, WIDTH, HEIGHT);
        }

        SDL_RenderPresent(renderer);
        
    }
}

PacManGR::~PacManGR(){
    delete p1;
    delete cache;
    delete text;
    delete framebuffer;
    delete mouse;
    delete keyboard;
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

}
