#define Point3_HPP

class Point3
{
	public:
		int x,y,z;
		Point3(int X = 0, int Y = 0, int Z = 0)
		{
			x = X;
			y = Y;
			z = Z;
		}
		Point3(const Point3 &v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
		}
		int magnitude()
		{
			return std::sqrt(x*x + y*y + z*z);
		}
		Point3 operator+(const Point3& v)
		{
			return Point3(this->x + v.x, this->y + v.y, this->z + v.z);
		}
		Point3 operator-(const Point3& v)
		{
			return Point3(this->x - v.x, this->y - v.y, this->z - v.z);
		}
		double operator*(const Point3& v)
		{
			return (this->x)*(v.x) + (this->y)*(v.y) + (this->z)*(v.z);
		}
};
