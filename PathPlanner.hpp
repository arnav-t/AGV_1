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
const float scale = 0.2;

class PathPlanner
{
private:
	OCVWrapper *imgMap;
	cv::Point start, end;
	//std::vector<Bitmap2D> cSpace;
	void createCSpace(float angle, std::vector< std::vector<cv::Point> > contours)
	{
		for(int j = 0; j < contours.size(); ++j)
		{
			
			for(int i = 0; i < contours[i].size();++i)
			{

			}
		}
	}
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
		std::vector<cv::Vec4i> hierarchy;
		std::vector< std::vector< cv::Point> > contours;
		imgMap->getContours(hierarchy, contours);
		for(int i = 0; i < angleDim; ++i)
			createCSpace((2*M_PI/angleDim)*i, contours);
	}
};