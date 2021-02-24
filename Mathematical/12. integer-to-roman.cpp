// https://leetcode.com/problems/integer-to-roman/

class Solution {
public:
	string intToRoman(int num) {
		vector<char> sym {'I', 'V', 'X', 'L', 'C', 'D', 'M', '#'};
		vector<int>  val {1, 5, 10, 50, 100, 500, 1000, INT_MAX};
		string roman;

		while (num > 0) {
			int i = 0;
			while (num / val[i] > 0) i++;

			int pv = isPower10(val[i]) ? i-2 : i-1;
			
			if (num >= val[i] - val[pv]) {
				roman.push_back(sym[pv]);
				roman.push_back(sym[i]);
				num %= (val[i] - val[pv]);
			}
			else {
				for (int k=0; k < (num/val[i-1]); k++)
					roman.push_back(sym[i-1]);
				num %= val[i-1];
			}
		}

		return roman;
	}

	bool isPower10(int n) {
		while (n >= 10 && n % 10 == 0)
			n /= 10;
		return n == 1;
	}
};







public static String intToRoman(int num){
	if (num < 1 || num > 3999) return "";
	
	StringBuilder result = new StringBuilder();
	
	String[] roman = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
	int[] values = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };
	
	int i = 0;
	//iterate until the number becomes zero, NO NEED to go until the last element in roman array
	while (num >0) {
		while ( num >= values[i]) {
			num -= values[i];
			result.append(roman[i]);
		}
		i++;
	}
	return result.toString();
}