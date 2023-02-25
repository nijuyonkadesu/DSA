#include<iostream>

using namespace std;

typedef enum {ON, OFF} bulbState;
typedef enum {TURN_ON, TURN_OFF} switchCommand;

int main(){
    bulbState state;
    switchCommand command;

}

void machine(bulbState& state, switchCommand& command) {
    switch (state) {
        case ON: 
            if(command == TURN_ON) {
            }
            else if (command == TURN_OFF){
                state = OFF;
            }
            break;
        case OFF:
            if(command == TURN_ON) {
                state = ON;
            }
            else if (command == TURN_OFF){
            }
            break;
    }
}
