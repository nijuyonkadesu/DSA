#include<math.h>
#include<climits>
#include<iostream>

using namespace std;

int main (int argc, char *argv[])
{
    int arr[] = {1, 65, -10, -70};
    int size = 4;
    int min = INT_MAX;

    for(int l = 0; l<size; l++)
        for(int r = l + 1; r < size; r++){
            if(abs(arr[l] + arr[r]) < abs(min)){
                min = arr[l] + arr[r];
            }
        }
    cout<<min;
    return 0;
}
