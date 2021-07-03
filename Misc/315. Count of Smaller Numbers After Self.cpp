// https://leetcode.com/problems/count-of-smaller-numbers-after-self/

/*
You are given an integer array nums and you have to return a new counts array.
The counts array has the property
where counts[i] is the number of smaller elements to the right of nums[i].

Example 1:

Input: nums = [5,2,6,1]
Output: [2,1,1,0]

Explanation:
To the right of 5 there are 2 smaller elements (2 and 1).
To the right of 2 there is only 1 smaller element (1).
To the right of 6 there is 1 smaller element (1).
To the right of 1 there is 0 smaller element.
*/











/*
I use merge sort, and in the process,
find the number of ele >= A[i] on its right.

then, use it to find number of ele < A[i] on its right;
*/
class Solution {
	vector<int> ans;
public:
	vector<int> countSmaller(vector<int>& nums) {
		int N = nums.size();
		ans.resize(N);
		vector<array<int,2>> A(N);
		for (int i = 0; i < N; i++)
			A[i] = { nums[i], i };

		// this will populate # of ele >= A[i] on right
		mergeSort(A, 0, N-1);

		for (int i = 0; i < N; i++) {
			ans[i] = (N - i - 1) - ans[i];
		}
		return ans;
	}

	void merge(vector<array<int,2>>& A, int s1, int e1, int s2, int e2) {
		int start = s1, end = e2;
		// it'll update the count of ele >= A[i] on its right in the array
		vector<array<int,2>> temp;
		while (s1 <= e1 and s2 <= e2) {
			if (A[s1][0] <= A[s2][0]) {
				temp.push_back(A[s1]);
				ans[A[s1][1]] += e2 - s2 + 1;
				s1++;
			} else {
				temp.push_back(A[s2++]);
			}
		}
		// leftovers
		while (s1 <= e1) temp.push_back(A[s1++]);
		while (s2 <= e2) temp.push_back(A[s2++]);

		// copy back merged array to original array
		for (int i = 0; i < temp.size(); i++) {
			A[i+start] = temp[i];
		}
	}

	void mergeSort(vector<array<int,2>>& A, int start, int end) {
		if (start == end) return;
		int mid = (start + end) / 2;
		mergeSort(A, start, mid);
		mergeSort(A, mid+1, end);
		merge(A, start, mid, mid+1, end);
	}
};
/*
2 5  1 6
1 2 5 6

2 5 6 1
2 5  1 6
*/






// more optimized - faster

class Solution {
	vector<int> ans;
	vector<array<int,2>> temp;
public:
	vector<int> countSmaller(vector<int>& nums) {
		int N = nums.size();
		ans.resize(N);
		temp.resize(N);
		vector<array<int,2>> A(N);
		for (int i = 0; i < N; i++)
			A[i] = { nums[i], i };

		// this will populate # of ele >= A[i] on right
		mergeSort(A, 0, N-1);

		for (int i = 0; i < N; i++) {
			ans[i] = (N - i - 1) - ans[i];
		}
		return ans;
	}

	void merge(vector<array<int,2>>& A, int s1, int e1, int s2, int e2) {
		int start = s1, size = e2-s1+1, k = 0;
		// it'll update the count of ele >= A[i] on its right in the array
		while (s1 <= e1 and s2 <= e2) {
			if (A[s1][0] <= A[s2][0]) {
				temp[k++] = A[s1];
				ans[A[s1][1]] += e2 - s2 + 1; // add count of remaining ele on right half
				s1++;
			} else {
				temp[k++] = A[s2++];
			}
		}
		while (s1 <= e1) temp[k++] = A[s1++];
		while (s2 <= e2) temp[k++] = A[s2++];

		// copy back merged array to original array
		for (int i = 0; i < size; i++) {
			A[i + start] = temp[i];
		}
	}

	void mergeSort(vector<array<int,2>>& A, int start, int end) {
		if (start == end) return;
		int mid = (start + end) / 2;
		mergeSort(A, start, mid);
		mergeSort(A, mid+1, end);
		merge(A, start, mid, mid+1, end);
	}
};