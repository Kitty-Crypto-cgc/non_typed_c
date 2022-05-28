#include "inputs.h"
#include "string_hashing.h"

int main()
{
   hstring my_string("~");
   unsigned long int len = 1;
   unsigned long int test_old = cint(my_string);
   unsigned long int test_new = test_old;
   for (int i = 1; i < my_string.get_max_len(); i++)
   {
      //cout << test_new << "     " << len << endl;
      std::string new_string = cstring(my_string) + "~";
      len++;
      my_string = new_string;
      test_new = cint(my_string);
      test_old = (test_new > test_old) ? test_new : test_old;
   }

   std::string new_string = cstring(my_string) + "zaasdasd";
   my_string = new_string;

   return 0;
}