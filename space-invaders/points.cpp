#include "points.h"

void Points::set_pts(int pts)
{
	Points::pts = pts;
}

int Points::get_pts(void)
{
	return pts;
}

void Points::add_pt(void)
{
	pts++;
}

void Points::pt_out(void)
{
	std::cout << pts << std::endl;
}
