#include "input.h"
#include "string.h"
#include "port.h"
#include "ip.h"
#include <iostream>
#include <cstring>

#define FAIL -1
#define RULE_NAME 0
#define RULE_VALUE 1
#define RULE_FIELDS 2

/*
  @brief receives a rule and packet file and return packets matching the filter.
*/
int main(int argc, char **argv) {
	String filter[RULE_FIELDS];
	String *sub_string;
	size_t size = 0;
	String empty_string("");
	Field *field = NULL;
	bool found = false;

	if (check_args(argc, argv) != 0) {
		return FAIL;
	}

	String rule(argv[1]);
	rule.split("=,", &sub_string, &size);
	for (int i = 0; i < (int)size; i++) {
		if (empty_string.equals(sub_string[i]) == false) {
			if (found == false) {
				filter[RULE_NAME] = sub_string[i].trim();
				filter[RULE_NAME] = filter[RULE_NAME].trim();
				found = true;
			}
			else {
				filter[RULE_VALUE] = sub_string[i].trim();
				filter[RULE_VALUE] = filter[RULE_VALUE].trim();
			}
		}
	}
	if (filter[RULE_NAME].equals(String("dst-ip")) ||
		filter[RULE_NAME].equals(String("src-ip"))) {
		  field = new Ip(filter[RULE_NAME]);
	}
	if (filter[RULE_NAME].equals(String("dst-port")) ||
		filter[RULE_NAME].equals(String("src-port"))) {
		  field = new Port(filter[RULE_NAME]);
	}
    
	field->set_value(filter[RULE_VALUE]);
	parse_input(*field);
	delete field;
	delete[] sub_string;

}