#ifndef OCVWrapper_HPP
#include "OCVWrapper.hpp"
#endif

#define Prelims_HPP

const int thres = 200;
const int thres2 = 220;

void Prelims(std::string path, OCVWrapper *dest, cv::Point &start, cv::Point &end)
{
	OCVWrapper src(path, 1);
	dest->loadImg(path, 0);
	dest->clear();
	for(int y = 0; y < src.getHeight(); ++y)
	{
		for(int x = 0; x < src.getWidth(); ++x)
		{
			cv::Vec3b color = src.getPixel<cv::Vec3b>(cv::Point(x,y));
			bool redFlag = false; 
			bool greenFlag = false;
			// white (obstacles)
			if(color[0] > thres && color[1] > thres && color[2] > thres)
				dest->setPixel<uchar>(cv::Point(x,y), 255);
			else
			{
				// red (finish)
				if(!redFlag)
				{
					if(color[2] > thres2)
					{
						end = cv::Point(x,y);
						redFlag = true;  
					}
				}
				// green (start)
				if(!greenFlag)
				{
					if(color[1] > thres2)
					{
						start = cv::Point(x,y);
						greenFlag = true;  
					}
				}
			}
		}
	}
}
