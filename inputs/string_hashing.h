/* this class intends to be fully compatible with string and char*. the idea is to add
switch case support to string objects by providing an int unique to each string known as a hash. */

#pragma once
#include <iostream>
#include "definitions.h"

#ifndef strhing_hashing_h
#define string_hashing_h

// static const unsigned long int max_hstring_lenght;
class hstring
{
private:
    int max_len = 19033;
    bool recalc_max_len = false, muting_errors = false;
    error__ error_message;

    // this struct contains the string and its unique hash.
    struct hashed_string
    {
        std::string my_string;
        unsigned long int my_hash;
    };

    // struct carried by the hstring object.
    hashed_string my_hashed_string;

    // short list of 168 prime numbers to assing to different chars and to the position of these chars in the string.
    int primes[168] =
        {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37,
         41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103,
         107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
         179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241,
         251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317,
         331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401,
         409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479,
         487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571,
         577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647,
         653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739,
         743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827,
         829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919,
         929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997};

    /* this function turns a char into a prime number. 168 numbers should be enough for all
       chars used in english, but in case extended chars are used, the modulo (%) 168 is used
       to cycle through the list if a char is out of range. */
    int prime_char(char input)
    {
        return primes[((int)input - (int)' ') % 168];
    }

    /* this function turns the position of a char in a string into a prime number. similarly as before,
       similar as in the prime_char function, if the position of the char is above 168, the function will
       cycle through the members of the primes list. */
    int position_to_ptime(int position)
    {
        return primes[position % 168];
    }

    // this function returns an integer that is unique to every string.
    int hash_string()
    {
        // n is the lenght of the string. buffer contains the hash during the hashing loop.
        unsigned int n = my_hashed_string.my_string.length(), buffer = 1;

        if (!(n > max_len))
        {
            char char_array[n + 1]; // char_array will be used to store the literal string into an array of chars for checking.

            strcpy(char_array, my_hashed_string.my_string.c_str()); // copying literal string into char_array.

            for (int i = 0; i < n; i++) // this for loop gets prime numbers from the chars in the array and their position
            {
                buffer += (prime_char(char_array[i]) * position_to_ptime(i)); // it adds the primes and multiplies them.
            }
            // buffer /= n; // dividing the buffer by the lenght of the string. this step is not mandatory but helps to keep hashes small.
        }
        return buffer;
    }

    // this function stores the passed string during declaration in the struct for hash string and generates the hash, storing it too.
    void initialise(const char *input_string, bool recalculate_max_len, int new_max_len, bool mute_errors = false)
    {
        recalc_max_len = recalculate_max_len;
        muting_errors = mute_errors;

        my_hashed_string.my_string = input_string;
        if (new_max_len == 0)
            max_len = (recalc_max_len) ? get_max_hstring_len() : max_len;
        else
            max_len = new_max_len;
        my_hashed_string.my_hash = hash_string();
        
        if (my_hashed_string.my_hash == 1 && !muting_errors)
        {
            error_message = "Error while hashing string ending in: ";
            for (int i = my_hashed_string.my_string.length() - 10; i < my_hashed_string.my_string.length() + 1; i++)
                error_message += my_hashed_string.my_string.c_str()[i];
            error_message += ". String is too long to hash";
            error_message.print_error();
        }
    }

    hashed_string get_hashed_string() // returns the struct containing the string and its hash
    {
        return my_hashed_string;
    }

    int get_max_hstring_len()
    {
        hstring my_string = "~";
        int len = 1;
        unsigned long int test_old = my_string.get_hash();
        unsigned long int test_new = test_old;
        while (test_new >= test_old)
        {
            // cout << test_new << "     " << len << endl;
            std::string new_string = my_string.get_string() + "~";
            len++;
            my_string = new_string;
            test_new = my_string.get_hash();
            test_old = (test_new > test_old) ? test_new : test_old;
        }
        return len;
    }

public:
    // constructors for different types of declarations

    hstring(const char *input_string, bool recalculate_max_len = false, int new_max_len = 0, bool mute_errors = false) // for char arrays
    {
        initialise(input_string, recalculate_max_len, new_max_len, mute_errors);
    }

    hstring(std::string input_string, bool recalculate_max_len = false, int new_max_len = 0, bool mute_errors = false) // for string literals
    {
        initialise(input_string.c_str(), recalculate_max_len, new_max_len, mute_errors);
    }

    hstring(bool recalculate_max_len = false, int new_max_len = 0, bool mute_errors = false)
    {
        initialise("", recalculate_max_len, new_max_len);
    }

    std::string get_string() // returns the string of the object
    {
        return my_hashed_string.my_string;
    }

    unsigned long int get_hash() // returns the hash for the object's string
    {
        return my_hashed_string.my_hash;
    }

    int get_max_len()
    {
        return max_len;
    }

    // operators for the class
    // comparators

    bool operator==(hstring other_string) // comparator with another hstring
    {
        return (my_hashed_string.my_hash == other_string.get_hashed_string().my_hash) ? true : false;
    }

    bool operator==(std::string other_string) // comparator with a string literal
    {
        return (my_hashed_string.my_string == other_string) ? true : false;
    }

    bool operator==(const char *other_string) // comparator with a char array
    {
        return (my_hashed_string.my_string.c_str() == other_string) ? true : false;
    }

    // assigners

    void operator=(hstring other_string) // from another hstring
    {
        initialise(other_string.get_string().c_str(), recalc_max_len, max_len, muting_errors);
    }

    void operator=(std::string other_string) // from another string literal
    {
        initialise(other_string.c_str(), recalc_max_len, max_len, muting_errors);
    }

    void operator=(const char *other_string) // from a string array
    {
        initialise(other_string, recalc_max_len, max_len, muting_errors);
    }
};

// operator for ostream to return the hashed string as a string
ostream &operator<<(ostream &out, hstring &s)
{
    out << s.get_string();
    return out;
}

// casting the hstring as a string
std::string cstring(hstring &caster)
{
    return caster.get_string();
}

// casting the hstring as a const char*
const char *cchar(hstring &caster)
{
    return caster.get_string().c_str();
}

// casting the hstring as an int*
unsigned long int cint(hstring &caster)
{
    return caster.get_hash();
}

#endif