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
	ListNode* swapPairs(ListNode* head) {
		ListNode** it = &head;
		ListNode *curr, *next;
		while ((curr = (*it)) && (next = (*it)->next)) {
			curr->next = next->next;
			next->next = curr;
			*it = next;
			it = &curr->next;
		}
		return head;
	}
};

void test(const vector<int>& values)
{
	List list(values);
	cout << list << " => ";
	list.head = Solution().swapPairs(list);
	cout << list << endl;
}

int main()
{
	test({});
	test({1});
	test({1, 2});
	test({1, 2, 3});
	test({1, 2, 3, 4});
	test({1, 2, 3, 4, 5});
	return 0;
}
