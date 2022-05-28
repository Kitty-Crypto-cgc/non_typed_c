#include "basic.h"

#ifndef char_input_h
#define char_input_h

class char_input : public basic_input
{

private:

public:
    char_input()
    {
        datatype = __char__;
        objectype = __alphanumeric__;
        define_compatibilities();
    }
};

#endif