// https://leetcode.com/problems/unique-binary-search-trees-ii/

// similar to: 894. all-possible-full-binary-trees

// *********** DP ************
class Solution {
public:
	vector<TreeNode*> generateTrees(int n) {

		vector<vector<vector<TreeNode*>>> dp(n+2, vector<vector<TreeNode*>>(n+2) );

		for (int i=1; i<=n+1; i++)
			dp[i][i-1] = {NULL};

		for (int len=1; len<=n; len++) {
			for (int start=1, end=start+len-1; end<=n; start++,end++) {
				if (len == 1) {
					dp[start][end] = {new TreeNode(start)};
					continue;
				}
				for (int pivot=start; pivot<=end; pivot++) {
					auto& left = dp[start][pivot-1];
					auto& right = dp[pivot+1][end];
					for (auto& l:left)
						for (auto& r:right)
						dp[start][end].push_back(new TreeNode(pivot,l,r));
				}
			}
		}

		return dp[1][n];
	}
};







class Solution {
public:
	vector<TreeNode*> generateTrees(int n, int start=1, int end=-1) {
		if (end == -1) end = n;
		if (start == end)
			return { new TreeNode(start) };

		vector<TreeNode*> ans;
		for (int i=start; i<=end; i++) {
			auto  left = i==start ? vector<TreeNode*>{NULL} : generateTrees(n,start,i-1);
			auto right = i==end   ? vector<TreeNode*>{NULL} : generateTrees(n, i+1, end);
			for (auto& l:left)
				for (auto& r:right)
					ans.push_back(new TreeNode(i,l,r));
		}

		return ans;
	}
};