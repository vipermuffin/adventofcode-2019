//
//  Advent of Code 2019 Solutions: Day 12
//
//  https://adventofcode.com/2019
//
//  Created by vipermuffin on 12/12/2019.
//  Copyright © 2019 vipermuffin. All rights reserved.
//

#include "Day12.h"
#include "AoCUtils.h"
//Common Libraries
#include <algorithm> //std::sort, find, for_each, max_element, etc
//#include <array>
#include <climits>   //INT_MIN, INT_MAX, etc.
//#include <chrono>
//#include <iostream>
//#include <fstream> //ifstream
//#include <functional> //std::function
//#include <iomanip> //setfill setw hex
//#include <map>
//#include <math.h> //sqrt
#include <numeric> //std::accumulate
//#include <queue>
//#include <regex>
//#include <set>
#include <sstream>
//#include <thread>
//#include <tuple>
#include <unordered_map>
#include <unordered_set>


using namespace std;
namespace AocDay12 {

    static const std::string InputFileName = "Day12.txt";
    std::string buildMoonStr(const vector<Moon>& mns);
    std::string solvea() {
        auto input = parseFileForLines(InputFileName);
        vector<Moon> moons;
        int x,y,z;
        for(const auto& line : input) {
            sscanf(line.c_str(), "<x=%d, y=%d, z=%d>", &x,&y,&z);
            moons.emplace_back(x,y,z);
        }
        
        for(x = 0; x < 1000;x++) {
            for(int i = 0; i < moons.size(); i++) {
                for(int j = 0; j < moons.size(); j++) {
                    if(i != j) {
                        moons[i] += moons[j];
                    }
                }
            }
            for_each(moons.begin(),moons.end(),[](Moon& m){m.step();});
        }
        
        long sum = 0;
        for(const auto& m : moons) {
            sum += m.kineticEnergy()*m.potentialEnergy();
        }
		return to_string(sum);
    }

    std::string solveb() {
        auto input = parseFileForLines(InputFileName);
        vector<Moon> moons;
        int x,y,z;
        for(const auto& line : input) {
            sscanf(line.c_str(), "<x=%d, y=%d, z=%d>", &x,&y,&z);
            moons.emplace_back(x,y,z);
        }
        long count = 0;
//        unordered_set<long> coords;
        for(;;count++)
        {
            
            for(int i = 0; i < moons.size(); i++) {
                for(int j = 0; j < moons.size(); j++) {
                    if(i != j) {
                        moons[i] += moons[j];
                    }
                }
            }
            for_each(moons.begin(),moons.end(),[](Moon& m){m.step();});
            long sum = 0;
            for(const auto& m : moons) {
                sum += m.kineticEnergy();
            }
            if(sum == 0 || count < 0) {
                return to_string(count);
            }
//            auto s = buildMoonStr(moons);
//            if(coords.count(s) > 0) {
//                return to_string(count);
//            } else {
//                coords.insert(s);
//            }914787595
        }
		return "---";
    }

    std::string buildMoonStr(const vector<Moon>& mns) {
        stringstream ss{};
        auto itr = mns.begin();
        while(itr != mns.end()) {
            ss << itr->position();
            if(++itr != mns.end()) {
                ss << "-";
            }
        }
        return ss.str();
    }
    
    Moon::Moon() {
        x.setTimestep(1);
        x.setOnTimeInSteps(1);
        y.setTimestep(1);
        y.setOnTimeInSteps(1);
        z.setTimestep(1);
        z.setOnTimeInSteps(1);
    }
    
    Moon::Moon(int xpos, int ypos, int zpos) {
        x.setPosition(xpos);
        y.setPosition(ypos);
        z.setPosition(zpos);
        Moon();
    }
    
    Moon& Moon::operator+=(const Moon& rhs) {
        auto velocity = x.velocity();
        if(x.position() != rhs.x.position()) {
            x.position() < rhs.x.position() ? velocity++ : velocity--;
            x.setVelocityPerTimeStep(velocity);
        }
        
        velocity = y.velocity();
        if(y.position() != rhs.y.position()) {
            y.position() < rhs.y.position() ? velocity++ : velocity--;
            y.setVelocityPerTimeStep(velocity);
        }
        
        velocity = z.velocity();
        if(z.position() != rhs.z.position()) {
            z.position() < rhs.z.position() ? velocity++ : velocity--;
            z.setVelocityPerTimeStep(velocity);
        }
        return *this;
    }
    
    bool Moon::operator==(const Moon& rhs) const {
        return x.position() == rhs.x.position() && x.velocity() == rhs.x.velocity() &&
        y.position() == rhs.y.position() && y.velocity() == rhs.y.velocity() &&
        z.position() == rhs.z.position() && z.velocity() == rhs.z.velocity();
    }
    
    void Moon::step() {
        x.step();
        y.step();
        z.step();
    }
    
    int Moon::potentialEnergy() const {
        int energy = 0;
        energy += x.position() > 0 ? x.position() : -x.position();
        energy += y.position() > 0 ? y.position() : -y.position();
        energy += z.position() > 0 ? z.position() : -z.position();
        return energy;
    }
    
    int Moon::kineticEnergy() const {
        int energy = 0;
        energy += x.velocity() > 0 ? x.velocity() : -x.velocity();
        energy += y.velocity() > 0 ? y.velocity() : -y.velocity();
        energy += z.velocity() > 0 ? z.velocity() : -z.velocity();
        return energy;
    }
    
    std::string Moon::position() const {
        stringstream ss{};
        ss << x.position() << "x" << y.position() << "x" << z.position();
        return ss.str();
    }
}
