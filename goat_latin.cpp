#include<iostream>
#include<sstream>

using namespace std;

class Solution {
public:
    bool isVowel(char ch){
        ch = tolower(ch);
        return (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u');
    }

    string toGoatLatin(string sentence) {
        stringstream ss(sentence);
        string word;

        stringstream toRes;
        int n = 2;

        while(ss >> word){
            if(isVowel(word[0])){
                toRes<<word;
                toRes<<'m';
                for(int i=1; i<=n; i++){
                    toRes<<'a';
                }
                toRes<<' ';
            } else {
                toRes<<word.substr(1);
                toRes<<word[0];
                toRes<<'m';
                for(int i=0; i<n; i++){
                    toRes<<'a';
                }
                toRes<<' ';
            }
            n++;
        }
        return toRes.str().substr(0, toRes.str().size()-1);
    }
};

// https://leetcode.com/problems/goat-latin/submissions/882298050/
