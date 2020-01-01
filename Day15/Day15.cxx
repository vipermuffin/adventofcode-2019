//
//  Advent of Code 2019 Solutions: Day 15
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/31/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//

#include "Day15.h"
#include "AoCUtils.h"
//Common Libraries
#include <algorithm> //std::sort, find, for_each, max_element, etc
#include <climits>   //INT_MIN, INT_MAX, etc.
#include <functional> //std::function
#include <sstream>
#include <unordered_map>


using namespace std;
namespace AocDay15 {

    union coordinateTranslator{
        int32_t XY[2];
        int64_t both;
    };
    constexpr size_t X = 0;
    constexpr size_t Y = 1;
    constexpr int32_t NORTH = 1;
    constexpr int32_t SOUTH = 2;
    constexpr int32_t WEST  = 3;
    constexpr int32_t EAST  = 4;
    constexpr coordinateTranslator origin{{0,0}};
    static const std::string InputFileName = "Day15.txt";
    unordered_map<int64_t,int64_t> extraMemory;
    int64_t gRelativePC;
    vector<int64_t> runProgram(std::vector<int64_t>& intops,const std::vector<int32_t>& stdIn, std::string& stdOut,int32_t* lastPtr);
    void discoverMap(std::vector<int64_t>& intops,std::unordered_map<int64_t,int32_t>& visited, coordinateTranslator& oxygenPos, coordinateTranslator currentPos, int32_t steps, int32_t* lastPtr);
    void goToOxygenPos(std::vector<int64_t>& intops,std::unordered_map<int64_t,int32_t>& visited,coordinateTranslator currentPos, bool& found, int32_t steps, int32_t* lastPtr);
    
    
    
    std::string solvea() {
        auto input = parseFileForLines(InputFileName);
        auto ops = parseCsvLineForLongNum(input[0]);
        coordinateTranslator oxyPos;
        int32_t lastPC = 0;
        extraMemory.clear();
        unordered_map<int64_t, int32_t> droidMap{{0,0}};
        oxyPos.both = 0;
        discoverMap(ops,droidMap,oxyPos,origin,1,&lastPC);
		return to_string(droidMap[oxyPos.both]);
    }

    std::string solveb() {
        auto input = parseFileForLines(InputFileName);
        auto ops = parseCsvLineForLongNum(input[0]);
        coordinateTranslator oxyPos;
        int32_t lastPC = 0;
        extraMemory.clear();
        unordered_map<int64_t, int32_t> droidMap{{0,0}};
        oxyPos.both = 0;
        bool found = false;
        goToOxygenPos(ops, droidMap, origin, found, 1, &lastPC);
        droidMap.clear();
        discoverMap(ops, droidMap, oxyPos, origin, 1, &lastPC);
        auto itr = max_element(droidMap.begin(), droidMap.end(), [](const std::pair<int64_t,int32_t>&rhs,const std::pair<int64_t,int32_t>&lhs){return rhs.second < lhs.second;});
        return to_string(itr->second);
    }

    void discoverMap(std::vector<int64_t>& intops,std::unordered_map<int64_t,int32_t>& visited, coordinateTranslator& oxygenPos, coordinateTranslator currentPos, int32_t steps, int32_t* lastPtr) {
        vector<int32_t> args{};
        vector<int32_t> antiArgs{};
        vector<int64_t> output{};
        string outStr{"---"};
        
        //Go north as far as can go, then retrace steps then east, then west, then south
        currentPos.XY[Y]++;
        if(visited.count(currentPos.both) == 0 || visited.at(currentPos.both) > steps) {
            args.push_back(NORTH);
            output = runProgram(intops, args, outStr, lastPtr);
            args.pop_back();
            if(output.back() != 0) {
                antiArgs.push_back(SOUTH);
                visited[currentPos.both] = steps;
                if(output.back() == 2) {
                    oxygenPos.both = currentPos.both;
                }
                
                discoverMap(intops, visited, oxygenPos, currentPos, steps+1, lastPtr);
                (void)runProgram(intops, antiArgs, outStr, lastPtr);
                antiArgs.pop_back();
            }
        }
        currentPos.XY[Y]--;
        
        currentPos.XY[X]++;
        if(visited.count(currentPos.both) == 0 || visited.at(currentPos.both) > steps) {
            args.push_back(EAST);
            output = runProgram(intops, args, outStr, lastPtr);
            args.pop_back();
            if(output.back() != 0) {
                antiArgs.push_back(WEST);
                visited[currentPos.both] = steps;
                if(output.back() == 2) {
                    oxygenPos.both = currentPos.both;
                }
                
                discoverMap(intops, visited, oxygenPos, currentPos, steps+1, lastPtr);
                (void)runProgram(intops, antiArgs, outStr, lastPtr);
                antiArgs.pop_back();
            }
        }
        currentPos.XY[X]--;
        
        currentPos.XY[X]--;
        if(visited.count(currentPos.both) == 0 || visited.at(currentPos.both) > steps) {
            args.push_back(WEST);
            output = runProgram(intops, args, outStr, lastPtr);
            args.pop_back();
            if(output.back() != 0) {
                antiArgs.push_back(EAST);
                visited[currentPos.both] = steps;
                if(output.back() == 2) {
                    oxygenPos.both = currentPos.both;
                }
                
                discoverMap(intops, visited, oxygenPos, currentPos, steps+1, lastPtr);
                (void)runProgram(intops, antiArgs, outStr, lastPtr);
                antiArgs.pop_back();
            }
        }
        currentPos.XY[X]++;
        
        currentPos.XY[Y]--;
        if(visited.count(currentPos.both) == 0 || visited.at(currentPos.both) > steps) {
            args.push_back(SOUTH);
            output = runProgram(intops, args, outStr, lastPtr);
            args.pop_back();
            if(output.back() != 0) {
                antiArgs.push_back(NORTH);
                visited[currentPos.both] = steps;
                if(output.back() == 2) {
                    oxygenPos.both = currentPos.both;
                }
                
                discoverMap(intops, visited, oxygenPos, currentPos, steps+1, lastPtr);
                (void)runProgram(intops, antiArgs, outStr, lastPtr);
                antiArgs.pop_back();
            }
        }
        currentPos.XY[Y]++;
    }
    
