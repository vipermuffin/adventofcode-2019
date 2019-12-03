//
//  Advent of Code 2019 Solutions: Day 1
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 11/30/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//

#include "Day01.h"
#include "AoCUtils.h"
//Common Libraries
#include <algorithm> //std::sort, find, for_each, max_element, etc
#include <climits>   //INT_MIN, INT_MAX, etc.
#include <numeric> //std::accumulate



using namespace std;
namespace AocDay01 {

	static const std::string InputFileName = "Day01.txt";
	std::string solvea() {
        auto input = parseFileForNumberPerLine(InputFileName);
        vector<int> x;
        x.reserve(input.size());
        for_each(input.begin(),input.end(),[&x](int y){x.push_back(y/3-2);});
        return to_string(std::accumulate(x.begin(), x.end(), 0));
	}

	std::string solveb() {
        auto input = parseFileForNumberPerLine(InputFileName);
        vector<int> x;
        x.reserve(input.size()*input.size());
        for_each(input.begin(),input.end(),[&x](int y){while(y>6){y=y/3-2;x.push_back(y);}});
        return to_string(std::accumulate(x.begin(), x.end(), 0));
	}

}
