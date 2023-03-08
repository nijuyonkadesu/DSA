#ifndef SUBSET_CONSTRUCT_H
#define SUBSET_CONSTRUCT_H

#include "nfa.h"
#include "dfa.h"

set<state> build_eps_closure(NFA nfa, set<state> states);
DFA subset_construct(NFA nfa);

#endif
