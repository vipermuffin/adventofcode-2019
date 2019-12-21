//
//  Advent of Code 2019 Solutions: Day 10
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/10/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//

#include "Day10.h"
#include "AoCUtils.h"
//Common Libraries
#include <algorithm> //std::sort, find, for_each, max_element, etc
//#include <array>
#include <climits>   //INT_MIN, INT_MAX, etc.
//#include <chrono>
//#include <iostream>
//#include <fstream> //ifstream
//#include <functional> //std::function
//#include <iomanip> //setfill setw hex
//#include <map>
//#include <math.h> //sqrt
//#include <numeric> //std::accumulate
//#include <queue>
//#include <regex>
//#include <set>
//#include <sstream>
//#include <thread>
//#include <tuple>
//#include <unordered_map>
//#include <unordered_set>


using namespace std;
namespace AocDay10 {

    static const std::string InputFileName = "Day10.txt";
    std::string solvea() {
        auto input = parseFileForLines(InputFileName);

		return to_string(DetermineMaxAsteroids(input));
    }

    std::string solveb() {
        auto input = parseFileForLines(InputFileName);
        auto startPos = DetermineMaxAsteroidsLoc(input);
        auto lastDestroyed = DestroyNumAsteroids(input, 200, startPos.first, startPos.second);
		return to_string(lastDestroyed.first*100+lastDestroyed.second);
    }
    
    int DetermineMaxAsteroids(const std::vector<std::string>& astMap) {
        vector<int> views{};
        views.reserve(astMap.size()*astMap[0].size());
        for(int x = 0; x < astMap[0].size();x++) {
            for(int y = 0; y < astMap.size(); y++) {
                if(astMap[y][x] == '#') {
                    views.push_back(DetermineVisibleAsteroidsAtPos(astMap, x, y));
                }
            }
        }
        std::sort(views.rbegin(), views.rend());
        return views[0];
    }
    
    std::pair<int,int> DetermineMaxAsteroidsLoc(const std::vector<std::string>& astMap) {
        std::pair<int,int> coordinates{0,0};
        int max = 0;
        
        for(int x = 0; x < astMap[0].size();x++) {
            for(int y = 0; y < astMap.size(); y++) {
                if(astMap[y][x] == '#') {
                    int z = DetermineVisibleAsteroidsAtPos(astMap, x, y);
                    if(z > max) {
                        max = z;
                        coordinates.first = x;
                        coordinates.second = y;
                    }
                }
            }
        }
        return coordinates;
    }
    
