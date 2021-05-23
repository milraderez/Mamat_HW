#include "string.h"
#include <iostream>
#include <cstring>
#include "ip.h"

#define IP 4
#define PORT 2
#define BYTE 8
#define SPACE ' '
#define STRING_END '\0'

//default constructor
String::String() {
	this->data = NULL;
	this->length = 0;
}

// copy constructor
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

// string constructor
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

//default destructor
String::~String() {
	if (this->data != NULL) {
		delete[] this->data;
	}
}

// = operator on reference
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

// = operator on string
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

// equal check on reference
bool String::equals(const String& rhs) const {
	if (rhs.length != this->length) {
		return false;
	}
	else if (strcmp(this->data, rhs.data) != 0) {
		return false;
	}
	return true;
}

// equal check on string
bool String::equals(const char* rhs) const {
	if (strlen(rhs) != this->length) {
		return false;
	}
	else if (strcmp(rhs, this->data) != 0) {
		return false;
	}
	return true;
}

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
		//for the last substring
		(*output)[current_subs] = String(&temp_str[subs_start]);
		delete[] temp_str;
		return;
}

int String::to_integer() const {
	int num = 0;
	size_t size = 0;
	String* sub_str;
	split(".", &sub_str, &size);
	for (unsigned int i = 0; i < size; i++) {
		sub_str[i] = sub_str[i].trim();
		int current_byte = atoi(sub_str[i].data);
		if (current_byte < 1 || current_byte > 255) {
			return 0;
		}
		else {
			num = num | ((INT_BITS - BYTE) << (i * BYTE));
		}
	}
	delete[] sub_str;
	return num;
}

String String::trim() const {
	int start = 0, end = this->length - 1;
	if (this->data == NULL) {
		return String();
	}
	else {
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
		else {
			int trimmed_length = end - start + 1;
			char new_str[trimmed_length];
			strncpy(new_str, &(this->data[start]), trimmed_length);
			new_str[trimmed_length - 1] = STRING_END;
			return String(new_str);
		}
	}
}