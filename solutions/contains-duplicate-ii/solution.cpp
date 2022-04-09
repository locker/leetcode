#include <iostream>
#include <tuple>
#include <unordered_map>
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
	bool containsNearbyDuplicate(const vector<int>& nums, int k) {
		unordered_map<int, int> seen; // value -> max idx
		for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
			auto it = seen.find(nums[i]);
			if (it == seen.end()) {
				seen.emplace(nums[i], i);
				continue;
			}
			if (i - it->second <= k)
				return true;
			it->second = i;
		}
		return false;
	}
};

int main()
{
	const tuple<vector<int>, int, bool> test_data[] = {
		{{1, 2, 3, 1}, 3, true},
		{{1, 2, 3, 1}, 2, false},
		{{1, 0, 1, 1}, 3, true},
		{{1, 0, 1, 1}, 1, true},
		{{1, 0, 1, 1}, 0, false},
		{{1, 2, 3, 1, 2, 3}, 3, true},
		{{1, 2, 3, 1, 2, 3}, 2, false},
	};
	bool success = true;
	Solution solution;
	for (const auto& [nums, k, expected] : test_data) {
		bool result = solution.containsNearbyDuplicate(nums, k);
		cout << "nums=" << nums << ", k=" << k << " => " <<
			(result ? "true" : "false") << endl;
		if (result != expected) {
			cout << "  ERROR: expected " <<
				(expected ? "true" : "false") << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
