#include<iostream>
#include<math.h>

using namespace std;
bool happy(int);

int main (int argc, char *argv[])
{
    int n;
    cin>>n;
    cout<<happy(n);
    return 0;
}

bool happy(int num){
    if(num == 1) return true;
    else return false;
    
    int sum = 0;
    while(num != 0){
        sum += pow(num%10, 2);
        num/=10;
    }
    return happy(sum);
}
