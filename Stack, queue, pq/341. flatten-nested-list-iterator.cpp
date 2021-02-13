// https://leetcode.com/problems/flatten-nested-list-iterator/

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *	 // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *	 bool isInteger() const;
 *
 *	 // Return the single integer that this NestedInteger holds, if it holds a single integer
 *	 // The result is undefined if this NestedInteger holds a nested list
 *	 int getInteger() const;
 *
 *	 // Return the nested list that this NestedInteger holds, if it holds a nested list
 *	 // The result is undefined if this NestedInteger holds a single integer
 *	 const vector<NestedInteger> &getList() const;
 * };
 */


class NestedIterator {
	deque<NestedInteger> dq;
	
	void pushAllToFront(vector<NestedInteger>& List) {
		for (int i=List.size()-1; i>=0; i--) {
			dq.push_front(List[i]);
		}
	}
	
public:
	NestedIterator(vector<NestedInteger>& List) {
		pushAllToFront(List);
	}
	
	int next() {
		auto curr = dq.front(); dq.pop_front();
		return curr.getInteger();
	}
	
	bool hasNext() {
		while (!dq.empty()) {
			if (dq.front().isInteger())
				return true;
			auto curr = dq.front(); dq.pop_front();
			pushAllToFront(curr.getList());
		}
		return false;
	}
};
/*
The same idea as a DFS, the only tricky part probably is you have to find a value node to claim there is next.
And to do that, you have to look through all the nodes in the worst case in the entire graph.
So you just keep going until you find a value node; if you can't, there is no next.
// optionally, use pointers of NestedInteger class to save memory
*/










// ****** simply perform dfs on List and store in a vector *****
class NestedIterator {
	vector<int> v;
	int ind;
	void recur(vector<NestedInteger>& List) {
		for (int i=0; i<List.size(); i++) {
			if (List[i].isInteger()) {
				v.push_back(List[i].getInteger());
			} else {
				recur(List[i].getList());
			}			
		}
	}
	
public:
	NestedIterator(vector<NestedInteger>& List) {
		recur(List);
		ind = 0;
	}
	
	int next() {
		return v[ind++];
	}
	
	bool hasNext() {
		return ind<v.size();
	}
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */