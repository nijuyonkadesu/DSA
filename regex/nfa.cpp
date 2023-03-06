#include<iostream>
#include<string>
#include<cassert>
#include<cstdlib>
#include "nfa.h"

NFA::NFA(unsigned size_, state initial_, state final_){
    size = size_;
    initial = initial_;
    final = final_;
    assert(is_legal_state(initial));
    assert(is_legal_state(final));

    // Initialize trans_table with an "empty graph"
    // cannot pre-determine the size of matrix, hence have to push back manually
    vector<input> v(size, NONE);
    for(unsigned i = 0; i < size; ++i)
        trans_table.push_back(v);
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

void NFA::append_empty_state(){

    // append an empty row at the bottom 
    // with size + 1 as length
    vector<input> empty_row(size+1, NONE);
    trans_table.push_back(empty_row);
    
    // append a column at the right
    for(state i = 0; i < size; ++i)
        trans_table[i].push_back(NONE);
    size += 1;
}

void NFA::shift_states(unsigned shift){
    // calculate new size and create a new transition table 
    unsigned new_size = size + shift;
    vector<input> empty_row(new_size, NONE);
    vector<vector<input>> new_trans_table(new_size, empty_row);

    for(state i = 0; i < size; ++i)
        for(state j = 0; j < size; ++j)
            new_trans_table[i + shift][j + shift] = trans_table[i][j];

    // update NFA members
    size = new_size;
    initial += shift;
    final += shift;
    trans_table = new_trans_table;
}

void NFA::fill_states(const NFA &other){

    // trans_table = other.trans_table;
    for (state i = 0; i < other.size; ++i){
        for (state j = 0; j < other.size; ++j){
            trans_table[i][j] = other.trans_table[i][j];
        }
    }

    // copying inputs of other to nfa2
    for(set<input>::const_iterator i = other.inputs.begin();
            i != other.inputs.end(); ++i)
        inputs.insert(*i);
}

NFA build_nfa_basic(input in){
    // Build basic nfa for a single input    
    NFA basic(2, 0, 1);
    basic.add_trans(0, 1, in);
    return basic;
}

NFA build_nfa_alter(NFA nfa1, NFA nfa2){
    // Make room for new initial state
    // #1
    nfa1.shift_states(1);

    // Make room for nfa1 to be combined
    // #2
    nfa2.shift_states(nfa1.size);

    // copy of nfa2
    NFA new_nfa(nfa2);

    // #1 + #2, ie, combine trans_table
    new_nfa.fill_states(nfa1);

    // new initial state
    new_nfa.initial = 0;
    new_nfa.add_trans(0, nfa1.initial, EPS);
    new_nfa.add_trans(0, nfa2.initial, EPS);
    
    // new final state
    new_nfa.append_empty_state();
    new_nfa.final = new_nfa.size - 1;
    new_nfa.add_trans(nfa1.final, new_nfa.final, EPS);
    new_nfa.add_trans(nfa2.final, new_nfa.final, EPS);

    return new_nfa;
}

NFA build_nfa_star(NFA nfa){
    // create empty states all around the trans_table
    // and update initial and final state
    nfa.shift_states(1);
    nfa.append_empty_state();

    nfa.add_trans(nfa.final, nfa.initial, EPS);
    nfa.add_trans(0, nfa.initial, EPS);
    nfa.add_trans(nfa.final, nfa.size - 1, EPS);
    nfa.add_trans(0, nfa.size - 1, EPS);

    nfa.initial = 0;
    nfa.final = nfa.size - 1;

    return nfa;
}

NFA build_nfa_concat(NFA nfa1, NFA nfa2){
    // 1's final overlaps with 2's initial
    nfa2.shift_states(nfa1.size - 1);
    NFA new_nfa(nfa2);

    new_nfa.fill_states(nfa1);
    new_nfa.initial = nfa1.initial;

    return new_nfa;
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

