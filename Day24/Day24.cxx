//
//  Advent of Code 2019 Solutions: Day 24
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/24/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//

#include "Day24.h"
#include "AoCUtils.h"
//Common Libraries
#include <algorithm> //std::sort, find, for_each, max_element, etc
#include <climits>   //INT_MIN, INT_MAX, etc.
#include <functional> //std::function
#include <sstream>
#include <unordered_set>


using namespace std;
namespace AocDay24 {

    static const std::string InputFileName = "Day24.txt";
    std::string solvea() {
        auto input = parseFileForLines(InputFileName);
        watchForDuplicateLifecycle(input);
        auto val = calculateBiodiversity(input);
		return to_string(val);
    }

    std::string solveb() {
        auto input = parseFileForLines(InputFileName);

		return to_string(simulateRecursiveLifecycles(input, 200));
    }

    void processBugLife(std::vector<std::string>& bugs) {
        vector<string> bc{bugs};
        
        for(int i = 0; i < bugs.size();i++) {
            for(int j = 0; j < bugs[0].size();j++) {
                int count = 0;
                for(int y = -1; y <= 1; y+=2) {
                    try {
                        if(bugs.at(y+i).at(j) == '#') {
                            count++;
                        }
                    } catch (const std::out_of_range& e) {
                    }
                }
                for(int x = -1; x <= 1;x+=2) {
                    try {
                        if(bugs.at(i).at(x+j) == '#') {
                            count++;
                        }
                    } catch (const std::out_of_range& e) {
                    }
                }
                if(bugs[i][j] == '#') {
                    if(count != 1) {
                        bc[i][j] = '.';
                    }
                } else {
                    if(count == 1 || count == 2) {
                        bc[i][j] = '#';
                    }
                }
            }
        }
        
        std::swap(bugs,bc);
    }
    
    void processRecursiveBugLifecycle(std::vector<std::string>& bugs,InfiniteGrids& levels,int currentLevel) {
        vector<string> bc{bugs};
        
        for(int i = 0; i < bugs.size();i++) {
            for(int j = 0; j < bugs[0].size();j++) {
                int count = 0;
                for(int y = -1; y <= 1; y+=2) {
                    try {
                        auto c = bugs.at(y+i).at(j);
                        if(c == '#') {
                            count++;
                        } else if (c == '?') {
                            int levelYIdx = y< 0 ? 4 : 0;
                            for(const auto ch : levels[currentLevel+1][levelYIdx]) {
                                if(ch == '#') {
                                    count++;
                                }
                            }
                        }
                    } catch (const std::out_of_range& e) {
                        int levelYIdx = y< 0 ? 1 : 3;
                        if(levels[currentLevel-1][levelYIdx][2] == '#') {
                            count++;
                        }
                    }
                }
                
                for(int x = -1; x <= 1;x+=2) {
                    try {
                        auto c = bugs.at(i).at(x+j);
                        if(c == '#') {
                            count++;
                        } else if (c == '?') {
                            int levelXIdx = x< 0 ? 4 : 0;
                            for(int z = 0; z < 5; z++) {
                                if(levels[currentLevel+1][z][levelXIdx] == '#') {
                                    count++;
                                }
                            }
                        }
                    } catch (const std::out_of_range& e) {
                        int levelXIdx = x< 0 ? 1 : 3;
                        if(levels[currentLevel-1][2][levelXIdx] == '#') {
                            count++;
                        }
                    }
                }
                if(bugs[i][j] == '?') {
                    //Do nothing
                } else if(bugs[i][j] == '#') {
                    if(count != 1) {
                        bc[i][j] = '.';
                    }
                } else {
                    if(count == 1 || count == 2) {
                        bc[i][j] = '#';
                    }
                }
            }
        }
        
        std::swap(bugs,bc);
    }
    
    string flattenBugs(const std::vector<std::string>& bugs) {
        stringstream ss;
        for_each(bugs.begin(), bugs.end(), [&ss](const string& s){ss << s;});
        return ss.str();
    }
    
    int32_t watchForDuplicateLifecycle(std::vector<std::string>& bugs) {
        unordered_set<string> lifecycles;
        
        auto s = flattenBugs(bugs);
        while(lifecycles.count(s) == 0) {
            lifecycles.insert(s);
            processBugLife(bugs);
            s = flattenBugs(bugs);
        }
        
        return lifecycles.size();
    }
    
    int32_t calculateBiodiversity(const std::vector<std::string>& bugs) {
        auto s = flattenBugs(bugs);
        int32_t val = 0;
        for(int i = 0;i < s.size();i++) {
            if(s[i] == '#') {
                val += 1 << i;
            }
        }
        return val;
    }
    
    int32_t simulateRecursiveLifecycles(std::vector<std::string>& bugs, int numTimes) {
        InfiniteGrids ig;
        ig.reserve(numTimes*2+1);
        vector<string> b {
            ".....",
            ".....",
            "..?..",
            ".....",
            "....."
        };
        for(int i = 0; i < numTimes*2+3; i++) {
            ig.push_back(b);
        }
        bugs[2][2] = '?';
        int baseIdx = numTimes+1;
        ig[baseIdx] = bugs;
        
        for(int i = 1; i <= numTimes;i++) {
            InfiniteGrids igCpy{ig};
            for(int j = baseIdx-i;j <= baseIdx+i;j++) {
                processRecursiveBugLifecycle(igCpy[j], ig, j);
            }
            std::swap(ig,igCpy);
        }
        
        return countBugs(ig);
    }
    
    int32_t countBugs(const InfiniteGrids& levels) {
        int32_t sum{0};
        for_each(levels.begin(), levels.end(), [&sum](const std::vector<std::string>& vs){auto s = flattenBugs(vs); sum += std::count(s.begin(),s.end(),'#');});
        return sum;
    }
}
