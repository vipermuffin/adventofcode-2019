//
//  Advent of Code 2019 Solutions: Day 11
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/11/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//

#include "Day11.h"
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
#include <sstream>
//#include <thread>
//#include <tuple>
#include <unordered_map>
//#include <unordered_set>


using namespace std;
namespace AocDay11 {

    static const std::string InputFileName = "Day11.txt";
    unordered_map<long,long> extraMemory;
    long gRelativePC;
    std::string solvea() {
        auto input = parseFileForLines(InputFileName);
        auto x = parseCsvLineForLongNum(input[0]);
        vector<int> args{0};
        string outStr{"---"};
        int lastPC = 0;
        RobotPainter rb;
        
        extraMemory.clear();
        gRelativePC = 0;
        runProgram(x, args, outStr, &lastPC);

        while(lastPC!=0) {
            bool paint = outStr[0] == '1';
            bool turnRight = outStr[1] == '1';
            (void) rb.paintAndTurn(paint, turnRight);
            args.clear();
            paint = rb.step();
            args.push_back(paint ? 1 : 0);
            runProgram(x, args, outStr, &lastPC);
        }
		return to_string(rb.countPaintedTiles());
    }

    std::string solveb() {
        auto input = parseFileForLines(InputFileName);
        auto x = parseCsvLineForLongNum(input[0]);
        vector<int> args{1};
        string outStr{"---"};
        int lastPC = 0;
        RobotPainter rb;
        rb.paintAndTurn(true, true);
        rb.paintAndTurn(true, false);
        extraMemory.clear();
        gRelativePC = 0;
        runProgram(x, args, outStr, &lastPC);
        
        while(lastPC!=0) {
            bool paint = outStr[0] == '1';
            bool turnRight = outStr[1] == '1';
            (void) rb.paintAndTurn(paint, turnRight);
            args.clear();
            paint = rb.step();
            args.push_back(paint ? 1 : 0);
            runProgram(x, args, outStr, &lastPC);
        }
        (void) rb.paintAndTurn(outStr[0] == '1', outStr[1] == '1');
        (void) rb.step();
        rb.viewCanvas();
		return outStr;
    }

    void runProgram(std::vector<long>& intops,const std::vector<int>& stdIn, std::string& stdOut,int* lastPtr) {
        long relativePC = gRelativePC;
//        unordered_map<long,long> extraMemory;
        
        stringstream ss{};
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
            [&ss](long*p1,long*,long*){ss << *p1;return 2;},
            [&intops,&itr](long*p1,long*p2,long*){return (*p1 != 0 ? (intops.begin()+*p2)-itr : 3);},
            [&intops,&itr](long*p1,long*p2,long*){return (*p1 == 0 ? (intops.begin()+*p2)-itr : 3);},
            [](long*p1,long*p2,long*p3){(*p1 < *p2) ? *p3=1 : *p3 = 0;return 4;},
            [](long*p1,long*p2,long*p3){(*p1 == *p2) ? *p3=1 : *p3 = 0;return 4;},
            [&relativePC](long*p1,long*,long*){relativePC += *p1; return 2;}
        };
        
        while(itr < intops.end() && *itr != 99 && !needsInput) {
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
        gRelativePC = relativePC;
    }
    
    void RobotPainter::viewCanvas() const {
        int min[] = {INT_MAX,INT_MAX};
        int max[] = {INT_MIN,INT_MIN};
        union cordinateTranslator ct;
        for(const auto& kvp : canvas) {
            ct.both = kvp.first;
            for(int i = 0; i < 2; i++) {
                if(ct.XY[i] > max[i]) {
                    max[i] = ct.XY[i];
                }
                if(ct.XY[i] < min[i]) {
                    min[i] = ct.XY[i];
                }
            }
        }
        cout << min[X] << "," << max[X] << endl;
        cout << min[Y] << "," << max[Y] << endl;
        //Get range
        std::string s(max[X]-min[X],' ');
        std::vector<std::string> board;
        board.reserve((max[Y]-min[Y])*(max[X]-min[X]));
        for(int i = 0; i <= max[Y]-min[Y]; i++) {
            board.push_back(s);
        }
        
        for(const auto& kvp : canvas) {
            if(kvp.second.first) {
                ct.both = kvp.first;
                board[(ct.XY[Y]-min[Y])][ct.XY[X]-min[X]] = '@';
            }
        }
        
        auto yItr = board.rbegin();
        while(yItr != board.rend()) {
            auto xItr = yItr->begin();
            while(xItr != yItr->end()) {
                cout << *xItr;
                xItr++;
            }
            cout << endl;
            yItr++;
        }
    }
}
