#include <algorithm>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

namespace {

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v)
{
	out << '[';
	bool first = true;
	for (const auto& x : v) {
		if (!first)
			out << ',';
		out << x;
		first = false;
	}
	out << ']';
	return out;
}

class Trie {
private:
	static constexpr int max_bit = 31;

	struct TrieNode {
		TrieNode* children[2];
		TrieNode() : children{nullptr, nullptr} {}
	};

	TrieNode* root;
public:
	Trie() : root(nullptr) {}

	~Trie() {
		queue<TrieNode*> todo;
		todo.push(root);
		while (!todo.empty()) {
			TrieNode* node = todo.front();
			todo.pop();
			if (node) {
				todo.push(node->children[0]);
				todo.push(node->children[1]);
				delete node;
			}
		}
	}

	void insert(int num) {
		if (!root)
			root = new TrieNode();
		TrieNode *node = root;
		for (int i = max_bit; i >= 0; --i) {
			int bit = (num >> i) & 1;
			TrieNode** pnext = &node->children[bit];
			if (!*pnext)
				*pnext = new TrieNode();
			node = *pnext;
		}
	}

	int findMaximumXOR(int num) {
		if (!root)
			return 0;
		int result = 0;
		TrieNode *node = root;
		for (int i = max_bit; i >= 0; --i) {
			int bit = 1 - ((num >> i) & 1);
			TrieNode *next = node->children[bit];
			if (!next) {
				next = node->children[1 - bit];
			} else {
				result += 1 << i;
			}
			node = next;
		}
		return result;
	}
};

class Solution {
public:
	int findMaximumXOR(const vector<int>& nums) {
		Trie t;
		int result = 0;
		for (int num : nums) {
			result = max(result, t.findMaximumXOR(num));
			t.insert(num);
		}
		return result;
	}
};

} // namespace

int main()
{
	const tuple<vector<int>, int> test_data[] = {
		{{3,10,5,25,2,8}, 28},
		{{14,70,53,83,49,91,36,80,92,51,66,70}, 127},
	};
	bool success = true;
	Solution solution;
	for (const auto& [nums, expected] : test_data) {
		int result = solution.findMaximumXOR(nums);
		cout << nums << " -> " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
