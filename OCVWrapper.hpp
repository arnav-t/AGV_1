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
	OCVWrapper(int width, int height, bool color)
	{
		if(color)
			img = cv::Mat(height, width, CV_8UC3, cv::Scalar(0,0,0));
		else
			img = cv::Mat(height, width, CV_8UC1, cv::Scalar(0));
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
	void scaleImg(float scale)
	{
		cv::Size sz(img.cols*scale, img.rows*scale);
		cv::resize(img, img, sz);
	}
	void getContours(std::vector<cv::Vec4i> &hierarchy, std::vector< std::vector<cv::Point> > &contours)
	{
		findContours(img, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);
	}
	template <class T>
	void drawPoly(std::vector< std::vector<cv::Point> > polygons, T color)
	{
		cv::fillPoly(img, polygons, color);	
	}
	template <class T>
	void drawContours(std::vector<std::vector<cv::Point> > contours, T color, int lineType)
	{
		for(int i = 0; i < contours.size(); ++i)
			cv::drawContours(img, contours, i, color, lineType);	
	}
};
