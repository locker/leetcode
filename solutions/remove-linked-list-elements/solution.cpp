#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

namespace {

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v)
{
	out << '[';
	bool is_first = true;
	for (const auto& x : v) {
		if (!is_first)
			out << ',';
		out << x;
		is_first = false;
	}
	out << ']';
	return out;
}

struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* newList(const vector<int>& values)
{
	ListNode* head = nullptr;
	ListNode* tail = nullptr;
	for (int val : values) {
		ListNode* node = new ListNode(val);
		if (tail) {
			tail->next = node;
		} else {
			head = node;
		}
		tail = node;
	}
	return head;
}

void deleteList(ListNode* head)
{
	while (head) {
		ListNode* next = head->next;
		delete head;
		head = next;
	}
}

vector<int> listValues(ListNode *head)
{
	vector<int> values;
	while (head) {
		values.push_back(head->val);
		head = head->next;
	}
	return values;
}

class Solution {
public:
	ListNode* removeElements(ListNode* head, int val) {
		ListNode** pnode = &head;
		while (*pnode) {
			ListNode* node = (*pnode);
			if (node->val == val) {
				*pnode = node->next;
				delete node;
			} else {
				pnode = &node->next;
			}
		}
		return head;
	}
};

} // namespace

int main()
{
	const tuple<vector<int>, int, vector<int>> test_data[] = {
		{{}, 1, {}},
		{{1}, 1, {}},
		{{1, 1}, 1, {}},
		{{1, 2}, 1, {2}},
		{{1, 2}, 2, {1}},
		{{2, 2, 2}, 2, {}},
		{{1, 2, 3}, 2, {1, 3}},
		{{1, 2, 3}, 2, {1, 3}},
		{{1, 2, 6, 3, 4, 5, 6}, 6, {1, 2, 3, 4, 5}},
	};
	bool success = true;
	Solution solution;
	for (const auto& [values, val, expected] : test_data) {
		auto head = solution.removeElements(newList(values), val);
		auto result = listValues(head);
		cout << values << " - " << val << " = " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
		deleteList(head);
	}
	return success ? 0 : 1;
}
