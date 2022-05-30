#include "basic.h"
#include "numerical.h"
#include "louble_input.h"

#ifndef int_input_h
#define int_input_h

class int_input : public numerical
{
public:

    int_input(int input_in)
    {
        define_object(__int__);
        input.value.int_ = input_in;
        define_compatibilities();
        initialised = true;
    }

    int_input(basic_input input_in)
    {
        define_object(__int__);
        input.value.int_ = input_in.cast_to_int();
        define_compatibilities();
        initialised = true;
    }

    int_input()
    {
        initialised = false;
    }
    
};

#endif