#include <iostream>

#include "c_container/cc.h"


int main()
{
	cc_code_template_t code_template;
	code_template.field = cc_code_template_macro;
	cc_code_template_function(&code_template);
	return 0;
}
