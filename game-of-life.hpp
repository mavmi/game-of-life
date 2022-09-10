#pragma once

#include "field.hpp"
#include <unistd.h>

class GameOfLife{
public:
    GameOfLife(int alive_count = 200, int width = 40)
        : field_(alive_count, width) {

    }
    GameOfLife(const std::string& fileName)
        : field_(fileName){

    }

    void run(){
        int prev_hash;
        int hash = -1;
        
        label:

        system("clear");
        std::cout << field_ << std::endl;

        for (int x = 0; x < field_.getWidth(); x++){
        for (int y = 0; y < field_.getWidth(); y++){

            int aliveNeighbours = 0;
            for (int neighShiftX = -1; neighShiftX <= 1; neighShiftX++){
            for (int neighShiftY = -1; neighShiftY <= 1; neighShiftY++){
                if (neighShiftX || neighShiftY) aliveNeighbours += isNeighbourAlive_(x, y, neighShiftX, neighShiftY);
            }
            }
            if (field_.isDead(x, y) && aliveNeighbours == 3) field_.setCell(x, y, BORN);
            else if (field_.isAlive(x, y) && aliveNeighbours != 2 && aliveNeighbours != 3) field_.setCell(x, y, DEAD);

        }
        }

        for (int x = 0; x < field_.getWidth(); x++){
        for (int y = 0; y < field_.getWidth(); y++){

            if (field_.getCell(x, y) == BORN) field_.setCell(x, y, ALIVE);

        }
        }

        prev_hash = hash;
        hash = hash_();
        if (hash == prev_hash) return;
        usleep(100000);

        goto label;
    }

private:
    Field field_;

    bool isNeighbourAlive_(int curX, int curY, int neighShiftX, int neighShiftY) const {
        int neighX = curX + neighShiftX;
        int neighY = curY + neighShiftY;

        auto getValidNumber = [](const Field& field, int coord){
            if (coord < 0) return field.getWidth() + coord;
            else if (coord >= field.getWidth()) return coord - field.getWidth();
            else return coord;
        };

        neighX = getValidNumber(field_, neighX);
        neighY = getValidNumber(field_, neighY);

        return field_.isAlive(neighX, neighY);
    }

    int hash_() const {
        int hash = 0;
        int counter = 0;
        
        for (int x = 0; x < field_.getWidth(); x++){
        for (int y = 0; y < field_.getWidth(); y++){
            hash += field_.getCell(x, y) * counter++;
        }
        }

        return hash;
    }

};
