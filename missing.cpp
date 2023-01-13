#include<iostream>

using namespace std;

// simply print the missing numbers from an array
int main (int argc, char *argv[])
{
    int n;
    cin>>n;

    int arr[n];
    
    for(int i=0; i<n; i++){
        cin>>arr[i];
    }
    
    int start = arr[0];
    int end = arr[n-1];

    for(int i=0 ; start < end ; start++){
        if(start != arr[i]){
            cout<<start;
        } else {
            i++;
        }
    }
    return 0;
}
