#ifndef NFA_H
#define NFA_H

#include "common.h"

// Implement Copy constructor

class NFA {
    public:
        // Number of states, initial & final state
        NFA(unsigned size_, state initial_, state final_);

        // add a new transtion from a state to another with a input
        void add_trans(state from, state to, input in);
        void show(void);

        void append_empty_state();
        void shift_states(unsigned shift);
        void fill_states(const NFA& other);

        bool is_legal_state(state s);
        state initial;
        state final;
        unsigned size;
        vector<vector<input>> trans_table;

        // set of all input states
        set<input> inputs;
        set<state> move(set<state> states, input inp);
};

// NFA building functions

NFA build_nfa_alter(NFA nfa1, NFA nfa2);
NFA build_nfa_star(NFA nfa);
NFA build_nfa_concat(NFA nfa1, NFA nfa2);
NFA build_nfa_basic(input in);

#endif
