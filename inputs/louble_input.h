#include "basic.h"
#include "numerical.h"

#ifndef louble_input_h
#define louble_input_h

class louble_input : public numerical
{

public:
    louble_input(Louble input_in)
    {
        define_object(__louble__);
        input.value.louble_ = input_in;
        define_compatibilities();
        initialised = true;
    }

    louble_input(basic_input input_in)
    {
        define_object(__louble__);
        input.value.louble_ = input_in.cast_to_double();
        define_compatibilities();
        initialised = true;
    }

    louble_input()
    {
        initialised = false;
    }

};

#endif