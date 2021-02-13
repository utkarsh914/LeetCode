// https://leetcode.com/problems/design-a-stack-with-increment-operation/


// simply store elements in array, and increment first k ele of array
class CustomStack {
	int* s;
	int maxSize, ind;
public:
	CustomStack(int maxSize) {
		this->s = new int[maxSize];
		this->maxSize = maxSize;
		this->ind = 0;
	}
	
	void push(int x) {
		if (ind < maxSize)
			s[ind++] = x;
	}
	
	int pop() {
		int ans = -1;
		if (ind != 0) {
			ans = s[--ind];
		}
		return ans;
	}
	
	void increment(int k, int val) {
		if (k>ind) k = ind;
		for (int i=0; i<k; i++)
			s[i] += val;
	}
};





/*
*********** O(1) INCREMENT ***********

Use an additional array to record the increment value.
inc[i] means for all elements stack[0] ~ stack[i],
we should plus inc[i] when popped from the stack.
Then inc[i-1]+=inc[i],
so that we can accumulate the increment inc[i]
for the bottom elements and the following pops.
*/

class CustomStack {
	int *s, *inc;
	int maxSize, ind;
public:
	CustomStack(int maxSize) {
		this->s = (int*)calloc(maxSize, sizeof(int));
		this->inc = (int*)calloc(maxSize, sizeof(int));
		this->maxSize = maxSize;
		this->ind = 0;
	}
	
	void push(int x) {
		if (ind < maxSize)
			s[ind++] = x;
	}
	
	int pop() {
		int ans = -1;
		if (ind > 0) {
			ind--;
			ans = s[ind] + inc[ind];
			if (ind>0) inc[ind-1] += inc[ind];
			inc[ind] = 0;
		}
		return ans;
	}
	
	void increment(int k, int val) {
		if (k > ind) k = ind;
		if (k > 0) inc[k-1] += val;
	}
};

/**
 * Your CustomStack object will be instantiated and called as such:
 * CustomStack* obj = new CustomStack(maxSize);
 * obj->push(x);
 * int param_2 = obj->pop();
 * obj->increment(k,val);
 */