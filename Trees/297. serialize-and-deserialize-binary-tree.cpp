// https://leetcode.com/problems/serialize-and-deserialize-binary-tree/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *	 int val;
 *	 TreeNode *left;
 *	 TreeNode *right;
 *	 TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */


// **************** MUCH CLEANER APPROACH (Like leetCode's) ***************
class Codec {
public:
	// Encodes a tree to a single string (in level order traversal)
	string serialize(TreeNode* root) {
		if (!root) return "[]";

		string output = "";
		queue<TreeNode*> q;
		q.push(root);
		while (!q.empty()) {
			TreeNode* curr = q.front(); q.pop();
			if (curr == NULL) {
				output += "N, ";
				continue;
			}
			output += to_string(curr->val) + ", ";
			q.push(curr->left);
			q.push(curr->right);
		}

		return "[" + output.substr(0, output.length()-2) + "]";
	}


	// Decodes your encoded data to tree.
	TreeNode* deserialize(string input) {
		trimLeftSpaces(input); // remove extra spaces in begin/end
		trimRightSpaces(input);
		input = input.substr(1, input.length()-2); // remove brackets
		if (input.length() == 0)
			return NULL;

		string item;
		stringstream ss;
		ss.str(input);

		getline(ss, item, ','); // get first item from ss separated by ',' and store in 'item'

		TreeNode* root = new TreeNode(stoi(item)); // create root from first item
		queue<TreeNode*> q;
		q.push(root);

		while (true) {
			TreeNode* curr = q.front(); q.pop();
			
			if (!getline(ss, item, ',')) break; // get left item

			trimLeftSpaces(item);
			if (item != "N") {
				curr->left = new TreeNode(stoi(item));
				q.push(curr->left);
			}

			if (!getline(ss, item, ',')) break; // get right item

			trimLeftSpaces(item);
			if (item != "N") {
				curr->right = new TreeNode(stoi(item));
				q.push(curr->right);
			}
		}

		return root;
	}

private:
	void trimLeftSpaces(string& input) {
		if (input.length() == 0) return;
		while (input.length() && isspace(input[0]))
			input.erase(input.begin());
	}

	void trimRightSpaces(string& input) {
		if (input.length() == 0) return;
		while (input.length() && isspace(input.back()))
			input.pop_back();
	}
};








// ********* very clean solution using streams **********
// ******** preorder *************

class Codec {
public:

	string serialize(TreeNode* root) {
		ostringstream out;
		serialize(root, out);
		return out.str();
	}

	TreeNode* deserialize(string data) {
		istringstream in(data);
		return deserialize(in);
	}

private:

	void serialize(TreeNode* root, ostringstream& out) {
		if (root) {
			out << root->val << ' ';
			serialize(root->left, out);
			serialize(root->right, out);
		} else {
			out << "# ";
		}
	}

	TreeNode* deserialize(istringstream& in) {
		string val;
		in >> val;
		if (val == "#")
			return nullptr;
		TreeNode* root = new TreeNode(stoi(val));
		root->left = deserialize(in);
		root->right = deserialize(in);
		return root;
	}
};












class Codec {
public:

	// Encodes a tree to a single string.
	string serialize(TreeNode* r) {
		string s;
		queue<TreeNode*> q;
		q.push(r);
		while (!q.empty()) {
			TreeNode* curr = q.front(); q.pop();
			if (curr == NULL) {
				s += "N";
				continue;
			}
			s += "."+to_string(curr->val)+".";
			q.push(curr->left);
			q.push(curr->right);
		}
		return s;
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(string s) {
		if (s[0] == 'N') return NULL; // tree is empty if first node is N

		queue<TreeNode*> q;
		// get root node value, create a node, and set it as root
		// remember, numbers are encoded as wrapped by '.' (ex- ".20.")
		int i=0, j=i+1;
		while (s[j]!='.') j++; // j is the index of right wrapping '.'
		TreeNode* root = new TreeNode(stoi(s.substr(i+1, j-i-1)));
		q.push(root);
		i=j+1; // advance i after the right wrapping '.'

		while (!q.empty() && i<s.length()) {
			TreeNode* curr = q.front(); q.pop();
			if (curr==NULL) continue;
			// get left child from string
			if (s[i]=='.') { // some number ahead. get it, create a node, and set the cur->left
				j=i+1; while (s[j]!='.') j++;
				curr->left = new TreeNode(stoi(s.substr(i+1, j-i-1)));
				i = j+1;
			} else { // it is 'N', a null node. so do nothing
				i++;
			}
			// break condition
			if (i >= s.length()) break;
			// get right child from string
			if (s[i]=='.') { // some number ahead. get it, create a node, and set the cur->right
				j=i+1; while (s[j]!='.') j++;
				curr->right = new TreeNode(stoi(s.substr(i+1, j-i-1)));
				i = j+1;
			} else { // it is 'N', a null node. so do nothing
				i++;
			}
			// push left/right nodes to queue
			if (curr->left) q.push(curr->left);
			if (curr->right) q.push(curr->right);
		}

		return root;
	}
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));