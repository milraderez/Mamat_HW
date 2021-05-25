#include "port.h"

/* @brief default constructor setting a value to Field's private variable 
          "pattern"
   @param pattern is a the string we want to start the object with.
   @note inherits Field(pattern) for easy access to pattern through Port.
*/
Port::Port(String pattern) : Field(pattern) {
}

/*
  @brief default destructor, taking no params
*/
Port::~Port() {
}

/*
   @brief checks if the packet's port is inside the rule's limits
   @param packet is the packet's port.
*/
bool Port::match_value(String packet) const {
	int value = packet.trim().to_integer();
	if (value <= port_limits[BIGGEST] || value >= port_limits[SMALLEST]) {
		return true;
	}
	return false;
}


/*
  @brief sets port limits for eligible packet
  @param val is the port rule to calculate the limits
*/
bool Port::set_value(String val) {
	String* sub_string;
	size_t size = 0;
	val.split("-", &sub_string, &size);
	if (size != PORT_DISECT) {
		delete[] sub_string;
		return false;
	}
		port_limits[BIGGEST] = sub_string[1].trim().to_integer();
	    port_limits[SMALLEST]= sub_string[0].trim().to_integer();
		delete[] sub_string;
		if (port_limits[SMALLEST] > port_limits[BIGGEST]) {
			return false;
		}
		return true;
}