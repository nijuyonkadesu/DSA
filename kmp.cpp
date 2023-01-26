#include<iostream>
#include<vector>

using namespace std;

int isSubStr(string haystack, string needle);

int main(){
    cout<<isSubStr("aaaxaaaa", "aaaa");
}

int isSubStr(string haystack, string needle){
    if(needle.empty()) return 0;
    vector<int> lps(needle.size()); // longest prefix suffix
    int prevLps = 0, i = 1; // Pointers to lps vector

    // Preprocessing target substring
    while(i < needle.size()){
        if(needle[prevLps] == needle[i]) {
            lps[i] = prevLps + 1; // as we find adjacent characters are same, therefore suffix size is increased by 1
            prevLps++;
            i++;
        } else { // if adjacent characters are different
            if(prevLps == 0) { // if ABAAA <- AB mismatch, where lps is 0
                lps[i] = 0;
                i++;
            }
            else { // mismatch in other positions
                prevLps = lps[prevLps - 1]; // ** play with this, try more example to figure out
            }
        }
    }
    
    int j = 0;
    i = 0;

    while(i < haystack.size()){
        if(haystack[i] == needle[j]){ // Usual comparision
            i++;
            j++;
        }
        else {
            if(j == 0){
                i++;
            }
            else {
                j = lps[j-1];
            }
        }
        if(j == needle.size()){
            return i - needle.size();
        }
    }
    return -1;
}

// https://www.youtube.com/watch?v=JoF0Z7nVSrA 
