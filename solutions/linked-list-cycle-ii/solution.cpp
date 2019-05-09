#include <iostream>
#include <utility>

using namespace std;

struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* makeList(int count)
{
	ListNode* head = nullptr;
	for (int i = count; i > 0; --i) {
		auto node = new ListNode(i);
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

void cycleList(ListNode* head, int pos)
{
	if (pos < 0)
		return;
	ListNode* prev = nullptr;
	ListNode* cycle = nullptr;
	for (auto it = head; it; it = it->next) {
		if (pos-- == 0)
			cycle = it;
		prev = it;
	}
	if (cycle)
		prev->next = cycle;
}

void uncycleList(ListNode* head, int pos)
{
	if (pos < 0)
		return;
	ListNode* cycle = nullptr;
	for (auto it = head; it; it = it->next) {
		if (pos-- == 0)
			cycle = it;
		if (it->next == cycle) {
			it->next = nullptr;
			return;
		}
	}
}

class Solution {
public:
	ListNode *detectCycle(ListNode *head) {
		//
		// If we run two iterators over the list, one walking one list
		// node at a time, another two nodes, they will finally meet at
		// some node in the list provided the list has a cycle. Let's
		// find the meeting point.
		//
		// Suppose the cycle starts at position k in the list and has n
		// nodes. By the time the slow iterator steps on node k, the
		// fast iterator will have travelled k nodes of the cycle. To
		// reach the beginning of the cycle again, the fast iterator
		// will have to take (n-k)/2 steps (remember it jumps two nodes
		// at a time). When this happens, the slow iterator will be at
		// position (n-k)/2 in the cycle, i.e. (n-k)/2 nodes ahead of
		// the fast iterator. To catch up with the slow iterator, the
		// fast iterator will have to take another (n-k)/2 steps. That
		// is, the meeting point is at node k+(n-k)/2+(n-k)/2=n or
		// n-k nodes after the beginning of the cycle or equivalently
		// k noes before the beginning of the cycle.
		//
		// This means that if we start the third iterator travelling
		// one node at a time when the first two iterators meet, it
		// will run into the slow iterator exactly at the beginning of
		// the cycle.
		//
		auto it1 = head;
		auto it2 = head;
		while (it2 && it2->next) {
			it1 = it1->next;
			it2 = it2->next->next;
			if (it1 == it2) {
				auto it3 = head;
				while (it1 != it3) {
					it1 = it1->next;
					it3 = it3->next;
				}
				return it1;
			}
		}
		return nullptr;
	}
};

int main()
{
	pair<int, int> input[] = {
		{1, 0},
		{2, 0},
		{3, 1},
		{5, 2},
		{8, 7},
		{0, -1},
		{1, -1},
		{2, -1},
		{4, -1},
		{8, -1},
	};
	Solution solution;
	for (const auto& p: input) {
		int count = p.first;
		int pos = p.second;
		auto head = makeList(count);
		cycleList(head, pos);
		cout << "count = " << count << ", pos = " << pos << " => ";
		auto cycle = solution.detectCycle(head);
		cout << (cycle ? cycle->val : -1) << endl;
		uncycleList(head, pos);
		deleteList(head);
	}
	return 0;
}
