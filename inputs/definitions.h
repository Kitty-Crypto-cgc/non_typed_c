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
using Byte = char;
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

public:
    multitype()
    {
        initialised = false;
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