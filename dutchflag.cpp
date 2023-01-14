#include<iostream>
#include<algorithm>

using namespace std;
void tatooOnTheScreen(int data[],int size);

int main (int argc, char *argv[])
{
    // Get size and input array
    int size;
    cin>>size;
    int data[size];
    for(int i=0; i<size; i++)
        cin>>data[i];

    int futureZero = 0, futureTwo = size - 1, t = 0; // t = traveller

    for( ; t < size - 1; ){
        if(data[t] == 0){
            swap(data[t], data[futureZero]);
            futureZero++;
        }
        else {
            if(data[t] == 2){
                swap(data[t], data[futureTwo]);
                futureTwo--;
            }
            if(data[t] == 0){
                futureZero++;
            }
        }
        tatooOnTheScreen(data, size);
        t++;
    }

    return 0;
}

void tatooOnTheScreen(int data[],int size){
    for(int i = 0; i<size; i++){
        cout<<data[i]<<" ";
    }
}