    void goToOxygenPos(std::vector<int64_t>& intops,std::unordered_map<int64_t,int32_t>& visited,coordinateTranslator currentPos, bool& found, int32_t steps, int32_t* lastPtr) {
        vector<int32_t> args{};
        vector<int32_t> antiArgs{};
        vector<int64_t> output{};
        string outStr{"---"};
        
        
        //Go north as far as can go, then retrace steps then east, then west, then south
        currentPos.XY[Y]++;
        if(!found && (visited.count(currentPos.both) == 0 || visited.at(currentPos.both) > steps)) {
            args.push_back(NORTH);
            output = runProgram(intops, args, outStr, lastPtr);
            args.pop_back();
            if(output.back() != 0) {
                antiArgs.push_back(SOUTH);
                visited[currentPos.both] = steps;
                if(output.back() == 2) {
                    found = true;
                    return;
                }
                
                goToOxygenPos(intops, visited, currentPos, found, steps+1, lastPtr);
                if(found) {
                    return;
                } else {
                    (void)runProgram(intops, antiArgs, outStr, lastPtr);
                    antiArgs.pop_back();
                }
            }
        }
        currentPos.XY[Y]--;
        
        currentPos.XY[X]++;
        if(!found && (visited.count(currentPos.both) == 0 || visited.at(currentPos.both) > steps)) {
            args.push_back(EAST);
            output = runProgram(intops, args, outStr, lastPtr);
            args.pop_back();
            if(output.back() != 0) {
                antiArgs.push_back(WEST);
                visited[currentPos.both] = steps;
                if(output.back() == 2) {
                    found = true;
                    return;
                }
                
                goToOxygenPos(intops, visited, currentPos, found, steps+1, lastPtr);
                if(found) {
                    return;
                } else {
                    (void)runProgram(intops, antiArgs, outStr, lastPtr);
                    antiArgs.pop_back();
                }
            }
        }
        currentPos.XY[X]--;
        
        currentPos.XY[X]--;
        if(!found && (visited.count(currentPos.both) == 0 || visited.at(currentPos.both) > steps)) {
            args.push_back(WEST);
            output = runProgram(intops, args, outStr, lastPtr);
            args.pop_back();
            if(output.back() != 0) {
                antiArgs.push_back(EAST);
                visited[currentPos.both] = steps;
                if(output.back() == 2) {
                    found = true;
                    return;
                }
                
                goToOxygenPos(intops, visited, currentPos, found, steps+1, lastPtr);
                if(found) {
                    return;
                } else {
                    (void)runProgram(intops, antiArgs, outStr, lastPtr);
                    antiArgs.pop_back();
                }
            }
        }
        currentPos.XY[X]++;
        
        currentPos.XY[Y]--;
        if(!found && (visited.count(currentPos.both) == 0 || visited.at(currentPos.both) > steps)) {
            args.push_back(SOUTH);
            output = runProgram(intops, args, outStr, lastPtr);
            args.pop_back();
            if(output.back() != 0) {
                antiArgs.push_back(NORTH);
                visited[currentPos.both] = steps;
                if(output.back() == 2) {
                    found = true;
                    return;
                }
                
                goToOxygenPos(intops, visited, currentPos, found, steps+1, lastPtr);
                if(found) {
                    return;
                } else {
                    (void)runProgram(intops, antiArgs, outStr, lastPtr);
                    antiArgs.pop_back();
                }
            }
        }
        currentPos.XY[Y]++;
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
