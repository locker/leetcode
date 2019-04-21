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
	ListNode* insertionSortList(ListNode* head) {
		auto p1 = &head;
		while (*p1) {
			auto p2 = &head;
			while (p2 != p1) {
				if ((*p2)->val > (*p1)->val) {
					auto node = *p1;
					*p1 = node->next;
					node->next = *p2;
					*p2 = node;
					break;
				}
				p2 = &(*p2)->next;
			}
			if (p2 == p1)
				p1 = &(*p1)->next;
		}
		return head;
	}
};

void test(const vector<int>& values)
{
	ListNode* head = newList(values);
	cout << head << " => ";
	head = Solution().insertionSortList(head);
	cout << head << endl;
	deleteList(head);
}

int main()
{
	vector<int> input[] = {
		{},
		{1},
		{1, 2},
		{2, 1, 3},
		{3, 4, 2, 1},
		{5, 4, 3, 2, 1},
		{1, 6, 2, 5, 3, 4},
		{7, 1, 6, 2, 5, 3, 4},
		{8, 6, 4, 2, 7, 5, 3, 1},
		{9, 6, 3, 1, 2, 4, 5, 8, 7},
	};
	for (const auto& values: input)
		test(values);
	return 0;
}
