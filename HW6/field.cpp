#include "field.h"
#include <iostream>
#include <cstring>

/* @brief default constructor setting a value to Field's private variable 
          "pattern"
   @param pattern is a the string we want to start the object with.
*/
Field::Field(String pattern) {
	this->pattern = pattern;
}

/*
  @brief compares between packet and rule to find a match.
  @note after split, the order in sub_string becomes name-value-name-value,and
        therefore we scan for name in i+=2 jumps.
  @note only when name matches, we check for value match. 
*/
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
