// https://leetcode.com/problems/validate-stack-sequences/

class Solution {
public:
	bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
		int j=0;
		stack<int> s;

		for (int p: pushed) {
			s.push(p);
			while (!s.empty() && s.top()==popped[j]) {
				s.pop(), j++;
			}
		}
		
		while (!s.empty() && j<popped.size()) {
			if (s.top() != popped[j])
				return false;
			s.pop();
			j++;
		}

		return true;
	}
};



// ******** shorter *******
class Solution {
public:
	bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
		int j=0;
		stack<int> s;
		for (int p: pushed) {
			s.push(p);
			while (!s.empty() && s.top()==popped[j]) {
				s.pop(), j++;
			}
		}
		return s.empty();
	}
};




// ******** O(1) space *******
// ****** use 'pushed' as stack ******
class Solution {
public:
	bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
		int i = 0, j = 0;
		for (int p: pushed) {
			pushed[i++] = p;
			while (i>0 && pushed[i-1]==popped[j]) {
				i--, j++;
			}
		}
		return i==0;
	}
};