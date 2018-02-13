#include <iostream>
#include <string>

#ifndef OCVWrapper_HPP
#include "OCVWrapper.hpp"
#endif

using namespace std;
using namespace cv;

int main()
{
	OCVWrapper lena("lena.jpg",1);
	cout << (int)lena.getPixel<Vec3b>(Point(0,0))[0] << endl;
	lena.showImg("Full image");
	lena.update(0);
	return 0;
}
