#include <iostream>
#include <string>

#ifndef OCVWrapper_HPP
#include "OCVWrapper.hpp"
#endif

#ifndef PathPlanner_HPP
#include "PathPlanner.hpp"
#endif

#ifndef Prelims_HPP
#include "Prelims.hpp"
#endif

#define IMG_PATH "a.png"

const int everyNth = 15;

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
	if(argc == 3)
	{
		bWidth = stoi(argv[1]);
		bHeight = stoi(argv[2]);
	}
	OCVWrapper img(IMG_PATH, 0);
	Point start, end;
	Prelims(IMG_PATH, &img, start, end);
	PathPlanner pp(start, end, &img);
	vector<Point3> path = pp.getPath();
	OCVWrapper imgFinal(IMG_PATH, 1);
	OCVWrapper imgDisp(IMG_PATH, 1);
	vector< vector<Point> > polygons;
	vector< vector<Point> > currPolygon;
	bHeight /= scale;
	bWidth /= scale;
	for(int i = path.size() - 1; i >= 0; i -= 1)
	{
		imgDisp.loadImg(IMG_PATH, 1);
		currPolygon.clear();
		Point origin = Point(path[i].x, path[i].y);
		float angle = path[i].z*2*M_PI/angleDim;
		vector<Point> rotatedRect;
		rotatedRect.clear();
		rotatedRect.push_back(origin);
		rotatedRect.push_back(origin + Point(bHeight*sin(angle), bHeight*cos(angle)));
		rotatedRect.push_back(origin + Point(bHeight*sin(angle) + (bWidth)*sin(angle + M_PI/2), bHeight*cos(angle) + (bWidth)*cos(angle + M_PI/2)));
		rotatedRect.push_back(origin + Point(bWidth*sin(angle + M_PI/2), bWidth*cos(angle + M_PI/2)));
		if(i % everyNth == 0)
			polygons.push_back(rotatedRect);
		currPolygon.push_back(rotatedRect);
		imgDisp.drawPolyLines<Scalar>(currPolygon, Scalar(255,0,0));
		imgDisp.showImg("Final Path Animation");
		imgDisp.update(8);
	}
	imgFinal.drawPolyLines<Scalar>(polygons, Scalar(255,0,0));
	imgFinal.showImg("Final Path");
	imgFinal.update(0);
	return 0;
}
