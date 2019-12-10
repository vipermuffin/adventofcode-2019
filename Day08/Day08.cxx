//
//  Advent of Code 2019 Solutions: Day 8
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/08/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//

#include "Day08.h"
#include "AoCUtils.h"
//Common Libraries
#include <algorithm> //std::sort, find, for_each, max_element, etc
#include <climits>   //INT_MIN, INT_MAX, etc.
#include <unordered_map>


using namespace std;
namespace AocDay08 {

	static const std::string InputFileName = "Day08.txt";
	std::string solvea() {
        auto input = parseFileForLines(InputFileName);
        constexpr int wide = 25;
        constexpr int tall = 6;
        constexpr int layerLen = wide*tall;
        vector<string> layers{};
        layers.reserve(wide*tall);
        auto itr = input[0].begin();
        while(itr < input[0].end()) {
            layers.emplace_back(itr,itr+layerLen);
            itr += layerLen;
        }
        
        vector<int> zero,one,two;
        
        for(const auto& s : layers) {
            unordered_map<char, int> cksm;
            for(const auto& c : s) {
                cksm[c]++;
            }
            zero.push_back(cksm['0']);
            one.push_back(cksm['1']);
            two.push_back(cksm['2']);
        }
        
        auto itr0 = std::min_element(zero.begin(), zero.end());
        int index = static_cast<int>(itr0-zero.begin());
		return to_string(one[index]*two[index]);
	}

	std::string solveb() {
        auto input = parseFileForLines(InputFileName);
        constexpr int wide = 25;
        constexpr int tall = 6;
        constexpr int layerLen = wide*tall;
        vector<string> layers{};
        layers.reserve(wide*tall);
        auto itr = input[0].begin();
        while(itr < input[0].end()) {
            layers.emplace_back(itr,itr+layerLen);
            itr += layerLen;
        }

        string blankImg = "-------------------------";
        vector<string> image;
        image.reserve(tall);
        for(int i = 0;i < tall; i++) {
            image.push_back(blankImg);
        }
        for(int i = 0; i < layers.size();i++) {
            for(int j = 0; j < layers[i].size();j++) {
                int imgIdx = j / wide;
                int imgPixIdx = j % wide;
                if(image[imgIdx][imgPixIdx] == '-' && layers[i][j] != '2') {
                    image[imgIdx][imgPixIdx] = layers[i][j] == '0' ? ' ' : '|';
                }
            }
        }
        cout << endl;
        for(const auto& line : image) {
            cout << line << endl;
        }
		return "---";
	}

}
