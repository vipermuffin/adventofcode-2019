//
//  Advent of Code 2019 Solutions: Day 6
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/05/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//

#include "Day06.h"
#include "AoCUtils.h"
//Common Libraries
#include <algorithm> //std::sort, find, for_each, max_element, etc
#include <climits>   //INT_MIN, INT_MAX, etc.
#include <unordered_map>



using namespace std;
namespace AocDay06 {

	static const std::string InputFileName = "Day06.txt";
	std::string solvea() {
        auto input = parseFileForLines(InputFileName);
        unordered_map<string, vector<string>> dtree,idtree;
        vector<string> outp;
        buildTree(dtree,input);
        for(const auto& kvp : dtree) {
            parseTree(kvp.first, dtree, outp);
        }
		return to_string(outp.size());
	}

	std::string solveb() {
        auto input = parseFileForLines(InputFileName);
        unordered_map<string, vector<string>> dtree,idtree;
        vector<string> outp;
        buildTree(dtree,input);
		return to_string(findPath("YOU", "SAN", dtree));
	}

    void buildTree(std::unordered_map<std::string, std::vector<std::string>>& tree, const std::vector<std::string>& defs) {
        for(const auto& s : defs) {
            auto idx = s.find(")");
            string a{s.begin(),s.begin()+idx},b{s.begin()+idx+1,s.end()};
            tree[a].push_back(b);
        }
    }
    
    void parseTree(const std::string& node, const std::unordered_map<std::string, std::vector<std::string>>& tree, std::vector<std::string>& iNodes) {
        if(tree.count(node) > 0) {
            for(const auto& n : tree.at(node)) {
                iNodes.push_back(n);
                parseTree(n,tree,iNodes);
            }
        }
    }
    
    int findPathParentChild(const std::string& loc, const std::string& dst,const std::unordered_map<std::string, std::vector<std::string>>& tree, int count) {
        if(tree.count(loc) > 0) {
            for(const auto& n : tree.at(loc)) {
                int x;
                if(n == dst) {
                    return count;
                } else {
                    x = findPathParentChild(n, dst, tree, count+1);
                    if(x > 0) {
                        return x;
                    }
                }
            }
        }
        return -1;
    }
    
    int findPath(const std::string& loc, const std::string& dst,const std::unordered_map<std::string, std::vector<std::string>>& tree) {
        vector<string> outp;
        vector<string> minVector;
        string sharedNode;
        outp.reserve(tree.size());
        
        for(const auto& kvp : tree) {
            parseTree(kvp.first, tree, outp);
            auto pItr = std::find(outp.begin(), outp.end(),loc);
            auto itr = std::find(outp.begin(), outp.end(),dst);
            if(itr != outp.end() && pItr != outp.end()) {
                if(minVector.size()==0 || minVector.size() > outp.size()) {
                    minVector = outp;
                    sharedNode = kvp.first;
                }
            }
            outp.clear();
        }
        
        int x = findPathParentChild(sharedNode, dst, tree, 0);
        int y = findPathParentChild(sharedNode, loc, tree, 0);
        
        return x+y;
    }
}
