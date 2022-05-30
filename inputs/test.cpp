#include "var.h"
#include "string_hashing.h"

int main()
{

   var a = 4;

   var b = 4;

   var c = (a + b);

   c.print_value();
   c.print_datatype();
   return 0;
}