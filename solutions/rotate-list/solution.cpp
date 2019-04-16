#include <iostream>
#include <utility>
#include <vector>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(nullptr) {}
};

static ListNode* newList(const vector<int>& values)
{
	ListNode* head = nullptr;
	for (auto it = values.rbegin(); it != values.rend(); ++it) {
		auto node = new ListNode(*it);
		node->next = head;
		head = node;
	}
	return head;
}

static void deleteList(ListNode* head)
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
	while (head) {
		out << head->val;
		head = head->next;
		if (head)
			out << ',';
	}
	out << ']';
	return out;
}

class Solution {
public:
	ListNode* rotateRight(ListNode* head, int k) {
		//
		// Let the input be [1, 2, 3, 4, 5, 6, 7], k = 2.
		// First, reverse first n-k entries: [5, 4, 3, 2, 1, 6, 7].
		// Second, reverse last k entries: [5, 4, 3, 2, 1, 7, 6].
		// Finally, reverse the whole list: [6, 7, 1, 2, 3, 4, 5].
		// Done.
		//
		int n = 0;
		for (auto it = head; it; it = it->next)
			++n;
		if (n == 0)
			return head;
		k %= n;
		if (k == 0)
			return head;
		auto curr = head;
		ListNode* prev = nullptr;
		for (int i = 0; i < n - k; ++i) {
			auto next = curr->next;
			curr->next = prev;
			prev = curr;
			curr = next;
		}
		auto pivot = head;
		head = prev;
		prev = nullptr;
		while (curr) {
			auto next = curr->next;
			curr->next = prev;
			prev = curr;
			curr = next;
		}
		pivot->next = prev;
		curr = head;
		prev = nullptr;
		while (curr) {
			auto next = curr->next;
			curr->next = prev;
			prev = curr;
			curr = next;
		}
		head = prev;
		return head;
	}
};

void test(const vector<int>& values, int k)
{
	ListNode* head = newList(values);
	Solution solution;
	cout << head << " >> " << k << " = ";
	head = solution.rotateRight(head, k);
	cout << head << endl;
	deleteList(head);
}

int main()
{
	pair<vector<int>, int> input[] = {
		{{}, 0},
		{{1}, 0},
		{{1}, 1},
		{{1,2}, 0},
		{{1,2}, 1},
		{{1,2}, 2},
		{{1,2,3}, 0},
		{{1,2,3}, 1},
		{{1,2,3}, 2},
		{{1,2,3}, 3},
		{{1,2,3,4}, 0},
		{{1,2,3,4}, 1},
		{{1,2,3,4}, 2},
		{{1,2,3,4}, 3},
		{{1,2,3,4}, 4},
		{{1,2,3,4,5}, 0},
		{{1,2,3,4,5}, 1},
		{{1,2,3,4,5}, 2},
		{{1,2,3,4,5}, 3},
		{{1,2,3,4,5}, 4},
		{{1,2,3,4,5}, 5},
	};
	for (const auto& p: input)
		test(p.first, p.second);
	return 0;
}
