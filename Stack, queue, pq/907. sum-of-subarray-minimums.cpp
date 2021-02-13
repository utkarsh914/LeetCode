// https://leetcode.com/problems/sum-of-subarray-minimums/


/*
 **** need to find prev less, and next less ele of each ele ****

NOTE: The last thing that needs to be mentioned for handling duplicate elements:
Method: Set strict less and non-strict less(less than or equal to) for finding NLE and PLE respectively.
The order doesn't matter.
*/
class Solution {
public:
	int sumSubarrayMins(vector<int>& arr) {
		stack<int> prevStk, nextStk; // stores index of prev less/next less ele
		vector<long long> prev(arr.size()), next(arr.size());

		// find prev less ele
		for (int i=0; i<arr.size(); i++) {
			while (!prevStk.empty() && arr[prevStk.top()] > arr[i])
				prevStk.pop();
			prev[i] = !prevStk.empty() ? prevStk.top() : -1;
			prevStk.push(i);
		}
		// find next less ele
		for (int i=arr.size()-1; i>=0; i--) {
			while (!nextStk.empty() && arr[nextStk.top()] >= arr[i])
				nextStk.pop();
			next[i] = !nextStk.empty() ? nextStk.top() : arr.size();
			nextStk.push(i);
		}

		long long sum = 0, mod = 1e9+7;
		for (int i=0; i<arr.size(); i++) {
			sum += ( arr[i] * (i-prev[i]) * (next[i]-i) ) % mod;
			sum %= mod;
		}

		return sum;
	}
};




// ******** shorter *********
class Solution {
public:
	int sumSubarrayMins(vector<int>& arr) {
		stack<int> s; s.push(-1);
		arr.push_back(0);
		long long result = 0;
		for (int i = 0; i < arr.size(); ++i) {
			while (s.top() != -1 && arr[s.top()] > arr[i]) {
				int index = s.top();  s.pop();
				result = (result + (long long)(index-s.top()) * (i-index) * arr[index]) % 1e9+7;
			}
			s.push(i);
		}
		return result;
	}
};




/*
How can the monotonous increase stack be applied to this problem?
For example:
Consider the element 3 in the following vector:

							[2, 9, 7, 8, 3, 4, 6, 1]
				 			 |										|
				 the previous less	   the next less 
					element of 3		  		element of 3

After finding both NLE and PLE of 3, we can determine the
distance between 3 and 2(previous less) , and the distance between 3 and 1(next less).
In this example, the distance is 4 and 3 respectively.

How many subarrays with 3 being its minimum value?
The answer is 4*3.

9 7 8 3 
9 7 8 3 4 
9 7 8 3 4 6 
7 8 3 
7 8 3 4 
7 8 3 4 6 
8 3 
8 3 4 
8 3 4 6 
3 
3 4 
3 4 6
How much the element 3 contributes to the final answer?
It is 3*(4*3).
What is the final answer?
Denote by left[i] the distance between element A[i] and its PLE.
Denote by right[i] the distance between element A[i] and its NLE.

The final answer is,
sum(A[i]*left[i]*right[i] )


********* why 3*4 subarrays **********

This is impossible to derive in interview. An easier way of looking at it is this:
The number of subarrays with 3 in it will be anything that starts in [L..3] and ends in [3..R].
So we have [L..3] starting positions and [3..R] ending positions.
In other words, we have d1 starting positions and d2 ending positions.
So the total number of subarrays is just d1*d2.

For example:
in [9,7,8,3,4,6]
we have 4 choices to start with (9,7,8,3)
we have 3 choices to end with (3,4,6)

So answer is just 4*3.
*/




// // ******* wrong *********
// // ******** TWO POINTER , O(1) space **********
// // *** SIMILAR TO: LARGEST RECT IN HISTOGRAM ***
// class Solution {
// public:
// 	int sumSubarrayMins(vector<int>& arr) {
		
// 		long long sum = 0, mod = 1e9+7;
// 		int PLE = 0, NLE = arr.size()-1;
// 		int lo = 0, hi = arr.size()-1;

// 		while (lo < hi) {
// 			PLE = arr[lo]<arr[PLE] ? lo : PLE;
// 			NLE = arr[hi]<arr[NLE] ? hi : NLE;
// 			int prev, next, currEle;

// 			if (arr[lo] >= arr[hi]) {
// 				prev = lo-PLE==0 ? 1 : lo-PLE;
// 				next = NLE-lo==0 ? 1 : NLE-lo;
// 				currEle = arr[lo];
// 				lo++;
// 			} else {
// 				prev = hi-PLE==0 ? 1 : hi-PLE;
// 				next = NLE-hi==0 ? 1 : NLE-hi;
// 				currEle = arr[hi];
// 				hi--;
// 			}

// 			sum += ( currEle * prev * next ) % mod;
// 			sum %= mod;
// 		}

// 		return sum;
// 	}
// };
