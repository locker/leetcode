#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(nullptr) {}
};

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

ostream& operator<<(ostream& out, const ListNode* head)
{
	out << '[';
	for (auto node = head; node; node = node->next) {
		if (node != head)
			out << ',';
		out << node->val;
	}
	out << ']';
	return out;
}

ListNode* makeList(const vector<int>& nums)
{
	ListNode* head = nullptr;
	for (auto it = nums.rbegin(); it != nums.rend(); ++it) {
		auto node = new ListNode(*it);
		node->next = head;
		head = node;
	}
	return head;
}

void deleteList(ListNode* head)
{
	while (head) {
		auto node = head->next;
		delete head;
		head = node;
	}
}

ostream& operator<<(ostream& out, const TreeNode* root)
{
	out << '[';
	queue<const TreeNode*> todo;
	todo.push(root);
	int null_count = 0;
	while (!todo.empty()) {
		auto node = todo.front();
		todo.pop();
		if (node) {
			todo.push(node->left);
			todo.push(node->right);
			if (node != root)
				out << ',';
			while (null_count > 0) {
				out << "null,";
				--null_count;
			}
			out << node->val;
		} else {
			++null_count;
		}
	}
	out << ']';
	return out;
}

void deleteTree(TreeNode* root)
{
	if (root) {
		deleteTree(root->left);
		deleteTree(root->right);
		delete root;
	}
}

class Solution {
	// Given the head and the length of a sorted list, turn the list
	// into a binary search tree and advance the head pointer to the
	// node following the last processed one.
	TreeNode* doSortListToBST(ListNode** head, int len) {
		if (len == 0)
			return nullptr;

		int left_len = len / 2;
		int right_len = len / 2;
		if (len % 2 == 0)
			--right_len;

		auto left = doSortListToBST(head, left_len);
		auto root = new TreeNode((*head)->val);
		*head = (*head)->next;
		auto right = doSortListToBST(head, right_len);

		root->left = left;
		root->right = right;
		return root;
	}
public:
	TreeNode* sortedListToBST(ListNode* head) {
		int len = 0;
		for (auto node = head; node; node = node->next)
			++len;
		return doSortListToBST(&head, len);
	}
};

int main()
{
	vector<int> input[] = {
		{},
		{1},
		{-4, 4},
		{-1, 0, 10},
		{-2, -1, 3, 5},
		{-10, -3, 0, 5, 9},
	};
	Solution solution;
	for (const auto& nums: input) {
		auto list = makeList(nums);
		auto tree = solution.sortedListToBST(list);
		cout << list << " => " << tree << endl;
		deleteList(list);
		deleteTree(tree);
	}
	return 0;
}
