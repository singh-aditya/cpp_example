#include <iostream>

#include "math/addition.h"
#include "math/division.h"
#include "print/print_result.h"

int main(){

float first_no, second_no, result_add, result_div;

std::cout<< "Enter first number:\t";
std::cin>> first_no;
std::cout<< "Enter second number:\t";
std::cin>> second_no;

result_add = my_math::addition(first_no , second_no);
result_div = my_math::division(first_no , second_no);

my_print::print_result("Addition", result_add);
my_print::print_result("Division", result_div);

return 0;
}
