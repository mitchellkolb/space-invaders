#ifndef POINTS_H
#define POINTS_H

#include "point_interface.h"
#include <iostream>

class Points : public Point_interface
{
public:
	void set_pts(int pts);
	int get_pts(void);
	void add_pt(void);
	void pt_out(void);
};

#endif