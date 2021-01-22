#include <iostream>
#include "hello.h"


int main(int argc, char* argv[])
{
    using namespace std;
    if(argc == 1)
    {
        send(cout, "Hello world!");
    }
    else
    {
        for(int i{1}; i < argc; i++ && cout)
            send(cout, argv[i]);
    }
    return !cout.good();
}
