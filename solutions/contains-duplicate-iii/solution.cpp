#include <iostream>
#include <set>
#include <tuple>
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
	bool containsNearbyAlmostDuplicate(const vector<int>& nums,
					   int k, int t) {
		multiset<int> nearby;
		int s = 0;
		for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
			auto it = nearby.lower_bound(nums[i]);
			if (it != nearby.end() &&
			    static_cast<long long>(*it) - nums[i] <= t)
				return true;
			if (it != nearby.begin() &&
			    nums[i] - static_cast<long long>(*--it) <= t)
				return true;
			nearby.insert(nums[i]);
			if (i - s >= k) {
				nearby.erase(nearby.find(nums[s]));
				++s;
			}
		}
		return false;
	}
};

int main()
{
	const tuple<vector<int>, int, int, bool> test_data[] = {
		{{1, 2, 3, 1}, 3, 0, true},
		{{1, 2, 3, 1}, 2, 0, false},
		{{1, 2, 3, 1}, 2, 1, true},
		{{1, 2, 3, 1}, 1, 0, false},
		{{1, 0, 1, 1}, 1, 2, true},
		{{1, 5, 9, 1, 5, 9}, 2, 3, false},
		{{1, 5, 9, 1, 5, 9}, 2, 4, true},
	};
	bool success = true;
	Solution solution;
	for (const auto& [nums, k, t, expected] : test_data) {
		bool result = solution.containsNearbyAlmostDuplicate(nums, k, t);
		cout << "nums=" << nums << ", k=" << k << ", t=" << t << " => " <<
			(result ? "true" : "false") << endl;
		if (result != expected) {
			cout << "  ERROR: expected " <<
				(expected ? "true" : "false") << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
