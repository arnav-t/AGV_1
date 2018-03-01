#include <cmath>

#ifndef OCVWrapper_HPP
#include "OCVWrapper.hpp"
#endif

#ifndef Bitmap2D_HPP
#include "Bitmap2D.hpp"
#endif

#define PathPlanner_HPP

const int angleDim = 16;
float bHeight = 10;
float bWidth = 20;
const float scale = 0.2;

class PathPlanner
{
private:
	OCVWrapper *imgMap;
	cv::Point start, end;
	//std::vector<Bitmap2D> cSpace;
	void createCSpace(float angle, std::vector< std::vector<cv::Point> > contours)
	{
		OCVWrapper cPlane(int(imgMap->getWidth()), int(imgMap->getHeight()), false);
		cPlane.drawContours<int>(contours, 255, CV_FILLED);
		std::vector< std::vector<cv::Point> > polygons;
		for(int j = 0; j < contours.size(); ++j)
		{
			
			for(int i = 0; i < contours[j].size();++i)
			{
				cv::vector<cv::Point> rotatedRect;
				cv::Point origin = contours[j][i];
				// Coordinates reflected about origin because only then the minkowski sum would give a 2D configurational space
				rotatedRect.clear();
				rotatedRect.push_back(origin);
				rotatedRect.push_back(origin + cv::Point(-bHeight*sin(angle), -bHeight*cos(angle)));
				rotatedRect.push_back(origin + cv::Point(-bHeight*sin(angle) + (-bWidth)*sin(angle + M_PI/2), -bHeight*cos(angle) + (-bWidth)*cos(angle + M_PI/2)));
				rotatedRect.push_back(origin + cv::Point(-bWidth*sin(angle + M_PI/2), -bWidth*cos(angle + M_PI/2)));

				polygons.push_back(rotatedRect);
			}
		}
		cPlane.drawPoly<int>(polygons, 255);
		cPlane.showImg("ConfigSpace");
		cPlane.update(0);
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
		start *= scale;
		end *= scale;
		bWidth *= scale;
		bHeight *= scale;
		std::vector<cv::Vec4i> hierarchy;
		std::vector< std::vector< cv::Point> > contours;
		imgMap->getContours(hierarchy, contours);
		for(int i = 0; i < angleDim; ++i)
			createCSpace((2*M_PI/angleDim)*i, contours);
	}
};