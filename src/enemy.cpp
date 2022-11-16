#include "enemy.h"

Ghost::Ghost(SpriteCache * cache, int x, int y, int w, int h, string src, string t, Player * player){}

void Ghost::Process(Clock * clock, int height){}

void Ghost::Move(string d){

}

void Ghost::Reset(){}

void Ghost::SetPos(int x, int y){}

bool Ghost::TouchingPlayer(SDL_Rect * rect){}

void Ghost::Render(){}

Ghost::~Ghost(){}

Blinky::Blinky(SpriteCache * cache, int x, int y, int w, int h, string src, string t, Player * player) 
: Ghost(cache, x, y, w, h, src, t, player){}

Pinky::Pinky(SpriteCache * cache, int x, int y, int w, int h, string src, string t, Player * player) 
: Ghost(cache, x, y, w, h, src, t, player){}

Inky::Inky(SpriteCache * cache, int x, int y, int w, int h, string src, string t, Player * player) 
: Ghost(cache, x, y, w, h, src, t, player){}

Clyde::Clyde(SpriteCache * cache, int x, int y, int w, int h, string src, string t, Player * player) 
: Ghost(cache, x, y, w, h, src, t, player){}