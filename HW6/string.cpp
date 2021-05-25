#include "string.h"
#include <iostream>
#include <cstring>
#include "ip.h"

#define IP 4
#define PORT 2
#define BYTE 8
#define SPACE ' '
#define STRING_END '\0'
#define MAX_BYTES_MOVE 3
#define MAX_BYTE_SIZE 256
#define MIN_BYTE_SIZE 0
#define IP_SIZE 4

/*
   @brief default constructor, taking no params
*/
String::String() {
	this->data = NULL;
	this->length = 0;
}

/* 
   @brief copy constructor by reference
*/
String::String(const String &str) {
	if (str.length == 0) {
		this->data = NULL;
	}
	else {
		this->length = str.length;
		this->data = new char[str.length + 1];
		strncpy(this->data, str.data, str.length + 1);
	}
}

/*
   @brief copy constructor by string
*/
String::String(const char* str) {
	if (str == NULL) {
		this->data = NULL;
		this->length = 0;
	}
	else {
		this->length = strlen(str);
		if (this->length == 0) {
			this->data = NULL;
		}
		else {
			this->data = new char[this->length + 1];
			strncpy(this->data, str, this->length + 1);
		}
	}
}

/*
   @brief default destructor, taking no params
*/  
String::~String() {
	if (this->data != NULL) {
		delete[] this->data;
	}
}

/*
    @brief = operator by reference
*/    
String& String::operator=(const String &rhs) {
	if (this == &rhs) {
		return *this;
	}
	if (this->data != NULL) {
		delete[] this->data;
	 }
	this->length = rhs.length;
	this->data = new char[rhs.length + 1];
	strncpy(this->data, rhs.data, rhs.length);
	return *this;
}

/*
    @brief = operator by string
*/ 
String& String::operator=(const char* str) {
	if (this->data != NULL) {
		delete[] this->data;
	}
	if (str == NULL) {
		this->data = NULL;
		this->length = 0;
		return *this;
	}
	else {
		this->length = strlen(str);
		if (this->length == 0) {
			this->data = NULL;
		}
		else {
			this->data = new char[this->length + 1];
			strncpy(this->data, str, this->length + 1);
		}
	}
	return *this;
}

/* 
   @brief equal check on reference
*/   
bool String::equals(const String& rhs) const {
	if (rhs.length != this->length) {
		return false;
	}
	else if (strcmp(this->data, rhs.data) != 0) {
		return false;
	}
	return true;
}

/* 
   @brief equal check on string
*/ 
bool String::equals(const char* rhs) const {
	if (strlen(rhs) != this->length) {
		return false;
	}
	else if (strcmp(rhs, this->data) != 0) {
		return false;
	}
	return true;
}

/*
   @brief splits the string by delimiters,returns separated value to output.
   @note scans for number of delimiters, and then rerun and set '/0' for each
   		 delimiter, and sends the new word to output.
   @note last send to output outside the loop meant for the last substring.
*/
void String::split(const char* delimiters, String** output, size_t* size) const
{
	int deli_count = 0, subs_start = 0;
	unsigned int deli_types_count = 0,current_subs = 0;
	if (size == NULL) {
		return;
	}
	*size = 0;
	if (delimiters == NULL || this->data == NULL) {
		return;
	}
	deli_types_count = strlen(delimiters);
	for (unsigned int i = 0; i < this->length; i++) {
		for (unsigned int deli = 0; deli < deli_types_count; deli++) {
			if (this->data[i] == delimiters[deli]) {
				deli_count++;
			}
		}
	}
	*size = deli_count + 1;
	if (output == NULL) {
		return;
	}
    *output = new String[deli_count + 1];
    char* temp_str = new char[this->length + 1];
	strncpy(temp_str, this->data, this->length + 1);
	for (unsigned int i = 0; i < this->length; i++) {
		for (unsigned int deli = 0; deli < deli_types_count; deli++) {
			if (temp_str[i] == delimiters[deli]) {
				temp_str[i] = STRING_END;
				(*output)[current_subs] = String(&temp_str[subs_start]);
				subs_start = i + 1;
				current_subs++;
			}
		  }
     	}
		(*output)[current_subs] = String(&temp_str[subs_start]);
		delete[] temp_str;
		return;
}

/*
   @brief transforms string to int
*/
int String::to_integer() const {
	int num = 0;
	size_t size = 0;
	String* sub_str;
	split(".", &sub_str, &size);
	if(size == IP_SIZE){
		for (unsigned int i = 0; i < size; i++) {
			int current_byte = atoi(sub_str[i].trim().data);
			if (current_byte < MIN_BYTE_SIZE || current_byte > MAX_BYTE_SIZE) {
				return 0;
			}
			else {
			 num = num | current_byte << ((MAX_BYTES_MOVE - i) * BYTE);
			}
		}
	}
	else{
		num = atoi(sub_str[0].trim().data);
	}
	delete[] sub_str;
	return num;
}

/*
   @brief returns new string without spaces
*/
String String::trim() const {
	int start = 0, end = (this->length - 1);
	if (this->data == NULL) {
		return String();
	}

	while (this->data[start] == SPACE) {
		start++;
	}
	while (start != end && this->data[end] == SPACE) {
		end--;
	}

	end++;

	if (start >= end) {
		return String();
	}

	int trimmed_length = (end - start);
	char new_str[trimmed_length + 1];
	strncpy(new_str, &(this->data[start]), trimmed_length);
	new_str[trimmed_length] = STRING_END;

	return String(new_str);
}
