#include "ip.h"

//constructor + access to pattern
Ip::Ip(String pattern): Field(pattern) {
}

Ip::~Ip() {
}

bool Ip::set_value(String val) {
	String* sub_string;
	size_t size = 0;
	val.split("/", &sub_string, &size);
	if (size != MASK_DISECT) {
		delete[] sub_string;
		return false;
	}
	int ip = sub_string[0].trim().to_integer();
	int mask_size = sub_string[1].trim().to_integer();
	if (mask_size < 0 || mask_size > INT_BITS)
		return false;
	unsigned int bitmask;
	if (mask_size == INT_BITS) {
		bitmask = INT_MAX_ADDRESS;
	}
	else {
		// mask_size of 0's and 32-mask_size 1's
		bitmask = (((unsigned int)1 << (INT_BITS - mask_size)) - 1);
	}
	smallest_address = (~bitmask) & ip;
	biggest_address = bitmask | ip;
    delete[] sub_string;
	return true;
}

bool Ip::match_value(String packet) const {
	unsigned int value = packet.trim().to_integer();
	if (value < biggest_address && value > smallest_address) {
		return true;
	}
	return false;
}