//
//  Advent of Code 2019 Solutions: Day 13
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/13/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//

#include "Day13.h"
#include "AoCUtils.h"
//Common Libraries
#include <algorithm> //std::sort, find, for_each, max_element, etc
#include <climits>   //INT_MIN, INT_MAX, etc.
#include <sstream>
#include <unordered_map>


using namespace std;
namespace AocDay13 {

    static const std::string InputFileName = "Day13.txt";
    unordered_map<long,long> extraMemory;
    long gRelativePC;
    vector<long> runProgram(std::vector<long>& intops,const std::vector<int>& stdIn, std::string& stdOut,int* lastPtr);
    union cordinateTranslator{
        int XY[2];
        long both;
    };
    constexpr int X = 0;
    constexpr int Y = 1;
    constexpr int PADDLE = 3;
    constexpr int BALL = 4;
    
    std::string solvea() {
        auto input = parseFileForLines(InputFileName);
        extraMemory.clear();
        gRelativePC = 0;
        auto x = parseCsvLineForLongNum(input[0]);
        vector<int> args{};
        string outStr{"---"};
        int lastPC = 0;
        auto outI = runProgram(x, args, outStr,&lastPC);
        unordered_map<long, int> board;
        union cordinateTranslator ct;
        auto itr = outI.begin();
        while(itr < outI.end()) {
            ct.XY[X] = static_cast<int>(*itr++);
            ct.XY[Y] = static_cast<int>(*itr++);
            board[ct.both] = *itr++;
        }
        int count = 0;
        for(const auto& kvp : board) {
            if(kvp.second == 2) {
                count++;
            }
        }

		return to_string(count);
    }

    std::string solveb() {
        auto input = parseFileForLines(InputFileName);
        extraMemory.clear();
        gRelativePC = 0;
        auto x = parseCsvLineForLongNum(input[0]);
        vector<int> args{};
        string outStr{"---"};
        int lastPC = -1;
        x[0] = 2;
        union cordinateTranslator ct;
        union cordinateTranslator lastBallLoc, currBallLoc, paddleLoc;
        currBallLoc.both = 0;
        unordered_map<long, int> board;
        while(lastPC != 0) {
            auto outI = runProgram(x, args, outStr,&lastPC);
            args.clear();
            auto itr = outI.begin();
            while(itr < outI.end()) {
                ct.XY[X] = static_cast<int>(*itr++);
                ct.XY[Y] = static_cast<int>(*itr++);
                board[ct.both] = *itr++;
                if((ct.XY[X]==-1 && ct.XY[Y]==0)) {
                    //Score, do nothing
                }else if(board[ct.both] == PADDLE) {
                    paddleLoc.both = ct.both;
                } else if(board[ct.both] == BALL) {
                    lastBallLoc.both = currBallLoc.both;
                    currBallLoc.both = ct.both;
                    int deltaX = currBallLoc.XY[X] - lastBallLoc.XY[X];
                    int deltaY = currBallLoc.XY[Y] - lastBallLoc.XY[Y];
                    int desiredLoc = currBallLoc.XY[X];
                    if(deltaY > 0) {
                        //ball is traveling to paddle, get to tracked diagnal position
                        if(deltaX > 0) {
                            desiredLoc++;
                        } else {
                            desiredLoc--;
                        }
                    }
                    if(paddleLoc.XY[X] == desiredLoc) {
                        args.push_back(0);
                    } else if( paddleLoc.XY[X] > desiredLoc) {
                        args.push_back(-1);
                    } else {
                        args.push_back(1);
                    }
                }
            }
        }
        ct.XY[X] = -1;
        ct.XY[Y] = 0;
        
		return to_string(board[ct.both]);
    }

    vector<long> runProgram(std::vector<long>& intops,const std::vector<int>& stdIn, std::string& stdOut,int* lastPtr) {
        long relativePC = gRelativePC;
//        unordered_map<long,long> extraMemory;
        
        stringstream ss{};
        vector<long> outInts{};
        auto inItr = stdIn.begin();
        auto itr = intops.begin();
        if(lastPtr != nullptr) {
            if(*lastPtr > 0) {
                itr += *lastPtr;
            }
            *lastPtr = 0;
        }
        bool needsInput{false};
        vector<std::function<int(long*,long*,long*)>> ops = {
            [&itr](long*,long*,long*){cerr << "ERROR: Op code Undefinded: " << *itr << endl;return 4;},
            [](long*p1,long*p2,long*p3){*p3=*p1+*p2;return 4;},
            [](long*p1,long*p2,long*p3){*p3=*p1**p2;return 4;},
            [&](long*p1,long*,long*){if(inItr==stdIn.end()){needsInput = true;if(lastPtr != nullptr) {*lastPtr = static_cast<int>(itr-intops.begin());if(*lastPtr == 0) {*lastPtr = -1;}}}else {*p1= *inItr++;} return 2;},
            [&ss,&outInts](long*p1,long*,long*){ss << *p1;outInts.push_back(*p1);return 2;},
            [&intops,&itr](long*p1,long*p2,long*){return (*p1 != 0 ? (intops.begin()+*p2)-itr : 3);},
            [&intops,&itr](long*p1,long*p2,long*){return (*p1 == 0 ? (intops.begin()+*p2)-itr : 3);},
            [](long*p1,long*p2,long*p3){(*p1 < *p2) ? *p3=1 : *p3 = 0;return 4;},
            [](long*p1,long*p2,long*p3){(*p1 == *p2) ? *p3=1 : *p3 = 0;return 4;},
            [&relativePC](long*p1,long*,long*){relativePC += *p1; return 2;}
        };
        
        while(itr <= intops.end() && *itr != 99 && !needsInput) {
            int code = *itr %100;
            int pMode[3];
            pMode[0] = (*itr /100) % 10;
            pMode[1] = (*itr /1000) % 10;
            pMode[2] = (*itr /10000);
            long vals[] = {*(itr+1),*(itr+2),*(itr+3)};
            long* params[3];
            for(int i = 0; i < 3; i++) {
                long index = pMode[i] == 2 ? vals[i]+relativePC : vals[i];
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
