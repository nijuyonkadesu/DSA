#include<iostream>

using namespace std;

int main (int argc, char *argv[])
{
    int a=12;
    int b=36;
    int i, j, m;

    int factorOfA[100], factorOfB[100];
    
    for(i=1; i<a; i++){
        for(j=0; j<10; j++){
            if(a%i == 0){
                factorOfA[j] = i;
            }
        }
    }
    for(int k=1;k<b;k++){
        for(m=0;m<10;m++){
            if(b%k==0){
                factorOfB[m]=k;
            }
        }
    }
    int gcd=0;
    for(int a=0;a<j;j++){
        for(int b=0;b<m;b++){
            if(factorOfA[a]==factorOfB[b]){
                if (gcd<factorOfA[a]) {
                    gcd=factorOfA[a];
                    
                }
            }
        }
    }
    cout<<gcd;
    return 0;
}
