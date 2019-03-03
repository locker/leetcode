#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* makeList(const vector<int>& values)
{
	ListNode* list = nullptr;
	for (auto it = values.rbegin(); it != values.rend(); ++it) {
		auto node = new ListNode(*it);
		node->next = list;
		list = node;
	}
	return list;
}

void deleteList(ListNode* list)
{
	while (list) {
		auto node = list->next;
		delete list;
		list = node;
	}
}

ostream& operator<< (ostream& out, ListNode* l)
{
	out << "(";
	auto node = l;
	while (node) {
		if (node != l)
			out << " -> ";
		out << node->val;
		node = node->next;
	}
	out << ")";
	return out;
}

class Solution {
public:
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		ListNode* result = nullptr;
		ListNode** out = &result;
		while (l1 || l2) {
			ListNode** next;
			if (l1 && l2)
				next = l1->val < l2->val ? &l1 : &l2;
			else
				next = l1 ? &l1 : &l2;
			*out = *next;
			out = &(*out)->next;
			*next = (*next)->next;
		}
		return result;
	}
};

void test(const vector<int>& v1, const vector<int>& v2)
{
	auto l1 = makeList(v1);
	auto l2 = makeList(v2);
	cout << l1 << " + " << l2 << " = ";
	auto result = Solution().mergeTwoLists(l1, l2);
	cout << result << endl;
	deleteList(result);
}

int main()
{
	test({}, {});
	test({1, 2, 3}, {});
	test({}, {4, 5, 6});
	test({1, 3, 5, 7}, {2, 4, 6, 8});
	test({1, 3, 5, 7, 8}, {2, 4, 6});
	test({1, 3, 5}, {2, 4, 6, 7, 8, 9});
	return 0;
}
