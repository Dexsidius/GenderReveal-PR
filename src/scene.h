#pragma once
#include "headers.h"
#include "player.h"
#include "text.h"
#include "pellets.h"
#include "buttons.h"
#include "framebuffer.h"

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
        LevelScene(SDL_Renderer * r, Framebuffer * framebuffer, SpriteCache *, TextCache *);
        void Process(Clock *, KeyboardManager *, MouseManager, string *, int, int);
        void RenderScene();
        ~LevelScene();
        void AddEnemy();
        void AddPlayer(Player *);
};

class MenuScene {
    private:
        Player * player;
        SDL_Renderer * flip;
        SpriteCache * cache;
        Framebuffer * framebuffer;
        map<string, Button *> buttons;
        TextCache * text_cache;

        // Menu Conditions open/close
        bool select_newgame = false;
        bool its_boy = false;
        bool its_girl = false;


    public:
        bool starting;
        bool running;
        bool finished;
        MenuScene(SpriteCache *, Framebuffer * framebuffer, TextCache *, Player *);
        ~MenuScene();
        bool Process(Clock * clock, MouseManager * mouse, string * state, string * scene_path);
        void RenderScene();

};