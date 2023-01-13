#include <iostream>
#include <algorithm>

using namespace std;

// Find number of trailing zeros present in n!
// only 5x2 can yield a 0, so taking the minimum of 5s / 2s can determine how many zeros are there
int trailingZeros(int n){
    int fives = 0, twos = 0;

    for( ; n>=2; n--){
        for(int multiple = n; multiple>0; ){
            if(multiple%5==0){
                multiple/=5;
                fives ++;
            } else {
                break; // break is necessary, because, have to end loop when there is no further 5 is present in the number
            }
        }
        for(int multiple = n; multiple>0; ){
            if(multiple%2==0){
                multiple/=2;
                twos++;
            } else {
                break;
            }
        }
    }
    return min(fives, twos);
} 

int main (int argc, char *argv[])
{
    int n;
    cin>>n;
    cout<<trailingZeros(n);
    return 0;
}
