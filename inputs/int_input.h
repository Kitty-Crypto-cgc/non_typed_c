#include "basic.h"
#include "numerical.h"
#include "louble_input.h"

#ifndef int_input_h
#define int_input_h

class int_input : public louble_input
{
private:
    using MYTYPE = signed int;
    using MYMETATYPE = int_input;

protected:

    template <typename T>
        T add(T & lhs, T & rhs)
        {
            lhs.plus(rhs);
            return lhs;
        }
        template <typename T>
        T subtract(T & lhs, T & rhs)
        {
            lhs.minus(rhs);
            return lhs;
        }
        template <typename T>
        T multiply(T & lhs, T & rhs)
        {
            lhs.times(rhs);
            return lhs;
        }
        template <typename T>
        T divide(T & lhs, T & rhs)
        {
            lhs.over(rhs);
            return lhs;
        }

    void cast_buffer(MYTYPE *buffer, basic_input other_operand)
    {
        switch (input.datatype)
        {
        case __louble__:
            *buffer = input.value.louble_ + other_operand.cast_to_double();
            break;
        case __int__:
            *buffer = input.value.int_ + other_operand.cast_to_int();
        default:
            break;
        }
    }

    bool check_size(basic_input *input_1, basic_input *input_2, MYTYPE buffer, String operation, bool mute = false)
    {
        if ((buffer <= std::numeric_limits<MYTYPE>::max()) && (buffer >= std::numeric_limits<MYTYPE>::min()))
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

    bool check_size(basic_input *other_input, MYTYPE buffer, String operation, bool mute)
    {
        if ((buffer <= std::numeric_limits<MYTYPE>::max()) && (buffer >= std::numeric_limits<MYTYPE>::min() + 1))
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

    void plus(basic_input other_operand, bool mute = false, String operation = "addition")
    {
        basic_input *address_other_op = &other_operand;

        MYTYPE result = 0;

        if (operation_checks(address_other_op, operation))
        {
            MYTYPE buffer = 0;

            cast_buffer(&buffer, other_operand);

            if (check_size(address_other_op, buffer, operation, mute))
                result = buffer;
        }

        save_input(static_cast<void *>(&result));
    }

    void times(basic_input other_operand, bool mute = false, String operation = "multiplication")
    {
        basic_input *address_other_op = &other_operand;

        MYTYPE result = 0;

        if (operation_checks(address_other_op, operation))
        {
            MYTYPE buffer = 0;

            switch (input.datatype)
            {
            case __louble__:
                buffer = input.value.louble_ * other_operand.cast_to_double();
                break;
            case __int__:
                buffer = input.value.int_ * other_operand.cast_to_int();
            default:
                break;
            }

            if (check_size(address_other_op, buffer, operation, mute))
                result = buffer;
        }

        save_input(static_cast<void *>(&result));
    }

    void minus(basic_input other_operand, bool mute = false, String operation = "subtraction")
    {
        MYTYPE negated_other_operand = -1 * (other_operand.cast_to_double());
        MYMETATYPE new_operand(negated_other_operand);
        plus(new_operand, mute, operation);
    }

    void over(basic_input other_operand, bool mute = false, String operation = "division")
    {
        if (other_operand.cast_to_double() == 0.0)
        {
            print_error("Error: Dividing by 0");
            return;
        }

        MYTYPE inverse_other_operand = pow(other_operand.cast_to_double(), -1);
        MYMETATYPE new_operand(inverse_other_operand);
        times(new_operand, mute, operation);
    }

    /*void power(basic_input other_operand, bool mute = false, String operation = "potentiation")
    {
        input.value.louble_ = pow(input.value.louble_, other_operand.cast_to_double());
    }

    void logarithm(basic_input other_operand, bool mute = false, String operation = "logarithm")
    {
        input.value.louble_ = log10(input.value.louble_) / log10(other_operand.cast_to_double());
    }

    void logn(bool mute = false, String operation = "logarithm")
    {
        input.value.louble_ = log10(input.value.louble_) / log10(M_E);
    }*/

public:
    int_input(int input_in)
    {
        define_object(__int__);
        input.value.int_ = input_in;
        define_compatibilities();
        initialised = true;
    }

    int_input()
    {
        initialised = false;
    }

    ~int_input()
    {
    }

    MYMETATYPE operator+(basic_input other_int)
    {
        MYMETATYPE temp1(input.value.int_);
        MYMETATYPE temp2(other_int.cast_to_int());
        return add(temp1, temp2);
    }

    MYMETATYPE operator-(basic_input other_int)
    {
        MYMETATYPE temp1(input.value.int_);
        MYMETATYPE temp2(other_int.cast_to_int());
        return subtract(temp1, temp2);
    }

    MYMETATYPE operator*(basic_input other_int)
    {
        MYMETATYPE temp1(input.value.int_);
        MYMETATYPE temp2(other_int.cast_to_int());
        return multiply(temp1, temp2);
    }

    MYMETATYPE operator/(basic_input other_int)
    {
        MYMETATYPE temp1(input.value.int_);
        MYMETATYPE temp2(other_int.cast_to_int());
        return divide(temp1, temp2);
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