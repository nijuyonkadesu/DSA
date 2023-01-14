#include<iostream>
#include<vector>

using namespace std;

void rightRotate(vector<int>& data, int k);

int main (int argc, char *argv[])
{
    vector<int> data = {5, 4, 3, 2, 1, 0};
    int k;
    cin>>k;
    rightRotate(data, k);
    return 0;
}

void rightRotate(vector<int>& data, int k){
    k = k % data.size();
    vector<int> rightPart (data.end() - k, data.end());
    data.erase(data.end() - k, data.end());
    data.insert(data.begin(), rightPart.begin(), rightPart.end());
}
