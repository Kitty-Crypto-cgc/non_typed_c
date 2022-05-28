#include "basic.h"
#include "numerical.h"
#include "louble_input.h"

#ifndef int_input_h
#define int_input_h

class int_input : public numerical
{

private:
public:
    int_input(signed int input_in)
    {
        define_object(__int__);
        input.value.int_ = input_in;
        define_compatibilities();

        initialised = true;
    }

    void plus(basic_input other_operand, bool mute = false, String operation = "addition")
    {
        basic_input *addess_other_op = &other_operand;

        if (!is_initialised())
        {
            print_not_init_error(operation);
            return;
        }

        signed int result = 0;

        if (!are_compatibile(addess_other_op))
        {
            print_incompatible_error(addess_other_op, operation);
            input.value.int_ = result;
            return;
        }

        Louble buffer;
        buffer = round(input.value.int_ + cast_to_int(addess_other_op));
        if (check_size(addess_other_op, buffer, operation, mute))
            result = (signed int)buffer;

        input.value.int_ = result;
    }

    void times(basic_input other_operand, bool mute = false, String operation = "multiplication")
    {
        basic_input *addess_other_op = &other_operand;

        if (!is_initialised())
        {
            print_not_init_error(operation);
            return;
        }
        
        signed int result = 0;
        
        if (!are_compatibile(addess_other_op))
        {
            print_incompatible_error(addess_other_op, operation);
            input.value.int_ = result;
            return;
        }
        
        Louble buffer;
        buffer = round((input.value.int_) * (cast_to_double(addess_other_op)));
        if (check_size(addess_other_op, buffer, operation, mute))
            result = (signed int)buffer;
        
        input.value.int_ = result;
    }

    void minus(basic_input other_operand, bool mute = false, String operation = "subtraction")
    {
        signed int negated_other_operand = -1 * (cast_to_int(&other_operand));
        int_input new_operand(negated_other_operand);
        plus(new_operand, mute, operation);
    }

    void over(basic_input other_operand, bool mute = false, String operation = "division")
    {
        if (cast_to_int(&other_operand) == 0)
        {
            print_error("Error: Dividing by 0");
            return;
        }

        Louble inverse_other_operand = pow((Louble)cast_to_int(&other_operand), -1);      
        louble_input new_operand(inverse_other_operand);
        times(new_operand, mute, operation);
    }

    void power(basic_input other_operand, bool mute = false, String operation = "potentiation")
    {
        input.value.int_ = pow(input.value.int_, cast_to_double(&other_operand));
    }

      void logarithm(basic_input other_operand , bool mute = false, String operation = "logarithm")
    {
        input.value.int_ = log10(input.value.int_)/log10(cast_to_double(&other_operand));
    }

     void logn(bool mute = false, String operation = "logarithm")
    {
        input.value.int_ = log10(input.value.int_)/log10(M_E);
    }


    int_input operator+(basic_input other_int)
    {
        int_input temp1(input.value.int_);
        int_input temp2(cast_to_int(&other_int));
        return add(temp1, temp2);
    }

    int_input operator-(basic_input other_int)
    {
        int_input temp1(input.value.int_);
        int_input temp2(cast_to_int(&other_int));
        return subtract(temp1, temp2);
    }

    int_input operator*(basic_input other_int)
    {
        int_input temp1(input.value.int_);
        int_input temp2(cast_to_int(&other_int));
        return multiply(temp1, temp2);
    }

    int_input operator/(basic_input other_int)
    {
        int_input temp1(input.value.int_);
        int_input temp2(cast_to_int(&other_int));
        return divide(temp1, temp2);
    }

    int_input operator^(basic_input other_int)
    {
        louble_input temp1(input.value.int_);
        louble_input temp2(cast_to_double(&other_int));
        louble_input temp3 = potentiate(temp1, temp2);
        int_input temp4(cast_to_int(&temp3));
        return temp4;
    }

    bool check_size(basic_input *input_1, basic_input *input_2, Louble buffer, String operation, bool mute = false)
    {
        if ((buffer <= std::numeric_limits<signed int>::max()) && (buffer >= std::numeric_limits<signed int>::min()))
            return true;
        else
        {
            if (mute)
                return false;
            print_incompatible_error(input_1, input_2, operation, false);
            print_error(". Result is out of output class' limits");
            return false;
        }
    }

    bool check_size(basic_input *other_input, Louble buffer, String operation, bool mute)
    {
        if ((buffer <= std::numeric_limits<signed int>::max()) && (buffer >= std::numeric_limits<signed int>::min()))
            return true;
        else
        {
            if (mute)
                return false;
            print_incompatible_error(other_input, operation, false);
            print_error(". Result is out of output class' limits");
            return false;
        }
    }

    void print_input(bool add_endl = true, String operation = "printig")
    {
        if (is_initialised())
        {
            cout << to_string(input.value.int_);
            if (add_endl)
                cout << endl;
        }
        else
            print_not_init_error(operation);
    }
};

#endif