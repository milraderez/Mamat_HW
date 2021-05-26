#include "ip.h"

/* @brief default constructor setting a value to Field's private variable 
          "pattern"
   @param pattern is a the string we want to start the object with.
   @note inherits Field(pattern) for easy access to pattern through Ip.
*/
Ip::Ip(String pattern): Field(pattern) {
}

/*
  @brief sets ip limits for eligible packet
  @param val is the ip rule to calculate the limits
*/
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
		smallest_address = biggest_address = ip;
	}
	else {
		// mask_size of 0's and 32-mask_size 1's
		bitmask = (((unsigned int)1 << (INT_BITS - mask_size)) - 1);
		smallest_address = (~bitmask) & ip;
		biggest_address = bitmask | ip;
}
    delete[] sub_string;
	return true;
}
/*
   @brief checks if the packet's ip is inside the rule's limits
   @param packet is the packet's ip.
*/
bool Ip::match_value(String packet) const {
	unsigned int value = packet.trim().to_integer();
	if (value <= biggest_address && value >= smallest_address) {
		return true;
	}
	return false;
}
