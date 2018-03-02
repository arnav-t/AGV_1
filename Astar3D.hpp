#include <queue>

#define Astar3D_HPP

const int greed = 1;
cv::Point finish;

class Node
{
	private:
		Point3 location;
		Node *parent;
		int weight;
	public:
		Node(Point3 l = Point3(0,0,0), Node *p = NULL)
		{
			location = l;
			weight = 0;
			setParent(p);
		}
		int getHeuristicWeight() const
		{
			return greed*(abs(finish.x - location.x) + abs(finish.y - location.y)) + weight;
		}
		Point3 getLocation() const
		{
			return location;
		}
		int getWeight() const
		{
			return weight;
		}
		void setParent(Node *p)
		{
			parent = p;
			if(parent == NULL)
				weight = 0;
			else if((parent->getLocation().x - location.x) && (parent->getLocation().y - location.y))
				weight = 14 + parent->getWeight();
			else
				weight = 10 + parent->getWeight();
		}
		void addToPath(std::vector<Point3> &p)
		{
			p.push_back(location); 
			if(parent != NULL)
			{
				parent->addToPath(p);
			}
		}
};

inline bool operator<(const Node &l, const Node &r) 
{
    return l.getHeuristicWeight() > r.getHeuristicWeight();
}


void Astar3D(std::priority_queue< Node, std::vector<Node> > &open, Node n, std::vector<Point3> &p, std::vector<OCVWrapper> &cSpace, std::vector<OCVWrapper> &vSpace)
{
	int y = n.getLocation().y;
	int x = n.getLocation().x;
	int z = n.getLocation().z;
	if(!open.empty())
		open.pop();
	if(!(cSpace[0].inBounds(cv::Point(x,y))))
	{
		Astar3D(open, open.top(), p, cSpace, vSpace);
		return;
	}
	if(cSpace[z].getPixel<uchar>(cv::Point(x,y)) >= 128 || vSpace[z].getPixel<uchar>(cv::Point(x,y)) >= 128)
	{
		Astar3D(open, open.top(), p, cSpace, vSpace);
		return;
	}
	vSpace[z].setPixel<uchar>(cv::Point(x,y), 255);
	if(x == finish.x && y == finish.y)
	{
		n.addToPath(p);
		while(!open.empty())
			open.pop();
		return;
	}
	for(int k = -1; k <= 1; ++k)
	{
		for(int j =-1; j <= 1; ++j)
		{
			for(int i = -1; i <= 1; ++i)
			{
				if(j || i || k)
					if(cSpace[0].inBounds(cv::Point(x+i,y+j)) && (z+k > 0 && z+k < vSpace.size()))
						if(cSpace[z+k].getPixel<uchar>(cv::Point(x+i,y+j)) < 128 || vSpace[z+k].getPixel<uchar>(cv::Point(x+i,y+j)) < 128)
						{
							Node *newNode = new Node(Point3(x+i,y+j,z+k), &n);
							if(newNode != NULL)
								open.push(*newNode);
						}
			}
		}
	}
	if(!open.empty())
		Astar3D(open, open.top(), p, cSpace, vSpace);
}