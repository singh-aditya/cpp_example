#include <iostream>
#include "print/print_result.h"

namespace my_print {
	void print_result( std::string result_type, float result_value){
		std::cout << result_type.c_str() << " result:\t" << result_value << "\n";
	}
}
