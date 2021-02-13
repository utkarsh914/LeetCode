// https://leetcode.com/problems/verify-preorder-serialization-of-a-binary-tree/

// it is same as iterative preorder traversal
class Solution {
public:
	bool isValidSerialization(string preorder) {
		stringstream ss(preorder);
		stack<string> s;
		string curr;
		getline(ss, curr, ',');

		while (!s.empty() or curr != "#") {
			// reach leftmost node
			while (curr != "#") {
				s.push(curr);
				if (!getline(ss, curr, ','))
					return false;
			}
			// at this point curr must be "#"
			curr = s.top(); s.pop();
			getline(ss, curr, ',');
		}

		return s.empty() && curr=="#" && !getline(ss, curr, ',');
	}
};





// check indegree and outdegree of each node
/*
if we consider null as leaves, then

all non-null node provides 2 outdegree and 1 indegree (2 children and 1 parent), except root
all null node provides 0 outdegree and 1 indegree (0 child and 1 parent).
Suppose we try to build this tree. During building,
we record the difference between out degree and in degree diff = outdegree - indegree.
When the next node comes, we then decrease diff by 1, because the node provides an in degree.
If the node is not null, we increase diff by 2, because it provides two out degrees.
If a serialization is correct, diff should never be negative and diff will be zero when finished.
*/
class Solution {
public:
	bool isValidSerialization(string& preorder) {
		stringstream ss(preorder);
		string curr;
		int indegree = 1, outdegree = 0;
		
		while (getline(ss, curr, ',')) {
			indegree--;
			// The count of in should not be greater than out
			if (indegree + outdegree < 0)
				return false;
			if (curr != "#")
				outdegree += 2;
		}
		
		return indegree+outdegree == 0;
	}
};