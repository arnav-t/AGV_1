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


using namespace std;
using namespace cv;

int main()
{
	OCVWrapper img(IMG_PATH, 0);
	Point start, end;
	Prelims(IMG_PATH, &img, start, end);
	PathPlanner pp(start, end, &img);
	pp.getPath();
	return 0;
}
