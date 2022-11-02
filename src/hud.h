#pragma once
#include "headers.h"
#include "player.h"
#include "framebuffer.h"
#include "enemy.h"
#include "text.h"

class HUD {
    public:
        Player * player;
        int score = 0;
        int highscore;
        string score_string;
        string lives_string;
        vector<Sprite *> life_sprites;
        Framebuffer * framebuffer;
        Sprite * life_sprite;
        TextCache * text_cache;
        SDL_Renderer * renderer;

        HUD(SpriteCache *, Framebuffer *, Player *, TextCache *);
        ~HUD();

        void AddScore(int);
        void SetScore(int);

        void Render();
        void UpdateLivesAndScore();
};