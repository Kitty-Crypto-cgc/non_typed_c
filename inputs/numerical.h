#include "basic.h"

#ifndef numerical_h
#define numerical_h

class numerical : public basic_input
{
protected:
    template <typename T>
    T add(T &lhs, T &rhs)
    {
        lhs.plus(rhs);
        return lhs;
    }
    template <typename T>
    T subtract(T &lhs, T &rhs)
    {
        lhs.minus(rhs);
        return lhs;
    }
    template <typename T>
    T multiply(T &lhs, T &rhs)
    {
        lhs.times(rhs);
        return lhs;
    }
    template <typename T>
    T divide(T &lhs, T &rhs)
    {
        lhs.over(rhs);
        return lhs;
    }

    bool operands_are_ints(numerical operand1, numerical operand2)
    {
        if(operand1.cast_to_double() == operand1.cast_to_int())
            return (operand2.cast_to_double() == operand2.cast_to_int()) ? true : false;
        return false;
    }

public:

    numerical(multitype input_in)
    {
        input = input_in.input;
    }

    numerical(__object__ input_in)
    {
        input = input_in;
    }

    numerical()
    {
        //
    }

    void plus(basic_input other_operand, bool mute = false, String operation = "addition")
    {
        switch (input.datatype)
        {
        case __byte__:
            // input.value.byte_ = input.value.byte_ + cast_to_double(other_operand);
            break;
        case __ubyte__:
            //
            break;
        case __int__:
            input.value.int_ = input.value.int_ + other_operand.cast_to_int();
            break;
        case __sint__:
            //
            break;
        case __lint__:
            //
            break;
        case __uint__:
            //
            break;
        case __usint__:
            //
            break;
        case __ulint__:
            //
            break;
        case __float__:
            //
            break;
            //
            break;
        case __louble__:
            input.value.louble_ = input.value.louble_ + other_operand.cast_to_double();
            break;
        }
    }

    void times(basic_input other_operand, bool mute = false, String operation = "multiplication")
    {
        switch (input.datatype)
        {
        case __byte__:
            // input.value.byte_ = input.value.byte_ + cast_to_double(other_operand);
            break;
        case __ubyte__:
            //
            break;
        case __int__:
            input.value.int_ = input.value.int_ * other_operand.cast_to_int();
            break;
        case __sint__:
            //
            break;
        case __lint__:
            //
            break;
        case __uint__:
            //
            break;
        case __usint__:
            //
            break;
        case __ulint__:
            //
            break;
        case __float__:
            //
            break;
            //
            break;
        case __louble__:
            input.value.louble_ = input.value.louble_ * other_operand.cast_to_double();
            break;
        }
    }

    void minus(basic_input other_operand, bool mute = false, String operation = "subtraction")
    {
        switch (input.datatype)
        {
        case __byte__:
            // input.value.byte_ = input.value.byte_ + cast_to_double(other_operand);
            break;
        case __ubyte__:
            //
            break;
        case __int__:
            input.value.int_ = input.value.int_ - other_operand.cast_to_int();
            break;
        case __sint__:
            //
            break;
        case __lint__:
            //
            break;
        case __uint__:
            //
            break;
        case __usint__:
            //
            break;
        case __ulint__:
            //
            break;
        case __float__:
            //
            break;
            //
            break;
        case __louble__:
            input.value.louble_ = input.value.louble_ - other_operand.cast_to_double();
            break;
        }
    }

    void over(basic_input other_operand, bool mute = false, String operation = "division")
    {
        if (other_operand.cast_to_double() == 0.0)
        {
            print_error("Error: Dividing by 0");
            return;
        }

        switch (input.datatype)
        {
        case __byte__:
            // input.value.byte_ = input.value.byte_ + cast_to_double(other_operand);
            break;
        case __ubyte__:
            //
            break;
        case __int__:
            input.value.int_ = input.value.int_ / other_operand.cast_to_int();
            break;
        case __sint__:
            //
            break;
        case __lint__:
            //
            break;
        case __uint__:
            //
            break;
        case __usint__:
            //
            break;
        case __ulint__:
            //
            break;
        case __float__:
            //
            break;
            //
            break;
        case __louble__:
            input.value.louble_ = input.value.louble_ / other_operand.cast_to_double();
            break;
        }
    }

    numerical operator+(numerical other_number)
    {
        numerical operand1(input);
        numerical operand2(other_number.input);
        numerical output;
        if(!operands_are_ints(operand1, operand2))
        {
            operand1.recast(__louble__);
            operand2.recast(__louble__);
        }
        output = add(operand1, operand2);
        return output;
    }
};

#endif