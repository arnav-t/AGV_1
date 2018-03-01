#include <cmath>

#ifndef OCVWrapper_HPP
#include "OCVWrapper.hpp"
#endif

#ifndef Bitmap2D_HPP
#include "Bitmap2D.hpp"
#endif

#define PathPlanner_HPP

const int angleDim = 16;

class PathPlanner
{
private:
	OCVWrapper ogImg;
	Bitmap2D oMap, cSpace[angleDim];
};