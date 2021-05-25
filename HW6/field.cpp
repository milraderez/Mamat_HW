#include "field.h"
#include <iostream>
#include <cstring>

// constructor
Field::Field(String pattern) {
	this->pattern = pattern;
}

//destructor
Field::~Field() {
}

bool Field::match(String packet) {
	size_t size = 0;
	String* sub_string;
	bool field_match = false;
	packet.split(",=", &sub_string, &size);
	if(size == 0){
		return false;
	}
	for (int i = 0; i < int(size); i+=2) {
		if (pattern.equals(sub_string[i].trim()) == true) {
			field_match = match_value(sub_string[i + 1]);
			break;
		}
	}
	delete[] sub_string;
	return field_match;
}