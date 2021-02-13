/*
https://leetcode.com/problems/smallest-string-with-swaps/
*/
class Solution {
public:

vector<int> parent;

int find(int x) {
	if (parent[x] != x)
		parent[x] = find(parent[x]);
	return parent[x];
}

void uni(int x, int y) {
	x = find(x);
	y = find(y);
	if (x != y) {
		parent[y] = x;
	}
}
string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
	// fill parent array (for union find) and create unions
	for (int i=0; i<s.length(); i++) parent.push_back(i);
	for (auto& p:pairs)
		uni(p[0], p[1]);
	unordered_map<int, multiset<char>> groups;
	vector<int> freq(s.length(), 0);
	for (int i=0; i<s.length(); i++) {
		int p = find(i);
		groups[p].insert(s[i]);
	}
	for (int i=0; i<s.length(); i++) {
		int p = find(i);
		s[i] = *groups[p].begin();
		groups[p].erase(groups[p].begin());
	}
	return s;
}};





//********** fastest solution till now for this problem ***********
// *********************** (224 ms) *******************************

static auto _______ = [](){
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	return 0;
}();

class Solution {
public:
int *parent, *rank;

int find(int x) {
	if (parent[x] != x)
		parent[x] = find(parent[x]);
	return parent[x];
}

void uni(int x, int y) {
	x = find(x);
	y = find(y);
	if (rank[x]<rank[y])
		parent[x]=y;
	else if (rank[x]>rank[y])
		parent[y]=x;
	else {
		parent[y] = x;
		rank[x]++;
	}
}
string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
	// fill parent array (for union find) and create unions
	parent = new int[s.length()];
	rank = new int[s.length()]();
	for (int i=0; i<s.length(); i++) parent[i] = i;
	for (auto& p:pairs)	uni(p[0], p[1]);
	
	vector<string> groups(s.length());
	
	for (int i=0; i<s.length(); i++)
		groups[find(i)].push_back(s[i]);
	
	for (auto& v:groups)
		 sort(v.begin(), v.end(), greater<char>());

	for (int i=0; i<s.length(); i++) {
		int p = find(i);
		s[i] = groups[p].back();
		groups[p].pop_back();
	}

	return s;
}};