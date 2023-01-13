#include<iostream>

using namespace std;
int findGcd(int, int);

int main (int argc, char *argv[])
{
    int a, b;
// a should be smaller than b
    cin>>a>>b;
    cout<<findGcd(a, b);
    return 0;
}

int findGcd(int small, int big){
    if(small == 0 || big == 0){
        return big;
    }
    return findGcd(big%small, small);
}
// Things to see:...
// modular arithmetic
// RSA, a is congruent to b mod x: a%x = b%x is same
// (a+b) % x => (a % x + b % x) % x  :: Uses > Time adjustment +5:30 gmt
// Equivalence class :: 3's factor 0,1,3
//
// class 1 class 2 class 3
// 0 1 2
// 3 4 5
// 6 7 8 ... add 3 to all, and continue
// 
// this is a cryptographic algorithm, 
// we get same remainder on % on different class!!
