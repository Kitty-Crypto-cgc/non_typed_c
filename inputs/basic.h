#include "definitions.h"

#ifndef basic_h
#define basic_h

class basic_input : public multitype
{
public:
    basic_input()
    {
        initialised = false;
    }

    void initialise()
    {
        initialised = true;
    }

    void define_object(char in_datatype)
    {
        input.datatype = in_datatype;

        switch (in_datatype)
        {
        case __byte__:
        case __ubyte__:
        case __int__:
        case __sint__:
        case __lint__:
        case __uint__:
        case __usint__:
        case __ulint__:
        case __float__:
        case __double__:
        case __louble__:
            input.objectype = __numeric__;
            break;
        case __char__:
        case __string__:
            input.objectype = __alphanumeric__;
            break;
        case __bool__:
        case __tern__:
            input.objectype = __logic__;
            break;
        default:
            input.objectype = __undefined_objectype__;
            break;
        }
    }

    void recast(char in_datatype)
    {
        switch (in_datatype)
        {
        case __byte__:
        case __ubyte__:
        case __int__:
            input.value.int_ = cast_to_int();
            define_object(__int__);
            break;
        case __sint__:
        case __lint__:
        case __uint__:
        case __usint__:
        case __ulint__:
        case __float__:
        case __double__:
        case __louble__:
            input.value.louble_ = cast_to_double();
            define_object(__louble__);
            break;
        case __char__:
        case __string__:
        case __bool__:
        case __tern__:
        default:
            define_object(__undefined_datatype__);
            break;
        }
    }

    String print_datatype(char input_datatype = -128, bool mute = false, bool add_endl = true)
    {
        char output_datatype;
        String output;

        if (input_datatype == -128)
            output_datatype = input.datatype;
        else
            output_datatype = input_datatype;

        switch (output_datatype)
        {
        case __char__:
            output = "char";
            break;
        case __byte__:
            output = "byte";
            break;
        case __ubyte__:
            output = "unsigned byte";
            break;
        case __string__:
            output = "string";
            break;
        case __int__:
            output = "int";
            break;
        case __sint__:
            output = "short int";
            break;
        case __lint__:
            output = "long int";
            break;
        case __uint__:
            output = "unsigned int";
            break;
        case __ulint__:
            output = "unigned long int";
            break;
        case __usint__:
            output = "unsigned short int";
            break;
        case __float__:
            output = "float";
            break;
        case __double__:
            output = "double";
            break;
        case __louble__:
            output = "long double";
            break;
        case __bool__:
            output = "bool";
            break;
        case __tern__:
            output = "ternary";
            break;
        default:
            output = "undefined";
            break;
        }

        if (!mute)
        {
            cout << output;
            if (add_endl)
                cout << "." << endl;
        }
        return output;
    }

    bool are_compatibile(basic_input *input_1, basic_input *input_2, bool two_inputs = true)
    {
        bool result = false;

        char *the_compatible_types = input_1->get_compatible_types();

        char datatype2 = input_2->get_datatype();

        for (Byte i = 0; i < input_1->get_size_of_compat(); i++)
        {
            if (datatype2 == the_compatible_types[i])
            {
                result = true;
                break;
            }
        }

        return result;
    }

    bool are_compatibile(basic_input *other_input)
    {
        bool result = false;

        char *the_compatible_types = get_compatible_types();

        char datatype2 = other_input->get_datatype();

        for (Byte i = 0; i < get_size_of_compat(); i++)
        {
            if (datatype2 == the_compatible_types[i])
            {
                result = true;
                break;
            }
        }

        return result;
    }

    char get_datatype() { return input.datatype; }

    char *get_compatible_types()
    {
        char *output = new char[1];
        output[0] = __undefined_datatype__;

        if (!is_initialised())
            print_error("Cannot determine compatible types: Object type has not been declared");
        else
        {
            delete[] output;
            output = input.compatible_types;
        }

        return output;
    }

    Byte get_size_of_compat() { return input.size_of_compat; }

    void print_incompatible_error(basic_input *input_1, basic_input *input_2, String operation, bool add_endl = true)
    {
        String error_message;
        char in1_type, in2_type;

        in1_type = input_1->get_datatype();
        in2_type = input_2->get_datatype();

        error_message = "Cannot perform " + operation + " of " + print_datatype(in2_type, true, false) + ", with " + print_datatype(in1_type, true, false);
        print_error(error_message, add_endl);
    }

    void print_incompatible_error(basic_input *other_input, String operation, bool add_endl = true)
    {
        String error_message;
        char my_type, other_type;

        my_type = get_datatype();
        other_type = other_input->get_datatype();

        error_message = "Cannot perform " + operation + " of " + print_datatype(other_type, true, false) + ", with " + print_datatype(my_type, true, false);
        print_error(error_message, add_endl);
    }

    void print_not_init_error(String operation, bool add_endl = true)
    {
        String error_message;
        error_message = "Cannot perform " + operation + " operation. Object is not initialised";
        print_error(error_message, add_endl);
    }

