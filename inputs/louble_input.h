#include "basic.h"
#include "numerical.h"

#ifndef louble_input_h
#define louble_input_h

class louble_input : public numerical
{
private:
public:
    louble_input(Louble input_in)
    {
        define_object(__louble__);
        input.value.louble_ = input_in;
        define_compatibilities();
        initialised = true;
    }

    louble_input()
    {
        initialised = false;
    }

    ~louble_input()
    {
    }

    void plus(basic_input other_operand, bool mute = false, String operation = "addition")
    {
        basic_input *addess_other_op = &other_operand;
        if (!is_initialised())
        {
            print_not_init_error(operation);
            return;
        }

        Louble result = 0;

        if (!are_compatibile(addess_other_op))
        {
            print_incompatible_error(addess_other_op, operation);
            input.value.louble_ = result;
            return;
        }

        Louble buffer;
        buffer = input.value.louble_ + cast_to_double(addess_other_op);
        if (check_size(addess_other_op, buffer, operation, mute))
            result = buffer;

        input.value.louble_ = result;
    }

    void times(basic_input other_operand, bool mute = false, String operation = "multiplication")
    {
        basic_input *addess_other_op = &other_operand;
        if (!is_initialised())
        {
            print_not_init_error(operation);
            return;
        }

        Louble result = 0;

        if (!are_compatibile(addess_other_op))
        {
            print_incompatible_error(addess_other_op, operation);
            input.value.louble_ = result;
            return;
        }

        Louble buffer;
        buffer = input.value.louble_ * cast_to_double(addess_other_op);
        if (check_size(addess_other_op, buffer, operation, mute))
            result = buffer;

        input.value.louble_ = result;
    }

    void minus(basic_input other_operand, bool mute = false, String operation = "subtraction")
    {
        Louble negated_other_operand = -1 * (cast_to_double(&other_operand));
        louble_input new_operand(negated_other_operand);
        plus(new_operand, mute, operation);
    }

    void over(basic_input other_operand, bool mute = false, String operation = "division")
    {
        if (cast_to_double(&other_operand) == 0)
        {
            print_error("Error: Dividing by 0");
            return;
        }

        Louble inverse_other_operand = pow(cast_to_double(&other_operand), -1);
        louble_input new_operand(inverse_other_operand);
        times(new_operand, mute, operation);
    }

    void power(basic_input other_operand, bool mute = false, String operation = "potentiation")
    {
        input.value.louble_ = pow(input.value.louble_, cast_to_double(&other_operand));
    }

    void logarithm(basic_input other_operand , bool mute = false, String operation = "logarithm")
    {
        input.value.louble_ = log10(input.value.louble_)/log10(cast_to_double(&other_operand));
    }

     void logn(bool mute = false, String operation = "logarithm")
    {
        input.value.louble_ = log10(input.value.louble_)/log10(M_E);
    }

    louble_input operator+(basic_input other_louble)
    {
        louble_input temp1(input.value.louble_);
        louble_input temp2(cast_to_double(&other_louble));
        return add(temp1, temp2);
    }

    louble_input operator-(basic_input other_louble)
    {
        louble_input temp1(input.value.louble_);
        louble_input temp2(cast_to_double(&other_louble));
        return subtract(temp1, temp2);
    }

    louble_input operator*(basic_input other_louble)
    {
        louble_input temp1(input.value.louble_);
        louble_input temp2(cast_to_double(&other_louble));
        return multiply(temp1, temp2);
    }

    louble_input operator/(basic_input other_louble)
    {
        louble_input temp1(input.value.louble_);
        louble_input temp2(cast_to_double(&other_louble));
        return divide(temp1, temp2);
    }

    louble_input operator^(basic_input other_louble)
    {
        louble_input temp1(input.value.louble_);
        louble_input temp2(cast_to_double(&other_louble));
        return potentiate(temp1, temp2);
    }

    bool check_size(basic_input *input_1, basic_input *input_2, Louble buffer, String operation, bool mute = false)
    {
        if ((buffer <= std::numeric_limits<Louble>::max()) && (buffer >= -1 * std::numeric_limits<Louble>::min()))
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
        if ((buffer <= std::numeric_limits<Louble>::max()) && (buffer >= -1 + std::numeric_limits<Louble>::min()))
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
            cout << to_string(input.value.louble_);
            if (add_endl)
                cout << endl;
        }
        else
            print_not_init_error(operation);
    }

};

#endif