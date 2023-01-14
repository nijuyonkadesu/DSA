#include<iostream>

using namespace std;
int sum(int);

int main (int argc, char *argv[])
{
    cout<<sum(5);    
    return 0;
}

int sum(int n){
    if(n<=1)
        return n;
    return n + sum(n-1);
}
