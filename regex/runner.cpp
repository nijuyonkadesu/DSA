#include "nfa.h"

int main(){
    // (a|b)*ab
    NFA a = build_nfa_basic('a');
    NFA b = build_nfa_basic('b');
    NFA alt = build_nfa_alter(a, b);
    NFA str = build_nfa_star(alt);
    NFA sa = build_nfa_concat(str, a);
    NFA sab = build_nfa_concat(sa, b);

    sab.show(); 
    return 0; 
}
