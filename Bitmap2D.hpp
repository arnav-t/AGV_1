#define Bitmap2D_HPP

class Bitmap2D
{
private:
	int height, width;
	bool map[height][width];
public:
	Bitmap2D(int width, int height)
	{
		for(int y = 0;y < height; ++y)
			for(int x = 0;x < width; ++x)
				map[y][x] = false;
	}
	Bitmap2D(const Bitmap2D bMapObj)
	{
		
	}
};