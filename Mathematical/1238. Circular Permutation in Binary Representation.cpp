// https://leetcode.com/problems/circular-permutation-in-binary-representation/

/*
Given 2 integers n and start. Your task is return any permutation p of (0,1,2.....,2^n -1) such that :

p[0] = start
p[i] and p[i+1] differ by only one bit in their binary representation.
p[0] and p[2^n -1] must also differ by only one bit in their binary representation.
 

Example 1:

Input: n = 2, start = 3
Output: [3,2,0,1]
Explanation: The binary representation of the permutation is (11,10,00,01). 
All the adjacent element differ by one bit. Another valid permutation is [3,1,0,2]
Example 2:

Input: n = 3, start = 2
Output: [2,6,7,5,4,0,1,3]
Explanation: The binary representation of the permutation is (010,110,111,101,100,000,001,011).
 

Constraints:

1 <= n <= 16
0 <= start < 2 ^ n
*/






/*
Use gray code to generate a n-bit sequence.
Rotate the sequence such that its first element is start.
*/
class Solution {
public:
	vector<int> circularPermutation(int n, int start) {
		vector<int> ans;
		for (int i = 0; i < (1<<n); i++)
			ans.push_back(toGray(i));
		
		int startInd = find(ans.begin(), ans.end(), start) - ans.begin();
		// rotate around start
		reverse(ans.begin(), ans.begin() + startInd);
		reverse(ans.begin() + startInd, ans.end());
		reverse(ans.begin(), ans.end());
		return ans;
	}
	
	inline int toGray(int n) {
		string num = bitset<16> (n).to_string();
		string gray;
		gray += num[0];
		for (int i = 1; i < 16; i++) {
			if (num[i] == num[i-1]) gray += '0';
			else gray += '1';
		}
		return stoi(gray, 0, 2);
	}
};






/*
simple way to generate Gray code is to xor with right shifted self
i.e. gray(n) = n ^ (n>>1)
*/
	vector<int> circularPermutation(int n, int start) {
		vector<int> ans;
		for (int i = 0; i < (1<<n); i++)
			ans.push_back(i ^ (i >> 1));
		
		int startInd = find(ans.begin(), ans.end(), start) - ans.begin();
		// rotate around start
		reverse(ans.begin(), ans.begin() + startInd);
		reverse(ans.begin() + startInd, ans.end());
		reverse(ans.begin(), ans.end());
		return ans;
	}



/*
gray(n) = n ^ (n>>1)

once you have all grayCode, you can apply XOR operator on given number.
Since grayCode only vary by one bit,
you will have your result that will also vary by one bit at a time.

we can do this on the fly as well
*/
	vector<int> circularPermutation(int n, int start) {
		vector<int> ans;
		for (int i = 0; i < (1<<n); i++)
			ans.push_back(start ^ i ^ (i >> 1));
		return ans;
	}