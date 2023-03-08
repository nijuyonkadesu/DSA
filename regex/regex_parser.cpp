// Recursive Descent Parsing
// LL(1) parser
#include "nfa.h"
#include "subset_construct.h"

// Singleton class, encaptulates the input stream
class Scanner{
    public:

        void init(string data_){
            data = preprocess(data_);
            next = 0;
        }

        // returns the current data
        char peek(){
            return (next < data.size()) ? data[next] : 0;
        }

        // returns current data and updates next pointer
        // more like deque (idk why he named it pop)
        char pop(){
            char cur = peek();
            if(next < data.size())
                ++next;
            
            return cur;
        }

        // returns the current position
        unsigned get_pos(){
            return next;
        }

        friend Scanner& my_scanner();

    private:
        Scanner()
        {}

        // To preprocess input regex
        string preprocess(string in);

        string data;
        unsigned next;
};

Scanner& my_scanner(){
    static Scanner my_scan_singleton;
    return my_scan_singleton;
}

// Send the input expression here
string Scanner::preprocess(string in){
    string out = "";

    // c = current, up = current + 1
    string::const_iterator c = in.begin(), up = c + 1;
    
    // Go through all input symbols
    for( ; up != in.end(); ++c, ++up){
        out.push_back(*c);

        // only passes when char: aa, )a => a.a, ).a
        // makes sense right ??
        if ((isalnum(*c) || *c == ')' || *c == '*' || *c == '?') &&
            (*up != ')' && *up != '|' && *up != '*' && *up != '?'))
            out.push_back('.'); // symbol for concatenation
    }

    // Since the previous loop stops because of up pointer, add the last char
    if(c != in.end())
        out.push_back(*c);

    return out;
}

typedef enum {CHR, STAR, QUESTION, ALTER, CONCAT} node_type;
// Parse Node
struct parse_node {
    parse_node(node_type type_, char data_, parse_node* left_, parse_node* right_):
        type(type_), data(data_), left(left_), right(right_)
    {}

    node_type type;
    char data;
    parse_node* left;
    parse_node* right;
};

parse_node* expr();

void print_tree(parse_node* node, unsigned offset){
    if (!node)
        return;

    for (unsigned i = 0; i < offset; ++i)
        cout << " ";

    switch (node->type)
    {
    case CHR:
        cout << node->data;
        break;
    case ALTER:
        cout << '|';
        break;
    case CONCAT:
        cout << '.';
        break;
    case QUESTION:
        cout << '?';
        break;
    case STAR:
        cout << '*';
        break;
    default:
        assert(0);
    }

    cout << endl;

    print_tree(node->left, offset + 4);
    print_tree(node->right, offset + 4);
}

NFA tree_to_nfa(parse_node* tree){
    assert(tree);
    switch(tree->type){
        case CHR:
            return build_nfa_basic(tree->data);
        case ALTER:
            return build_nfa_alter(tree_to_nfa(tree->left), tree_to_nfa(tree->right));
        case CONCAT:
            return build_nfa_concat(tree_to_nfa(tree->left), tree_to_nfa(tree->right));
        case STAR:
            return build_nfa_star(tree_to_nfa(tree->left));
        case QUESTION:
            return build_nfa_alter(tree_to_nfa(tree->left), build_nfa_basic(EPS));
        default: 
            assert(0);
    }
}

// RD Parser Begin:
// Character
// #5
parse_node* chr(){
    char data = my_scanner().peek();

    if(isalnum(data) || data == 0){
        return new parse_node(CHR, my_scanner().pop(), 0, 0);
    }

    cerr << "Parse error: expected alphanumeric, got" << my_scanner().peek() << "at #" << my_scanner().get_pos() << endl;
    exit(1);
}

// Within parenthesis
// '(' expr ')'
// #4
parse_node* atom(){
    parse_node* atom_node;

    if(my_scanner().peek() == '('){
        my_scanner().pop();
        atom_node = expr();

        if(my_scanner().pop() != ')'){
            cerr << "Parse error: expected ')'" << endl;
            exit(1);
        }
    } else {
        atom_node = chr();
    }

    return atom_node;
}

// atom '*'
// atom '?'
// #3
parse_node* rep(){

    parse_node* atom_node = atom();

    if(my_scanner().peek() == '*'){
        my_scanner().pop();

        parse_node* rep_node = new parse_node(STAR, 0, atom_node, 0);
        return rep_node;
    } else if (my_scanner().peek() == '?') {
        my_scanner().pop();

        parse_node* rep_node = new parse_node(QUESTION, 0, atom_node, 0);
        return rep_node;
    } else {
        return atom_node;
    }
}

// rep '.' concat
// #2
parse_node* concat() {
    parse_node* left = rep();
    
    if(my_scanner().peek() == '.'){
        my_scanner().pop();
        parse_node* right = concat();

        parse_node* concat_node = new parse_node(CONCAT, 0, left, right);
        return concat_node;
    } else {
        return left;
    }
}

// concat '|' expr
// #1
parse_node* expr(){
    parse_node* left = concat();

    if(my_scanner().peek() == '|'){
        my_scanner().pop();
        parse_node* right = expr();

        parse_node* expr_node = new parse_node(ALTER, 0, left, right);
        return expr_node;
    } else {
        return left;
    }
}
// RD Parser Ends:

int main(int argc, char** argv){
    if(argc != 3){
        cerr << "Usage: " << argv[0] << " <regex> <string>" << endl;
        exit(1);
    }

    my_scanner().init(argv[1]);

    parse_node* n = expr();

    // Successful parsing returns 0 on peek
    // coz, you're in last element, there's no next
    if(my_scanner().peek() != 0){
        cerr << "Parse error: unexpected char " << my_scanner().peek() 
                << " at #" << my_scanner().get_pos() << endl;
        exit(1);
    }

    NFA nfa = tree_to_nfa(n);
    nfa.show();
    print_tree(n, 0);

    DFA dfa = subset_construct(nfa);
    dfa.show();
    cout<<endl<<endl;

    cout<<"Result: "<<dfa.simulate(argv[2])<<endl;
}
