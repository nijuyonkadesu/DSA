#include<math.h>
#include<climits>
#include<iostream>

using namespace std;

int main (int argc, char *argv[])
{
    int arr[] = {1, 9, 0, 0, 2, 0, 9};
    int size = 7;
    int target = 11;

    for(int l = 0; l<size; l++)
        for(int r = l + 1; r < size; r++){
            for(int m = r + 1; m < size; m++){
                for(int n = m + 1; n < size; n++){
                    if(arr[l] + arr[r] + arr[m] + arr[n] == target){
                        cout<< arr[l] <<  arr[r] <<  arr[m] <<  arr[n] <<"\n";
                    }
                }
            }
        }

    return 0;
}
