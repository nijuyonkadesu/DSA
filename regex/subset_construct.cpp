#include "subset_construct.h"

set<state> build_eps_closure(NFA nfa, set<state> states){
    // Push all states into stack, to look at it one by one in loop
    vector<state> unchecked_stack(states.begin(), states.end());

    // Eg: E clos{3, 4} = {3, 4, ...<yet to be found out>..}
    // the input 3, 4 are it's content in the begining.
    // why 3 & 4 ?? coz, EPS transition can happen within itself: 3->3
    set<state> eps_closure(states.begin(), states.end());

    while(!unchecked_stack.empty()){

        // take a single state, say 3
        state t = unchecked_stack.back();
        unchecked_stack.pop_back();

        for(vector<input>::const_iterator i = nfa.trans_table[t].begin(); i != nfa.trans_table[t].end(); ++i){
            if(*i == EPS){
                // if 3->4 on EPS, u gets the value 4
                state u = i - nfa.trans_table[t].begin();

                // if u not already in the set, add it
                if(eps_closure.find(u) == eps_closure.end()){
                    eps_closure.insert(u);
                    // to see whether u has EPS transtition or not
                    unchecked_stack.push_back(u);
                }
            }
        }
    }           
    return eps_closure;
}

static state gen_new_state(){
    static state num = 0;
    return num++;
}

// Subset Construction algorithm
// Creates Equivalent DFA from NFA

DFA subset_construct(NFA nfa){
    DFA dfa;

    // state_rep set of NFA states that represent a DFA state
    // DFA state '0' = {1,2,3,4}
    typedef set<state> state_rep;
    set<state_rep> marked_states;
    set<state_rep> unmarked_states;

    // {1,2,3,4} -> give it a name 0 or 1 or 2 ...
    map<state_rep, state> dfa_state_num;

    // Start exploring from NFA's initial state
    set<state> nfa_initial;
    nfa_initial.insert(nfa.initial);

    // Eg: first = Eclos{0} = {0, 4, 3, 5}
    state_rep first(build_eps_closure(nfa, nfa_initial));
    unmarked_states.insert(first);

    // Assign a name to Eclos{0} as '0' & inserting it as a DFA state
    state dfa_initial = gen_new_state();
    dfa_state_num[first] = dfa_initial;
    dfa.start = dfa_initial;
    
    while(!unmarked_states.empty()){
        // unmarked: Set of States yet to be explored
        // marked: Fully explored states
        // Take a set of states {...} - remove from unmared and add to marked
        state_rep a_state = *(unmarked_states.begin());
        unmarked_states.erase(unmarked_states.begin());
        marked_states.insert(a_state);

        // See if this {...} is an Acceptance State
        // if yes: add it's respective state number to final{} set.
        if(a_state.find(nfa.final) != a_state.end())
            dfa.final.insert(dfa_state_num[a_state]);

        // Iterate throuth the Language {}
        // eg {a, b} is the Language of (a|b)*abb
        // and apply them to {...}
        for(set<input>::const_iterator inp_i = nfa.inputs.begin(); inp_i != nfa.inputs.end(); ++inp_i){
            state_rep next = build_eps_closure(nfa, nfa.move(a_state, *inp_i));

            // As I find new unique set of states on my way of exploration, I add it to unmarked_states.
            // Remember: we started from Eclos{0} ie, first{}
            if(unmarked_states.find(next) == unmarked_states.end() &&
                    marked_states.find(next) == marked_states.end()) {
                unmarked_states.insert(next);
                // Save: Move['0', a] -> Eclos{...} -> (ie, new set of state)
                dfa_state_num[next] = gen_new_state();
            }

            // Pair [{...} state set with a input symbol] and 
            // map it to the State Number.
            dfa.trans_table[make_pair(dfa_state_num[a_state], *inp_i)] = dfa_state_num[next];
        }
    }

    return dfa;
}

