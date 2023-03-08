#include<iostream>
#include<vector>
#include<stdbool.h>

using namespace std;

vector<vector<char>> railFence(string& plain, int key);
string encrypt(vector<vector<char>>& fence);

vector<vector<char>> railFenceInverse(string& plain, int key);
string decrypt(vector<vector<char>>& fence, string& cipher, int key);

void printMatrix(string& msg, int key);

int main(){
    int key;
    cin>>key;
    string plain;
    cin >> plain;
    vector<vector<char>> fence = railFence(plain, key);
    printMatrix(plain, key);
    
    string cipher = encrypt(fence);
    cout<<"\n Cipher: "<<cipher;
    
    vector<vector<char>> fenceInverse = railFenceInverse(cipher, key);
    
    plain = decrypt(fenceInverse, cipher, key);
    // plain = squash(fenceInverse);
    cout<<"\n Plain: "<<plain;
}

vector<vector<char>> railFence(string& plain, int key){
    vector<vector<char>> fence(key);
    
    int row = 0;
    bool toIncrease = true;
    for(auto ch: plain){
        ch = toupper(ch);
        
        if(row == 0) toIncrease = true;
        else if(row == key - 1) toIncrease = false;
        
        if (toIncrease) {
            fence[row%key].push_back(ch);
            row++;
        }
        else {
            fence[row%key].push_back(ch);
            row--;
        }
    }
    return fence;
}

vector<vector<char>> railFenceInverse(string& cipher, int key){
    // string test = "hhhhhh";
    vector<vector<char>> fenceInverse = railFence(cipher, key);
    int pos = 0;
    // for(auto row: fenceInverse){
    for(int i = 0; i<key; i++){
        for(int j = 0; j<fenceInverse[i].size(); ++j){
            fenceInverse[i][j] = cipher[pos++];
        }
    }
    return fenceInverse;
}

string encrypt(vector<vector<char>>& fence){
    string chapathi;
    for(auto row: fence){
        for(auto ch: row){
            chapathi.push_back(ch);
        }
    }
    return chapathi;
}

string decrypt(vector<vector<char>>& fence, string& cipher, int key){
    int row = 0;
    bool toIncrease = true;
    string chapathi;
    
    for(auto ch: cipher){
        
        if(row == 0){
            toIncrease = true;
        } 
        else if(row == key - 1) {
            toIncrease = false;
        }
        
        if (toIncrease) {
            chapathi.push_back(fence[row%key][0]);
            fence[row%key].erase(fence[row%key].begin());
            ++row;
        }
        else {
            chapathi.push_back(fence[row%key][0]);
            fence[row%key].erase(fence[row%key].begin());
            --row;
        }
    }
    return chapathi;
}

void printMatrix(string& msg, int key){
    int spaces = key;
    bool toIncrease = true;
    cout<<endl;
    
    for(auto ch: msg){
        if(toIncrease){ 
            for(int i=0; i<spaces; i++){
                cout<<"  ";
            }
            spaces--;
        } else {
            spaces++;
            for(int i=1; i<spaces; i++){
                cout<<"  ";
            }
        }

        if(spaces == key) {
            toIncrease = true;
        }
        else if(spaces == 0){
            toIncrease = false;
        }

        cout<<ch<<endl;
    }
}
