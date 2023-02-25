#ifndef NFA_H
#define NFA_H
#include <vector>
#include <set>

using namespace std;

typedef unsigned state;
typedef char input;
enum {EPS = -1, NONE = 0};

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

    // private:
        bool is_legal_state(state s);
        state initial;
        state final;
        unsigned size;
        vector<vector<input>> trans_table;

        // set of all input states
        set<input> inputs;
};

// NFA building functions

NFA build_nfa_alter(NFA nfa1, NFA nfa2);

#endif
