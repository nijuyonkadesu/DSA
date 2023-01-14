#include<iostream>

int handshakeWithMe(int n){
    if(n == 2) return 1;
    return n - 1 + handshakeWithMe(n - 1);
}

int main (int argc, char *argv[])
{
    std::cout<<handshakeWithMe(6)<<std::endl;
    int handshakes;
    std::cin>>handshakes;
    std::cout<<handshakes * (handshakes - 1) / 2 ; // usual summation formula is n(n+1)/2
    return 0;
}
