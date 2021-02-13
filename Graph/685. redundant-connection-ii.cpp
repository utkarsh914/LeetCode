/*
https://leetcode.com/problems/redundant-connection-ii/

In this problem, a rooted tree is a directed graph such that, there is exactly one node (the root)
for which all other nodes are descendants of this node, plus every node has exactly one parent,
except for the root node which has no parents.
The given input is a directed graph that started as a rooted tree with n nodes (with distinct values from 1 to n),
with one additional directed edge added. The added edge has two different vertices chosen from 1 to n,
and was not an edge that already existed.
The resulting graph is given as a 2D-array of edges.
Each element of edges is a pair [ui, vi] that represents a directed edge connecting nodes ui and vi,
where ui is a parent of child vi.
Return an edge that can be removed so that the resulting graph is a rooted tree of n nodes.
If there are multiple answers, return the answer that occurs last in the given 2D-array.


// ********* APPROACH *********

1) Check whether there is a node having two parents. 
	If so, store them as candidates A and B, and set the second edge invalid. 
2) Perform normal union find. 
	If the tree is now valid 
		   simply return candidate B
	else if candidates not existing 
		   we find a circle, return current edge; 
	else 
		   remove candidate A instead of B.
*/

class Solution {
public:
vector<int> parent;

int find(int x) {
	if (parent[x] != x)
		parent[x] = find(parent[x]);
	return parent[x];
}

void uni(int x, int y) {
	x = find(x);
	y = find(y);
	if (x != y) {
		parent[y] = x;
	}
}

vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
	parent = vector<int> (edges.size()+1,0);
	vector<int> candA, candB;
	// find two parents of same node and put as possible candidates
	for (auto& e: edges) {
		if (parent[e[1]] == 0) {
			parent[e[1]] = e[0];
		}
		else {
			candA = {parent[e[1]], e[1]};
			candB = e;
			e[1] = 0; // mark curr edge as invalid
		}
	}
	// perform union find, if goes well, candB was the problem
	for (int i = 0; i < parent.size(); i++) parent[i] = i;
	for (auto& e:edges) {
		if (e[1] == 0) continue; // skip candB
		int u=e[0], v=e[1];
		if (find(u) == v) {
			if (candA.empty()) return e; // circle exists, and we are on last edge
			else return candA;
		}
		uni(u,v);
	}
	return candB;
}};



// ************* USING REDUNDANT CONNECTION-I ******************
// The same idea but it is possible to re-use the solution of "684. Redundant Connection" problem:

class Solution {
	
	Map<Integer, Integer> incoming = new HashMap<>();
	
	public int[] findRedundantDirectedConnection(int[][] a) {
		
		// count incoming edges for all nodes
		int nodeWithTwoIncomingEdges = -1;
		for(int[] v : a){
			incoming.put(v[1], incoming.getOrDefault(v[1], 0)+1);
			if(incoming.get(v[1])==2) nodeWithTwoIncomingEdges=v[1];
		}
		
		if(nodeWithTwoIncomingEdges==-1){	
			// if there are no nodes with 2 incoming edges -> just find a cycle
			return findRedundantConnection(a, -1);
		}else{
			// if there is a node with 2 incoming edges -> skip them one by one and try to build a graph
			// if we manage to build a graph without a cycle - the skipped node is what we're looking for
			for(int i=a.length-1;i>=0;i--){						   
				if(a[i][1]==nodeWithTwoIncomingEdges) {
					int[] res = findRedundantConnection(a, i);
					if(res==null) return a[i];
				}
			}
		}
		
		return null;
	}
	
	// 'Redundant Connection' solution is extended to skip a node.
	int[] findRedundantConnection(int[][] a, int skip){
		UnionFind uf = new UnionFind();
		
		for(int i=0;i<a.length;i++){
			if(i==skip) continue;
			if(!uf.union(a[i][0], a[i][1])) return a[i];
		} 
		
		return null;
	}
	
	class UnionFind {
		Map<Integer, Integer> map = new HashMap<>();

		int find(int x){
			if(!map.containsKey(x)) map.put(x, x);

			if(map.get(x)==x) return x;
			int par = find(map.get(x));
			map.put(x, par);
			return par;
		}

		boolean union(int x, int y){
			int px = find(x);
			int py = find(y);

			if(px==py) return false;
			map.put(px, py);
			return true;
		}		
	}
	
}