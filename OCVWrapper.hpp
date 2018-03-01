#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include <vector>

#define OCVWrapper_HPP

class OCVWrapper
{
private:
	cv::Mat img;
	bool inBounds(cv::Point p) const
	{
		if(p.y >= img.rows || p.y < 0)
			return false;
		else if(p.x >= img.cols || p.x < 0)
			return false;
		else 
			return true;
	}
public:
	OCVWrapper(std::string path, bool color)
	{
		img = cv::imread(path, color);
		if(!img.rows && !img.cols)
		{
			std::cout << "Image cannot be loaded, exiting...\n";
			exit(1);
		}
	}
	~OCVWrapper()
	{
		img.release();
	}
	void loadImg(std::string path, bool color)
	{
		img = cv::imread(path, color);
		if(!img.rows && !img.cols)
		{
			std::cout << "Image cannot be loaded, exiting...\n";
			exit(1);
		}
	}
	void showImg(std::string windowName) const
	{
		cv::imshow(windowName, img);
	}
	void update(int wait) const
	{
		cv::waitKey(wait);
	}
	void clear()
	{
		if(img.channels() == 1)
			img = cv::Scalar(0);
		else if(img.channels() == 3)
			img = cv::Scalar(0,0,0);
	}
	template <class T>
	T getPixel(cv::Point p) const
	{
		if(!inBounds(p))
			return -1;
		else if(img.channels() == 1)
			return img.at<uchar>(p.y, p.x);
		else if(img.channels() == 3)
			return img.at<cv::Vec3b>(p.y, p.x);
	}
	template <class T>
	void setPixel(cv::Point p, T pixelValue)
	{
		if(!inBounds(p))
			return;
		else if(img.channels() == 1)
			img.at<uchar>(p.y, p.x) = pixelValue;
		else if(img.channels() == 3)
			img.at<cv::Vec3b>(p.y, p.x) = pixelValue;
	}
	int getWidth() const
	{
		return img.cols;
	}
	int getHeight() const
	{
		return img.rows;
	}
};
