#include<iostream>
#include<string>
#include<cassert>
#include<cstdlib>
#include "nfa.h"

using namespace std;

NFA::NFA(unsigned size_, state initial_, state final_){
    size = size_;
    initial = initial_;
    final = final_;
    assert(is_legal_state(initial));
    assert(is_legal_state(final));

    // Initialize trans_table with an "empty graph"
    // cannot pre-determine the size of matrix, hence have to push back manually
    for(unsigned i = 0; i < size; ++i){
        vector<state> v;
        for(unsigned j = 0; j < size; ++j){
            v.push_back(NONE);
        }
        trans_table.push_back(v);
        v.clear();
    }
}

bool NFA::is_legal_state(state s){
    if(s < 0 || s >= size) return false;
    return true;
}

void NFA::add_trans(state from, state to, input in){
    assert(is_legal_state(from));
    assert(is_legal_state(to));
    trans_table[from][to] = in;
}

void NFA::show() {
    cout<<"NFA States: "<<size<<" 0 to "<<size-1<<endl;
    cout<<"Initial State: "<<initial<<endl;
    cout<<"Final State: "<<final<<endl;

    for(unsigned from = 0; from < size; ++from){
        for(unsigned to = 0; to < size; ++to){
            input in = trans_table[from][to];
            if(in != NONE){
                cout<<from<<" -> "<<to<<" (";
                if(in == EPS){
                    cout<<"ε"<<")"<<endl;
                } else {
                    cout<<in<<")"<<endl;
                }
            }
        }
    }
}

