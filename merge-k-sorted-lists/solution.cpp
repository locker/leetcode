#include <algorithm>
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
	ListNode* mergeKLists(vector<ListNode*>& lists) {
		auto cmp = [](ListNode* l1, ListNode* l2) {
			return l1->val > l2->val;
		};

		auto beg = lists.begin();
		auto end = lists.end();
		auto new_end = beg;

		// Remove empty lists;
		for (auto it = beg; it != end; ++it) {
			if (*it)
				*new_end++ = *it;
		}
		end = new_end;

		// Insert all non-empty lists into a heap sorted
		// by value. Then in a loop remove the list with
		// the smallest element from the heap and append
		// it to the output. If the list isn't empty, put
		// it back to the heap.
		make_heap(beg, end, cmp);

		ListNode* result = nullptr;
		ListNode** out = &result;
		while (beg < end) {
			pop_heap(beg, end, cmp);
			auto next = end - 1;
			*out = *next;
			out = &(*out)->next;
			*next = (*next)->next;
			if (*next)
				push_heap(beg, end, cmp);
			else
				--end;
		}
		return result;
	}
};

void test(const vector<vector<int>>& vectors)
{
	vector<ListNode*> lists;
	for (auto& v: vectors)
		lists.push_back(makeList(v));
	for (auto it = lists.begin(); it != lists.end(); ++it) {
		if (it != lists.begin())
			cout << " + ";
		cout << *it;
	}
	cout << " = ";
	auto result = Solution().mergeKLists(lists);
	cout << result << endl;
	deleteList(result);
}

int main()
{
	test({{}});
	test({{1, 2, 3}, {}});
	test({{7}, {1, 2, 3}, {}, {4, 5, 6}});
	test({{9}, {1, 5, 7}, {3}, {}, {2, 4}, {6, 8, 10}});
	return 0;
}