    Lint cast_to_int()
    {
        Lint output = 0;
        switch (input.datatype)
        {
        case __char__:
            output = (Lint)input.value.char_;
            break;
        case __byte__:
            output = (Lint)input.value.byte_;
            break;
        case __ubyte__:
            output = (Lint)input.value.ubyte_;
            break;
        case __int__:
            output = input.value.int_;
            break;
        case __sint__:
            output = (Lint)input.value.sint_;
            break;
        case __lint__:
            output = (Lint)input.value.lint_;
            break;
        case __uint__:
            output = (Lint)input.value.uint_;
            break;
        case __usint__:
            output = (Lint)input.value.usint_;
            break;
        case __ulint__:
            output = (Lint)input.value.ulint_;
            break;
        case __float__:
            output = round((Lint)input.value.float_);
            break;
        case __double__:
            output = round((Lint)input.value.double_);
            break;
        case __louble__:
            output = round((Lint)input.value.louble_);
            break;
        case __bool__:
            if (input.value.bool_ == true)
                output = 1;
            else
                output = 0;
            break;
        case __tern__:
            output = (Lint)input.value.tern_;
            break;
        default:
            String error_message;
            error_message = "Cannot typecast " + print_datatype(get_datatype(), true) + " into int";
            print_error(error_message);
        }
        return output;
    }

    Louble cast_to_double()
    {
        Louble output = 0;
        switch (input.datatype)
        {
        case __char__:
            output = (Louble)input.value.char_;
            break;
        case __byte__:
            output = (Louble)input.value.byte_;
            break;
        case __ubyte__:
            output = (Louble)input.value.ubyte_;
            break;
        case __int__:
            output = (Louble)input.value.int_;
            break;
        case __sint__:
            output = (Louble)input.value.sint_;
            break;
        case __lint__:
            output = (Louble)input.value.lint_;
            break;
        case __uint__:
            output = (Louble)input.value.uint_;
            break;
        case __usint__:
            output = (Louble)input.value.usint_;
            break;
        case __ulint__:
            output = (Louble)input.value.ulint_;
            break;
        case __float__:
            output = (Louble)input.value.float_;
            break;
        case __double__:
            output = (Louble)input.value.double_;
            break;
        case __louble__:
            output = input.value.louble_;
            break;
        case __bool__:
            if (input.value.bool_ == true)
                output = 1;
            else
                output = 0;
            break;
        case __tern__:
            output = (Louble)input.value.tern_;
            break;
        default:
            String error_message;
            error_message = "Cannot typecast " + print_datatype(get_datatype(), true) + " into double";
            print_error(error_message);
        }
        return output;
    }

    multitype get_input()
    {
        multitype output;
        switch (input.datatype)
        {
        case __char__:
            output.input.value.char_ = input.value.char_;
            break;
        case __byte__:
            output.input.value.byte_ = input.value.byte_;
            break;
        case __ubyte__:
            output.input.value.ubyte_ = input.value.ubyte_;
            break;
        case __int__:
            output.input.value.int_ = input.value.int_;
            break;
        case __sint__:
            output.input.value.sint_ = input.value.sint_;
            break;
        case __lint__:
            output.input.value.lint_ = input.value.lint_;
            break;
        case __uint__:
            output.input.value.uint_ = input.value.uint_;
            break;
        case __usint__:
            output.input.value.usint_ = input.value.usint_;
            break;
        case __ulint__:
            output.input.value.ulint_ = input.value.ulint_;
            break;
        case __float__:
            output.input.value.float_ = input.value.float_;
            break;
        case __double__:
            output.input.value.double_ = input.value.double_;
            break;
        case __louble__:
            output.input.value.louble_ = input.value.louble_;
            break;
        case __bool__:
            output.input.value.bool_ = input.value.bool_;
            break;
        case __tern__:
            output.input.value.tern_ = input.value.tern_;
            break;
        default:
            String error_message;
            error_message = "Cannot get " + print_datatype(get_datatype(), true);
            print_error(error_message);
        }
        return output;
    }

    virtual void print_input(bool add_endl = true, String operation = "printig")
    {
        if (is_initialised())
        {
            switch (input.datatype)
            {
            case __char__:
                cout << input.value.char_;
                break;
            case __byte__:
                cout << input.value.byte_;
                break;
            case __ubyte__:
                cout << input.value.ubyte_;
                break;
            case __int__:
                cout << input.value.int_;
                break;
            case __sint__:
                cout << input.value.sint_;
                break;
            case __lint__:
                cout << input.value.lint_;
                break;
            case __uint__:
                cout << input.value.uint_;
                break;
            case __usint__:
                cout << input.value.usint_;
                break;
            case __ulint__:
                cout << input.value.ulint_;
                break;
            case __float__:
                cout << input.value.float_;
                break;
            case __double__:
                cout << input.value.double_;
                break;
            case __louble__:
                cout << input.value.louble_;
                break;
            case __bool__:
                cout << input.value.bool_;
                break;
            case __tern__:
                cout << input.value.tern_;
                break;
            default:
                String error_message;
                error_message = "Cannot print " + print_datatype(get_datatype(), true);
                print_error(error_message);
            }
            if (add_endl)
            {
                cout << endl;
            }
        }
        else
            print_not_init_error(operation);
    }

    void replace_input(multitype new_input)
    {
        input.value = new_input.input.value;
        input.datatype = new_input.input.datatype;
        input.objectype = new_input.input.objectype;
        input.compatible_types = new_input.input.compatible_types;
        input.size_of_compat = new_input.input.size_of_compat;
        initialised = true;
    }
};

#endif