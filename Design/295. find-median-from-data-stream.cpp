// https://leetcode.com/problems/find-median-from-data-stream/

class MedianFinder {
	// left.size() is never less than right.size()
	priority_queue<int> left;
	priority_queue<int, vector<int>, greater<int>> right;

public:
	
	MedianFinder() {}
	
	void addNum(int num) {
		left.push(num);
		right.push(left.top());
		left.pop();

		if (left.size() < right.size()) {
			left.push(right.top());
			right.pop();
		}
	}
	
	double findMedian() {
		if (left.size() > right.size())
			return left.top();
		else
			return (double)(left.top()+right.top())/2;
	}

	// void addNum(int num) {
	// 	if (left.empty()) {
	// 		left.push(num);
	// 	} else if (num <= left.top()) {
	// 		left.push(num);
	// 	} else {
	// 		right.push(num);
	// 	}

	// 	while (right.size()+1 < left.size()) {
	// 		right.push(left.top());
	// 		left.pop();
	// 	}
	// 	while (left.size() < right.size()) {
	// 		left.push(right.top());
	// 		right.pop();
	// 	}
	// }
};

/*
************ FOLLOW UPS ***********

1. If all integer numbers from the stream are between 0 and 100, how would you optimize it?

We can maintain an integer array of length 100 to store the count of each number along with a total count.
Then, we can iterate over the array to find the middle value to get our median.
Time and space complexity would be O(100) = O(1).

2. If 99% of all integer numbers from the stream are between 0 and 100, how would you optimize it?
In this case, we need an integer array of length 100 and a TREEMAP for these numbers that are not in [0,100].
*/




/*
As the input numbers are random, so the height of the binary search tree is O(logN)
We maintain every single node's children's size and it's easy to implement because it just has add operation.
*/

struct BST {
	struct node {
		int val;
		int size;
		node* left, *right;
		node(int v) : size(1), val(v) {};
	} *Null, *root;
	
	BST() {
		Null = new node(0);
		Null->size = 0;
		root = Null;
	}
	
	void add(int val, node*& R) {
		if(R == Null) {
			R = new node(val);
			R->left = R->right = Null;
			return;
		}
		if(R->val <= val) add(val, R->left);
		else add(val, R->right);
		R->size = R->left->size + R->right->size + 1;
	}
	
	int rank(int k) {
		node* t = root;
		while(true) {
			int leftSize =  t->left->size;
			if(leftSize == k) return t->val;
			if(leftSize > k) {
				t = t->left;
			} else {
				k = k - leftSize - 1;
				t = t->right;
			}
		}
		return -1;
	}
};


class MedianFinder {
public:
	BST* bst;
	MedianFinder() {
		bst = new BST();
	}
	// Adds a number into the data structure.
	void addNum(int num) {
		bst->add(num, bst->root);
	}
	
	// Returns the median of current data stream
	double findMedian() {
		int sz = bst->root->size;
		if(sz % 2 == 0) {
			return 1.0 * (bst->rank(sz / 2) + bst->rank(sz / 2 - 1)) / 2;
		} else return bst->rank(sz / 2);
		
	}
};





/*
// ********* wrong ans ********

class MedianFinder {
	// left.size() is never less than right.size()
	priority_queue<int> left;
	priority_queue<int, vector<int>, greater<int>> right;
	int capacity, leftCap, rightCap, count;
	int minValue, maxValue;

public:
	
	MedianFinder() {
		capacity = 5, count = 0;
		leftCap = 1+capacity/2, rightCap = capacity/2;
		minValue = maxValue = -1;
	}
	
	void addNum(int num) {

		if (++count > capacity) {
			if (left.size() == right.size())
				minValue = right.top();
			maxValue = left.top();

			left = priority_queue<int> ();
			right = priority_queue<int, vector<int>, greater<int>> ();

			if (maxValue > 0) left.push(maxValue);
			if (minValue > 0) right.push(minValue);

			count = 0, minValue = maxValue = -1;
		}

		left.push(num);
		right.push(left.top());
		left.pop();

		if (left.size() < right.size()) {
			left.push(right.top());
			right.pop();
		}
	}
	
	double findMedian() {
		if (left.size() > right.size())
			return left.top();
		else
			return (double)(left.top()+right.top())/2;
	}
};
*/



/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */