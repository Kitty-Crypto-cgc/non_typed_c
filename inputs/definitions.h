#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <climits>
#include <cctype>
#include <sstream>
#include <iterator>
#include <limits>
#include <cmath>

#include "../mods/colourmod.h"

using namespace std;
using String = std::string;
using Byte = signed char;
using Ubyte = unsigned char;
using Sint = signed short int;
using Lint = signed long int;
using Uint = unsigned int;
using Usint = unsigned short int;
using Ulint = unsigned long int;
using Louble = long double;

#ifndef definitions_h
#define definitions_h

class error__
{
protected:
    String error_text;
    bool locked, initialised;

public:
    error__(String in_prompt = "NULL", bool add_endl = true)
    {
        if (in_prompt != "NULL")
        {
            error_text = in_prompt;
            initialised = true;
            print_error(error_text, add_endl);
        }
        else
            initialised = false;

        locked = false;
    }

    void change_text(String in_text)
    {
        if (!is_locked())
            error_text = in_text;
        else
            print_error("Error changing text: Error handler locked");
    }

    void print_error(String in_error_text = "NULL", bool add_endl = true)
    {
        Color::Modifier red_text(Color::FG_RED);
        Color::Modifier default_text(Color::FG_DEFAULT);

        if (in_error_text != "NULL")
        {
            cout << red_text << in_error_text << default_text;
            if (add_endl)
                cout << red_text << "." << default_text << endl;
        }
        else
        {
            if (is_initialised())
            {
                cout << red_text << error_text << default_text;
                if (add_endl)
                    cout << red_text << "." << default_text << endl;
            }
            else
                print_error("No error message provided");
        }
    }

    void operator=(const char *other_string)
    {
        change_text(other_string);
        initialised = true;
    }

    void operator+=(const char *other_string)
    {
        string new_text = error_text + other_string;
        change_text(new_text);
        initialised = true;
    }

    void operator+=(char other_string)
    {
        string new_text = error_text + other_string;
        change_text(new_text);
        initialised = true;
    }

    error__ operator+(const char *other_string)
    {
        string new_text = error_text + other_string;
        error__ output;

        output.change_text(new_text);
        return output;
    }

    error__ operator+(char other_string)
    {
        string new_text = error_text + other_string;
        error__ output;

        output.change_text(new_text);
        return output;
    }

    void lock() { locked = true; }
    void unlock() { locked = false; }

    void clear()
    {
        if (!is_locked())
            initialised = false;
        else
            print_error("Can't clear object: Object is locked");
    }

    bool is_initialised() { return initialised; }
    bool is_locked() { return locked; }
};

class multitype : public error__
{
protected:
    enum Tern : char
    {
        false_t = -1,
        unkown_t = 0,
        true_t = 1,
    };

    enum datatypes : char
    {
        __char__ = 0,
        __byte__,
        __ubyte__,
        __string__,
        __int__,
        __sint__,
        __lint__,
        __uint__,
        __usint__,
        __ulint__,
        __float__,
        __double__,
        __louble__,
        __bool__,
        __tern__,
        __undefined_datatype__ = -1
    };

    enum objectypes : char
    {
        __numeric__ = 0,
        __alphanumeric__,
        __logic__,
        __undefined_objectype__ = -1
    };

    struct __types__
    {
        char char_;
        Byte byte_;
        Ubyte ubyte_;
        String string_;
        signed int int_;
        signed short int sint_;
        signed long int lint_;
        Uint uint_;
        Usint usint_;
        Ulint ulint_;
        float float_;
        double double_;
        Louble louble_;
        bool bool_;
        Tern tern_;
    };

    struct __object__
    {
        __types__ value;
        char datatype;
        char objectype;
        char *compatible_types;
        Ubyte size_of_compat;
    };

    virtual void define_compatibilities()
    {
        switch (input.objectype)
        {
        case __numeric__:
            input.size_of_compat = 11;
            input.compatible_types = new char[input.size_of_compat];
            input.compatible_types[0] = __byte__;
            input.compatible_types[1] = __ubyte__;
            input.compatible_types[2] = __int__;
            input.compatible_types[3] = __sint__;
            input.compatible_types[4] = __lint__;
            input.compatible_types[5] = __uint__;
            input.compatible_types[6] = __usint__;
            input.compatible_types[7] = __ulint__;
            input.compatible_types[8] = __float__;
            input.compatible_types[9] = __double__;
            input.compatible_types[10] = __louble__;
            break;
        case __alphanumeric__:
            input.size_of_compat = 2;
            input.compatible_types = new char[input.size_of_compat];
            input.compatible_types[0] = __char__;
            input.compatible_types[1] = __string__;
            break;
        case __logic__:
            input.size_of_compat = 2;
            input.compatible_types = new char[input.size_of_compat];
            input.compatible_types[0] = __bool__;
            input.compatible_types[1] = __tern__;
            break;
        default:
            input.size_of_compat = 1;
            input.compatible_types = new char[input.size_of_compat];
            input.compatible_types[0] = __undefined_datatype__;
            break;
        }
    }

public:
    __object__ input;

    multitype()
    {
        initialised = false;
    }

    void operator=(multitype other_object)
    {
        input.value = other_object.input.value;
        input.datatype = other_object.input.datatype;
        input.objectype = other_object.input.objectype;
        input.compatible_types = other_object.input.compatible_types;
        input.size_of_compat = other_object.input.size_of_compat;
        initialised = true;
    }

    void operator=(Byte other_object)
    {
        input.value.byte_ = other_object;
        input.datatype = __byte__;
        input.objectype = __numeric__;
        define_compatibilities();
        initialised = true;
    }

    void operator=(Ubyte other_object)
    {
        input.value.ubyte_ = other_object;
        input.datatype = __ubyte__;
        input.objectype = __numeric__;
        define_compatibilities();
        initialised = true;
    }

    void operator=(int other_object)
    {
        input.value.int_ = other_object;
        input.datatype = __int__;
        input.objectype = __numeric__;
        define_compatibilities();
        initialised = true;
    }

    void operator=(Sint other_object)
    {
        input.value.sint_ = other_object;
        input.datatype = __sint__;
        input.objectype = __numeric__;
        define_compatibilities();
        initialised = true;
    }

    void operator=(Lint other_object)
    {
        input.value.lint_ = other_object;
        input.datatype = __lint__;
        input.objectype = __numeric__;
        define_compatibilities();
        initialised = true;
    }

    void operator=(Uint other_object)
    {
        input.value.uint_ = other_object;
        input.datatype = __uint__;
        input.objectype = __numeric__;
        define_compatibilities();
        initialised = true;
    }

    void operator=(Usint other_object)
    {
        input.value.usint_ = other_object;
        input.datatype = __usint__;
        input.objectype = __numeric__;
        define_compatibilities();
        initialised = true;
    }

    void operator=(Ulint other_object)
    {
        input.value.ulint_ = other_object;
        input.datatype = __ulint__;
        input.objectype = __numeric__;
        define_compatibilities();
        initialised = true;
    }

    void operator=(float other_object)
    {
        input.value.float_ = other_object;
        input.datatype = __float__;
        input.objectype = __numeric__;
        define_compatibilities();
        initialised = true;
    }

    void operator=(double other_object)
    {
        input.value.double_ = other_object;
        input.datatype = __double__;
        input.objectype = __numeric__;
        define_compatibilities();
        initialised = true;
    }

    void operator=(Louble other_object)
    {
        input.value.louble_ = other_object;
        input.datatype = __louble__;
        input.objectype = __numeric__;
        define_compatibilities();
        initialised = true;
    }

    void operator=(char other_object)
    {
        input.value.char_ = other_object;
        input.datatype = __char__;
        input.objectype = __alphanumeric__;
        define_compatibilities();
        initialised = true;
    }

    void operator=(String other_object)
    {
        input.value.string_ = other_object;
        input.datatype = __string__;
        input.objectype = __alphanumeric__;
        define_compatibilities();
        initialised = true;
    }

    void operator=(bool other_object)
    {
        input.value.bool_ = other_object;
        input.datatype = __bool__;
        input.objectype = __logic__;
        define_compatibilities();
        initialised = true;
    }

    void operator=(Tern other_object)
    {
        input.value.char_ = other_object;
        input.datatype = __tern__;
        input.objectype = __logic__;
        define_compatibilities();
        initialised = true;
    }
};

String int_to_str(Lint input)
{
    stringstream my_stream;
    String output;
    my_stream << input;
    my_stream >> output;
    return output;
}

String real_to_str(Louble input)
{
    stringstream my_stream;
    String output;
    my_stream << input;
    my_stream >> output;
    return output;
};

String logic_to_str(bool input)
{
    String output;
    if (input == true)
        output = "true";
    else
        output = "false";
    return output;
};

    /*String logic_to_str(Tern input)
    {
        String output;
        switch (input)
        {
            case false_t:
                output = "false"
                break;
            case unkown_t:
                output = "unkown"
                break;
            case true_t:
                output = "true"
                break;
        }
        return output;
    }*/

#endif