#pragma once
#include "headers.h"
#include "player.h"
#include "text.h"
#include "pellets.h"
#include "buttons.h"
#include "framebuffer.h"
#include "enemy.h"

class LevelScene {
    private:
        vector<Pellets *> pellets;
        
        Player * player = nullptr;
        SpriteCache * cache;
        Framebuffer * framebuffer;
        SDL_Renderer * renderer;
        TextCache * text_renderer;
        
        

        
    public:
        bool paused;
        bool finished;
        bool starting;
        bool running;


        LevelScene(SDL_Renderer *, Framebuffer *, SpriteCache *, TextCache *);
        void Process(Clock *, KeyboardManager *, MouseManager *, string *, int, int, string *);
        void RenderScene();
        ~LevelScene();
        void AddPlayer(Player *);
        void AddEnemy(Ghost * ghost);
        void Reset();
};

class MenuScene {
    private:
        Player * player;
        SDL_Renderer * renderer;
        SpriteCache * cache;
        Framebuffer * framebuffer;
        map<string, Button *> buttons;
        map<string, Button *> gender_options;
        TextCache * text_cache;

        double animate_interval = 0.0;
        double seconds_passed = 0.0;

        // Menu Conditions open/close
        bool select_newgame = false;

        // Gender Reveal Conditions
        bool its_boy = false;
        bool its_girl = false;
        


    public:
        bool starting;
        bool running;
        bool finished;
        MenuScene(SpriteCache *, Framebuffer * framebuffer, TextCache *, Player *);
        ~MenuScene();
        bool Process(Clock * clock, MouseManager * mouse, string * state, string * scene_path, string * gender);
        void RenderScene();

};