#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(nullptr) {}
};

ostream& operator<<(ostream& out, const ListNode* head)
{
	out << '[';
	for (auto it = head; it; it = it->next) {
		if (it != head)
			out << ',';
		out << it->val;
	}
	out << ']';
	return out;
}

class Solution {
public:
	ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
		int lenA = 0;
		for (auto it = headA; it; it = it->next)
			++lenA;

		int lenB = 0;
		for (auto it = headB; it; it = it->next)
			++lenB;

		auto itA = headA;
		auto itB = headB;
		if (lenA > lenB) {
			for (int i = 0; i < lenA - lenB; ++i)
				itA = itA->next;
		} else {
			for (int i = 0; i < lenB - lenA; ++i)
				itB = itB->next;
		}

		while (itA != itB) {
			itA = itA->next;
			itB = itB->next;
		}
		return itA;
	}
};

void test(ListNode* headA, ListNode* headB)
{
	cout << headA << ", " << headB << " => " <<
		Solution().getIntersectionNode(headA, headB) << endl;
}

int main()
{
	vector<ListNode> nodes;
	for (int i = 0; i < 8; ++i)
		nodes.emplace_back(i);

	nodes[0].next = &nodes[1];
	nodes[1].next = nullptr;
	nodes[2].next = &nodes[3];
	nodes[3].next = &nodes[4];
	nodes[4].next = nullptr;
	test(&nodes[0], &nodes[2]);
	test(&nodes[0], nullptr);
	test(nullptr, &nodes[2]);

	nodes[1].next = nodes[4].next = &nodes[5];
	nodes[5].next = &nodes[6];
	nodes[6].next = &nodes[7];
	test(&nodes[0], &nodes[2]);
	test(&nodes[0], &nodes[5]);
	test(&nodes[5], &nodes[3]);

	return 0;
}
