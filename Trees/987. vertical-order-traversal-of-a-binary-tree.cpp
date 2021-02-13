// https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *	 int val;
 *	 TreeNode *left;
 *	 TreeNode *right;
 *	 TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *	 TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *	 TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
// https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *	 int val;
 *	 TreeNode *left;
 *	 TreeNode *right;
 *	 TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *	 TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *	 TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {

class Node{
public:
	TreeNode* ptr;
	int level, position;
	Node(TreeNode* ptr, int level, int position): ptr(ptr), level(level), position(position) {}
};

public:
	vector<vector<int>> verticalTraversal(TreeNode* root) {
		if (!root) return vector<vector<int>>();

		unordered_map<int, vector<Node>> map;
		queue<Node> q;
		q.push({root, 0, 0});
		int minPosition = 0, maxPosition = 0;

		while (!q.empty()) {
			int size = q.size();

			while (size--) {
				TreeNode* curr = q.front().ptr;
				int position = q.front().position;
				int level = q.front().level; q.pop();

				minPosition = min(minPosition, position);
				maxPosition = max(maxPosition, position);

				map[position].push_back({curr, level, position});

				if (curr->left) q.push({curr->left, level+1, position-1});
				if (curr->right) q.push({curr->right, level+1, position+1});
			}
		}

		vector<vector<int>> result;
		for (int position=minPosition; position<=maxPosition; position++) {
			auto itr = map.find(position);
			if (itr == map.end())
				continue;

			vector<Node>& curr = itr->second;
			sort(curr.begin(), curr.end(),
			[](const Node& n1, const Node& n2) -> bool {
					if (n1.level == n2.level)
						return n1.ptr->val < n2.ptr->val;
					return n1.level < n2.level;
			});

			vector<int> currLevelFinal;
			for (Node& n:curr) currLevelFinal.push_back(n.ptr->val);
			result.push_back(currLevelFinal);
		}

		return result;
	}
};












// ************* more concise **************
class Solution {
public:
	vector<vector<int>> verticalTraversal(TreeNode* root) {
		vector<vector<int>> res;
		if (!root) {
			return res;
		}
		// x		  y	  values
		map<int, map<int, multiset<int>>> m;
		queue<pair<pair<int, int>, TreeNode *>> q;
		q.push({{0,0}, root});
		while (!q.empty()) {
			auto node = q.front(); q.pop();
			int x = node.first.first;
			int y = node.first.second;
			m[x][y].insert(node.second->val);
			if (node.second->left) {
				q.push({{x - 1, y - 1}, node.second->left});
			}
			if (node.second->right) {
				q.push({{x + 1, y - 1}, node.second->right});
			}
		}
		for (auto &it : m) {
			vector<int> t;
			for (auto &yit : it.second) {
				t.insert(t.begin(), yit.second.begin(), yit.second.end());
			}
			res.push_back(t);
		}
		return res;
	}
};