
class Solution {
public:

class Point{
public:
	int x,y;
	Point(int a, int b) {x=a, y=b;}
	Point() {x=y=0;}
	bool equals(const Point& p) {
		return x==p.x && y==p.y;
	}
	bool operator==(const Point& p) const {
		return x==p.x && y==p.y;
	}
};

class Edge {
public:
	Point u, v; int w;
	Edge(Point a, Point b, int w) {
		u=a, v=b, this->w=w;
	}
	Edge() {u=v=Point(0,0), w=0;}
};

struct compare {
	bool operator()(const Edge& a, const Edge& b) const {
		return a.w < b.w;
	}
};

class MyHashFunction {
public:
	size_t operator()(const Point& p) const {
		return -p.x + p.y;
	}
};

// union find
unordered_map<Point, Point, MyHashFunction> parent;

Point find(Point x) {
	if (!parent.count(x)) {
		return parent[x]=x;
	}
	if (!parent[x].equals(x))
		parent[x] = find(parent[x]);
	return parent[x];
}

void uni(Point x, Point y) {
	x = find(x);
	y = find(y);
	if (!x.equals(y)) {
		parent[y] = x;
	}
}

int minCostConnectPoints(vector<vector<int>>& points) {
	// build an array connecting all points to each other with weighted edges
	// and sort it
	vector<Edge> edges;
	for (int i=0; i<points.size(); i++) {
		Point a(points[i][0], points[i][1]);
		for (int j=i+1; j<points.size(); j++) {
			// if (i==j) continue;
			Point b(points[j][0], points[j][1]);
			int w = abs(a.x-b.x) + abs(a.y-b.y);
			edges.push_back(Edge(a,b,w));
			// edges.push_back(Edge(b,a,w));
		}
	}
	sort(edges.begin(), edges.end(), compare());
	// pick edges one by one starting from minimum
	// and if it creates a loop, discard it, o/w add it
	int totalWeight = 0;
	for (auto& e: edges) {
		Point pu=find(e.u), pv=find(e.v);
		if (pu.equals(pv)) continue; // cycle, so discard this edge
		uni(pu, pv);
		totalWeight += e.w;
	}

	return totalWeight;
}};










// ************** FASTER *****************
class UnionFind {
	vector<int> component;
	int distinctComponents;
public:
	/*
	 *   Initially all 'n' nodes are in different components.
	 *   e.g. component[2] = 2 i.e. node 2 belong to component 2.
	 */
	UnionFind(int n) {
		distinctComponents = n;
		for (int i=0; i<=n; i++) {
			component.push_back(i);
		}
	}
	
	/*
	 *   Returns true when two nodes 'a' and 'b' are initially in different
	 *   components. Otherwise returns false.
	 */
	bool unite(int a, int b) {	   
		if (findComponent(a) == findComponent(b)) {
			return false;
		}
		component[findComponent(a)] = b;
		distinctComponents--;
		return true;
	}
	
	/*
	 *   Returns what component does the node 'a' belong to.
	 */
	int findComponent(int a) {
		if (component[a] != a) {
			component[a] = findComponent(component[a]);
		}
		return component[a];
	}
	
	/*
	 *   Are all nodes united into a single component?
	 */
	bool united() {
		return distinctComponents == 1;
	}
};

class Solution {
public:
	int minCostConnectPoints(vector<vector<int>>& points) {
		int n = points.size();			  // Total points.
		vector<array<int, 3>> edges;		// All edges. Each point to every other point.
		for (int i=0; i<n-1; i++) {		 // Point 1
			for (int j=i+1; j<n; j++) {	 // Point 2
				int dist = abs(points[i][0]-points[j][0]) + abs(points[i][1]-points[j][1]); // Manhattan distance.
				edges.push_back({dist, i, j}); // Add the edge.
			}
		}
		// Note: Unfortunately sorting, priority_queue gives TLE.
		make_heap(edges.begin(), edges.end(), greater<>());  // For heap sort.
		UnionFind uf(n);   // Very important to have this data structure ready.
		int cost = 0;	  // Stores the cost.
		while(!edges.empty() && !uf.united()) { // Until the forest is not a single component.
			pop_heap(edges.begin(), edges.end(), greater<>()); 
			auto edge = edges.back(); // Minimum cost edge.
			int p1 = edge[1];  // Point 1
			int p2 = edge[2];  // Point 2
			if (uf.unite(p1, p2)) {  // Merge two components.
				cost += edge[0];  // Add the cost if they were not already merged.
			}
			edges.pop_back();  // Remove the lowest cost edge.
		}
		return cost;   // Yay, solved.
	}
};