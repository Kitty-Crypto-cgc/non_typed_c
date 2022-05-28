#include "definitions.h"

#ifndef basic_h
#define basic_h

class basic_input : public multitype
{
protected:
    __object__ input;

public:
    basic_input()
    {
        initialised = false;
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

    Lint cast_to_int(basic_input *caster)
    {
        Lint output = 0;
        switch (caster->input.datatype)
        {
            case __char__:
                output = (Lint)caster->input.value.char_;
                break;
            case __byte__:
                output = (Lint)caster->input.value.byte_;
                break;
            case __ubyte__:
                output = (Lint)caster->input.value.ubyte_;
                break;
            case __int__:
                output = caster->input.value.int_;
                break;
            case __sint__:
                output = (Lint)caster->input.value.sint_;
                break;
            case __lint__:
                output = (Lint)caster->input.value.lint_;
                break;
            case __uint__:
                output = (Lint)caster->input.value.uint_;
                break;
            case __usint__:
                output = (Lint)caster->input.value.usint_;
                break;
            case __ulint__:
                output = (Lint)caster->input.value.ulint_;
                break;
            case __float__:
                output = round((Lint)caster->input.value.float_);
                break;
            case __double__:
                output = round((Lint)caster->input.value.double_);
                break;
            case __louble__:
                output = round((Lint)caster->input.value.louble_);
                break;
            case __bool__:
                if (caster->input.value.bool_ == true)
                    output = 1;
                else
                    output = 0;
                break;
            case __tern__:
                output = (Lint)caster->input.value.tern_;
                break;
            default:
                String error_message;
                error_message = "Cannot typecast " + print_datatype(caster->get_datatype(), true) + " into int"; 
                print_error(error_message);
        }
        return output;
    }

    Louble cast_to_double(basic_input *caster)
    {
        Louble output = 0;
        switch (caster->input.datatype)
        {
            case __char__:
                output = (Louble)caster->input.value.char_;
                break;
            case __byte__:
                output = (Louble)caster->input.value.byte_;
                break;
            case __ubyte__:
                output = (Louble)caster->input.value.ubyte_;
                break;
            case __int__:
                output = (Louble)caster->input.value.int_;
                break;
            case __sint__:
                output = (Louble)caster->input.value.sint_;
                break;
            case __lint__:
                output = (Louble)caster->input.value.lint_;
                break;
            case __uint__:
                output = (Louble)caster->input.value.uint_;
                break;
            case __usint__:
                output = (Louble)caster->input.value.usint_;
                break;
            case __ulint__:
                output = (Louble)caster->input.value.ulint_;
                break;
            case __float__:
                output = (Louble)caster->input.value.float_;
                break;
            case __double__:
                output = (Louble)caster->input.value.double_;
                break;
            case __louble__:
                output = caster->input.value.louble_;
                break;
            case __bool__:
                if (caster->input.value.bool_ == true)
                    output = 1;
                else
                    output = 0;
                break;
            case __tern__:
                output = (Louble)caster->input.value.tern_;
                break;
            default:
                String error_message;
                error_message = "Cannot typecast " + print_datatype(caster->get_datatype(), true) + " into double"; 
                print_error(error_message);
        }
        return output;
    }

};

#endif