#include<algorithm>
#include<vector>
#include<iostream>

using namespace std;


bool testPortals(vector<int> portals, int target){

    int currentPortal = 1;
    int prevPortal = 1;

    do{

        prevPortal = currentPortal;
        currentPortal = portals[currentPortal - 1];
        if(currentPortal == target) 
            return true;

    } while(currentPortal != prevPortal);

    return false;
}

void testPortalsExtended(vector<int> portals){

    vector<int> possiblePaths;
    int start = 1;

    int currentPortal = 1;
    int prevPortal = 1;
    int maxLengthOfPath = 0;
    
    do {
        int thisPathLength = 0;

        do {
            prevPortal = currentPortal;
            currentPortal = portals[currentPortal - 1]; 
            thisPathLength++;
        } while (currentPortal != prevPortal);

        // On checking a cycle, unnecessarily adds +1
        thisPathLength--;

        if(thisPathLength >= maxLengthOfPath){
            maxLengthOfPath = thisPathLength;
            possiblePaths.push_back(start);
        }

        start++;
        currentPortal = start;
        prevPortal = start;

    } while(start != *(portals.end()-1));

    for(auto portal: possiblePaths)
        cout<<portal<<" ";
}

int main (int argc, char *argv[]){

    int noOfPortals, target;
    // Get number of portals and the target
    cin >> noOfPortals>> target;

    vector<int> portals(noOfPortals); 

    // Get all of the portals
    for(int i = 0; i<noOfPortals; i++)
        cin>>portals[i];

    if(testPortals(portals, target)){
        cout<<"yes\n";
    } else {
        cout<<"no\n";
    }


    testPortalsExtended(portals);

    return 0;
}

/*
 * Main Q
 *  https://docs.google.com/document/d/e/2PACX-1vQ-VC2rZ_fLdP9Zw5Z8wq968ykE7n7v_5vGxAiCVWgi9FVhJljK4LRbgUZXSDjdhI_VHOCFYmREJ5Wi/pub
 *
 * Extended
 *  https://docs.google.com/document/d/e/2PACX-1vT3cB2kGUUmkZ6Gua91yNSBvxkAjbEO2hHt-nEyRORhaknHGBJnsGVf09lmLLdc0IIOQUw9ppYYpOW6/pub
 */
