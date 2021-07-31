// https://leetcode.com/problems/water-and-jug-problem/

class Solution {
	// A hash function used to hash a pair of any kind
struct hash_pair {
	template <class T1, class T2>
	size_t operator()(const pair<T1, T2>& p) const {
		auto hash1 = hash<T1>{}(p.first);
		auto hash2 = hash<T2>{}(p.second);
		return hash1 ^ hash2;
	}
};

public:
	bool canMeasureWater(int jug1Cap, int jug2Cap, int target) {
		if (target > jug1Cap + jug2Cap)
			return false;

		unordered_set<pair<int,int>, hash_pair> taken;
		queue<pair<int,int>> q;
		q.push({0,0});
		taken.insert({0,0});

		while (!q.empty()) {
			auto [j1, j2] = q.front(); q.pop();
			if (j1 == target or j2 == target or j1+j2 == target)
				return true;

			int pour = 0;
			unordered_set<pair<int,int>, hash_pair> set {
				{ j1, jug2Cap }, { jug1Cap, j2 }, // operation 1
				{ 0, j2 }, { j1, 0 }, // operation 2
				// operation 3
				// pour from jug1 to jug2
				{ j1 - min(j1, jug2Cap - j2), j2 + min(j1, jug2Cap - j2) },
				// pour from jug2 to jug1
				{ j1 + min(j2, jug1Cap - j1), j2 - min(j2, jug1Cap - j1) }
			};
			
			for (auto& p : set)
				if (!taken.count(p))
					q.push(p), taken.insert(p);
		}

		return false;
	}
};