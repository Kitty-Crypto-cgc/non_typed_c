#include "basic.h"

#ifndef bool_input_h
#define bool_input_h

class bool_input : public basic_input
{

private:
public:
    bool_input()
    {
        datatype = __bool__;
        objectype = __logic__;
        define_compatibilities();
    }
};

#endif