    std::pair<int,int> DestroyNumAsteroids(std::vector<std::string>& astMap, int num2Destroy, int x, int y) {
        std::pair<int,int> lastDestroyed{-1,1};
        int destroyCount = 0;
        while(destroyCount < num2Destroy) {
            vector<vector<bool>> isBlocked;
            isBlocked.reserve(astMap.size()*astMap[0].size());
            isBlocked.resize(astMap.size());
            for(int i = 0; i < astMap.size();i++) {
                isBlocked[i].resize(astMap[0].size());
            }
            
            for(int ix = 0; ix < astMap[0].size()-x;ix++) {
                for(int iy = 0; iy < astMap.size()-y;iy++) {
                    if((ix == 0 && iy == 0) || isBlocked[y+iy][x+ix]) {
                        //This is the asteroid of interest or blocked...skip
                        isBlocked[y+iy][x+ix] = true;
                    } else {
                        if(astMap[y+iy][x+ix] == '#') {
                            int jx{ix},jy{iy};
                            int z=2;
                            jy = jx == 0 ? 1 : jy;
                            jx = jy == 0 ? 1 : jx;
                            while(z <= jx && z <= jy) {
                                if(jx%z==0 && jy%z==0) {
                                    jx /= z;
                                    jy /= z;
                                } else {
                                    z++;
                                }
                            }
                            z=1;
                            while(x+ix+jx*z < astMap[0].size() && y+iy+jy*z < astMap.size()) {
                                isBlocked[y+iy+jy*z][x+ix+jx*z] = true;
                                z++;
                            }
                        }
                    }
                }
            }
            
            for(int ix = 0; ix <= x;ix++) {
                for(int iy = 0; iy < astMap.size()-y;iy++) {
                    if((ix == 0 && iy == 0) || isBlocked[y+iy][x-ix]) {
                        //This is the asteroid of interest or blocked...skip
                    } else {
                        if(astMap[y+iy][x-ix] == '#') {
                            int jx{ix},jy{iy};
                            int z=2;
                            jy = jx == 0 ? 1 : jy;
                            jx = jy == 0 ? 1 : jx;
                            while(z <= jx && z <= jy) {
                                if(jx%z==0 && jy%z==0) {
                                    jx /= z;
                                    jy /= z;
                                } else {
                                    z++;
                                }
                            }
                            z=1;
                            while(x-ix-jx*z >= 0 && y+iy+jy*z < astMap.size()) {
                                isBlocked[y+iy+jy*z][x-ix-jx*z] = true;
                                z++;
                            }
                        }
                    }
                }
            }
            
            for(int ix = 0; ix < astMap[0].size()-x;ix++) {
                for(int iy = 0; iy <= y;iy++) {
                    if((ix == 0 && iy == 0) || isBlocked[y-iy][x+ix]) {
                        //This is the asteroid of interest or blocked...skip
                    } else {
                        if(astMap[y-iy][x+ix] == '#') {
                            int jx{ix},jy{iy};
                            int z=2;
                            jy = jx == 0 ? 1 : jy;
                            jx = jy == 0 ? 1 : jx;
                            while(z <= jx && z <= jy) {
                                if(jx%z==0 && jy%z==0) {
                                    jx /= z;
                                    jy /= z;
                                } else {
                                    z++;
                                }
                            }
                            z=1;
                            while(x+ix+jx*z < astMap[0].size() && y-iy-jy*z >= 0) {
                                isBlocked[y-iy-jy*z][x+ix+jx*z] = true;
                                z++;
                            }
                        }
                    }
                }
            }
            
            for(int ix = 0; ix <= x;ix++) {
                for(int iy = 0; iy <= y;iy++) {
                    if((ix == 0 && iy == 0) || isBlocked[y-iy][x-ix]) {
                        //This is the asteroid of interest or blocked...skip
                    } else {
                        if(astMap[y-iy][x-ix] == '#') {
                            int jx{ix},jy{iy};
                            int z=2;
                            jy = jx == 0 ? 1 : jy;
                            jx = jy == 0 ? 1 : jx;
                            while(z <= jx && z <= jy) {
                                if(jx%z==0 && jy%z==0) {
                                    jx /= z;
                                    jy /= z;
                                } else {
                                    z++;
                                }
                            }
                            z=1;
                            while(x-ix-jx*z >= 0 && y-iy-jy*z >= 0) {
                                isBlocked[y-iy-jy*z][x-ix-jx*z] = true;
                                z++;
                            }
                        }
                    }
                }
            }
            
            //Destroy them clockwise
            struct RelPos {
                RelPos(int x, int y, int x0, int y0) {
                    _x = x;
                    _y = y;
                    if(x-x0 != 0) {
                        slope = (static_cast<double>(y)-static_cast<double>(y0))/(static_cast<double>(x)-static_cast<double>(x0));
                    }
                }
                bool operator<(const RelPos& rhs) const {
                    return this->slope < rhs.slope;
                }
                int _x;
                int _y;
                double slope;
            };
            vector<RelPos> q1,q2,q3,q4;
            
            for(int ix = x+1; ix < astMap[0].size(); ix++) {
                for(int iy = 0; iy < y; iy++) {
                    q1.emplace_back(ix,iy,x,y);
                }
            }
            
            for(int iy = y+1; iy < astMap.size(); iy++) {
                for(int ix = astMap[0].size()-1; ix > x; ix--) {
                    q2.emplace_back(ix,iy,x,y);
                }
            }
            
            for(int ix = x-1; ix >= 0; ix--) {
                for(int iy = astMap.size()-1; iy > y; iy--) {
                    q3.emplace_back(ix,iy,x,y);
                }
            }
            
            for(int iy = y-1; iy >= 0; iy--) {
                for(int ix = 0; ix < x; ix++) {
                    q4.emplace_back(ix,iy,x,y);
                }
            }
            
            //Straight up
            for(int iy = y-1;iy >= 0;iy--) {
                if(astMap[iy][x] == '#' && !isBlocked[iy][x]) {
                    astMap[iy][x] = 'x';
                    lastDestroyed.first = x;
                    lastDestroyed.second = iy;
                    destroyCount++;
                    if(destroyCount == num2Destroy) {
                        return lastDestroyed;
                    }
                }
            }
            
            //Q1
            //              |
            //          Q4  |   Q1
            //       -------+-------
            //          Q3  |   Q2
            //              |
            
            std::sort(q1.begin(),q1.end());
            for(const auto& pos : q1) {
                if(astMap[pos._y][pos._x] == '#' && !isBlocked[pos._y][pos._x]) {
                    astMap[pos._y][pos._x] = 'x';
                    lastDestroyed.first = pos._x;
                    lastDestroyed.second = pos._y;
                    destroyCount++;
                    if(destroyCount == num2Destroy) {
                        return lastDestroyed;
                    }
                }
            }
            
            //Straight right
            for(int ix = astMap.size()-1;ix > x;ix--) {
                if(astMap[y][ix] == '#' && !isBlocked[y][ix]) {
                    astMap[y][ix] = 'x';
                    lastDestroyed.first = ix;
                    lastDestroyed.second = y;
                    destroyCount++;
                    if(destroyCount == num2Destroy) {
                        return lastDestroyed;
                    }
                }
            }
            
            //Q2
            std::sort(q2.begin(),q2.end());
            for(const auto& pos : q2) {
                if(astMap[pos._y][pos._x] == '#' && !isBlocked[pos._y][pos._x]) {
                    astMap[pos._y][pos._x] = 'x';
                    lastDestroyed.first = pos._x;
                    lastDestroyed.second = pos._y;
                    destroyCount++;
                    if(destroyCount == num2Destroy) {
                        return lastDestroyed;
                    }
                }
            }
            
            //Straight down
            for(int iy = astMap.size()-1;iy > y;iy--) {
                if(astMap[iy][x] == '#' && !isBlocked[iy][x]) {
                    astMap[iy][x] = 'x';
                    lastDestroyed.first = x;
                    lastDestroyed.second = iy;
                    destroyCount++;
                    if(destroyCount == num2Destroy) {
                        return lastDestroyed;
                    }
                }
            }
            
            //Q3
            std::sort(q3.begin(),q3.end());
            for(const auto& pos : q3) {
                if(astMap[pos._y][pos._x] == '#' && !isBlocked[pos._y][pos._x]) {
                    astMap[pos._y][pos._x] = 'x';
                    lastDestroyed.first = pos._x;
                    lastDestroyed.second = pos._y;
                    destroyCount++;
                    if(destroyCount == num2Destroy) {
                        return lastDestroyed;
                    }
                }
            }
            
            //Straight left
            for(int ix = 0;ix < x;ix++) {
                if(astMap[y][ix] == '#' && !isBlocked[y][ix]) {
                    astMap[y][ix] = 'x';
                    lastDestroyed.first = ix;
                    lastDestroyed.second = y;
                    destroyCount++;
                    if(destroyCount == num2Destroy) {
                        return lastDestroyed;
                    }
                }
            }
            
            //Q4
            std::sort(q4.begin(),q4.end());
            for(const auto& pos : q4) {
                if(astMap[pos._y][pos._x] == '#' && !isBlocked[pos._y][pos._x]) {
                    astMap[pos._y][pos._x] = 'x';
                    lastDestroyed.first = pos._x;
                    lastDestroyed.second = pos._y;
                    destroyCount++;
                    if(destroyCount == num2Destroy) {
                        return lastDestroyed;
                    }
                }
            }
        }
        
        return lastDestroyed;
    }
    
