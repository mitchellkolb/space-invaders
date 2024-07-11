#ifndef POINT_INTERFACE_H
#define POINT_INTERFACE_H

class Point_interface
{
protected:
	int pts;
public:
	virtual void set_pts(int) = 0;
	virtual int get_pts(void) = 0;
	virtual void add_pt(void) = 0;
	virtual void pt_out(void) = 0;
};

#endif