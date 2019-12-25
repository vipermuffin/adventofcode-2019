//
//  Advent of Code 2019 Solutions: Day 19
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/21/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//

#include "Day19.h"
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
#include <numeric> //std::accumulate
//#include <queue>
//#include <regex>
//#include <set>
#include <sstream>
//#include <thread>
//#include <tuple>
#include <unordered_map>
//#include <unordered_set>


using namespace std;
namespace AocDay19 {

    static const std::string InputFileName = "Day19.txt";
    unordered_map<int64_t,int64_t> extraMemory;
    int64_t gRelativePC;
    vector<int64_t> runProgram(std::vector<int64_t>& intops,const std::vector<int32_t>& stdIn, std::string& stdOut,int32_t* lastPtr);
    union cordinateTranslator{
        int32_t XY[2];
        int64_t both;
    };
    
    std::string solvea() {
        constexpr int32_t gridSize = 50;
        auto input = parseFileForLines(InputFileName);
        auto x = parseCsvLineForLongNum(input[0]);
        vector<int32_t> args{};
        vector<int64_t> output{};
        string outStr{"---"};
        int32_t lastPC = 0;
        for(int32_t iy = 0; iy < gridSize;iy++) {
            for(int32_t ix = 0; ix < gridSize;ix++) {
                args.clear();
                args.push_back(ix);
                args.push_back(iy);
                auto input = x;
                auto outI = runProgram(input, args, outStr,&lastPC);
                for_each(outI.begin(),outI.end(),[&output](const int64_t i){output.push_back(i);});
            }
        }
        
		return to_string(std::accumulate(output.begin(), output.end(), 0));
    }

    //4090569 is too low
    std::string solveb() {
        constexpr int32_t gridSize = 50000;
        constexpr int32_t minShipSz = 100;
//        stringstream view{};
        auto input = parseFileForLines(InputFileName);
        auto ins = parseCsvLineForLongNum(input[0]);
        vector<int32_t> args{};
        string outStr{"---"};
        int32_t lastPC = 0;
//        view << "\n";
        auto firstX = 0;
        auto lastX = 0;
        auto firstY = 0;
        auto lastY = 0;
        for(int32_t iy = 0; iy < gridSize;iy++) {
            bool xDone = false;
            bool xStart = false;
            for(int32_t ix = firstX; !xDone && ix < gridSize;ix++) {
                args.clear();
                args.push_back(ix);
                args.push_back(iy);
                auto input = ins;
                auto outI = runProgram(input, args, outStr,&lastPC);
                if(outI.back() == 1) {
                    if(!xStart) {
                        firstX = ix;
                        xStart = true;
                    }
                } else {
                    if(xStart) {
                        xDone = true;
                        lastX = ix;
                    }
                }
            }
            if(lastX-firstX >= minShipSz) {
                for(int32_t x = firstX; x <= lastX-minShipSz; x++) {
                    bool yDone = false;
                    bool yStart = false;
                    for(int32_t y = iy; !yDone && y < iy+minShipSz;y++) {
                        args.clear();
                        args.push_back(x);
                        args.push_back(y);
                        auto input = ins;
                        auto outI = runProgram(input, args, outStr,&lastPC);
                        if(outI.back() == 1) {
                            if(!yStart) {
                                firstY = y;
                                yStart = true;
                            }
                        } else {
                            if(yStart) {
                                yDone = true;
                                lastY = y;
                            }
                        }
                    }
                    if(!yDone) {
                        lastY = iy+minShipSz;
                    }
                    if(lastY-firstY >= minShipSz) {
                        return to_string(x*10000+firstY);
                    }
                }
                
            }
        }
		return "---";
    }

    vector<int64_t> runProgram(std::vector<int64_t>& intops,const std::vector<int32_t>& stdIn, std::string& stdOut,int32_t* lastPtr) {
            int64_t relativePC = gRelativePC;
    //        unordered_map<int64_t,int64_t> extraMemory;
            
            stringstream ss{};
            vector<int64_t> outInts{};
            auto inItr = stdIn.begin();
            auto itr = intops.begin();
            if(lastPtr != nullptr) {
                if(*lastPtr > 0) {
                    itr += *lastPtr;
                }
                *lastPtr = 0;
            }
            bool needsInput{false};
            vector<std::function<int32_t(int64_t*,int64_t*,int64_t*)>> ops = {
                [&itr](int64_t*,int64_t*,int64_t*){cerr << "ERROR: Op code Undefinded: " << *itr << endl;return 4;},
                [](int64_t*p1,int64_t*p2,int64_t*p3){*p3=*p1+*p2;return 4;},
                [](int64_t*p1,int64_t*p2,int64_t*p3){*p3=*p1**p2;return 4;},
                [&](int64_t*p1,int64_t*,int64_t*){if(inItr==stdIn.end()){needsInput = true;if(lastPtr != nullptr) {*lastPtr = static_cast<int32_t>(itr-intops.begin());if(*lastPtr == 0) {*lastPtr = -1;}}}else {*p1= *inItr++;} return 2;},
                [&ss,&outInts](int64_t*p1,int64_t*,int64_t*){if(*p1 < 128) {ss << static_cast<char>(*p1);} else {ss << *p1;}outInts.push_back(*p1);return 2;},
                [&intops,&itr](int64_t*p1,int64_t*p2,int64_t*){return (*p1 != 0 ? (intops.begin()+*p2)-itr : 3);},
                [&intops,&itr](int64_t*p1,int64_t*p2,int64_t*){return (*p1 == 0 ? (intops.begin()+*p2)-itr : 3);},
                [](int64_t*p1,int64_t*p2,int64_t*p3){(*p1 < *p2) ? *p3=1 : *p3 = 0;return 4;},
                [](int64_t*p1,int64_t*p2,int64_t*p3){(*p1 == *p2) ? *p3=1 : *p3 = 0;return 4;},
                [&relativePC](int64_t*p1,int64_t*,int64_t*){relativePC += *p1; return 2;}
            };
            
            while(itr <= intops.end() && *itr != 99 && !needsInput) {
                int32_t code = *itr %100;
                int32_t pMode[3];
                pMode[0] = (*itr /100) % 10;
                pMode[1] = (*itr /1000) % 10;
                pMode[2] = (*itr /10000);
                int64_t vals[] = {*(itr+1),*(itr+2),*(itr+3)};
                int64_t* params[3];
                for(int32_t i = 0; i < 3; i++) {
                    int64_t index = pMode[i] == 2 ? vals[i]+relativePC : vals[i];
                    params[i] = pMode[i] == 1 ? &vals[i] : index >= intops.size() ? &extraMemory[index] : &intops[index];
                }
                
                if(code < 0 || code >= ops.size()) {
                    code = 0;
                }
                itr += ops[code](params[0],params[1],params[2]);
            }
            stdOut = ss.str();
            return outInts;
        }
}
