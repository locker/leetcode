#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

namespace {

struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct List {
	ListNode *head;
	List(const vector<int> values) : head(nullptr) {
		for (auto it = values.rbegin(); it != values.rend(); ++it)
			head = new ListNode(*it, head);
	}
	~List() {
		while (head) {
			ListNode *node = head;
			head = node->next;
			delete node;
		}
	}
};

class Solution {
private:
	vector<int> values;
public:
	Solution(ListNode* head) {
		while (head) {
			values.push_back(head->val);
			head = head->next;
		}
	}

	int getRandom() {
		return values[rand() % values.size()];
	}
};

} // namespace

int main()
{
	List list({1, 2, 3, 4, 5, 6, 7, 8, 9});
	Solution solution(list.head);
	for (int i = 0; i < 40; ++i)
		cout << solution.getRandom() << ' ';
	cout << endl;
	return 0;
}
