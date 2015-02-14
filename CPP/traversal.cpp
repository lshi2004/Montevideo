//============================================================================
// Name        : TS1.cpp
// Author      : TS1
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) { }
};

class Solution {
public:
	vector<vector<int>> levelOrder(TreeNode *root) {
		vector<vector<int>> result;

		if (root == nullptr)
			return result;

		queue<TreeNode*> current, next;
		vector<int> level;

		current.push(root);

		while (!current.empty()) {
			while (!current.empty()) {
				TreeNode *node = current.front();
				current.pop();
				level.push_back(node->val);
				if (node->left != nullptr) next.push(node->left);
				if (node->right != nullptr) next.push(node->right);
			}
			result.push_back(level);
			level.clear();
			swap(next, current);
		}


		return result;
	}


};


int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
