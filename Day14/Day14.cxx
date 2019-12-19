//
//  Advent of Code 2019 Solutions: Day 14
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/14/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//

#include "Day14.h"
#include "AoCUtils.h"
//Common Libraries
#include <algorithm> //std::sort, find, for_each, max_element, etc
#include <climits>   //INT_MIN, INT_MAX, etc.
#include <sstream>



using namespace std;
namespace AocDay14 {

    static const std::string InputFileName = "Day14.txt";
    std::string solvea() {
        auto input = parseFileForLines(InputFileName);
        ChemicalDictionary x;
        buildMapOfChemicals(input, x);
        auto actual = findIngredients("ORE", "FUEL", x);
		return to_string(actual);
    }

    std::string solveb() {
        auto input = parseFileForLines(InputFileName);
        ChemicalDictionary x;
        buildMapOfChemicals(input, x);
        string base = "ORE";
        string start = "FUEL";
        auto actual = findIngredients(base, start, x,10);
        int64_t num = 1000000000000;
        int64_t low = 10*num/(actual);
        while(actual < num) {
            low+=100;
            actual = findIngredients(base, start, x, low);
        }
        low-=100;
        actual = 0;
        while(actual < num) {
            low++;
            actual = findIngredients(base, start, x, low);
        }

		return to_string(--low);
    }

    
    void parseChemicalFormula(const std::string& chemDef, ChemicalDictionary& chemDict) {
        string s{chemDef};
        for(auto& c : s) {
            if(c == ',' || c == '=' || c == '>') {
                c = ' ';
            }
        }
        stringstream ss{s};
        int x;
        vector<pair<string,int>> d;
        while(ss >> x >> s) {
            d.emplace_back(s,x);
        }
        chemDict[d.back().first] = d;
    }
    
    void buildMapOfChemicals(const std::vector<std::string>& input, ChemicalDictionary& chemDict) {
        for(const auto& line : input) {
            parseChemicalFormula(line, chemDict);
        }
    }
    
    int findIngredientsLevels(const std::string& base, const ChemicalDictionary& chemDict, std::unordered_map<string,int>& chemLevels) {
        vector<string> bases{};
        bases.reserve(chemDict.size());
        //Find elements with base unit
        for(const auto& kvp : chemDict) {
            for(const auto& vp : kvp.second) {
                if(base == vp.first) {
                    bases.push_back(kvp.first);
                }
            }
        }
        int level = 0;
        while(chemLevels.size() != chemDict.size()) {
            level++;
            for(const auto& s : bases) {
                if(chemLevels.count(s) == 0){
                    chemLevels[s] = level;
                }
            }
            bases.clear();
            
            for(const auto& kvp : chemDict) {
                int count = 0;
                for(const auto& vp : kvp.second) {
                    if(chemLevels.count(vp.first) > 0) {
                        count++;
                    }
                }
                if(count == kvp.second.size()-1) {
                    bases.push_back(kvp.first);
                }
            }
        }
        
        return level;
    }
    
    int64_t findIngredients(const std::string& base, const std::string& start, const ChemicalDictionary& chemDict, int64_t needed) {
        unordered_map<string,int> level;
        int maxLevel = findIngredientsLevels(base, chemDict, level);
        
        unordered_map<string, int64_t> required;
        
        if(chemDict.count(start) > 0) {
            
            for(const auto& kvp : chemDict) {
                //Create now so do not accidentally add item and mess up itr below
                required[kvp.first] = 0;
            }
            required[start] = needed;
            
            for(int i = maxLevel; i > 0;i--) {
                vector<string> itemsToErase;
                auto itr = required.begin();
                while(itr != required.end()) {
                    if(level[itr->first] == i) {
                        itemsToErase.push_back(itr->first);
                        if(chemDict.count(itr->first) > 0) {
                            const auto& nextItem = chemDict.at(itr->first);
                            int64_t nextQty = required[itr->first] / nextItem.back().second;
                            if(nextItem.back().second > 1) {
                                if(required[itr->first] % nextItem.back().second != 0) {
                                    nextQty++;
                                }
                            }
                            
                            for(int j = 0; j < nextItem.size()-1;j++) {
                                required[nextItem[j].first] += nextItem[j].second*nextQty;
                            }
                        }
                    }
                    itr++;
                }
                for(const auto& s : itemsToErase) {
                    required.erase(s);
                }
            }
        }

        if(required.size() != 1) {
            for(const auto& kvp : required) {
                cout << kvp.first << ":" << kvp.second << " --> " << level[kvp.first] << endl;
            }
        }
        return required[base];
    }
}
