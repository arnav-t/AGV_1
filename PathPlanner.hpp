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
const float scale = 0.125;

class PathPlanner
{
private:
	OCVWrapper *imgMap;
	cv::Point start, end;
	//std::vector<Bitmap2D> cSpace;


public:
	PathPlanner(cv::Point s, cv::Point e, OCVWrapper *mapPtr)
	{
		imgMap = mapPtr;
		start = s;
		end = e;
	}
	void getPath()
	{
		imgMap->scaleImg(scale);
		imgMap->showImg("Scaled Map");
		imgMap->update(0);
		start *= scale;
		end *= scale;
		
	}
};