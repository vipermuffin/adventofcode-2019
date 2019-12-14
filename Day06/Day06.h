//
//  Advent of Code 2019 Solutions: Day 6
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/05/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//
#pragma once
#include <string>
#include <vector>
#include <unordered_map>

namespace AocDay06 {
//Function Definitions
    void buildTree(std::unordered_map<std::string, std::vector<std::string>>& tree, const std::vector<std::string>& defs);
    void parseTree(const std::string& node, const std::unordered_map<std::string, std::vector<std::string>>& tree, std::vector<std::string>& iNodes);
    int findPath(const std::string& loc, const std::string& dst,const std::unordered_map<std::string, std::vector<std::string>>& tree);
}
