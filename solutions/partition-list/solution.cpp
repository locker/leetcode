#include <iostream>
#include <utility>
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
	ListNode* partition(ListNode* head, int x) {
		// Find the link to the first node that stores
		// a value greater than or equal to x.
		ListNode** pivot;
		for (pivot = &head; *pivot; pivot = &(*pivot)->next) {
			if ((*pivot)->val >= x)
				break;
		}
		ListNode* it = *pivot;
		if (!it) {
			// All nodes store values greater than
			// or equal to x. Nothing to do.
			return head;
		}
		// Iterate over following nodes. Upon running into
		// a node that stores a value less than x, move it
		// before *pivot.
		while (it->next) {
			ListNode* next = it->next;
			if (next->val >= x) {
				it = next;
				continue;
			}
			it->next = next->next;
			next->next = *pivot;
			*pivot = next;
			pivot = &next->next;
		}
		return head;
	}
};

void test(const vector<int> values, int x)
{
	Solution solution;
	ListNode *head = newList(values);
	cout << "Input: head = " << head << ", x = " << x << endl;
	head = solution.partition(head, x);
	cout << "Output: " << head << endl;
	deleteList(head);
}

int main()
{
	pair<vector<int>, int> input[] = {
		{{}, 1},
		{{1}, 1},
		{{1}, 2},
		{{2}, 1},
		{{1, 2, 3}, 2},
		{{3, 2, 1}, 2},
		{{3, 2, 1}, 1},
		{{1, 4, 3, 2, 5, 2}, 3},
		{{4, 4, 4, 3, 2, 1, 5, 6, 3, 4}, 4},
	};
	for (const auto& p: input)
		test(p.first, p.second);
	return 0;
}
