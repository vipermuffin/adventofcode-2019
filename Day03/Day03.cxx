//
//  Advent of Code 2019 Solutions: Day 3
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/02/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//

#include "Day03.h"
#include "AoCUtils.h"
//Common Libraries
#include <algorithm> //std::sort, find, for_each, max_element, etc
#include <climits>   //INT_MIN, INT_MAX, etc.
#include <sstream>
#include <unordered_map>

using namespace std;
namespace AocDay03 {

	static const std::string InputFileName = "Day03.txt";
	std::string solvea() {
        auto input = parseFileForLines(InputFileName);
        auto p = findIntersections(input[0], input[1]);
        int min = INT_MAX;
        for(const auto& k : p) {
            int md = k.first>0 ? k.first : -k.first;
            md += k.second>0 ? k.second : -k.second;
            if(md < min) {
                min = md;
            }
        }
		return to_string(min);
	}

	std::string solveb() {
        auto input = parseFileForLines(InputFileName);
        
		return to_string(findBestIntersections(input[0], input[1]));
	}

    std::string pairToString(int x, int y) {
        stringstream ss{};
        ss << x << "x" << y;
        return ss.str();
    }
    
    std::vector<std::pair<int,int>> findIntersections(const std::string& wire1, const std::string& wire2) {
        
        vector<pair<int,int>> pairs;
        unordered_map<string, int> m;
        int x{0},y{0};
        m[pairToString(x,y)]++;
        auto input = parseCsvLineForWords(wire1);
        auto itr = input.begin();
        while(itr != input.end()) {
            string num{itr->begin()+1,itr->end()};
            int steps = stoi(num);
            for(int i = 0; i < steps;i++) {
                if((*itr)[0] == 'R') {
                    x++;
                } else if((*itr)[0] == 'L') {
                    x--;
                } else if((*itr)[0] == 'U') {
                    y++;
                } else if((*itr)[0] == 'D') {
                    y--;
                }
                m[pairToString(x,y)]++;
            }
            itr++;
        }
        x=0;
        y=0;
        input = parseCsvLineForWords(wire2);
        itr = input.begin();
        while(itr != input.end()) {
            string num{itr->begin()+1,itr->end()};
            int steps = stoi(num);
            for(int i = 0; i < steps;i++) {
                if((*itr)[0] == 'R') {
                    x++;
                } else if((*itr)[0] == 'L') {
                    x--;
                } else if((*itr)[0] == 'U') {
                    y++;
                } else if((*itr)[0] == 'D') {
                    y--;
                }
                if(m[pairToString(x,y)] > 0) {
                    pairs.emplace_back(x,y);
                }
            }
            itr++;
        }
        
        return pairs;
    }
    
    int findBestIntersections(const std::string& wire1, const std::string& wire2) {
        
        vector<pair<int,int>> pairs;
        unordered_map<string, int> m;
        int x{0},y{0};
        m[pairToString(x,y)]++;
        auto input = parseCsvLineForWords(wire1);
        auto itr = input.begin();
        while(itr != input.end()) {
            string num{itr->begin()+1,itr->end()};
            int steps = stoi(num);
            for(int i = 0; i < steps;i++) {
                if((*itr)[0] == 'R') {
                    x++;
                } else if((*itr)[0] == 'L') {
                    x--;
                } else if((*itr)[0] == 'U') {
                    y++;
                } else if((*itr)[0] == 'D') {
                    y--;
                }
                m[pairToString(x,y)] = 1;
            }
            itr++;
        }
        x=0;
        y=0;
        int count = 0;
        input = parseCsvLineForWords(wire2);
        itr = input.begin();
        while(itr != input.end()) {
            string num{itr->begin()+1,itr->end()};
            int steps = stoi(num);
            for(int i = 0; i < steps;i++) {
                if((*itr)[0] == 'R') {
                    x++;
                } else if((*itr)[0] == 'L') {
                    x--;
                } else if((*itr)[0] == 'U') {
                    y++;
                } else if((*itr)[0] == 'D') {
                    y--;
                }
                count++;
                if(m[pairToString(x,y)] == 1) {
                    m[pairToString(x,y)] = count;
                    pairs.emplace_back(x,y);
                }
            }
            itr++;
        }
        
        x=0;
        y=0;
        count =0;
        std::vector<int> crosses;
        input = parseCsvLineForWords(wire1);
        itr = input.begin();
        while(itr != input.end()) {
            string num{itr->begin()+1,itr->end()};
            int steps = stoi(num);
            for(int i = 0; i < steps;i++) {
                if((*itr)[0] == 'R') {
                    x++;
                } else if((*itr)[0] == 'L') {
                    x--;
                } else if((*itr)[0] == 'U') {
                    y++;
                } else if((*itr)[0] == 'D') {
                    y--;
                }
                count++;
                if(m[pairToString(x,y)] != 1) {
                    crosses.emplace_back(count+m[pairToString(x,y)]);
                    pairs.emplace_back(x,y);
                }
            }
            itr++;
        }
        std::sort(crosses.begin(),crosses.end());
        return crosses[0];
    }
}
