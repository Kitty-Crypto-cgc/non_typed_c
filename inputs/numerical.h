#include "basic.h"

#ifndef numerical_h
#define numerical_h

class numerical : public basic_input
{
public:
    virtual void save_input(void *input_in)
    {
        switch (input.datatype)
        {
        case __byte__:
            input.value.byte_ = *static_cast<Byte *>(input_in);
            break;
        case __ubyte__:
            input.value.ubyte_ = *static_cast<Ubyte *>(input_in);
            break;
        case __int__:
            input.value.int_ = *static_cast<int *>(input_in);
            break;
        case __sint__:
            input.value.sint_ = *static_cast<Sint *>(input_in);
            break;
        case __lint__:
            input.value.lint_ = *static_cast<Lint *>(input_in);
            break;
        case __uint__:
            input.value.uint_ = *static_cast<Uint *>(input_in);
            break;
        case __usint__:
            input.value.usint_ = *static_cast<Usint *>(input_in);
            break;
        case __ulint__:
            input.value.ulint_ = *static_cast<Ulint *>(input_in);
            break;
        case __float__:
            input.value.float_ = *static_cast<float *>(input_in);
            break;
            input.value.double_ = *static_cast<double *>(input_in);
            break;
        case __louble__:
            input.value.louble_ = *static_cast<Louble *>(input_in);
            break;
        default:
            print_error("Error: unrecognised type ");
        }
    }
    virtual void plus(basic_input other_operand, bool mute = false, String operation = "addition") = 0;
    virtual void minus(basic_input other_operand, bool mute = false, String operation = "subtraction") = 0;
    virtual void times(basic_input other_operand, bool mute = false, String operation = "multiplication") = 0;
    virtual void over(basic_input other_operand, bool mute = false, String operation = "division") = 0;
    // virtual void power(basic_input other_operand, bool mute = false, String operation = "potentiation") = 0;

    virtual bool check_size(basic_input *input_1, basic_input *input_2, Louble buffer, String operation, bool mute = false) = 0;
    virtual bool check_size(basic_input *other_input, Louble buffer, String operation, bool mute) = 0;

    virtual void print_input(bool add_endl = true, String operation = "printing") = 0;
};

#endif