#include <cmath>

#ifndef OCVWrapper_HPP
#include "OCVWrapper.hpp"
#endif

#ifndef Bitmap2D_HPP
#include "Bitmap2D.hpp"
#endif

#define PathPlanner_HPP

const int angleDim = 16;
const int bHeight = 10;
const int bWidth = 20;

class PathPlanner
{
private:
	OCVWrapper *imgMap;
	cv::Point start, end;
	//Bitmap2D cSpace[angleDim];
public:
	PathPlanner(cv::Point s, cv::Point e, OCVWrapper *mapPtr)
	{
		imgMap = mapPtr;
		start = s;
		end = e;
	}
};