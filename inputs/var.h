#include "inputs.h"

#ifndef var_h
#define var_h

class var
{
private:
    numerical my_input;

public:

    var (numerical input_in)
    {
        my_input = input_in;
    }
    var(int input)
    {
        int_input *the_input = new int_input[1];
        the_input[0] = input;
        my_input = the_input[0];
        // my_input->input = the_input.input;
        delete [] the_input;
    }

    var(Louble input)
    {
        louble_input *the_input = new louble_input[1];
        the_input[0] = input;
        my_input = the_input[0];
        // my_input->input = the_input.input;
        delete [] the_input;
    }

    var(double input)
    {
        louble_input *the_input = new louble_input[1];
        the_input[0] = input;
        my_input = the_input[0];
        // my_input->input = the_input.input;
        delete [] the_input;
    }

    var()
    {
    }

    basic_input get_input()
    {
        return my_input;
    }

    void print_value()
    {
        my_input.print_input();
    }

    void print_datatype()
    {
        my_input.print_datatype();
    }

    var operator+(var other_var)
    {
        var output = (my_input + other_var.get_input());
        return output;
    }
};

#endif