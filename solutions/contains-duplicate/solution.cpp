#include <iostream>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

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

class Solution {
public:
	bool containsDuplicate(const vector<int>& nums) {
		unordered_set<int> seen;
		for (int x : nums) {
			if (seen.count(x) > 0)
				return true;
			seen.insert(x);
		}
		return false;
	}
};

int main()
{
	const pair<vector<int>, bool> test_data[] = {
		{{}, false},
		{{1}, false},
		{{1, 1}, true},
		{{1, 1, 1}, true},
		{{1, 2, 3}, false},
		{{1, 2, 3, 1}, true},
		{{1, 2, 3, 4}, false},
		{{1, 1, 1, 3, 3, 4, 3, 2, 4, 2}, true},
	};
	bool success = true;
	Solution solution;
	for (const auto& [nums, expected] : test_data) {
		bool result = solution.containsDuplicate(nums);
		cout << nums << " => " << (result ? "true" : "false") << endl;
		if (result != expected) {
			cout << "  ERROR: expected " <<
				(expected ? "true" : "false") << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
