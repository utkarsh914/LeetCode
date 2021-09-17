// https://leetcode.com/problems/maximum-product-subarray/







int maxProduct(vector<int>& nums) {
	int mn = nums[0], mx = nums[0], ans = nums[0];
	
	for (int i = 1; i < nums.size(); i++) {
		int n = nums[i];
		int new_mn = min({n * mn, n * mx, n});
		int new_mx = max({n * mn, n * mx, n});
		mn = new_mn, mx = new_mx;
		ans = max(ans, mx);
	}
	
	return ans;
}





class Solution {
public:
	int maxProduct(vector<int>& n) {
		// store the result that is the max we have found so far
		// maxP/minP stores the max/min product of
		// subarray that ends with the current number n[i]
		int ans = n[0], maxP = n[0], minP = n[0];
		
		for (int i=1; i < n.size(); i++) {
			// multiplied by a negative makes big number smaller, small number bigger
			// so we redefine the extremums by swapping them
			if (n[i] < 0) swap(maxP, minP);
			// max/min product for the current number is either the current number itself
			// or the max/min by the previous number times the current one
			maxP = max(n[i], maxP*n[i]);
			minP = min(n[i], minP*n[i]);
			// the newly computed max value is a candidate for our global result
			ans = max(ans, maxP);
		}
		
		return ans;
	}
};






/*
There are 2 possibilities - either the number of -ve numbers is even or odd.

If they are even, then obviously we would want to include all of them(in fact the whole array(unless for zeros)) to maximise the product. This is because multiplying an even number of -ve numbers would make the result +ve.

If they are odd, then we would want to exclude at most(to maximise the product) one -ve number from our product. So, now the question is, which -ve number to exclude? There are 2 possibilities - first -ve num or last -ve num.
a. Note that, you cannot exclude a -ve number that is not the first or the last, because, if you do so, you will need to exclude all(because you are breaking the product at this point) other -ve nums following that -ve number and then that needn't result in the maximum product.
b. Remember, that our goal is to leave out only 1 -ve number so that we can maximise our product.
c. Note: We are leaving out one -ve number, so that we are able to make the number of -ve nums even. Having said all that, now the question is whether to exclude the first -ve num or the last -ve num in the array. We can only know the answer by trying both.
d. By taking the product from the beginning of the array, you forcefully include the first -ve number and exclude the last -ve number
e. vice-versa for taking the product from the end

To further explain 2d,e, let me take an example:

Assume the array has an odd number of -ve nums. The first -ve num is -2 and the last -ve num is -3. So the array is .....-2.......-3.......
The maximum product can either be made of all numbers from the beginning of the array to the first non-zero number just before -3, or from the end of the array to the first non-zero number just after -2.

This is why we are considering two possible products, one from the beginning and one from the end.

But wait, you might be thinking, why we are still continuing to multiply even beyond -3(forward iteration) or beyond -2 (backward iteration). That's all actually waste, as the product is only going to increase in negativity beyond those points. The maximum is already updated, so this doesn't affect at all.

Hope you find this useful!
*/
class Solution {
public:
	int maxProduct(vector<int>& nums) {
		int mul = 1, ans = INT_MIN;
		// from left to right (take leftmost -ve
		// [in case there are odd -ves], and leaves last -ve)
		for (int n : nums) {
			mul *= n;
			ans = max(ans, mul);
			if (mul == 0) mul = 1;
		}
		// from right to left (take righmost -ve
		// [in case there are odd -ves], and leaves first -ve)
		mul = 1;
		for (auto it = nums.rbegin(); it != nums.rend(); it++) {
			mul *= (*it);
			ans = max(ans, mul);
			if (mul == 0) mul = 1;
		}

		return ans;
	}
};
