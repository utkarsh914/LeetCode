// https://leetcode.com/problems/sliding-window-maximum/


/*
similar:
1696. Jump game VI
1425. constrained-subsequence-sum
*/

// ********* USING DEQUE ********
class Solution {
public:
	vector<int> maxSlidingWindow(vector<int>& a, int k) {
		vector<int> ans;
		int n = a.size();
		deque<int> dq; // stores indices
		
		// fill first window
		for (int i=0; i<k; i++) {
			// push curr element keeping dq monotonic decreasing
			while (!dq.empty() && a[dq.back()]<a[i])
				dq.pop_back();
			dq.push_back(i);
		}

		// for further windows
		for(int i=k; i <= n; i++) {
			// get max from prev window
			ans.push_back(a[dq.front()]);
			if (i == n) break;
			// remove out of range ele from front
			while (!dq.empty() && dq.front() <= i-k)
				dq.pop_front();
			// push curr element keeping dq monotonic decreasing
			while (!dq.empty() && a[dq.back()]<a[i])
				dq.pop_back();
			dq.push_back(i);
		}
		
		return ans;
	}
};





// ************* USING PQ **************
class Solution {
public:
	vector<int> maxSlidingWindow(vector<int>& a, int k)
	{
		vector<int> ans;
		int n = a.size();
		priority_queue<pair<int, int>> pq;
		
		for(int i=0; i < n; i++)
		{
			while(!pq.empty() && pq.top().second<=(i-k)) //step no. 4
				pq.pop(); // if the top of the pq( the max element value of the window), is from an element outside of the k-sized window, we pop it
			
			pq.push({ a[i], i }); // a priority queue, which stores elements of the array, with its corresponding index number.
			
			if(i >= k-1) // k sized window obtained, so we push the max element of it, into answer vector.
				ans.push_back(pq.top().first); 
		}
		
		return ans;
	}
};





// *********** USING MULTISET (VERY SLOW) ***********
class Solution {
public:
	vector<int> maxSlidingWindow(vector<int>& a, int k)
	{
		vector<int> ans;
		int n = a.size();
		multiset<int> s(a.begin(), a.begin()+k);
		
		for(int i=k; i <= n; i++) {
			// get max from prev window
			ans.push_back(*s.rbegin());
			if (i == n) break;
			s.erase(s.lower_bound(a[i-k]));
			s.insert(a[i]);
		}
		
		return ans;
	}
};
