#include<iostream>

using namespace std;

void check(int n){
    int f=1;
    for(int i =2;i<n;i++){
        if(n%i==0){
            if(!(i%2==0 || i%3==0 || i%5==0)){
                f=0;
                break;
            }
        }
    }
    if(f==1) cout<<"Ugly Number";
    else if(f==0) cout<<"Un-Ugly Number";
}


int main ()
{
    int n;
    cin>>n;
    check(n);
    return 0;
}
