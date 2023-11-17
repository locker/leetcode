#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

namespace {

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v)
{
	out << "[";
	bool first = true;
	for (const auto& x : v) {
		if (!first)
			out << ',';
		first = false;
		out << x;
	}
	out << "]";
	return out;
}

class Solution {
public:
	vector<int> largestDivisibleSubset(vector<int> nums) {
		sort(nums.begin(), nums.end());
		const int size = nums.size();
		vector<pair<int, int>> dp(size);
		pair<int, int> start(-1, 0);
		for (int i = size - 1; i >= 0; --i) {
			dp[i] = make_pair(-1, 0);
			for (int j = i + 1; j < size; ++j) {
				if (nums[j] % nums[i] == 0 &&
				    dp[j].second > dp[i].second)
					dp[i] = make_pair(j, dp[j].second);
			}
			++dp[i].second;
			if (dp[i].second > start.second)
				start = make_pair(i, dp[i].second);
		}
		vector<int> result;
		result.reserve(start.second);
		for (int i = start.first; i != -1; i = dp[i].first)
			result.push_back(nums[i]);
		return result;
	}
};

bool check(const vector<int>& nums)
{
	for (auto i = nums.begin(); i != nums.end(); ++i) {
		for (auto j = i + 1; j != nums.end(); ++j) {
			if (*i % *j != 0 && *j % *i != 0)
				return false;
		}
	}
	return true;
}

} // namespace

int main()
{
	const pair<vector<int>, size_t> test_data[] = {
		{{1}, 1},
		{{2, 3}, 1},
		{{2, 8}, 2},
		{{3, 1, 2}, 2},
		{{2, 4, 8}, 3},
		{{1, 2, 4, 8}, 4},
	};
	bool success = true;
	Solution solution;
	for (const auto& [nums, expected_subset_size] : test_data) {
		auto subset = solution.largestDivisibleSubset(nums);
		cout << nums << " -> " << subset << endl;
		if (!check(subset)) {
			cout << "  ERROR: subset not divisible" << endl;
			success = false;
		}
		if (subset.size() != expected_subset_size) {
			cout << "  ERROR: wrong subset size, expected " <<
				subset.size() << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
