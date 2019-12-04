//
//  Advent of Code 2019 Solutions: Day 4
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/03/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//

#include "Day04.h"
#include "AoCUtils.h"
//Common Libraries
#include <algorithm> //std::sort, find, for_each, max_element, etc
#include <climits>   //INT_MIN, INT_MAX, etc.
#include <unordered_map>


using namespace std;
namespace AocDay04 {

	static const std::string InputFileName = "Day04.txt";

	std::string solvea() {
        auto input = parseFileForLines(InputFileName);
        int count = 0;
        int low,high;
        sscanf(input[0].c_str(),"%d-%d",&low,&high);

        for(int i = low ; i <= high;i++) {
            if(passwordIsValid(to_string(i))) {
                count++;
            }
        }
		return to_string(count);
	}

	std::string solveb() {
        auto input = parseFileForLines(InputFileName);
        int count = 0;
        int low,high;
        sscanf(input[0].c_str(),"%d-%d",&low,&high);
        
        for(int i = low ; i <= high;i++) {
            if(passwordIsValid2(to_string(i))) {
                count++;
            }
        }
        return to_string(count);
	}

    bool passwordIsValid(const string& pw) {
        bool isValid = pw.size() == 6;
        bool isRepeat = false;
        auto itr = pw.begin();
        while(itr != pw.end()-1 && isValid) {
            isValid = *itr <= *(itr+1);
            isRepeat = isRepeat ? true : *itr == *(itr+1);
            itr++;
        }
        
        return isValid&&isRepeat;
    }

    bool passwordIsValid2(const string& pw) {
        bool isValid = pw.size() == 6;
        unordered_map<char,int> m;
        auto itr = pw.begin();
        bool isRepeat = false;
        while(itr != pw.end()-1 && isValid) {
            isValid = *itr <= *(itr+1);
            if(*itr == *(itr+1)) {
                m[*itr]++;
            }
            itr++;
        }
        for(const auto& kvp : m) {
            if(kvp.second == 1) {
                isRepeat = true;
                break;
            }
        }
        return isValid&&isRepeat;
    }

}
