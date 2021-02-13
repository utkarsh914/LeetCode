// https://leetcode.com/problems/unique-email-addresses/

class Solution {
public:
	int numUniqueEmails(vector<string>& emails) {
		unordered_set<string> set;

		for (auto& s:emails) {
			string email; email.reserve(s.size());
			bool ignore=false, domain=false;

			for (char c:s) {
				if (c=='@') {
					ignore=false, domain=true;
				}	else if (c == '+') {
					ignore = true;
				}
				
				if (domain) {
					email.push_back(c);
				} else if (!ignore && c!='.') {
					email.push_back(c);
				}
			}
			
			set.insert(email);
		}

		return set.size();
	}
};