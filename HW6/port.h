#ifndef PORT_H
#define PORT_H

#include "field.h"

#define BIGGEST 1
#define SMALLEST 0
#define PORT_DISECT 2


class Port : public Field {
private:
	int port_limits[2];

public:
	Port(String pattern);
	~Port();
	virtual bool match_value(String packet) const;
	virtual bool set_value(String val);
};

#endif