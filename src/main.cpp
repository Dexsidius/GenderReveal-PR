#include "game.h"

int main(int argc, char ** argv){
    PacManGR game;

    if (!game.Start(argc, argv)){
        return -1;
    }
}