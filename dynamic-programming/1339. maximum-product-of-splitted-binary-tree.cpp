// https://leetcode.com/problems/maximum-product-of-splitted-binary-tree/

class Solution {
	long long int ans = 0;
	long long int M = 1000000007;
	long long int rootSum;

	long long int findSum(TreeNode* r) {
		if (!r) return 0;
		long long int curSum = findSum(r->left) + findSum(r->right) + r->val;
		ans = max(ans, (rootSum-curSum)*curSum);
		return curSum;
	}

public:
	int maxProduct(TreeNode* root) {
		rootSum = findSum(root);
		findSum(root);
		return (int)(ans%M);
	}
};






// *************** long sol(incorrect for larger cases) ***********
// some issue with modulo 

class Solution {

	int ans = 0;
	int M = 1000000007;
	int rootSum;
	unordered_map<TreeNode*,int> sum;

	int findSum(TreeNode* r) {
		if (!r) return 0;
		return sum[r] = findSum(r->left) + findSum(r->right) + r->val;
	}

	int modMul(int a, int b, int M) {
		long long int ans = 0;
		for (int i=0; i<a; i++)
			ans = (ans+b) % M;
		return (int)(ans % M);
	}

	int dfs(TreeNode* r) {
		int left = 0, right = 0;
		if (r->left) {
			int part1 = sum[r->left];
			int part2 = rootSum - part1;
			ans = max(ans, modMul(part1,part2,M) );
			dfs(r->left);
		}
		if (r->right) {
			int part1 = sum[r->right];
			int part2 = rootSum - part1;
			ans = max(ans, modMul(part1,part2,M) );
			dfs(r->right);
		}
	}

public:
	int maxProduct(TreeNode* root) {
		rootSum = findSum(root);
		dfs(root);
		return ans;
	}
};