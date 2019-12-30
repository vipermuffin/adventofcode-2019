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
#include <climits>   //INT_MIN, INT_MAX, etc.
#include <numeric> //std::accumulate
#include <sstream>



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
        auto result = simulateMoons(moons);
		return to_string(result);
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
    
    bool Moon::xEquals(const Moon &rhs) const {
        return x.position() == rhs.x.position() && x.velocity() == rhs.x.velocity();
    }
    
    bool Moon::yEquals(const Moon &rhs) const {
        return y.position() == rhs.y.position() && y.velocity() == rhs.y.velocity();
    }
    
    bool Moon::zEquals(const Moon &rhs) const {
        return z.position() == rhs.z.position() && z.velocity() == rhs.z.velocity();
    }
    
    template<typename T>
    T gcf(T a, T b) {
        if (a == 0 || b == 0) {
            return 0;
        }
        if(a == b) {
            return a;
        }
        auto newA = a > b ? a : b;
        auto newB = a > b ? b : a;
        
        auto c = newA;
        while(c > newB) {
            c -= newB;
        }
        
        return gcf<T>(c,newB);
    }
    
    template<typename T>
    T lcm(T a, T b) {
        auto gcd = gcf<T>(a,b);
        return gcd>0 ? (a*b)/gcd : 0;
    }
    
    int64_t simulateMoons(const std::vector<Moon>& moons) {
        int xsteps{0},ysteps{0},zsteps{0};
        int steps{1};
        auto mcpy{moons};
        bool done = false;
        for(;!done;steps++) {
            for(int i = 0; i < mcpy.size(); i++) {
                for(int j = 0; j < moons.size(); j++) {
                    if(i != j) {
                        mcpy[i] += mcpy[j];
                    }
                }
            }
            for_each(mcpy.begin(),mcpy.end(),[](Moon& m){m.step();});
            
            if(xsteps== 0) {
                done = true;
                for(int x = 0; done && x < mcpy.size();x++) {
                    done = mcpy[x].xEquals(moons[x]);
                }
                if(done) {
                    xsteps = steps;
                }
            }
            
            if(ysteps == 0) {
                done = true;
                for(int y = 0; done && y < mcpy.size();y++) {
                    done = mcpy[y].yEquals(moons[y]);
                }
                if(done) {
                    ysteps = steps;
                }
            }
            
            if(zsteps == 0) {
                done = true;
                for(int z = 0; done && z < mcpy.size();z++) {
                    done = mcpy[z].zEquals(moons[z]);
                }
                if(done) {
                    zsteps = steps;
                }
            }
            
            done = xsteps != 0 && ysteps != 0 && zsteps != 0;
        }
        
        auto xyLcm = lcm<int64_t>(xsteps,ysteps);
        return lcm<int64_t>(xyLcm,zsteps);
    }
    
    int64_t simulateOneMoonDimension(const std::vector<AocUtils::LinearTraveler<int>>& moons){
        int64_t steps{0};
        auto mcpy{moons};
        bool done = false;
        for(;!done;steps++) {
            for(int i = 0; i < mcpy.size(); i++) {
                for(int j = 0; j < mcpy.size(); j++) {
                    if(i != j) {
                        auto d = mcpy[i].position();
                        auto dRhs = mcpy[j].position();
                        auto velocity = mcpy[i].velocity();
                        if(d != dRhs) {
                            d < dRhs ? velocity++ : velocity--;
                            mcpy[i].setVelocityPerTimeStep(velocity);
                        }
                    }
                }
            }
            for_each(mcpy.begin(),mcpy.end(),[](AocUtils::LinearTraveler<int>& m){m.step();});
            
            done = true;
            for(int x = 0; done && x < mcpy.size();x++) {
                done = mcpy[x].position() == moons[x].position() && mcpy[x].velocity() == moons[x].velocity();
            }
        }
        
        return steps;
    }
}
