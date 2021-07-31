// https://leetcode.com/problems/construct-quad-tree/

/*
Given a n * n matrix grid of 0's and 1's only. We want to represent the grid with a Quad-Tree.

Return the root of the Quad-Tree representing the grid.

Notice that you can assign the value of a node to True or False when isLeaf is False, and both are accepted in the answer.

A Quad-Tree is a tree data structure in which each internal node has exactly four children. Besides, each node has two attributes:

val: True if the node represents a grid of 1's or False if the node represents a grid of 0's. 
isLeaf: True if the node is leaf node on the tree or False if the node has the four children.
class Node {
    public boolean val;
    public boolean isLeaf;
    public Node topLeft;
    public Node topRight;
    public Node bottomLeft;
    public Node bottomRight;
}
We can construct a Quad-Tree from a two-dimensional area using the following steps:

If the current grid has the same value (i.e all 1's or all 0's) set isLeaf True and set val to the value of the grid and set the four children to Null and stop.
If the current grid has different values, set isLeaf to False and set val to any value and divide the current grid into four sub-grids as shown in the photo.
Recurse for each of the children with the proper sub-grid.

If you want to know more about the Quad-Tree, you can refer to the wiki.

Quad-Tree format:

The output represents the serialized format of a Quad-Tree using level order traversal, where null signifies a path terminator where no node exists below.

It is very similar to the serialization of the binary tree. The only difference is that the node is represented as a list [isLeaf, val].

If the value of isLeaf or val is True we represent it as 1 in the list [isLeaf, val] and if the value of isLeaf or val is False we represent it as 0.

 

Example 1:


Input: grid = [[0,1],[1,0]]
Output: [[0,1],[1,0],[1,1],[1,1],[1,0]]
Explanation: The explanation of this example is shown below:
Notice that 0 represnts False and 1 represents True in the photo representing the Quad-Tree.

Example 2:



Input: grid = [[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,1,1,1,1],[1,1,1,1,1,1,1,1],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0],[1,1,1,1,0,0,0,0]]
Output: [[0,1],[1,1],[0,1],[1,1],[1,0],null,null,null,null,[1,0],[1,0],[1,1],[1,1]]
Explanation: All values in the grid are not the same. We divide the grid into four sub-grids.
The topLeft, bottomLeft and bottomRight each has the same value.
The topRight have different values so we divide it into 4 sub-grids where each has the same value.
Explanation is shown in the photo below:

Example 3:

Input: grid = [[1,1],[1,1]]
Output: [[1,1]]
Example 4:

Input: grid = [[0]]
Output: [[1,0]]
Example 5:

Input: grid = [[1,1,0,0],[1,1,0,0],[0,0,1,1],[0,0,1,1]]
Output: [[0,1],[1,1],[1,0],[1,0],[1,1]]
 

Constraints:

n == grid.length == grid[i].length
n == 2^x where 0 <= x <= 6
*/









/*
// Definition for a QuadTree node.
class Node {
public:
	bool val;
	bool isLeaf;
	Node* topLeft;
	Node* topRight;
	Node* bottomLeft;
	Node* bottomRight;
	
	Node() {
		val = false;
		isLeaf = false;
		topLeft = NULL;
		topRight = NULL;
		bottomLeft = NULL;
		bottomRight = NULL;
	}
	
	Node(bool _val, bool _isLeaf) {
		val = _val;
		isLeaf = _isLeaf;
		topLeft = NULL;
		topRight = NULL;
		bottomLeft = NULL;
		bottomRight = NULL;
	}
	
	Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight,
		Node* _bottomLeft, Node* _bottomRight) {
		val = _val;
		isLeaf = _isLeaf;
		topLeft = _topLeft;
		topRight = _topRight;
		bottomLeft = _bottomLeft;
		bottomRight = _bottomRight;
	}
};
*/

class Solution {
	vector<vector<int>> sum;

	void computeSum(vector<vector<int>>& g) {
		int R = g.size(), C = g[0].size();
		sum.resize(R+1, vector<int> (C+1));
		// row-wise
		for (int i = 0; i < R; i++)
			for (int j = 0; j < C; j++)
				sum[i+1][j+1] = sum[i+1][j] + g[i][j];
		// col-wise
		for (int i = 1; i <= R; i++)
			for (int j = 0; j <= C; j++)
				sum[i][j] += sum[i-1][j];
	}

	int getsum(int i1, int j1, int i2, int j2) {
		return sum[i2+1][j2+1] - sum[i1][j2+1] - sum[i2+1][j1] + sum[i1][j1];
	}

public:
	Node* construct(vector<vector<int>>& g) {
		computeSum(g);
		int R = g.size(), C = g[0].size();
		return recur(g, 0, 0, R-1, C-1);
	}

	Node* recur(vector<vector<int>>& g, int i1, int j1, int i2, int j2) {
		int sum = getsum(i1, j1, i2, j2);
		int len = i2 - i1 + 1;
		if (sum == 0)
			return new Node(false, true);
		else if (sum == len * len)
			return new Node(true, true);
		
		len = len / 2;
		Node* ans = new Node();
		ans->topLeft = recur(g, i1, j1, i1+len-1, j1+len-1);
		ans->topRight = recur(g, i1, j1+len, i1+len-1, j2);
		ans->bottomLeft = recur(g, i1+len, j1, i2, j1+len-1);
		ans->bottomRight = recur(g, i1+len, j1+len, i2, j2);
		return ans;
	}
};