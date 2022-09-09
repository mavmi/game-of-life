#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <sys/time.h>

enum CELL{
    ALIVE,
    DEAD
};

class Field{
public:
    Field(int alive_count = 150, int width = 40) 
        : width_(width), field_(width_, std::vector<int>(width_, 0)) {
        for (int i = 0; i < alive_count;){
            timeval t; gettimeofday(&t, nullptr);
            srand(t.tv_usec);
            int x = rand() % width_;
            int y = rand() % width_;

            std::cout << x << " " << y << std::endl;

            if (field_.at(x).at(y) == 0){
                field_.at(x).at(y) = 1;
                i++;
            }
        }
    }

    int getWidth() const {
        return width_;
    }
    int getCell(int x, int y) const {
        return field_.at(x).at(y);
    }
    void setCell(int x, int y, int value){
        field_.at(x).at(y) = value;
    }
    bool isAlive(int x, int y) const {
        return field_.at(x).at(y) == 1;
    }

private:
    const int width_;
    std::vector<std::vector<int>> field_;

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
