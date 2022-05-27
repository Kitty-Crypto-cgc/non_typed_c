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
    template <typename T>
    T potentiate(T &lhs, T &rhs)
    {
        lhs.power(rhs);
        return lhs;
    }
    template <typename T>
    T ln(T &lhs)
    {
        lhs.logn();
        return lhs;
    }
    template <typename T>
    T loga(T &lhs, T &rhs)
    {
        lhs.logarithm(rhs);
        return lhs;
    }
public:
    virtual void plus(basic_input other_operand, bool mute = false, String operation = "addition") = 0;
    virtual void minus(basic_input other_operand, bool mute = false, String operation = "subtraction") = 0;
    virtual void times(basic_input other_operand, bool mute = false, String operation = "multiplication") = 0;
    virtual void over(basic_input other_operand, bool mute = false, String operation = "division") = 0;
    virtual void power(basic_input other_operand, bool mute = false, String operation = "potentiation") = 0;

    virtual bool check_size(basic_input *input_1, basic_input *input_2, Louble buffer, String operation, bool mute = false) = 0;
    virtual bool check_size(basic_input *other_input, Louble buffer, String operation, bool mute) = 0;

    virtual void print_input(bool add_endl = true, String operation = "printing") = 0;
};

#endif