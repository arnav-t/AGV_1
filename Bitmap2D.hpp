#define Bitmap2D_HPP

class Bitmap2D
{
private:
	int height, width;
	std::vector< std::vector<bool> > map2d;
public:
	Bitmap2D(int width, int height)
	{
		map2d.resize(height);
		for(int y = 0;y < height; ++y)
		{
			map2d[y].resize(width);
			for(int x = 0;x < width; ++x)
				map2d[y][x] = false;
		}
	}
	void reinit(int w, int h)
	{
		width = w;
		height = h;
		map2d.resize(height);
		for(int y = 0;y < height; ++y)
		{
			map2d[y].resize(width);
			for(int x = 0;x < width; ++x)
				map2d[y][x] = false;
		}
	}
	bool get(int x, int y)
	{
		return map2d[y][x];
	}
	void set(int x, int y, bool val)
	{
		map2d[y][x] = val;
	}
};