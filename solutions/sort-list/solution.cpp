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
	ListNode* sortList(ListNode* head) {
		//
		// Implementation of the standard bottom-top merge sort
		// algorithm: divide the list into partitions of equal
		// size and merge them in pairs, then double the size of
		// a partition and repeat.
		//
		auto p = &head;
		int part_size = 1;
		while (true) {
			auto p1 = p;
			// Find the link pointing to the head of the second
			// partition in this pair.
			auto p2 = p;
			for (int i = 0; i < part_size; ++i) {
				if (!*p2)
					break;
				p2 = &(*p2)->next;
			}
			// Merge the two partitions until any of them is empty.
			int c1 = 0;
			int c2 = 0;
			while (*p1 && *p2 && c1 < part_size && c2 < part_size) {
				if ((*p1)->val <= (*p2)->val) {
					// The first node stores a value less
					// than or equal to the second node
					// value. Simply advance to the next
					// node in the first partition.
					p1 = &(*p1)->next;
					++c1;
				} else {
					// The value of the first node is
					// greater than the second node's.
					// Move the second node before the
					// first node and advance to the next
					// node in the second partition.
					auto node = *p2;
					*p2 = node->next;
					node->next = *p1;
					*p1 = node;
					p1 = &node->next;
					++c2;
				}
			}
			// Advance to the end of the second partition.
			while (*p2 && c2 < part_size) {
				p2 = &(*p2)->next;
				++c2;
			}
			if (!*p2) {
				// End of the list. If it's the first pair,
				// we're done. Otherwise, double the size
				// of a partition and repeat.
				if (p == &head)
					break;
				part_size *= 2;
				p = &head;
			} else {
				// Iterate to the next pair.
				p = p2;
			}
		}
		return head;
	}
};

void test(const vector<int>& values)
{
	ListNode* head = newList(values);
	cout << head << " => ";
	head = Solution().sortList(head);
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
