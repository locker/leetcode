#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(nullptr) {}
};

struct List {
	ListNode* head;
	List(const vector<int>& values) : head(nullptr) {
		for (auto it = values.rbegin(); it != values.rend(); ++it) {
			auto node = new ListNode(*it);
			node->next = head;
			head = node;
		}
	}
	~List() {
		while (head) {
			auto node = head;
			head = node->next;
			delete node;
		}
	}
	operator ListNode*() { return head; }
};

ostream& operator<<(ostream& out, ListNode* head)
{
	out << '(';
	for (auto node = head; node; node = node->next) {
		if (node != head)
			out << ", ";
		out << node->val;
	}
	out << ')';
	return out;
}

class Solution {
public:
	ListNode* reverseKGroup(ListNode* head, int k) {
		if (k <= 1)
			return head;
		auto it = &head;
		while (*it) {
			// Find the next K nodes:
			// [start, stop] inclusive.
			auto start = *it;
			auto stop = start;
			for (int i = 0; i < k - 1; ++i) {
				stop = stop->next;
				if (!stop)
					return head;
			}
			// Reverse the K nodes.
			auto prev = start;
			auto curr = start->next;
			start->next = stop->next;
			do {
				auto next = curr->next;
				curr->next = prev;
				prev = curr;
				curr = next;
			} while (prev != stop);
			*it = stop;
			// Move on to the next node.
			it = &start->next;
		}
		return head;
	}
};

void test(const vector<int>& values, int k)
{
	List list(values);
	cout << list << " => ";
	list.head = Solution().reverseKGroup(list, k);
	cout << list << endl;
}

int main()
{
	test({}, 4);
	test({1, 2, 3, 4, 5}, 1);
	test({1, 2, 3, 4, 5}, 2);
	test({1, 2, 3, 4, 5}, 3);
	test({1, 2, 3, 4, 5}, 4);
	test({1, 2, 3, 4, 5}, 5);
	test({1, 2, 3, 4, 5}, 6);
	return 0;
}
