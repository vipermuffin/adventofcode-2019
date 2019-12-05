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
    
    std::vector<std::pair<int,int>> findIntersections(const std::string& wire1, const std::string& wire2) {
        constexpr int X = 0;
        constexpr int Y = 1;
        union {
            int all;
            int16_t  xy[2];
        } tmp;
        vector<pair<int,int>> pairs;
        vector<int> crs{};
        int16_t x{0},y{0};
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
                tmp.xy[X] = x;
                tmp.xy[Y] = y;
                crs.emplace_back(tmp.all);
            }
            itr++;
        }
        
        //Sort to take advantage of binary search
        std::sort(crs.begin(), crs.end());
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
                tmp.xy[X] = x;
                tmp.xy[Y] = y;
                if(binary_search(crs.begin(), crs.end(), tmp.all)) {
                    pairs.emplace_back(x,y);
                }
            }
            itr++;
        }
        
        return pairs;
    }

    int findBestIntersections(const std::string& wire1, const std::string& wire2) {
        //Union to store x,y values together and steps + bool
        constexpr int X = 0;
        constexpr int Y = 1;
        union {
            int all;
            int16_t  xy[2];
        } tmp,tmp2;
        
        unordered_map<int, int> m;
        int16_t x{0},y{0};
        int16_t count = 0;
        tmp2.xy[Y] = 1;
        
        //Map out first wire locations and number of steps
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
                count++;
                tmp.xy[X] = x;
                tmp.xy[Y] = y;
                tmp2.xy[X] = count;
                if(m[tmp.all] == 0) {
                    //Store steps for this location if first time here
                     m[tmp.all] = tmp2.all;
                }
            }
            itr++;
        }
        
        //Map out second wire and compare if it overlaps
        x=0;
        y=0;
        count = 0;
        std::vector<int> crosses;
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
                tmp.xy[X] = x;
                tmp.xy[Y] = y;
                tmp2.all = m[tmp.all];
                if(tmp2.xy[Y] == 1) {
                    //Wire overlaps, add to cross vector
                    crosses.emplace_back(count+tmp2.xy[X]);
                    tmp2.xy[Y]++;
                    m[tmp.all] = tmp2.all;
                }
            }
            itr++;
        }

        //Sort to get the min to the top
        std::sort(crosses.begin(),crosses.end());
        return crosses[0];
    }

}
