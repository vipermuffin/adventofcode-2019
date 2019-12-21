//
//  Advent of Code 2019 Solutions: Day 11
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/11/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//
#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
namespace AocDay11 {
//Function Definitions

    void runProgram(std::vector<long>& intops,const std::vector<int>& stdIn, std::string& stdOut,int* lastPtr);
    enum DIR {NORTH=0, EAST=1, SOUTH=2, WEST=3};
    constexpr int X = 0;
    constexpr int Y = 1;
    union cordinateTranslator{
        int XY[2];
        long both;
    };
    class RobotPainter {
    public:
        RobotPainter():
        currentDir(NORTH), currX{0}, currY{0},canvas{{0,{false,0}}} {
        }
        ~RobotPainter() = default;
        bool step() {
            switch(static_cast<enum DIR>(currentDir)) {
                case NORTH:
                case SOUTH:
                    currY += currentDir == NORTH ? 1 : -1;
                    break;
                    
                case EAST:
                case WEST:
                    currX += currentDir == EAST ? 1 : -1;
                    
                default:
                    break;
            }
            union cordinateTranslator ct;
            ct.XY[X] = currX;
            ct.XY[Y] = currY;
            return canvas[ct.both].first;
        }
        
        void viewCanvas() const;
        
        int countPaintedTiles() const {
            int count = 0;
            for(const auto& kvp : canvas) {
                if(kvp.second.second > 0) {
                    count++;
                }
            }
            return count;
        }
        int paintAndTurn(bool paint, bool turnRight) {
            union cordinateTranslator ct;
            ct.XY[X] = currX;
            ct.XY[Y] = currY;
            canvas[ct.both].first = paint;
            canvas[ct.both].second++;
            turnRight ? currentDir++ : currentDir--;
            currentDir &= 3;
            return canvas[ct.both].second;
        }
    private:
        int currentDir;
        int currX;
        int currY;
        std::unordered_map<long, std::pair<bool,int>> canvas;
    };
}
