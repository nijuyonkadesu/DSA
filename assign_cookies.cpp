#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

// https://leetcode.com/problems/assign-cookies/description
int findContentChildren(vector<int>& greed, vector<int>& cookieSize){
    int children = 0;
    sort(cookieSize.begin(), cookieSize.end());

    for(int j=0; j<cookieSize.size(); j++)
        for(int i=0; i<greed.size(); i++)
            if(greed[i]!=0 && cookieSize[j] >= greed[i]){
                children++;
                greed[i] = 0;
                cookieSize[j] = -1;
            } else {
                continue;
            }
    return children;
}
