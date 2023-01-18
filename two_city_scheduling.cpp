#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

// https://leetcode.com/problems/two-city-scheduling/description/
class Solution {
public:
    int twoCitySchedCost(vector<vector<int>>& costs) {
        int sum = 0;
        int cityA = costs.size() / 2;
        int cityB = costs.size() / 2;

        sort(costs.begin(), costs.end());

        for(auto x: costs){
            if(x[0]<x[1]){
                if(cityA-- != 0)
                    sum+=x[0];
            } else {
                if(cityB-- != 0)
                    sum+=x[1];
            }
        }
    return sum;
    }
};
