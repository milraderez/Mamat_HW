#ifndef IP_H
#define IP_H

#include "field.h"
#define MASK_DISECT 2
#define INT_BITS 32
#define INT_MAX_ADDRESS 0xFFFFFFFF

class Ip : public Field {
private:
	unsigned int smallest_address;
	unsigned int biggest_address;

public: 
	Ip(String pattern);
	~Ip();
	virtual bool set_value(String val);
	virtual bool match_value(String packet) const;
};

#endif