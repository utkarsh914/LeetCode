// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/

class Solution {
public:
	int maxProfit(vector<int>& prices) {
		int size = prices.size(), ans = 0;
		vector<int> fwd(size, 0), rev(size, 0);

		for (int i=0, min_=INT_MAX; i < size; i++) {
			min_ = min(min_, prices[i]);
			fwd[i] = prices[i] - min_;
			if (i > 0) fwd[i] = max(fwd[i], fwd[i-1]);
		}

		for (int i=size-1, max_=INT_MIN; i >= 0; i--) {
			max_ = max(max_, prices[i]);
			rev[i] = max_ - prices[i];
			if (i+1 < size) rev[i] = max(rev[i], rev[i+1]);
		}

		for (int i=0; i < size; i++) {
			int once = fwd[i];
			int twice = i+1 < size ? rev[i+1] : 0;
			ans = max(ans, once + twice);
		}

		return ans;
	}
};