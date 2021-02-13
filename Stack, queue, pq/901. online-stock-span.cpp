// https://leetcode.com/problems/online-stock-span/

/*
We should have a stack of a pair of (current  price, maximum number of consecutive days)
Since we don't have an access to the indicies.
*/

class StockSpanner {
	// decreasing stack, pair<price, count>
	stack<pair<int,int>> s;
public:
	StockSpanner() {}
	
	int next(int price) {
		int count = 0;
		while (!s.empty() && s.top().first <= price) {
			count += s.top().second;
			s.pop();
		}
		s.push({price, count+1});
		return s.top().second;
	}
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */