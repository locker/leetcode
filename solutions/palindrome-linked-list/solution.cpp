#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
	int val;
	ListNode* next;
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
	bool isPalindrome(ListNode* head) {
		if (!head || !head->next)
			return true;

		// Find the middle of the list.
		// Reverse the first half along the way.
		auto it1 = head;
		auto it2 = head;
		ListNode* prev = nullptr;
		while (it2 && it2->next) {
			auto curr = it1;
			it1 = it1->next;
			it2 = it2->next->next;
			curr->next = prev;
			prev = curr;
		}

		bool is_odd = !!it2; // is the number of entries odd?
		auto head1 = prev; // head of the first half (reversed)
		auto head2 = it1; // head of the second half

		// Walk over the two lists and check if their nodes match.
		it1 = head1;
		it2 = head2;
		if (is_odd)
			it2 = it2->next;
		while (it1 && it1->val == it2->val) {
			it1 = it1->next;
			it2 = it2->next;
		}
		bool is_palindrome = !it1;

		// Restore the original list.
		it1 = head1;
		prev = head2;
		while (it1) {
			auto next = it1->next;
			it1->next = prev;
			prev = it1;
			it1 = next;
		}
		return is_palindrome;
	}
};

int main()
{
	vector<int> input[] = {
		{}, // true
		{1}, // true
		{1, 1}, // true
		{1, 2}, // false
		{1, 2, 3}, // false
		{1, 2, 1}, // true
		{1, 2, 2, 1}, // true
		{1, 2, 3, 2, 1}, // true
		{1, 3, 3, 2, 1}, // false
		{2, 3, 4, 5, 3, 3}, // false
	};
	Solution solution;
	for (const auto& values: input) {
		auto head = newList(values);
		cout << head << " is ";
		if (!solution.isPalindrome(head))
			cout << "not ";
		cout << "a palindrome" << endl;
		deleteList(head);
	}
	return 0;
}
