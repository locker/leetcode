#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* newList(const vector<int>& values)
{
	ListNode* head = nullptr;
	for (auto it = values.rbegin(); it != values.rend(); ++it) {
		auto node = new ListNode(*it);
		node->next = head;
		head = node;
	}
	return head;
}

void deleteList(ListNode* head)
{
	while (head) {
		auto next = head->next;
		delete head;
		head = next;
	}
}

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

class Solution {
public:
	ListNode* deleteDuplicates(ListNode* head) {
		if (!head)
			return head;
		auto prev = head;
		auto node = prev->next;
		while (node) {
			if (node->val == prev->val) {
				prev->next = node->next;
				delete node;
			} else {
				prev = node;
			}
			node = prev->next;
		}
		return head;
	}
};

void test(const vector<int> values)
{
	Solution solution;
	ListNode *head = newList(values);
	cout << "Input: " << head << endl;
	head = solution.deleteDuplicates(head);
	cout << "Output: " << head << endl;
	deleteList(head);
}

int main()
{
	vector<int> input[] = {
		{},
		{1},
		{1, 1},
		{1, 2, 3},
		{1, 2, 2, 3},
		{1, 1, 2, 3, 3},
		{1, 1, 2, 2, 3, 3},
	};
	for (const auto& values: input)
		test(values);
	return 0;
}
