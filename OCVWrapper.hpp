#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

#define OCVWrapper_HPP

class OCVWrapper
{
private:
	cv::Mat img;
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
	void showImg(std::string windowName) const
	{
		cv::imshow(windowName, img);
	}
	void update(int wait) const
	{
		cv::waitKey(wait);
	}
	
};
