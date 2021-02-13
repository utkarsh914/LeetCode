// https://leetcode.com/problems/4sum-ii/

/*
AB[5] = 2 means a+b=5 appears 2 times in the a+b scenario.
Then we are looking for how many times does c+d = -5 appear so that it could be paired with AB[5] and form a 0.
That's why we then look for AB[-c-d] (or AB[-(c+d)] )
*/
class Solution {
public:
	int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
		unordered_map<int,int> m;
		for (int x:A)
			for (int y:B) m[x+y]++;

		int count = 0;
		for (int x:C)
			for (int y:D) count += m[-(x+y)];

		return count;
	}
};


/*
class Solution {
public:
	int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
		vector<vector<int>> V;
		V.emplace_back(A); V.emplace_back(B);
		V.emplace_back(C); V.emplace_back(D);
		for (auto& v : V) {
			sort(v.begin(), v.end());
				for (auto i:v) cout<<i<<" ";
				cout<<endl;
		}
		return k_Sum(V, 0, 4);
	}


	int k_Sum(vector<vector<int>>& V, int target, int k) {
		if (k == 2) return two_Sum(V, target);

		int count = 0, ind = 4-k;
		for (int i=0; i < V[ind].size(); i++) {
			count += k_Sum(V, target - V[ind][i], k-1);
		}
		return count;
	}


	int two_Sum(vector<vector<int>>& V, int target) {
		int size = V[3].size(), count = 0;
		int lo = 0, hi = size-1;
		
		while (lo<size && hi>=0) {
			int sum = V[2][lo] + V[3][hi];
			if (sum == target) {
				count++;
				lo++, hi--;
			}
			else if (sum > target)
				hi--;
			else
				lo++;
		}
		return count;
	}
};

*/