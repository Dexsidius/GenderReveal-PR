#include "game.h"
#include "headers.h"

int main(int argc, char ** argv){
    PacManGR game;

    if (!game.Start(argc, argv)){
        return -1;
    }else{
        game.Loop();

    }


    return 0;
}