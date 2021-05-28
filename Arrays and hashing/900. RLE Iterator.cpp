// https://leetcode.com/problems/rle-iterator/

class RLEIterator {
	vector<int> v;
	int i;
public:
	RLEIterator(vector<int>& encoding) {
		this->i = 0;
		this->v = encoding;
	}
	
	int next(int n) {
		int tosub = n, ans = -1;

		for (; i < v.size(); i += 2) {
			if (v[i] >= tosub) {
				v[i] -= tosub;
				tosub = 0;
				ans = v[i+1];
				break;
			}
			else {
				tosub -= v[i];
				v[i] = 0;
			}
		}

		return ans;
	}
};

/**
 * Your RLEIterator object will be instantiated and called as such:
 * RLEIterator* obj = new RLEIterator(encoding);
 * int param_1 = obj->next(n);
 */






class RLEIterator {
	int index;
	vector<int> A;

public:
	RLEIterator(vector<int>& A) {
		this->A = A;
		this->index = 0;
	}
	
	int next(int n) {
		while (index < A.size() and n > A[index]) {
			n = n - A[index];
			index += 2;
		}
		
		if (index >= A.size()) {
			return -1;
		}
		
		A[index] = A[index] - n;
		return A[index + 1];
	}
};