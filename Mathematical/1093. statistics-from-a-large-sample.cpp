// https://leetcode.com/problems/statistics-from-a-large-sample/

class Solution {
public:
	vector<double> sampleStats(vector<int>& count) {
		int min_ = 256, max_ = -1;
		int n = 0, mode = -1, maxF = 0;
		double sum = 0.0, median = 0.0;

		for (int i = 0; i < count.size(); i++) {
			if (count[i] == 0) continue;
			min_ = min(min_, i);
			max_ = max(max_, i);
			sum += 1.0 * i * count[i];
			n += count[i];
			if (count[i] > maxF) {
				maxF = count[i];
				mode = i;
			}
		}

		if (n % 2 == 0)
			median = (1.0 * (get(count, n/2) + get(count, 1+n/2))) / 2.0;
		else
			median = get(count, 1 + n/2);

		return {1.0*min_, 1.0*max_, sum/n, median, 1.0*mode};
	}
	
	int get(vector<int>& count, int k) {
		for (int i = 0; i < count.size(); i++) {
			if (count[i] != 0) {
				if (count[i] >= k) return i;
				else k -= count[i];
			}
		}
		return -1;
	}
};