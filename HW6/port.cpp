#include "port.h"

Port::Port(String pattern) : Field(pattern) {
}

Port::~Port() {
}

bool Port::match_value(String packet) const {
	int value = packet.trim().to_integer();
	if (value <= port_limits[BIGGEST] || value >= port_limits[SMALLEST]) {
		return true;
	}
	return false;
}

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