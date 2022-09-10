#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <unistd.h>

enum CELL_STATE{
    ALIVE,
    BORN,
    DEAD
};

class Field{
public:
    Field(int alive_count, int width) 
        : width_(width), field_(width_, std::vector<CELL_STATE>(width_, DEAD)) {
        for (int i = 0; i < alive_count;){
            timeval t; gettimeofday(&t, nullptr);
            srand(t.tv_sec * 1e+6 + t.tv_usec);
            int x = rand() % width_;
            int y = rand() % width_;

            if (field_.at(x).at(y) == DEAD){
                field_.at(x).at(y) = ALIVE;
                i++;
            }
        }
    }
    Field(const std::string& fileName){
        const std::string errorMsg = "Bad input file";
        std::ifstream inputFile(fileName);        
        if (!inputFile.is_open()) throw std::runtime_error(errorMsg);

        std::string line;
        while (inputFile >> line){
            std::vector<CELL_STATE> newLine;
            for (char c : line){
                if (c == '1') newLine.push_back(ALIVE);
                else if (c == '0') newLine.push_back(DEAD);
                else throw std::runtime_error(errorMsg);
            }
            if (field_.size() && field_.front().size() != newLine.size()) throw std::runtime_error(errorMsg);
            field_.push_back(std::move(newLine));
        }
        if (field_.size() != field_.front().size()) throw std::runtime_error(errorMsg);
        width_ = field_.size();
    }

    int getWidth() const {
        return width_;
    }
    CELL_STATE getCell(int x, int y) const {
        return field_.at(x).at(y);
    }
    void setCell(int x, int y, CELL_STATE value){
        field_.at(x).at(y) = value;
    }
    
    bool isAlive(int x, int y) const {
        return field_.at(x).at(y) == ALIVE;
    }
    bool isBorn(int x, int y) const {
        return field_.at(x).at(y) == BORN;
    }
    bool isDead(int x, int y) const {
        return field_.at(x).at(y) == DEAD;
    }

private:
    int width_;
    std::vector<std::vector<CELL_STATE>> field_;

};

std::ostream& operator<<(std::ostream& out, const Field& field){
    std::string str;

    for (int x = 0; x < field.getWidth(); x++){
        for (int y = 0; y < field.getWidth(); y++){
            str += (field.isAlive(x, y)) ? '0' : ' ';
        }
        str += '\n';
    }

    return out << str;
}
