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
	bool hasCycle(ListNode *head) {
		auto it1 = head;
		auto it2 = head;
		while (it2 && it2->next) {
			it1 = it1->next;
			it2 = it2->next->next;
			if (it1 == it2)
				return true;
		}
		return false;
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
		cout << "count = " << count << ", pos = " << pos << " => " <<
			(solution.hasCycle(head) ? "true" : "false") << endl;
		uncycleList(head, pos);
		deleteList(head);
	}
	return 0;
}
