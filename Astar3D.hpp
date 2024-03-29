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
			int hW = greed*10*(abs(finish.x - location.x) + abs(finish.y - location.y)) +  weight;
			if(parent != NULL)
				hW += abs(parent->getLocation().z - location.z);
			return hW;
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


void Astar3D(std::priority_queue< Node, std::vector<Node> > &open, std::vector<Point3> &p, std::vector<OCVWrapper> &cSpace)
{
	if(open.empty())
	{
		std::cout << "\nRan out of nodes...\n";	
		return;
	}
	Node n = open.top();
	open.pop();
	int y = n.getLocation().y;
	int x = n.getLocation().x;
	int z = n.getLocation().z;
	if(x == finish.x && y == finish.y)
	{
		n.addToPath(p);
		return;
	}
	if(!(cSpace[0].inBounds(cv::Point(x,y))))
	{
		Astar3D(open, p, cSpace);
		return;
	}
	if(cSpace[z].getPixel<uchar>(cv::Point(x,y)) >= 128)
	{
		Astar3D(open, p, cSpace);
		return;
	}
	//std::cout << x << "," << y << "," << z << " ";
	cSpace[z].setPixel<uchar>(cv::Point(x,y), 128);
	//char name[1];
	//name[0] = 48+z;
	//cSpace[0].showImg("base");
	//cSpace[0].update(1);
	for(int k = -1; k <= 1; ++k)
	{
		for(int j = -1; j <= 1; ++j)
		{
			for(int i = -1; i <= 1; ++i)
			{
				if(i || (j || k))
					if(cSpace[0].inBounds(cv::Point(x+i,y+j)))
					{
						int Z = (z+k)%cSpace.size();
						if(cSpace[Z].getPixel<uchar>(cv::Point(x+i,y+j)) == 0)
						{
							Node *newNode = new Node(Point3(x+i,y+j,Z), &n);
							if(newNode != NULL)
								open.push(*newNode);
						}
					}
			}
		}
	}
	//std::cout << "Memory occupied: " << open.size()*sizeof(Node)/1000000.f << " MB\n";
	if(!open.empty())
		Astar3D(open, p, cSpace);
	else
		std::cout << "\nRan out of nodes...\n";
}
