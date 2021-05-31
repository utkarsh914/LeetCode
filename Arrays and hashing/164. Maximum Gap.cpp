// https://leetcode.com/problems/maximum-gap/

class Solution {
public:
	int maximumGap(vector<int>& A) {
		radix_sort(A);
		int ans = 0;
		for (int i = 1; i < A.size(); i++)
			ans = max(ans, A[i] - A[i-1]);
		return ans;
	}

	void radix_sort(vector<int>& A) {
		int maxEle = *max_element(A.begin(), A.end());
		long exp = pow(10, to_string(maxEle).size());
		for (long ex = 10; ex <= exp; ex *= 10)
			bucket_sort(A, ex);
	}

	void bucket_sort(vector<int>& A, int exp) {
		vector<vector<int>> bucket(10);
		for (int& n : A) {
			int b = (n % exp) / (exp/10);
			bucket[b].push_back(n);
		}
		int ind = 0;
		for (auto& b : bucket)
			for (int& n : b)
				A[ind++] = n;
	}

	void count_sort(vector<int>& A, int exp) {
		int count[10] = {};
		vector<int> output(A.size());
		// store count of occurrences in count[]
		for (int& n : A) {
			int ind = (n % exp) / (exp / 10);
			count[ind]++;
		}
		// make cumulative count
		for (int i = 1; i < 10; i++)
			count[i] += count[i-1];
		// Build the output array
		for (int i = A.size()-1; i >= 0; i--) {
			int ind = (A[i] % exp) / (exp / 10);
			output[count[ind] - 1] = A[i];
			count[ind]--;
		}
		// assign output array to given array
		A = output;
	}
};









// https://leetcode.com/problems/maximum-gap/

class Solution {
public:
	int maximumGap(vector<int>& A) {
		radix_sort(A);
		int ans = 0;
		for (int i = 1; i < A.size(); i++)
			ans = max(ans, A[i] - A[i-1]);
		return ans;
	}

	void radix_sort(vector<int>& A) {
		vector<int> output(A.size());
		int maxEle = *max_element(A.begin(), A.end());
		long exp = pow(10, to_string(maxEle).size());
		for (long ex = 10; ex <= exp; ex *= 10)
			count_sort(A, ex, output);
	}

	void count_sort(vector<int>& A, int exp, vector<int>& output) {
		int count[10] = {};
		// store count of occurrences in count[]
		for (int& n : A) {
			int ind = (n % exp) / (exp / 10);
			count[ind]++;
		}
		// make cumulative count
		for (int i = 1; i < 10; i++)
			count[i] += count[i-1];
		// Build the output array
		for (int i = A.size()-1; i >= 0; i--) {
			int ind = (A[i] % exp) / (exp / 10);
			output[count[ind] - 1] = A[i];
			count[ind]--;
		}
		// assign output array to given array
		A.swap(output);
	}
};
