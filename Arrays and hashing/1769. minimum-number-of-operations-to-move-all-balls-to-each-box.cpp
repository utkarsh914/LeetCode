// https://leetcode.com/problems/minimum-number-of-operations-to-move-all-balls-to-each-box/

class Solution {
public:
	vector<int> minOperations(string& boxes) {
		vector<int> ans(boxes.size());
		int left = boxes[0]-'0', right = 0;

		for (int i = 1; i < boxes.size(); i++) {
			if (boxes[i] == '1')
				ans[0] += i, right++;
		}

		for (int i = 1; i < boxes.size(); i++) {
			ans[i] = ans[i-1] - right + left;
			if (boxes[i] == '1') left++, right--;
		}

		return ans;
	}
};