    int DetermineVisibleAsteroidsAtPos(const std::vector<std::string>& astMap, int x, int y) {
        vector<vector<bool>> isBlocked;
        isBlocked.reserve(astMap.size()*astMap[0].size());
        isBlocked.resize(astMap.size());
        for(int i = 0; i < astMap.size();i++) {
            isBlocked[i].resize(astMap[0].size());
        }
        
        for(int ix = 0; ix < astMap[0].size()-x;ix++) {
            for(int iy = 0; iy < astMap.size()-y;iy++) {
                if((ix == 0 && iy == 0) || isBlocked[y+iy][x+ix]) {
                    //This is the asteroid of interest or blocked...skip
                    isBlocked[y+iy][x+ix] = true;
                } else {
                    if(astMap[y+iy][x+ix] == '#') {
                        int jx{ix},jy{iy};
                        int z=2;
                        jy = jx == 0 ? 1 : jy;
                        jx = jy == 0 ? 1 : jx;
                        while(z <= jx && z <= jy) {
                            if(jx%z==0 && jy%z==0) {
                                jx /= z;
                                jy /= z;
                            } else {
                                z++;
                            }
                        }
                        z=1;
                        while(x+ix+jx*z < astMap[0].size() && y+iy+jy*z < astMap.size()) {
                            isBlocked[y+iy+jy*z][x+ix+jx*z] = true;
                            z++;
                        }
                    }
                }
            }
        }
        
        for(int ix = 0; ix <= x;ix++) {
            for(int iy = 0; iy < astMap.size()-y;iy++) {
                if((ix == 0 && iy == 0) || isBlocked[y+iy][x-ix]) {
                    //This is the asteroid of interest or blocked...skip
                } else {
                    if(astMap[y+iy][x-ix] == '#') {
                        int jx{ix},jy{iy};
                        int z=2;
                        jy = jx == 0 ? 1 : jy;
                        jx = jy == 0 ? 1 : jx;
                        while(z <= jx && z <= jy) {
                            if(jx%z==0 && jy%z==0) {
                                jx /= z;
                                jy /= z;
                            } else {
                                z++;
                            }
                        }
                        z=1;
                        while(x-ix-jx*z >= 0 && y+iy+jy*z < astMap.size()) {
                            isBlocked[y+iy+jy*z][x-ix-jx*z] = true;
                            z++;
                        }
                    }
                }
            }
        }
        
        for(int ix = 0; ix < astMap[0].size()-x;ix++) {
            for(int iy = 0; iy <= y;iy++) {
                if((ix == 0 && iy == 0) || isBlocked[y-iy][x+ix]) {
                    //This is the asteroid of interest or blocked...skip
                } else {
                    if(astMap[y-iy][x+ix] == '#') {
                        int jx{ix},jy{iy};
                        int z=2;
                        jy = jx == 0 ? 1 : jy;
                        jx = jy == 0 ? 1 : jx;
                        while(z <= jx && z <= jy) {
                            if(jx%z==0 && jy%z==0) {
                                jx /= z;
                                jy /= z;
                            } else {
                                z++;
                            }
                        }
                        z=1;
                        while(x+ix+jx*z < astMap[0].size() && y-iy-jy*z >= 0) {
                            isBlocked[y-iy-jy*z][x+ix+jx*z] = true;
                            z++;
                        }
                    }
                }
            }
        }
        
        for(int ix = 0; ix <= x;ix++) {
            for(int iy = 0; iy <= y;iy++) {
                if((ix == 0 && iy == 0) || isBlocked[y-iy][x-ix]) {
                    //This is the asteroid of interest or blocked...skip
                } else {
                    if(astMap[y-iy][x-ix] == '#') {
                        int jx{ix},jy{iy};
                        int z=2;
                        jy = jx == 0 ? 1 : jy;
                        jx = jy == 0 ? 1 : jx;
                        while(z <= jx && z <= jy) {
                            if(jx%z==0 && jy%z==0) {
                                jx /= z;
                                jy /= z;
                            } else {
                                z++;
                            }
                        }
                        z=1;
                        while(x-ix-jx*z >= 0 && y-iy-jy*z >= 0) {
                            isBlocked[y-iy-jy*z][x-ix-jx*z] = true;
                            z++;
                        }
                    }
                }
            }
        }
        
        //Count them up
        int count = 0;
        for(int i=0; i < astMap.size();i++) {
            for(int j=0; j < astMap[0].size();j++) {
                if(astMap[i][j] == '#' && !isBlocked[i][j]) {
                    count++;
                }
            }
        }
        return count;
    }
}
