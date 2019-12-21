//
//  Advent of Code 2019 Solutions: Day 14
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/14/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//
#pragma once
#include <string>
#include <unordered_map>
#include <vector>

namespace AocDay14 {
    using ChemicalDictionary = std::unordered_map<std::string,std::vector<std::pair<std::string,int>>>;
//Function Definitions
    void buildMapOfChemicals(const std::vector<std::string>& input, ChemicalDictionary& chemDict);
    void parseChemicalFormula(const std::string& chemDef, ChemicalDictionary& chemDict);
    int64_t findIngredients(const std::string& base, const std::string& start, const ChemicalDictionary& chemDict, int64_t needed = 1);
}
