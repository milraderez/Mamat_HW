#ifndef PORT_H
#define PORT_H

#include "field.h"

#define BIGGEST 1
#define SMALLEST 0
#define PORT_DISECT 2
#define PORT_FIELDS 2


class Port : public Field {
private:
	int port_limits[PORT_FIELDS];

public:
	/*
      @brief default constructor, takes pattern and insert to Field's 
             private variable "pattern"
	*/
	Port(String pattern);
	/*
      @brief checks for a match in port address between packet and rule's limits.
      @return true iff match.
	*/

	virtual bool match_value(String packet) const;
	/*
	  @brief takes a rule and decides on port limits.
	  @note returns true upon success, false for error
	*/
	virtual bool set_value(String val);
};

#endif
