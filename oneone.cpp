#include<iostream>

using namespace std;

int constructOne(int d){
    int n=1;
    int limit = d;
    int count = 1;

    while(n%d!=0){
        n=(n*10)+1;
        count++; 
    }
    if(count>=d) return -1;
    else return count;
}

int main (int argc, char *argv[])
{
    int n;
    cin>>n;
    cout<<constructOne(n);
    return 0;
}
