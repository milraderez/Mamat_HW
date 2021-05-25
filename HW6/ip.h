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
	/*
      @brief default constructor, takes pattern and insert to Field's 
             private variable "pattern"
	*/
	Ip(String pattern);
	/*
	  @brief default constructor
	*/
	~Ip();
	/*
	  @brief takes a rule and decides on ip limits based on ip and mask.
	  @note returns true upon success, false for error
	*/
	virtual bool set_value(String val);
	/*
      @brief checks for a match in ip address between packet and rule's limits.
      @return true iff match.
	*/
	virtual bool match_value(String packet) const;
};

#endif