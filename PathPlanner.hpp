#include <cmath>

#ifndef OCVWrapper_HPP
#include "OCVWrapper.hpp"
#endif

#ifndef Point3_HPP
#include "Point3.hpp"
#endif

#ifndef Astar3D_HPP
#include "Astar3D.hpp"
#endif

#define PathPlanner_HPP

const int angleDim = 64;
float bHeight = 10;
float bWidth = 20;
const float scale = 1;

class PathPlanner
{
private:
	OCVWrapper *imgMap;
	cv::Point start, end;
	std::vector<OCVWrapper> cSpace;
	void createCSpace(float angle, std::vector< std::vector<cv::Point> > contours)
	{
		OCVWrapper cPlane(int(imgMap->getWidth()), int(imgMap->getHeight()), false);
		cPlane.drawContours<uchar>(contours, 255, CV_FILLED);
		std::vector< std::vector<cv::Point> > polygons;
		for(int j = 0; j < contours.size(); ++j)
		{
			
			for(int i = 0; i < contours[j].size();++i)
			{
				cv::vector<cv::Point> rotatedRect;
				cv::Point origin = contours[j][i];
				// Coordinates reflected about origin for the minkowski sum to give the 2D configurational space
				rotatedRect.clear();
				rotatedRect.push_back(origin);
				rotatedRect.push_back(origin + cv::Point(-bHeight*sin(angle), -bHeight*cos(angle)));
				rotatedRect.push_back(origin + cv::Point(-bHeight*sin(angle) + (-bWidth)*sin(angle + M_PI/2), -bHeight*cos(angle) + (-bWidth)*cos(angle + M_PI/2)));
				rotatedRect.push_back(origin + cv::Point(-bWidth*sin(angle + M_PI/2), -bWidth*cos(angle + M_PI/2)));

				polygons.push_back(rotatedRect);
			}
		}
		cPlane.drawPoly<uchar>(polygons, 255);
		cSpace.push_back(cPlane);
	}
	std::vector<Point3> beginAstar3D()
	{
		std::vector<Point3> path;
		/*std::vector<OCVWrapper> vSpace;
		for(int i = 0; i < angleDim; ++i)
			vSpace.push_back(OCVWrapper(int(cSpace[0].getWidth()), int(cSpace[0].getHeight()), false));*/
		std::priority_queue< Node, std::vector<Node> > open;
		Node *startNode = new Node(Point3(start.x,start.y,0));
		open.push(*startNode);
		finish = end;
		Astar3D(open, path, cSpace);
		for(int i = 0; i < path.size(); ++i)
		{
			path[i].x /= scale;
			path[i].y /= scale;
		}
		return path;
	}
public:
	PathPlanner(cv::Point s, cv::Point e, OCVWrapper *mapPtr)
	{
		imgMap = mapPtr;
		start = s;
		end = e;
	}
	std::vector<Point3> getPath()
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
		return beginAstar3D();
	}
};