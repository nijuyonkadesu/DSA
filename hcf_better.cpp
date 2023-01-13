#include<iostream>

using namespace std;

int main (int argc, char *argv[])
{
    int a = 12, aIndex = 0;
    int b = 24, bIndex = 0;

    int factorOfA[10];
    int factorOfB[10];

    // find factor of A
    for(int i = 1; i<=a; i++){
        if(a%i == 0) factorOfA[aIndex++] = i;
    }
    // find factor of B
    for(int i = 1; i<=a; i++){
        if(a%i == 0) factorOfB[bIndex++] = i;
    }
    
    // Choose the maximum
    int maxCommonFactor = 1;
    for(int i = 0; i < aIndex; i++){
        if(factorOfA[i] > factorOfB[i]){
            maxCommonFactor = factorOfA[i];
        }
        else {
            maxCommonFactor = factorOfB[i];
        }
    }

    cout<<maxCommonFactor;

    return 0;
}
