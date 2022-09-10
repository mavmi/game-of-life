#include "game-of-life.hpp"

int main(int argc, char** argv){
    if (argc != 2){
        GameOfLife gameOfLife(2000, 80);
        gameOfLife.run();
    } else {
        GameOfLife gameOfLife(argv[1]);
        gameOfLife.run();
    }
}