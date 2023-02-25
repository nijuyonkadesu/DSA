#ifndef NFA_H
#define NFA_H
#include <vector>

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

    private:
        bool is_legal_state(state s);
        state initial;
        state final;
        unsigned size;
        vector<vector<state>> trans_table;
};

#endif
